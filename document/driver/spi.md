# SPI Driver

## Cấu trúc OOP/HAL

```c
SPI_Config_t    // Config struct - cấu hình SPI peripheral
SPI_Handle_t    // Handle struct - chứa base address + config
```

### SPI_Config_t

| Field            | Ý nghĩa                | Giá trị                                              |
|------------------|------------------------|------------------------------------------------------|
| SPI_DeviceMode   | Master/Slave           | `SPI_DEVICE_MODE_MASTER`, `SPI_DEVICE_MODE_SLAVE`    |
| SPI_BusConfig    | Kiểu bus               | `SPI_BUS_CONFIG_FD`, `HD`, `SIMPLEX_RXONLY`          |
| SPI_DFF          | Data frame format      | `SPI_DFF_8bits`, `SPI_DFF_16bits`                    |
| SPI_Frame_format | MSB/LSB first          | `MSB_TRANSMITTED_FIRST`, `LSB_TRANSMITTED_FIRST`     |
| SPI_CPOL         | Clock polarity         | `SPI_CPOL_LOW`, `SPI_CPOL_HIGH`                      |
| SPI_CPHA         | Clock phase            | `SPI_CPHA_LOW`, `SPI_CPHA_HIGH`                      |
| SPI_SSM          | Software slave mgmt    | `SPI_SSM_EN`, `SPI_SSM_DI`                           |
| speed            | Baud rate prescaler    | `SPI_SCLK_SPEED_DIV2` ... `SPI_SCLK_SPEED_DIV256`   |

### SPI_Handle_t

| Field     | Ý nghĩa                              |
|-----------|---------------------------------------|
| pSPIx     | Con trỏ tới SPI peripheral (SPI1, SPI2, SPI3) |
| SPIConfig | Struct config ở trên                  |
| CS_Port   | GPIO port của chân chip-select (NULL nếu dùng hardware NSS / app tự quản CS) |
| CS_Pin    | Số chân chip-select trên CS_Port (`GPIO_PIN_NO_x`) |
| pTxBuffer, pRxBuffer, TxLen, RxLen, TxState, RxState | Trạng thái nội bộ cho interrupt-mode — **không set thủ công** |

## Chip-select (CS) — vấn đề ODR reset

`GPIO_Init()` chỉ ghi MODER/OTYPER/OSPEEDR/PUPDR, **không đụng ODR**. Mà ODR
reset = 0, nên ngay khi một chân chuyển sang output nó đã ở mức **LOW**. Với
CS tích cực mức thấp, điều này nghĩa là **slave bị chọn (CS=LOW) ngay từ lúc
init**, trước cả transaction đầu tiên.

Hệ quả: lệnh `GPIO_Write_Pin(CS, 0)` trước lần đọc đầu trở thành no-op (CS đã
LOW từ trước) → **không có sườn xuống CS thật** → slave (LIS3DSH...) không đồng
bộ được frame → transaction đầu đọc ra giá trị rác (0xFF). Từ lần thứ 2 trở đi
mới có sườn xuống thật nên mới đúng.

**Cách xử lý trong driver:** điền `CS_Port`/`CS_Pin` vào handle. `SPI_Init()`
tự gọi `SPI_ChipSelect(handle, DISABLE)` để đưa CS lên HIGH (deselect) ngay sau
init. Mỗi transaction sau đó dùng `SPI_ChipSelect(handle, ENABLE/DISABLE)` để
tạo sườn xuống/lên đúng chuẩn.

```c
hspi1.CS_Port = GPIOE;
hspi1.CS_Pin  = GPIO_PIN_NO_3;   // LIS3DSH trên STM32F4-Discovery
SPI_Init(&hspi1);                // CS tự lên HIGH tại đây

SPI_ChipSelect(&hspi1, ENABLE);  // CS xuống LOW — bắt đầu frame
SPI_TransmitReceive(&hspi1, tx, rx, 2, 1000);
SPI_ChipSelect(&hspi1, DISABLE); // CS lên HIGH — kết thúc frame
```

Nếu `CS_Port == NULL`, driver bỏ qua toàn bộ phần CS (dùng hardware NSS hoặc app tự quản).

## Trình tự khởi tạo

```c
// 1. Cấu hình GPIO cho SPI pins (SCK, MOSI, MISO) + chân CS riêng
SPI_GpioConfig(SPI1);            // set AF cho SCK/MISO/MOSI
// CS là chân GPIO output thường (vd PE3), tự khai báo bằng GPIO_Init()

// 2. Khai báo và cấu hình handle
SPI_Handle_t hspi1;
hspi1.pSPIx = SPI1;
hspi1.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
hspi1.SPIConfig.SPI_BusConfig  = SPI_BUS_CONFIG_FD;
hspi1.SPIConfig.SPI_DFF        = SPI_DFF_8bits;
hspi1.SPIConfig.SPI_Frame_format = MSB_TRANSMITTED_FIRST;
hspi1.SPIConfig.SPI_SSM        = SPI_SSM_EN;
hspi1.SPIConfig.SPI_CPHA       = SPI_CPHA_HIGH;
hspi1.SPIConfig.SPI_CPOL       = SPI_CPOL_HIGH;
hspi1.SPIConfig.speed          = SPI_SCLK_SPEED_DIV128;
hspi1.CS_Port = GPIOE;            // chân CS do driver quản lý
hspi1.CS_Pin  = GPIO_PIN_NO_3;

// 3. Init — tự bật clock, ghi CR1, set SSI, bật SPE, và deselect CS.
//    Không cần gọi SPI_SSI_Config / SPI_PeripheralControl thủ công nữa.
SPI_Init(&hspi1);

// 4. Một transaction: kéo CS xuống, trao đổi data, nhả CS lên
SPI_ChipSelect(&hspi1, ENABLE);              // CS = LOW (chọn slave)
SPI_TransmitReceive(&hspi1, tx, rx, len, 1000);
SPI_ChipSelect(&hspi1, DISABLE);             // CS = HIGH (bỏ chọn)
```

## API

| Hàm                     | Mô tả                                                |
|--------------------------|------------------------------------------------------|
| `SPI_PeriClockControl`   | Bật/tắt clock (gọi tự động trong Init)               |
| `SPI_Init`               | Ghi toàn bộ config vào CR1                            |
| `SPI_DeInit`             | Reset SPI qua RCC                                     |
| `SPI_PeripheralControl`  | Set/clear SPE bit để bật/tắt SPI                      |
| `SPI_SSI_Config`         | Set/clear SSI bit (cần khi SSM=1)                     |
| `SPI_SSOE_Config`        | Set/clear SSOE bit (multi-master output enable)       |
| `SPI_ChipSelect`         | Kéo CS LOW (ENABLE) / HIGH (DISABLE) qua CS_Port/CS_Pin |
| `SPI_Transmit`           | Blocking send: chờ TXE, ghi DR, đọc bỏ echo, hỗ trợ 8/16-bit |
| `SPI_Receive`            | Blocking receive: gửi dummy để tạo clock, đọc DR      |
| `SPI_TransmitReceive`    | Blocking full-duplex; truyền/nhận đồng thời đúng `Size` byte |
| `SPI_GpioConfig`         | Helper cấu hình GPIO AF cho SPI1/2/3                  |
| `SPI_GetFlagStatus`      | Kiểm tra flag trong SR (TXE, RXNE, BSY)              |
| `SPI_Transmit_IT`        | Non-blocking send (interrupt-mode), gọi callback khi xong |
| `SPI_Receive_IT`         | Non-blocking receive (interrupt-mode), gọi callback khi xong |
| `SPI_IRQHandling`        | Xử lý ngắt, gọi từ `SPIx_IRQHandler` trong it.c      |
| `SPI_RegisterCallback`   | Đăng ký callback cho sự kiện TX/RX_CMPLT, OVR_ERR    |
| `MX_SPI_Init`            | `__weak` — init mặc định (SPI1 mode3, /128, CS=PE3); app override |

## Lưu ý quan trọng

- **SSM=1 bắt buộc SSI=1**: Nếu không, bit NSS bị kéo LOW → chip tưởng có master khác → MODF fault → SPI tự disable.
- **Phải bật SPE sau khi config xong**: Không ghi CR1 khi SPE=1.
- **SendData chờ BSY=0 cuối cùng**: Đảm bảo transfer hoàn tất trước khi tắt SPI.
- **Receive gửi dummy 0xFF**: Master phải tạo clock bằng cách ghi DR, dù không cần truyền gì.
- **Truy cập DR bằng word (32-bit)**: Driver ghi/đọc `pSPIx->DR` trực tiếp (không dùng con trỏ `uint8_t*`). Truy cập byte (STRB/LDRB) vào DR trên STM32F4 có thể không clear RXNE đúng → OVR ngầm, đọc ra dữ liệu cũ.

## Vấn đề chip-select (CS) và ODR reset — BẪY THƯỜNG GẶP

`GPIO_Init()` **không đụng thanh ghi ODR**, mà ODR reset value = `0x0000`. Nên ngay khi một chân chuyển sang output, nó ở mức **LOW**. Với chân CS tích cực-thấp, điều này nghĩa là **slave bị chọn (CS=LOW) ngay từ lúc GPIO_Init() chạy** — trước khi ứng dụng kịp gọi `GPIO_Write_Pin(..., 0)`.

Hậu quả: lệnh kéo CS xuống LOW sau đó trở thành **no-op** (CS đã LOW sẵn) → **không có sườn xuống CS thật** cho transaction đầu tiên. Slave như LIS3DSH cần sườn xuống để đồng bộ bộ đếm bit của một frame → lần đọc đầu ra giá trị rác (thường `0xFF`). Từ lần thứ 2 (trong vòng lặp) mới đúng vì lúc đó CS đã có sườn HIGH→LOW thật.

**Cách xử lý trong driver:** điền `CS_Port`/`CS_Pin` vào handle. `SPI_Init()` sẽ tự gọi `SPI_ChipSelect(handle, DISABLE)` để đưa CS lên HIGH (nghỉ) ngay sau khi cấu hình, đảm bảo có sườn xuống thật ở transaction đầu.

```c
hspi1.CS_Port = GPIOE;
hspi1.CS_Pin  = GPIO_PIN_NO_3;   // CS = PE3 (LIS3DSH onboard Discovery)
SPI_Init(&hspi1);                // tự deselect CS về HIGH

SPI_ChipSelect(&hspi1, ENABLE);  // CS=LOW: chọn slave (có sườn xuống thật)
SPI_TransmitReceive(&hspi1, tx, rx, 2, 1000);
SPI_ChipSelect(&hspi1, DISABLE); // CS=HIGH: bỏ chọn
```

Nếu `CS_Port = NULL` → driver không quản CS (dùng hardware NSS hoặc app tự điều khiển).

## Interrupt mode (non-blocking)

Mô hình theo đúng pattern EXTI: bảng callback + trap mặc định. Ứng dụng chỉ **kích hoạt** ở main.c; xử lý ngắt nằm trong `stm32f4xx_it.c`.

```c
// 1. Đăng ký callback (nếu không, sự kiện rơi vào trap while(1) để debugger bắt)
void SPI1_AppCallback(SPI_Handle_t *h, uint8_t evt) {
    if (evt == SPI_EVENT_TX_CMPLT) { /* ... */ }
    if (evt == SPI_EVENT_RX_CMPLT) { /* ... */ }
    if (evt == SPI_EVENT_OVR_ERR)  { /* ... */ }
}
SPI_RegisterCallback(SPI1, SPI1_AppCallback);

// 2. Bật NVIC cho SPI1 (bỏ comment trong irq_config.c → IRQ_Init())
//    DRV_NVIC_SetPriority(SPI1_IRQn, 6, 0);
//    DRV_NVIC_EnableIRQ(SPI1_IRQn);

// 3. Khởi động phiên non-blocking — hàm trả về ngay
SPI_Transmit_IT(&hspi1, txbuf, len);   // ISR ghi dần, xong → callback TX_CMPLT
SPI_Receive_IT(&hspi1, rxbuf, len);    // ISR đọc dần, xong → callback RX_CMPLT
```

**Luồng ngắt:** `SPI1_IRQHandler()` (trong `stm32f4xx_it.c`) gọi `SPI_IRQHandling(&hspi1)`. Hàm này kiểm tra TXE/RXNE/OVR, ghi/đọc DR, và khi hết `TxLen`/`RxLen` thì tắt ngắt tương ứng (TXEIE/RXNEIE) rồi gọi callback.

**Sự kiện callback:**

| Event                | Khi nào                          |
|----------------------|----------------------------------|
| `SPI_EVENT_TX_CMPLT` | Truyền xong toàn bộ `TxLen` byte |
| `SPI_EVENT_RX_CMPLT` | Nhận xong toàn bộ `RxLen` byte   |
| `SPI_EVENT_OVR_ERR`  | Overrun (chỉ khi ERRIE bật)      |

## Debug tips

- SPI không hoạt động: kiểm tra clock RCC đã bật (APB1 cho SPI2/3, APB2 cho SPI1)
- MODF fault: kiểm tra SSI=1 khi SSM=1
- Không nhận data: kiểm tra MISO pin đã cấu hình AF đúng
- Data sai: kiểm tra CPOL/CPHA phù hợp với slave device
- Tốc độ: SPI2/3 trên APB1 (max 42MHz/prescaler), SPI1 trên APB2 (max 84MHz/prescaler)
- Đọc ra `0xFF` ở lần đầu nhưng đúng từ lần 2 (trong `while(1)`): CS không có sườn xuống thật — xem mục "Vấn đề chip-select (CS) và ODR reset". Điền `CS_Port`/`CS_Pin` để `SPI_Init()` tự deselect.
- Đọc register slave kiểu MEMS ST qua blocking API hiện tại: giữ CS LOW, `SPI_Transmit()` command byte, sau đó `SPI_Receive()` dummy clocks, rồi CS HIGH. Không được nhả CS giữa command và data phase.

## Pin mapping (SPI2)

| Pin  | Function  |
|------|-----------|
| PB12 | NSS       |
| PB13 | SCK       |
| PB14 | MISO      |
| PB15 | MOSI      |


## Ghi chú cho LIS3DSH onboard STM32F407 Discovery

Board STM32F407 Discovery revision mới dùng accelerometer **LIS3DSH** onboard, không phải LIS3DH. Với LIS3DSH:

```c
WHO_AM_I register = 0x0F
WHO_AM_I value    = 0x3F
Read command      = 0x0F | (1U << 7) = 0x8F
```

SPI command byte dùng bit 7 làm read bit:

```c
cmd = reg | (1U << 7);   /* read */
```

Trong project hiện tại, `main.c` dùng SPI1 + CS PE3:

```c
hspi1.pSPIx = SPI1;
hspi1.SPIConfig.SPI_CPHA = SPI_CPHA_HIGH;
hspi1.SPIConfig.SPI_CPOL = SPI_CPOL_HIGH;
hspi1.CS_Port = GPIOE;
hspi1.CS_Pin = GPIO_PIN_NO_3;
```

Với LIS3DSH, multi-byte read được driver bật bằng `CTRL_REG6.ADD_INC`. Khi đọc 6 byte XYZ từ `OUT_X_L = 0x28`, command debug đúng là:

```c
0x28 | (1U << 7) = 0xA8
```

Không dùng tài liệu/register của LIS3DH cho sensor onboard này; LIS3DH có `WHO_AM_I = 0x33`, khác LIS3DSH.
