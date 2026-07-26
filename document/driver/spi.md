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

## Trình tự khởi tạo

```c
// 1. Cấu hình GPIO cho SPI pins (SCK, MOSI, MISO, NSS)
SPI_GpioConfig(SPI2);  // Helper: set PB12-15 AF5

// 2. Khai báo và cấu hình handle
SPI_Handle_t hspi2;
hspi2.pSPIx = SPI2;
hspi2.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
hspi2.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
hspi2.SPIConfig.SPI_DFF = SPI_DFF_8bits;
hspi2.SPIConfig.SPI_Frame_format = MSB_TRANSMITTED_FIRST;
hspi2.SPIConfig.SPI_SSM = SPI_SSM_EN;
hspi2.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
hspi2.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
hspi2.SPIConfig.speed = SPI_SCLK_SPEED_DIV8;

// 3. Init (tự bật clock, ghi CR1)
SPI_Init(&hspi2);

// 4. Nếu SSM=EN, phải set SSI=1 để tránh MODF fault
SPI_SSI_Config(SPI2, ENABLE);

// 5. Bật SPI peripheral
SPI_PeripheralControl(SPI2, ENABLE);

// 6. Gửi/nhận data
SPI_SendData(SPI2, txbuf, len);
SPI_ReceiveData(SPI2, rxbuf, len);

// 7. Tắt SPI khi xong
SPI_PeripheralControl(SPI2, DISABLE);
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
| `SPI_SendData`           | Blocking send: chờ TXE, ghi DR, hỗ trợ 8/16-bit      |
| `SPI_ReceiveData`        | Blocking receive: gửi dummy để tạo clock, đọc DR      |
| `SPI_GpioConfig`         | Helper cấu hình GPIO AF5 cho SPI2 (PB12-15)          |
| `SPI_GetFlagStatus`      | Kiểm tra flag trong SR (TXE, RXNE, BSY)              |

## Lưu ý quan trọng

- **SSM=1 bắt buộc SSI=1**: Nếu không, bit NSS bị kéo LOW → chip tưởng có master khác → MODF fault → SPI tự disable.
- **Phải bật SPE sau khi config xong**: Không ghi CR1 khi SPE=1.
- **SendData chờ BSY=0 cuối cùng**: Đảm bảo transfer hoàn tất trước khi tắt SPI.
- **ReceiveData gửi dummy 0xFF**: Master phải tạo clock bằng cách ghi DR, dù không cần truyền gì.

## Debug tips

- SPI không hoạt động: kiểm tra clock RCC đã bật (APB1 cho SPI2/3, APB2 cho SPI1)
- MODF fault: kiểm tra SSI=1 khi SSM=1
- Không nhận data: kiểm tra MISO pin đã cấu hình AF đúng
- Data sai: kiểm tra CPOL/CPHA phù hợp với slave device
- Tốc độ: SPI2/3 trên APB1 (max 42MHz/prescaler), SPI1 trên APB2 (max 84MHz/prescaler)

## Pin mapping (SPI2)

| Pin  | Function  |
|------|-----------|
| PB12 | NSS       |
| PB13 | SCK       |
| PB14 | MISO      |
| PB15 | MOSI      |
