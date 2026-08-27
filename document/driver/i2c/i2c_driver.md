# I2C Driver — Lý thuyết

## 1. Cấu trúc OOP/HAL

Giống mô hình các driver khác trong repo (SPI, GPIO...), I2C chia làm 2 struct:

```c
I2C_Config_t    // Config struct — cấu hình I2C peripheral
i2c_driver_t    // Handle struct — chứa base address + config
```

### Hai loại địa chỉ trong I2C

I2C có hai loại địa chỉ khác nhau:

| Loại địa chỉ | Tên gọi | Ví dụ | Ý nghĩa |
|--------------|---------|-------|---------|
| **Địa chỉ Target/Slave** | `DEVICE_ADDR` | `0x68` (MPU6050), `0x50` (EEPROM) | Địa chỉ 7-bit của thiết bị trên bus I2C |
| **Địa chỉ thanh ghi** | `REG_ADDR` | `0x0F` (WHO_AM_I), `0x28` (data) | Địa chỉ của thanh ghi bên trong thiết bị |

> **DEVICE_ADDR** nằm trên bus I2C — là thứ được gửi trong address frame (7-bit + R/W bit).
>
> **REG_ADDR** là byte đầu tiên của data payload — là thứ được firmware của Target hiểu là "địa chỉ thanh ghi".

Ví dụ: để đọc thanh ghi `WHO_AM_I` (0x0F) từ cảm biến địa chỉ `0x68`, phải
gửi `REG_ADDR` trong write phase trước repeated START:

```
Write phase:    (0x68 << 1) | 0 = 0xD0 → payload 0x0F
Repeated START
Read phase:     (0x68 << 1) | 1 = 0xD1 → Target trả WHO_AM_I
```

### Bốn kiểu giao dịch I2C trong driver

Khi viết driver theo kiểu HAL, nên tách rõ 4 kiểu giao dịch:

| Hàm | Chuỗi truyền | Ý nghĩa |
|-----|--------------|---------|
| `Master_Transmit()` | `Address + W → Data` | Gửi dữ liệu thô |
| `Master_Receive()` | `Address + R → Data` | Nhận dữ liệu thô |
| `Mem_Write()` | `Address + W → Register → Data` | Ghi vào thanh ghi bên trong target |
| `Mem_Read()` | `Address + W → Register → Repeated START → Address + R → Data` | Đọc thanh ghi bên trong target |

Trong tài liệu này, các tên trên là **tên giao dịch ở mức lý thuyết**. Tên hàm driver thực tế trong repo sẽ đi theo dạng:

| Khái niệm | Hàm driver hiện tại |
|-----------|---------------------|
| `Master_Transmit()` | `I2C_MasterSendData()` |
| `Master_Receive()` | `I2C_MasterReceiveData()` |
| `Mem_Write()` | `I2C_MemWriteData()` |
| `Mem_Read()` | `I2C_MemReadData()` |

**STM32–STM32 trao đổi buffer:** nếu hai STM32 chỉ truyền nhận buffer, không có khái niệm thanh ghi nội bộ. Khi đó dùng `Master_Transmit()` và `Master_Receive()` là đúng.

**Target có register map:** nếu target là cảm biến, EEPROM hoặc một firmware slave được thiết kế theo bản đồ thanh ghi, muốn đọc đúng thanh ghi thì phải dùng `Mem_Read()` hoặc tự tạo sequence tương đương.

Ví dụ đọc thanh ghi `0x05`:

```
START
→ Address + Write
→ 0x05
→ REPEATED START
→ Address + Read
→ Data
→ STOP
```

`Master_Receive()` có thể chọn đúng target bằng `DEVICE_ADDR`, nhưng không tự chọn được `REG_ADDR` bên trong target. Byte `REG_ADDR` chỉ có ý nghĩa nếu firmware của target hiểu byte đó là địa chỉ thanh ghi.

Các sự kiện EV5, EV6, EV7, EV8, EV9 trong RM0090 chỉ mô tả trạng thái phần cứng I2C; chúng không quyết định byte data có phải địa chỉ thanh ghi hay không.

### I2C_Config_t — 4 trường chính

| Field              | Ý nghĩa                      | Thanh ghi STM32 | Chức năng                    |
|--------------------|------------------------------|-----------------|------------------------------|
| `I2C_SCLSpeed`     | Tốc độ bus (100k/400k)       | `CR2`, `CCR`, `TRISE` | Tạo timing SCL      |
| `I2C_DeviceAddress`| Địa chỉ của chính MCU        | `OAR1`          | Địa chỉ khi MCU là slave     |
| `I2C_ACKControl`   | Bật/tắt ACK khi nhận         | `CR1.ACK`       | Điều khiển ACK khi nhận      |
| `I2C_FMDutyCycle`  | Tỷ lệ LOW/HIGH Fast-mode     | `CCR.DUTY`      | Duty 2:1 hoặc 16:9           |

### i2c_driver_t

| Field     | Ý nghĩa                                             |
|-----------|-----------------------------------------------------|
| `pI2Cx`   | Con trỏ tới I2C peripheral (`I2C1`, `I2C2`, `I2C3`) |
| `I2CConfig` | Struct config ở trên                              |
| *(thêm)*  | Trạng thái nội bộ TX/RX cho interrupt mode — không set thủ công |

### Vì sao không phân biệt Master/Slave trong struct config

Khác với SPI (`SPI_DeviceMode` master/slave khai báo tĩnh trong config), I2C
**không cần khai báo vai trò lúc cấu hình**:

- I2C phân biệt vai trò **theo thời điểm hoạt động**, không theo cấu hình:
  thiết bị nào phát START trên bus thì đóng vai **controller (master)** tại
  giao tiếp đó, còn lại đều là **target (slave)**.
- Do đó lúc init chỉ quan tâm: **tốc độ truyền (timing SCL)** và **địa chỉ của
  chính mình (`I2C_DeviceAddress`)** — để khi bị gọi (slave) thì biết mình có
  đúng là người được gọi không.
- **Địa chỉ của target** (sensor, LCD...) KHÔNG nằm trong struct cấu hình —
  nó được truyền làm tham số runtime khi gọi `I2C_MasterSendData(..., SlaveAddr, ...)`
  vì mỗi transaction có thể giao tiếp với target khác nhau trên cùng 1 bus.

## 2. Ánh xạ chi tiết 4 trường → thanh ghi

### a) `I2C_SCLSpeed` → `CR2.FREQ`, `CCR`, `TRISE`

Tốc độ SCL thực tế được quyết định bởi **3 thanh ghi**:

| Thanh ghi | Bit field      | Vai trò                                                        |
|-----------|----------------|----------------------------------------------------------------|
| `CR2`     | `FREQ[5:0]`    | **PCLK1 tính theo MHz** (vd PCLK1 = 42 MHz → FREQ = 42). Bắt buộc — mọi timing I2C đều lấy từ đây |
| `CCR`     | `FS` (bit 15)  | Chọn mode: `0` = Standard (100 kHz), `1` = Fast (400 kHz)      |
| `CCR`     | `CCR[11:0]`    | Số chu kỳ clock cho 1 pha LOW/HIGH của SCL → quyết định fSCL   |
| `TRISE`   | `TRISE[5:0]`   | **Rise time max** của bus (theo spec mode) + 1 — đơn vị chu kỳ PCLK1 |

**Công thức tính CCR** (đã ghi trong `i2c.md` mục 3.5-b4):

```
Standard:  CCR = PCLK1 / (2 × fSCL)          (DUTY không dùng)
Fast, DUTY=0 (2:1):    CCR = PCLK1 / (3 × fSCL)
Fast, DUTY=1 (16:9):   CCR = PCLK1 / (25 × fSCL)
```

> Lưu ý: `fSCL` nhập theo **Hz**, PCLK1 lấy theo Hz → ra CCR đúng. Nhưng `FREQ`
> trong CR2 lại nhập theo **MHz** → trong code phải `RCC_GetPLCK1Value()/1000000U`.

**Công thức TRISE**:

```
TRISE = (tr_max × PCLK1) + 1      (đơn vị chu kỳ PCLK1, làm tròn lên)
Standard:  tr_max = 1000 ns → TRISE = PCLK1(MHz) + 1
Fast:      tr_max = 300 ns  → TRISE = (300 × PCLK1) + 1  (thường cũng = PCLK1+1)
```

### b) `I2C_DeviceAddress` → `OAR1` (Own Address Register)

| Bit field | Vai trò                                             |
|-----------|-----------------------------------------------------|
| `ADD[7:1]`| Địa chỉ 7-bit của **chính MCU**                     |
| `ADD0`    | Bit LSB — `0` khi dùng 7-bit addressing             |
| `ADDMODE[15]`| Mode địa chỉ target: `0` = 7-bit, `1` = 10-bit |
| `Bit 14`     | **Luôn giữ = 1** (yêu cầu RM0090) |

Khi MCU là **target**: nhận address frame trên bus, so sánh với `OAR1` → trùng
thì ACK và bắt đầu giao tiếp. Khi MCU là **controller**: `OAR1` không dùng —
địa chỉ target được gửi trong address frame chứa trong `I2C_DR`.

### c) `I2C_ACKControl` → `CR1.ACK`

| Giá trị | Bit `ACK` | Hành vi khi nhận byte                                       |
|---------|-----------|-------------------------------------------------------------|
| Enable  | 1         | Tự động gửi ACK sau mỗi byte nhận (được)                    |
| Disable | 0         | Không gửi ACK → NACK — dùng cho byte **cuối** của chuỗi đọc |

Trong read sequence: controller phải NACK byte cuối để báo "đủ rồi" cho target
ngừng gửi. Thực tế driver thường bật ACK trong toàn transaction rồi gửi NACK
bằng cách set `POS`/chỉnh ACK trước byte cuối, hoặc dùng kỹ thuật tắt ACK ở
byte áp chót.

### d) `I2C_FMDutyCycle` → `CCR.DUTY` (chỉ dùng Fast-mode)

| Giá trị            | Bit `DUTY` | Tỷ lệ tLOW:tHIGH | Công thức CCR   |
|--------------------|------------|------------------|-----------------|
| `I2C_FM_DUTY_2`    | 0          | 2:1              | `PCLK1/(3×fSCL)`|
| `I2C_FM_DUTY_16_9` | 1          | 16:9             | `PCLK1/(25×fSCL)`|

Ở Standard-mode bit `DUTY` bị bỏ qua (tỷ lệ luôn 1:1).

## 3. Init API — trình tự khởi tạo SCL speed

Init I2C bắt đầu từ **tốc độ SCL** (`I2C_SCLSpeed`), vì tốc độ quyết định toàn
bộ timing phần cứng. Trình tự như sau:

### Bước 1 — Xác định PCLK1 (clock nguồn)

I2C trên STM32F407 nằm ở **APB1 bus** → clock cấp cho I2C là **PCLK1**.

```
Clock nguồn (HSI 16MHz / HSE 8MHz / PLL) → AHB prescaler → APB1 prescaler → PCLK1
```

### Bước 2 — Chọn `I2C_SCLSpeed` (SM hoặc FM)

`I2C_SCLSpeed` nhận 1 trong 2 giá trị mode:

| Giá trị | Tốc độ  | Chu kỳ t = 1/fSCL | Phân bố chu kỳ          |
|---------|---------|-------------------|-------------------------|
| SM      | 100 kHz | 10 µs             | tLOW = tHIGH = t/2 (5 µs) — tỷ lệ 1:1 |
| FM      | 400 kHz | 2.5 µs            | tLOW : tHIGH theo `DUTY` (2:1 hoặc 16:9) |

> SM: do tLOW = tHIGH = t/2 nên từ 100 kHz quy ra chu kỳ `t`, rồi mỗi pha
> LOW/HIGH chiếm `t/2`.

### Bước 3 — Ghi FREQ vào CR2

FREQ = **PCLK1 tính theo MHz** (vd PCLK1 = 42 MHz → FREQ = 42):

```c
CR2.FREQ = (PCLK1 / 1000000U) & 0x3F;
```

### Bước 4 — Tính CCR từ FREQ đã ghi

Đọc lại giá trị FREQ trong CR2 (hoặc dùng PCLK1) → đổi ra chu kỳ **TFREQ**:

```
TFREQ = 1 / (FREQ × 1 MHz)      // chu kỳ 1 xung PCLK1
CCR   = tLOW / TFREQ = (t/2) / TFREQ
```

Với SM: `t/2 = 1/(2×fSCL)` → suy ra công thức quen thuộc:

```
CCR = PCLK1 / (2 × fSCL)
```

Ví dụ SM, PCLK1 = 42 MHz:

```
TFREQ = 1/42 MHz ≈ 23.8 ns
tLOW  = 5 µs
CCR   = 5 µs / 23.8 ns = 210     (= 42e6 / (2 × 100e3) ✓)
```

> FM làm tương tự nhưng chia theo tỷ lệ `DUTY`: 2:1 → `CCR = PCLK1/(3×fSCL)`,
> 16:9 → `CCR = PCLK1/(25×fSCL)` (chi tiết mục 2-d).

### Bước 5 — Tính TRISE (max rise time)

TRISE giới hạn **thời gian sườn lên tối đa** của bus (do RC của pullup quyết
định, xem `i2c.md` 3.5). Giá trị = rise time spec của mode quy ra chu kỳ PCLK1,
rồi **+1**:

```
TRISE = (tr_max × PCLK1) + 1      // làm tròn lên, đơn vị chu kỳ PCLK1
```

| Mode | tr_max (spec) | Công thức rút gọn         |
|------|---------------|---------------------------|
| SM   | 1000 ns       | `TRISE = PCLK1(MHz) + 1`  |
| FM   | 300 ns        | `TRISE = (300ns × PCLK1) + 1` (thường cũng = PCLK1 + 1) |

Ví dụ PCLK1 = 42 MHz:

```
SM: TRISE = 1000 ns × 42 MHz + 1 = 42 + 1 = 43
FM: TRISE = 300 ns × 42 MHz + 1  = 12.6 + 1 ≈ 13.6 → 14
```

> Phải ghi TRISE trước khi bật PE, nếu không timing SCL sai → giao tiếp lỗi.

### Bước 6 — Cấu hình lọc nhiễu (NOISE FILTER — chỉ STM32F42xxx+)

I2C có thể lọc nhiễu trên SDA/SCL bằng 2 loại filter:

| Filter | Bit trong `CR1` | Vai trò                                    |
|--------|-----------------|--------------------------------------------|
| Analog filter (AF)  | `AF[3:0]` (và AF bit riêng) | Lọc nhiễu bằng mạch analog, không cần cấu hình thời gian |
| Digital filter (DNF) | `DNF[3:0]` | Lọc nhiễu bằng cách bỏ qua xung ngắn hơn `DNF × TPCLK1` (chu kỳ PCLK1) |

> **Quan trọng: bit AF/DNF chỉ tồn tại trên STM32F42xxx trở lên**
> (F427, F429, F43x, F44x...). **STM32F407 không có filter này** — bit không
> tồn tại trong `CR1`, ghi vào cũng vô tác dụng. Trên F407, nhiễu được xử lý
> bằng hardware bên ngoài (RC + pullup hợp lý), không qua thanh ghi.

Ví dụ F42xxx — tắt analog filter, digital filter loại xung < 4 chu kỳ PCLK1:

```c
CR1 &= ~AF;                       // bật analog filter (AF=0)
CR1 |= (4 << DNF_Pos);            // DNF = 4 → bỏ xung < 4 × TPCLK1
```

> Driver trong repo này viết cho **STM32F407** → bỏ qua bước này hoàn toàn,
> chỉ giữ để note khi port sang F42xxx+.

### Bước 7 — Cấu hình địa chỉ OAR1 (Own Address)

`OAR1` lưu **địa chỉ của chính MCU** — dùng khi MCU là target (slave) bị gọi:

| Bit field | Vai trò                                   |
|-----------|-------------------------------------------|
| `ADD[7:1]`| Địa chỉ 7-bit của MCU (từ `I2C_DeviceAddress`) |
| `ADD0`    | Bit LSB — `0` khi dùng 7-bit addressing   |
| `ADDMODE[15]`| Mode địa chỉ target: `0` = 7-bit, `1` = 10-bit |
| `Bit 14`     | **Luôn giữ = 1** (yêu cầu RM0090) |

Ghi như sau:

```c
OAR1 = (I2C_DeviceAddress << 1) | (1 << 14);
//       địa chỉ lên ADD[7:1]      Bit14=1 (bắt buộc), ADDMODE=0 → 7-bit
```

Ví dụ `I2C_DeviceAddress = 0x68`:

```
OAR1 = (0x68 << 1) | 0x4000 = 0x40D0
```

> `I2C_DeviceAddress` là địa chỉ **của MCU**, không phải của sensor. Nếu ứng
> dụng chỉ dùng MCU làm master (phổ biến nhất) thì địa chỉ này không quan trọng
> nhưng vẫn nên set.

### Bước 8 — Cấu hình ACK control (`CR1.ACK`)

`I2C_ACKControl` quyết định có tự động trả ACK sau mỗi byte nhận hay không:

| Giá trị          | Bit `ACK` (bit 10) | Khi nhận byte          |
|------------------|--------------------|------------------------|
| `I2C_ACK_ENABLE` | 1                  | Tự động trả ACK        |
| `I2C_ACK_DISABLE`| 0                  | Trả NACK — dùng cho byte cuối chuỗi đọc |

```c
CR1 |= (I2C_ACKControl << I2C_CR1_ACK_Pos);   // I2C_CR1_ACK_Pos = 10
```

> Trong init thường bật ACK (ENABLE). Khi master đọc nhiều byte, driver sẽ tắt
> ACK trước byte cuối để báo NACK — xử lý trong lúc transaction, không phải lúc
> init.

### Bước 9 — Cấu hình FMDutyCycle (`CCR.DUTY`) + mode FS

`I2C_FMDutyCycle` chỉ có ý nghĩa khi chạy **Fast-mode** (FS = 1). Đây là phần
cấu hình điều khiển của CCR (còn giá trị `CCR[11:0]` đã tính ở Bước 4):

| Bit trong `CCR` | Vai trò                                  |
|-----------------|------------------------------------------|
| `FS` (bit 15)   | `0` = Standard-mode, `1` = Fast-mode     |
| `DUTY` (bit 14) | `0` = tLOW:tHIGH = 2:1, `1` = 16:9       |
| `CCR[11:0]`     | Số chu kỳ PCLK1 (tính ở Bước 4)          |

```c
if (I2C_SCLSpeed > I2C_SCL_SPEED_SM)
{
    CCR |= (1 << I2C_CCR_FS_Pos);                      // FS = 1 → Fast-mode
    CCR |= (I2C_FMDutyCycle << I2C_CCR_DUTY_Pos);      // DUTY theo config
    CCR |= ccr_value;                                  // giá trị từ Bước 4
}
else
{
    CCR = ccr_value;                                   // FS = 0, DUTY bỏ qua
}
```

> Trong code thực tế Bước 4 + Bước 9 thường gộp chung 1 lần ghi CCR. Tách ra
> chỉ để dễ hiểu: Bước 4 tính **giá trị số**, Bước 9 set **bit điều khiển**.

### Bước 10 — Bật peripheral (`CR1.PE`)

Sau khi đã ghi xong mọi cấu hình, bật peripheral để I2C bắt đầu hoạt động:

| Bit `PE` (bit 0) | Trạng thái          |
|------------------|---------------------|
| 0                | I2C tắt (clock tạm dừng) |
| 1                | I2C hoạt động        |

```c
CR1 |= (1 << I2C_CR1_PE_Pos);
```

> **Thứ tự quan trọng khi init**: cấu hình timing/address (`CR2.FREQ`, `CCR`,
> `TRISE`, `OAR1`) trước khi set `PE=1`. Các bit điều khiển transaction trong
> `CR1` như `ACK`, `POS`, `START`, `STOP` được thay đổi khi peripheral đang hoạt
> động theo đúng event sequence; đặc biệt Controller receiver phải đổi `ACK/POS`
> trong transaction để tạo NACK cuối.

### Tổng kết trình tự init

```
1. PCLK1 (APB1)                       → 2. chọn SM/FM
3. CR2.FREQ  = PCLK1(MHz)
4. CCR[11:0] = PCLK1/(2×fSCL) hoặc theo DUTY
5. TRISE     = (tr_max × PCLK1) + 1
6. (F42xxx+): lọc nhiễu AF/DNF — F407 bỏ qua
7. OAR1      = (DeviceAddress << 1) | (1 << 14)
8. CR1.ACK   = I2C_ACKControl
9. CCR       = FS | DUTY | CCR[11:0]
10. CR1.PE = 1 → I2C sẵn sàng
```

## 4. Write data — master gửi dữ liệu

Khi MCU là master (controller) gửi data cho slave, giao tiếp trên bus:

```
START | Address (7-bit + R/W=0) + ACK | Data byte 1 + ACK | ... | Data byte N + ACK | STOP
```

Sơ đồ sequence phía Controller transmitter (bao gồm EV5, EV6 và
EV8/EV8_1/EV8_2) được mô tả trong hình sau:

![Controller transmitter sequence](image/image31.png)

Phía bên kia của cùng transaction là Target receiver trong ![Target receiver sequence](image/image26.png)
Target ACK address/data, sau đó nhận STOP do Controller phát và set `STOPF`.

**Chú thích các sự kiện (Event):**
*   **EV5:** `SB=1`, START đã phát xong; ghi address vào `DR`.
*   **EV6:** `ADDR=1`, target đã ACK address; clear bằng cách đọc `SR1` rồi `SR2`.
*   **EV8/EV8_1/EV8_2:** các trạng thái truyền khi `TXE`/`BTF` báo data register hoặc shift register đã sẵn sàng.
*   **AF:** target không ACK address hoặc data; clear theo quy định của `SR1`, sau đó kết thúc transaction.

`AF` không phải là một flag độc lập với NACK trên bus: nó là trạng thái ACK Failure của peripheral sau khi target không kéo SDA xuống ở chu kỳ ACK.

### 4.1 Trình tự polling từng bước

| Bước | Việc làm                                   | Flag chờ | Sự kiện (Event) | Hành vi khi chưa set |
|------|--------------------------------------------|----------|-----------------|----------------------|
| 1    | Phát START (`CR1.START`)                   | —        | —               | —                    |
| 2    | Chờ START phát xong                        | `SB` (SR1) | —               | SCL bị stretch |
| 3    | Ghi địa chỉ slave + R/W=0 vào `DR`        | —        | —               | —                    |
| 4    | Chờ address được target ACK                | `ADDR` (SR1) | **EV6**         | SCL bị stretch |
| 5    | Clear ADDR (đọc SR1 rồi đọc SR2)          | —        | —               | —                    |
| 6    | Vòng lặp: chờ `TXE` → ghi byte `DR`        | `TXE` (SR1) | **EV8/EV8_1**   | —                    |
| 7    | Byte cuối: chờ `TXE` + `BTF`              | `BTF` (SR1) | —               | SCL bị stretch |
| 8    | Phát STOP (`CR1.STOP`)                     | —        | —               | —                    |
| -    | Nếu target không ACK (address/data)        | `AF` (SR1) | Error           | Phát STOP, báo lỗi |

```c
DriverStatus_t I2C_MasterSendData(i2c_driver_t *pI2CDriver,
                                  uint8_t *pTxBuffer, uint16_t Len,
                                  uint16_t SlaveAddr, uint8_t Sr)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    /* Bước 1 — check bus idle (BUSY ở SR2) rồi phát START */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR2_BUSY) == FLAG_SET);
    I2C_GenerateSTART(pI2CDriver);

    /* Bước 2 — chờ SB = 1 */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_SB) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Bước 3 — gửi địa chỉ slave, R/W = 0 (write) */
    pI2Cx->DR = (uint8_t)((SlaveAddr << 1U) | I2C_WRITE);

    /* Bước 4 — chờ ADDR = 1 (target đã ACK địa chỉ) — EV6 */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET)
    {
        /* Kiểm tra lỗi ACK Failure */
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Bước 5 — clear ADDR: đọc SR1 rồi đọc SR2 (đúng thứ tự bắt buộc) */
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Bước 6 — gửi từng byte, chờ TXE trước mỗi lần ghi DR (EV8/EV8_1) */
    while (Len > 0U)
    {
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
        {
            /* Kiểm tra lỗi ACK Failure */
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
            {
                I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
                I2C_GenerateSTOP(pI2CDriver);
                return STATUS_ERROR;
            }
        }
        pI2Cx->DR = *pTxBuffer++;
        Len--;
    }

    /* Bước 7 — chờ BTF để đảm bảo byte cuối đã shift xong */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET);

    /* Bước 8 — phát STOP */
    I2C_GenerateSTOP(pI2CDriver);

    return STATUS_OK;
}
```

### 4.2 Giải thích chi tiết từng bước

**Bước 2 — `SB` (Start Bit, SR1 bit 0):** set khi START đã thật sự phát trên
bus. Cho tới khi SB được clear, SCL bị **clock stretching** (giữ low) — phần
cứng kéo SCL xuống để ngăn master tiếp tục khi phần mềm chưa sẵn sàng.

**Bước 4 — `ADDR` (SR1 bit 1):** set khi address frame xong và target đã ACK.
Nếu không có target nào trả lời → bit `AF` (Acknowledge Failure) set thay vì
ADDR → phải phát STOP và trả lỗi.

**Bước 5 — Clear ADDR:** quy định của ST — đọc **SR1 rồi SR2** (bắt buộc đúng
thứ tự) để clear ADDR. Nếu quên, SCL vẫn bị stretch vĩnh viễn → bus treo.

**Bước 6 — `TXE` (SR1 bit 7):** Data Register rỗng → được ghi byte mới. Điểm
quan trọng: sau khi ghi `DR`, phần cứng mới shift byte ra từ từ — phải chờ TXE
set lại (DR rỗng) trước khi ghi byte kế, nếu không byte cũ chưa gửi xong sẽ bị
ghi đè. Các trạng thái **EV8/EV8_1** liên quan đến `TXE` được
xử lý trong vòng lặp này.

**Bước 7 — `BTF` (Byte Transfer Finished, SR1 bit 2):** set khi **cả DR lẫn
shift register đều rỗng** — tức byte cuối đã ra hết trên bus. Chờ TXE trước,
ghi byte cuối vào DR, rồi chờ BTF để chắc chắn byte đã shift xong. Khi BTF = 1,
SCL bị stretch — chính lúc này tạo STOP an toàn.

**Bước 8 — STOP:** phát bằng `CR1.STOP`. Master **không cần chờ** STOP xong
(ác START — phải chờ SB). Phát STOP tự động clear BTF.

> **`Sr` (Repeated Start)** — tham số dùng khi muốn *write rồi đọc trong cùng
> transaction* (vd: ghi register address rồi đọc data). Ở cuối write sequence,
> thay vì STOP, phát START lần nữa (Repeated START) và đổi R/W=1. Chi tiết ở
> mục receive data.

### 4.3 So sánh START và STOP khi polling

| Điều kiện | START | STOP |
|-----------|-------|------|
| Set bit tại | `CR1.START` (bit 8) | `CR1.STOP` (bit 9) |
| Có phải chờ hoàn tất? | **Có** — chờ `SB` set | **Không** — cứ phát là xong |
| Clear tự động | SB clear khi đọc SR1 | STOP tự clear khi phát xong |
| Clear bằng tay | — | — |

> Ghi chú lịch sử: `START` và `STOP` nằm trong `CR1` (`START` bit 8, `STOP` bit 9) theo RM0090. Tài liệu cũ từng ghi nhầm sang `CR2`; code hiện tại đã dùng alias trỏ về đúng `I2C_CR1_START` và `I2C_CR1_STOP`.

### 4.4 BERR và ErrorRecovery trong polling

`BERR` là Bus Error trong `SR1`. Flag này thường set khi phần cứng thấy START
hoặc STOP ở vị trí không hợp lệ trên bus, nhiễu làm sai waveform, hoặc state
machine I2C rơi vào trạng thái không còn đồng bộ với bus.

Code polling hiện tại kiểm tra `BERR` trong các đoạn chờ quan trọng như chờ
`SB`, chờ `ADDR`, chờ `RXNE` và chờ `BTF`. Khi gặp `BERR`, driver làm ba việc:

1. Clear `BERR` trong `SR1`.
2. Phát `STOP` để cố gắng nhả bus ở mức giao thức.
3. Gọi `I2C_ErrorRecovery()`.

`I2C_ErrorRecovery()` dùng `CR1.SWRST` bit 15 để reset state machine I2C nội bộ,
sau đó gọi lại `I2C_Init()` để cấu hình lại `CR1/CR2/OAR1/CCR/TRISE`.

```c
pI2Cx->CR1 |= I2C_CR1_SWRST;
pI2Cx->CR1 &= ~I2C_CR1_SWRST;
I2C_Init(pI2CDriver);
```

Giới hạn quan trọng: `SWRST` chỉ reset peripheral I2C bên trong STM32. Nếu SDA
hoặc SCL bị kéo LOW vật lý bởi slave, dây chập, pull-up sai hoặc thiết bị ngoài
đang kẹt, `SWRST` không thể tự kéo bus lên lại. Trường hợp đó cần bus recovery ở
tầng GPIO, ví dụ tạm chuyển SCL sang GPIO output để tạo vài xung clock rồi phát
STOP bằng GPIO trước khi init lại I2C.

## 5. Receive data — master nhận dữ liệu

Khi MCU là master (controller) nhận data từ slave, giao tiếp trên bus:

```
START | Address (7-bit + R/W=1) + ACK | Data byte 1 + ACK | Data byte 2 + ACK | ... | Data byte N + NACK | STOP
```

Sơ đồ sequence phía Controller receiver (bao gồm EV5, EV6, EV7/EV7_1 và
NACK ở byte cuối) được mô tả trong hình sau:

![Controller receiver sequence](image/image30.png)

Phía bên kia của cùng transaction là Target transmitter trong ![Target transmitter sequence](image/image25.png)
Target gửi data, nhận NACK cuối từ Controller rồi nhận STOP. `AF`/EV3-2 ở
Target transmitter trong trường hợp này là tín hiệu kết thúc bình thường, không
nhất thiết là lỗi giao dịch.

**Chú thích các sự kiện (Event):**
*   **EV5:** `SB=1`, START đã phát xong; ghi address + R vào `DR`.
*   **EV6:** `ADDR=1`, target đã ACK address; clear bằng cách đọc `SR1` rồi `SR2`.
*   **EV7/EV7_1:** `RXNE=1`, `DR` có data mới; đọc `DR` để lấy byte và clear `RXNE`.
*   `STOPF` là trạng thái slave nhận STOP từ master, không phải event kết thúc khi master tự phát STOP.

### 5.1 Vì sao read phức tạp hơn write

Khi **write**, master hoàn toàn chủ động: muốn gửi bao nhiêu byte cũng được,
gửi xong phát STOP là xong.

Khi **read**, slave mới là bên gửi data — master chỉ cung cấp clock. Nhưng master
là bên quyết định **kết thúc** transaction, nên phải báo cho slave biết "đủ rồi,
ngừng gửi". Cách báo: master trả **NACK** (không ACK) sau byte cuối cùng, rồi
phát STOP.

Vấn đề: NACK phải được set **trước khi byte cuối được nhận**, vì ACK/NACK của
byte N được phát đi ngay sau byte N — không thể nhận xong byte N rồi mới quyết
định NACK (lúc đó phần cứng đã tự động ACK rồi). Do đó driver phải tính trước
byte nào là cuối và chuẩn bị NACK trước.

### 5.2 Trình tự polling từng bước

| Bước | Việc làm                                             | Flag chờ | Sự kiện | Hành vi khi chưa set |
|------|------------------------------------------------------|----------|---------|----------------------|
| 1    | Phát START (`CR1.START`)                             | —        | —       | —                    |
| 2    | Chờ START phát xong                                  | `SB` (SR1) | —     | SCL bị stretch       |
| 3    | Ghi địa chỉ slave + R/W=1 vào `DR`                   | —        | —       | —                    |
| 4    | Chờ address được target ACK                          | `ADDR` (SR1) | **EV6** | SCL bị stretch     |
| 5    | Cấu hình `ACK/POS` theo Len, sau đó clear ADDR       | —        | **EV6** | Phải làm trước khi SCL được nhả |
| 6    | Với Len > 2, đọc byte thường khi còn > 3 byte       | `RXNE` (SR1) | **EV7** | SCL bị stretch   |
| 7    | Xử lý riêng Len=1, Len=2 hoặc ba byte cuối           | `RXNE`/`BTF` | **EV7/EV7_1** | — |
| 8    | Lập trình STOP đúng thời điểm rồi đọc byte cuối      | `RXNE`/`BTF` (SR1) | **EV7/EV7_1** | —                  |
| -    | Nếu Slave không ACK address                          | `AF` (SR1) | —       | Phát STOP, báo lỗi   |

### 5.3 Xử lý NACK theo số byte cần đọc

Cách chuẩn bị NACK khác nhau tùy đọc **1 byte**, **2 byte** hay **nhiều hơn 2 byte**:

**Trường hợp Len = 1 (đọc đúng 1 byte):**

Phải tắt ACK **trước khi clear ADDR** để byte đầu tiên cũng là byte cuối cùng được
NACK đúng thời điểm:

```
START → Address+R/W=1 → ADDR=1 → POS=0 → ACK=0
  → clear ADDR → STOP → chờ RXNE → đọc DR
```

> **Cơ chế:** với `POS=0`, việc set `ACK=0` được áp dụng cho byte hiện tại đang
> được nhận vào shift register. Sau khi clear ADDR, byte đầu tiên chính là byte
> hiện tại nên nó được **NACK**.

**Trường hợp Len = 2:**

Theo RM0090, phải set `ACK=0` và `POS=1` khi `ADDR` còn set. Sau khi clear
`ADDR`, phần cứng nhận hai byte và giữ SCL LOW khi `BTF=1`; lúc đó Controller
lập trình STOP rồi đọc `DR` hai lần:

```
START → Address+R/W=1 → ADDR=1 → ACK=0 → POS=1 → clear ADDR
  → chờ BTF → STOP → đọc DR byte 1 → đọc DR byte 2
  → POS=0 → restore ACK
```

> **Cơ chế:** với `POS=1`, hiệu lực của `ACK=0` được **dịch sang byte kế tiếp**
> — vì vậy byte thứ nhất được ACK, byte thứ hai được NACK. CPU cố tình **không
> đọc `DR` sau byte thứ nhất**, nên khi byte thứ hai hoàn tất, DATA1 nằm trong
> `DR` và DATA2 nằm trong shift register → `BTF=1`. Sau STOP, đọc `DR` lần một
> lấy DATA1 và cho DATA2 chuyển xuống `DR`, rồi đọc `DR` lần hai lấy DATA2.

**Trường hợp Len > 2 (đọc nhiều byte):**

Duy trì ACK cho các byte đầu. Khi còn ba byte, chuyển sang sequence `BTF` để
NACK đúng byte cuối:

```
START → Address+R/W=1 → ADDR=1 → POS=0 → ACK=1 → clear ADDR
  → RXNE: đọc các byte khi còn nhiều hơn 3 byte
  → còn 3 byte: chờ BTF → ACK=0 → đọc byte N-2
  → còn 2 byte: chờ BTF → STOP → đọc byte N-1 và N
  → restore ACK
```

> **Trạng thái implementation:** `I2C_ReceivePhase()` hiện đã tuân thủ đầy đủ
> sequence RM0090 ở trên: dùng `POS=1` cho `Len=2`, chuyển sang `BTF` khi còn
> ba byte với `Len>2`, và program STOP trước khi đọc byte cuối (bên trong
> helper, không phải caller). Ghi chú cũ về technical debt tại đây đã được sửa
> và gỡ bỏ.

### 5.4 Giải thích chi tiết từng bước

**Bước 3 — Address frame với R/W=1:** khác write ở bit LSB = 1 thay vì 0. Target
nhận address, thấy R/W=1 → biết master muốn đọc → chuẩn bị data để gửi.

**Bước 5 — Clear ADDR (giống write):** đọc SR1 rồi SR2. Sau khi clear, target
bắt đầu shift data byte đầu tiên ra bus.

**Bước 6 — `RXNE` (Receive Not Empty, SR1 bit 6):** set khi shift register đã
nhận xong 1 byte và chuyển vào DR. Đọc `DR` tự động clear RXNE. Cho tới khi
RXNE được clear, SCL bị stretch — phần cứng giữ SCL low để target không gửi
byte kế khi phần mềm chưa đọc xong byte trước.

**Bước 7 — Chuẩn bị NACK trước byte cuối:** đây là điểm khác biệt cốt lõi giữa
read và write. Thời điểm ghi `CR1.ACK=0` phụ thuộc `Len`: tại `ADDR` với 1/2
byte, hoặc khi còn ba byte với `Len>2`. Riêng 2 byte phải kết hợp `POS=1`.

**Bước 8 — STOP trong sequence byte cuối:** Controller phải lập trình STOP khi
SCL đang được phần cứng giữ LOW theo sequence RM0090, trước khi đọc byte cuối
khỏi `DR`; không đợi đọc xong toàn bộ rồi mới quyết định STOP.

Sau transaction, driver phải restore `POS=0` và `ACK` theo
`I2CConfig.I2C_ACKControl` để transaction kế tiếp không kế thừa cấu hình receive
đặc biệt.

### 5.5 So sánh write và read

| Đặc điểm              | Write (Master Send)          | Read (Master Receive)          |
|-----------------------|------------------------------|--------------------------------|
| Bit R/W trong address | 0                            | 1                              |
| Ai gửi data           | Master → Slave               | Slave → Master                 |
| Ai gửi ACK            | Slave ACK mỗi byte           | Master ACK mỗi byte (trừ cuối) |
| Flag chờ data         | `TXE` (DR rỗng)              | `RXNE` (DR có data)            |
| Thao tác với DR       | Ghi `DR = data`              | Đọc `data = DR`                |
| Byte cuối đặc biệt    | Chờ `BTF` rồi STOP           | Tắt ACK (NACK) trước, rồi STOP |
| Xử lý ACK             | Không cần                    | Phải tắt ACK trước byte cuối   |

### 5.6 `Mem_Read` — write register rồi read data bằng Repeated START

Nhiều cảm biến yêu cầu: **ghi register address trước, rồi đọc data từ register
đó** — nhưng không được phát STOP giữa 2 phase (nếu STOP, sensor quên register
vừa ghi). Giải pháp: **Repeated Start** (Sr).

```
START | Addr + W | Register Address | Sr (Repeated START) | Addr + R | Data 1 | ... | Data N | STOP
```

Trong lý thuyết, `I2C_NO_STOP` có nghĩa là giữ quyền điều khiển bus để phát
Repeated START. Tuy nhiên, API `I2C_MasterReceiveData()` hiện tại luôn chờ
`SR2.BUSY` về 0 trước khi phát START, nên không được ghép hai API polling này
theo kiểu `MasterSendData(..., I2C_NO_STOP)` rồi `MasterReceiveData(...)`.

Đây chính là bản chất của `HAL_I2C_Mem_Read()`:

```
Address + W → Register Address → Repeated START → Address + R → Data
```

I2C peripheral không tự biết byte đầu tiên là địa chỉ thanh ghi. Driver chỉ gửi byte `REG_ADDR` như một data byte bình thường; target phải được thiết kế để hiểu byte đó là địa chỉ thanh ghi cần đọc.

### 5.7 Hàm mẫu — `I2C_MemReadData`

`I2C_MemReadData()` là hàm self-contained: tự thực hiện write phase, Repeated
START và receive phase trong cùng một hàm. Cách này giữ bus đang owned và tránh
việc gọi `I2C_MasterReceiveData()` khi `BUSY` vẫn còn set.

```c
DriverStatus_t I2C_MemReadData(i2c_driver_t *pI2CDriver,
                               uint16_t SlaveAddr,
                               uint8_t MemAddr,
                               uint8_t *pRxBuffer,
                               uint16_t Len)
{
    /* 1. START + Addr+W, sau đó clear ADDR. */
    /* 2. Gửi MemAddr, chờ TXE. */
    /* 3. Phát START lần hai khi bus vẫn đang owned. */
    /* 4. Gửi Addr+R, gọi I2C_ReceivePhase(), rồi phát STOP. */
}
```

**Ví dụ — đọc 2 byte từ register 0x28 của cảm biến:**

```c
uint8_t data[2];
I2C_MemReadData(&i2c1_handle,
                0x50,       /* SlaveAddr / DEVICE_ADDR */
                0x28,       /* MemAddr / REG_ADDR      */
                data,
                2U);
```

**Lưu ý khi implement thực tế:**

- Hàm thật trong driver là một sequence self-contained, không gọi hai hàm master polling nền.
- `MemAddr` chỉ là data byte đầu tiên của write phase; ý nghĩa "địa chỉ thanh ghi" nằm ở firmware/hardware của target.
- `I2C_MasterReceiveData()` đọc dữ liệu thô từ target hiện tại; nó không biết và không chọn register.

### 5.8 Hàm mẫu — `I2C_MemWriteData`

Ghi thanh ghi đơn giản hơn đọc thanh ghi vì không cần Repeated START. Master gửi `REG_ADDR` trước, sau đó gửi data cần ghi:

```
START | Addr + W | Register Address | Data 1 | ... | Data N | STOP
```

```c
DriverStatus_t I2C_MemWriteData(i2c_driver_t *pI2CDriver,
                                uint16_t SlaveAddr,
                                uint8_t MemAddr,
                                uint8_t *pTxBuffer,
                                uint16_t Len)
{
    /* START -> Addr+W -> clear ADDR */
    /* Gửi MemAddr như byte payload đầu tiên. */
    /* Với mỗi byte data: chờ TXE rồi ghi DR. */
    /* Chờ BTF và phát STOP. */
}
```

Ví dụ ghi 1 byte `0x80` vào register `0x20`:

```c
uint8_t value = 0x80;
I2C_MemWriteData(&i2c1_handle,
                 0x50,       /* SlaveAddr / DEVICE_ADDR */
                 0x20,       /* MemAddr / REG_ADDR      */
                 &value,
                 1U);
```

> Code thực tế gửi `MemAddr` rồi gửi từng byte data trong cùng transaction; không tạo buffer phụ.

## 5.x Bốn cặp giao dịch — controller ↔ target

Mục này đối xứng **8 API = 4 cặp** theo 2 phía controller và target. Mỗi cặp có cùng chuỗi trên bus nhưng phân tích theo từng role. Chi tiết event RM0090 cho từng vai trò xem `i2c.md` mục 4.5.

| Cặp | Controller API | Target API | Chuỗi trên bus |
|-----|----------------|------------|----------------|
| Truyền | `Master_Transmit()` | `Slave_Receive()` | `Addr + W → Data` |
| Nhận | `Master_Receive()` | `Slave_Transmit()` | `Addr + R → Data` |
| Ghi thanh ghi | `Mem_Write()` | `Slave_Mem_Write()` | `Addr + W → REG → Data` |
| Đọc thanh ghi | `Mem_Read()` | `Slave_Mem_Read()` | `Addr + W → REG → Sr → Addr + R → Data` |

> **Lưu ý:** Mục 4 và 5 đã trình bày code polling cho controller (`I2C_MasterSendData`, `I2C_MasterReceiveData`) và `I2C_MemReadData`/`I2C_MemWriteData`. Các mục 5.x dưới đây **tham chiếu** code đã có và **bổ sung skeleton code cho target side**.

### 5.x.1 Cặp truyền — `Master_Transmit()` ↔ `Slave_Receive()`

**Bus:** `S → Addr + W → Data1 → … → DataN → P`

**Controller side** (đã có ở mục 4): `I2C_MasterSendData()` — tham chiếu mục 4.1, 4.2.

**Target side** — `I2C_SlaveReceiveData()`:

```c
/**
 * @brief  Skeleton: Target nhận data thô từ controller (polling).
 * @param  pI2CDriver : handle I2C đã init
 * @param  pRxBuffer  : buffer nơi lưu data nhận được
 * @param  Len        : số byte tối đa cần nhận
 * @return STATUS_OK / STATUS_ERROR
 *
 * Event RM0090 (target receiver, Figure 242):
 *   EV1: ADDR=1 (đúng địa chỉ mình) → clear SR1+SR2
 *   EV2: RxNE=1 (lặp lại cho mỗi byte) → đọc DR
 *   EV4: STOPF=1 (controller phát STOP) → kết thúc
 *
 * Quy tắc: target KHÔNG tự quyết định dừng — phải chờ STOP từ controller.
 */
DriverStatus_t I2C_SlaveReceiveData(i2c_driver_t *pI2CDriver,
                                    uint8_t *pRxBuffer, uint16_t Len)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint16_t received = 0U;

    /* Bước 1 — chờ EV1: ADDR=1 (target được controller gọi) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET)
    {
        /* TODO: kiểm tra BERR/OVR nếu cần */
    }

    /* Bước 2 — clear ADDR: đọc SR1 rồi SR2 (bắt buộc đúng thứ tự) */
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Bước 3 — vòng lặp: chờ RxNE (EV2), đọc DR cho đến khi STOP */
    while (received < Len)
    {
        /* EV2: RxNE=1 — đã có byte trong DR */
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_RXNE) != FLAG_SET)
        {
            /* EV4: STOPF=1 — controller phát STOP, giao dịch kết thúc */
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_STOPF) == FLAG_SET)
            {
                /* Clear STOPF: đọc SR1 rồi ghi vào CR1 (theo RM0090) */
                (void)pI2Cx->SR1;
                pI2Cx->CR1 |= 0x0000U;  /* dummy write to clear STOPF */
                return STATUS_OK;
            }
        }
        pRxBuffer[received++] = (uint8_t)pI2Cx->DR;
    }

    /* Nếu đủ Len mà chưa thấy STOPF — chờ STOP bổ sung */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_STOPF) != FLAG_SET);
    (void)pI2Cx->SR1;
    pI2Cx->CR1 |= 0x0000U;  /* clear STOPF */

    return STATUS_OK;
}
```

**Interrupt target side** — skeleton:

```c
/**
 * @brief  Skeleton: Bật target mode + ngắt để nhận data từ controller.
 *
 * HAL flow: EnableListen_IT → ISR xử lý EV1/EV2/EV4 → callback RxCplt/ListenCplt.
 */
void I2C_SlaveReceiveDataIT(i2c_driver_t *pI2CDriver,
                            uint8_t *pRxBuffer, uint16_t Len)
{
    /* Lưu context vào handle */
    pI2CDriver->pRxBuffer = pRxBuffer;
    pI2CDriver->RxLen     = Len;
    pI2CDriver->RxSize    = Len;
    pI2CDriver->TxRxState = I2C_BUSY_IN_RX;

    /* Bật ngắt event (SB, ADDR, STOPF, BTF) + buffer (RXNE) + error */
    pI2Cx->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN;

    /* Bật listen mode: peripheral ACK address match → start SR1/DR */
    pI2Cx->CR2 |= I2C_CR2_ITBUFEN;
}

/* Callback trong ISR — ví dụ xử lý EV1, EV2, EV4 */
void I2C_EV_IRQHandling_SlaveRx(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint32_t sr1 = pI2Cx->SR1;

    if (sr1 & I2C_SR1_ADDR)
    {
        /* EV1 — đọc SR1 rồi SR2 để clear ADDR */
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;
        return;
    }
    if (sr1 & I2C_SR1_RXNE)
    {
        /* EV2 — đọc DR */
        if (pI2CDriver->RxLen > 0U)
        {
            *pI2CDriver->pRxBuffer++ = (uint8_t)pI2Cx->DR;
            pI2CDriver->RxLen--;
        }
        return;
    }
    if (sr1 & I2C_SR1_STOPF)
    {
        /* EV4 — controller đã STOP, kết thúc */
        (void)pI2Cx->SR1;
        pI2Cx->CR1 |= 0x0000U;
        pI2CDriver->TxRxState = I2C_READY;
        I2C_ApplicationEventCallback(pI2CDriver, I2C_EV_RX_CMPLT);
        return;
    }
}

/* Callback khi controller kết thúc (do HAL gọi sau khi xử lý ListenCplt) */
void HAL_I2C_SlaveRxCplt(I2C_HandleTypeDef *hi2c)
{
    /* Application override */
}
```

### 5.x.2 Cặp nhận — `Master_Receive()` ↔ `Slave_Transmit()`

**Bus:** `S → Addr + R → Data1 → … → DataN (NACK) → P`

**Controller side** (đã có ở mục 5): `I2C_MasterReceiveData()` — tham chiếu mục 5.2, 5.3, 5.4.

**Target side** — `I2C_SlaveTransmitData()`:

```c
/**
 * @brief  Skeleton: Target gửi data thô cho controller (polling).
 * @param  pI2CDriver : handle I2C đã init
 * @param  pTxBuffer  : buffer data cần gửi
 * @param  Len        : số byte cần gửi
 * @return STATUS_OK / STATUS_ERROR
 *
 * Event RM0090 (target transmitter, Figure 241):
 *   EV1:  ADDR=1 (đúng địa chỉ + R) → clear SR1+SR2
 *   EV3_1: TxE=1 lần đầu → nạp Data1 vào DR
 *   EV3:  TxE=1 (lặp lại) → nạp byte kế
 *   EV3_2: AF=1 — controller NACK byte cuối → dừng
 *
 * Quy tắc: target KHÔNG tự quyết định khi nào dừng — chờ NACK từ controller.
 */
DriverStatus_t I2C_SlaveTransmitData(i2c_driver_t *pI2CDriver,
                                     uint8_t *pTxBuffer, uint16_t Len)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint16_t sent = 0U;

    /* Bước 1 — chờ EV1: ADDR=1 (controller gọi + R) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET);

    /* Bước 2 — clear ADDR */
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Bước 3 — vòng lặp: nạp DR khi TxE=1 */
    while (sent < Len)
    {
        /* EV3_1 / EV3: TxE=1 — DR rỗng, sẵn sàng nhận byte mới */
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
        {
            /* EV3_2: AF=1 — controller NACK, đây là tín hiệu kết thúc */
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
            {
                /* Clear AF theo RM0090: ghi 0 vào bit AF của SR1 */
                pI2Cx->SR1 &= ~I2C_SR1_AF;
                return STATUS_OK;
            }
        }
        pI2Cx->DR = pTxBuffer[sent++];
    }

    /* Sau byte cuối — chờ AF (controller NACK) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) != FLAG_SET);
    pI2Cx->SR1 &= ~I2C_SR1_AF;

    return STATUS_OK;
}
```

**Interrupt target side** — skeleton:

```c
/**
 * @brief  Skeleton: Bật target transmit mode bằng interrupt.
 */
void I2C_SlaveTransmitDataIT(i2c_driver_t *pI2CDriver,
                             uint8_t *pTxBuffer, uint16_t Len)
{
    pI2CDriver->pTxBuffer = pTxBuffer;
    pI2CDriver->TxLen     = Len;
    pI2CDriver->TxRxState = I2C_BUSY_IN_TX;

    pI2Cx->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN;
}

/* Callback ISR */
void I2C_EV_IRQHandling_SlaveTx(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint32_t sr1 = pI2Cx->SR1;

    if (sr1 & I2C_SR1_ADDR)
    {
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;
        return;
    }
    if (sr1 & I2C_SR1_TXE)
    {
        if (pI2CDriver->TxLen > 0U)
        {
            pI2Cx->DR = *pI2CDriver->pTxBuffer++;
            pI2CDriver->TxLen--;
        }
        return;
    }
    if (sr1 & I2C_SR1_AF)
    {
        /* Controller NACK — kết thúc */
        pI2Cx->SR1 &= ~I2C_SR1_AF;
        pI2CDriver->TxRxState = I2C_READY;
        I2C_ApplicationEventCallback(pI2CDriver, I2C_EV_TX_CMPLT);
        return;
    }
}
```

### 5.x.3 Cặp ghi thanh ghi — `Mem_Write()` ↔ `Slave_Mem_Write()`

**Bus:** `S → Addr + W → REG_ADDR → Data1 → … → DataN → P`

**Controller side** (đã có ở mục 5.8): `I2C_MemWriteData()` — tham chiếu mục 5.8.

**Target side** — `I2C_SlaveMemWriteData()`:

```c
/**
 * @brief  Skeleton: Target nhận data ghi vào thanh ghi nội bộ (polling).
 * @param  pI2CDriver  : handle I2C
 * @param  RegCallback : callback application xử lý mỗi byte ghi vào thanh ghi
 *                       signature: void (*)(uint8_t regAddr, uint8_t value)
 *
 * Yêu cầu target tự quy ước: byte đầu tiên sau ADDR là REG_ADDR,
 * các byte tiếp theo là data ghi vào thanh ghi (auto-increment tuỳ IC).
 */
typedef void (*I2C_RegWriteCallback_t)(uint8_t regAddr, uint8_t value);

DriverStatus_t I2C_SlaveMemWriteData(i2c_driver_t *pI2CDriver,
                                     I2C_RegWriteCallback_t RegCallback)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint8_t currentReg = 0U;
    uint8_t byteIndex = 0U;

    /* Bước 1 — chờ EV1: ADDR=1 */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET);
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Bước 2 — chờ RxNE, đọc byte đầu tiên = REG_ADDR */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_RXNE) != FLAG_SET);
    currentReg = (uint8_t)pI2Cx->DR;
    byteIndex = 1U;  /* đã đọc 1 byte */

    /* Bước 3 — vòng lặp: đọc các byte data, gọi callback ghi vào thanh ghi */
    while (1)
    {
        /* Chờ byte tiếp theo */
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_RXNE) != FLAG_SET)
        {
            /* EV4: STOPF — controller kết thúc */
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_STOPF) == FLAG_SET)
            {
                (void)pI2Cx->SR1;
                pI2Cx->CR1 |= 0x0000U;  /* clear STOPF */
                return STATUS_OK;
            }
        }
        uint8_t value = (uint8_t)pI2Cx->DR;

        /* Gọi callback application — firmware target tự quyết định
         * cách ghi vào thanh ghi (auto-increment hay không, validate, ...) */
        RegCallback(currentReg, value);
        currentReg++;  /* auto-increment: tuỳ IC, có thể cần tắt */
        byteIndex++;
    }
}
```

### 5.x.4 Cặp đọc thanh ghi — `Mem_Read()` ↔ `Slave_Mem_Read()`

**Bus:** `S → Addr + W → REG_ADDR → Sr → Addr + R → Data1 → … → DataN (NACK) → P`

Đây là cặp phức tạp nhất: target phải **chuyển role trong cùng transaction** — phase 1 là receiver (nhận REG_ADDR), phase 2 là transmitter (phát data từ thanh ghi đó).

**Controller side** (đã có ở mục 5.7): `I2C_MemReadData()` — tham chiếu mục 5.7.

**Target side** — `I2C_SlaveMemReadData()`:

```c
/**
 * @brief  Skeleton: Target cho controller đọc thanh ghi nội bộ (polling).
 * @param  pI2CDriver  : handle I2C
 * @param  RegCallback : callback application trả về giá trị thanh ghi hiện tại
 *                       signature: uint8_t (*)(uint8_t regAddr)
 *
 * Phase 1 (target = receiver): nhận REG_ADDR, lưu vào biến nội bộ.
 * Phase 2 (target = transmitter): phát giá trị từng thanh ghi, tăng con trỏ.
 */
typedef uint8_t (*I2C_RegReadCallback_t)(uint8_t regAddr);

DriverStatus_t I2C_SlaveMemReadData(i2c_driver_t *pI2CDriver,
                                    I2C_RegReadCallback_t RegCallback)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint8_t currentReg = 0U;

    /* ========== PHASE 1: nhận REG_ADDR ========== */

    /* Chờ EV1: ADDR=1 (Addr+W) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET);
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Chờ EV2: RxNE=1, đọc REG_ADDR */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_RXNE) != FLAG_SET);
    currentReg = (uint8_t)pI2Cx->DR;

    /* Chờ Repeated START — phát hiện bằng ADDR set lần 2 (Addr+R) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET);
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* ========== PHASE 2: phát data từ thanh ghi ========== */

    while (1)
    {
        /* Gọi callback application để lấy giá trị thanh ghi */
        uint8_t value = RegCallback(currentReg);

        /* EV3_1 / EV3: chờ TxE, ghi vào DR */
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
        {
            /* EV3_2: AF=1 — controller NACK, kết thúc */
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
            {
                pI2Cx->SR1 &= ~I2C_SR1_AF;
                return STATUS_OK;
            }
        }
        pI2Cx->DR = value;
        currentReg++;  /* auto-increment: tuỳ IC */
    }
}
```

### 5.x.5 Bảng tổng hợp 4 cặp

| Cặp | Controller API | Target API | Controller event | Target event | Ai NACK byte cuối? |
|-----|----------------|------------|------------------|--------------|--------------------|
| Truyền | `Master_Transmit()` | `Slave_Receive()` | EV5, EV6, EV8_1, EV8, EV8_2 | EV1, EV2, EV4 | Không — controller STOP |
| Nhận | `Master_Receive()` | `Slave_Transmit()` | EV5, EV6, EV7, EV7_1 | EV1, EV3_1, EV3, EV3_2 | Controller (NACK byte N) |
| Ghi thanh ghi | `Mem_Write()` | `Slave_Mem_Write()` | giống `Master_Transmit()` | giống `Slave_Receive()` (có xử lý REG_ADDR) | Không — controller STOP |
| Đọc thanh ghi | `Mem_Read()` | `Slave_Mem_Read()` | phase1=transmit, phase2=receive | phase1=target RX, phase2=target TX | Controller (NACK byte N ở phase 2) |

## 6. Test cases nhỏ

Phần này ghi lại các test case nhỏ khi chạy driver thật và đối chiếu với waveform/logic analyzer. Mỗi test case nên có:

- Đoạn code test.
- Ảnh waveform.
- Kết quả decode trên bus.
- Kết luận lỗi hoặc hành vi đúng.

### Test case 1 — Master Send tới địa chỉ `0x68` nhưng nhận NACK

Đoạn code test:

```c
GPIO_Toggle_Pin(&hgpiod, GPIO_PIN_NO_13);
status1 = I2C_MasterSendData(&hi2c1,
                             (uint8_t *)"hello lucas",
                             strlen("hello lucas"),
                             0x68,
                             I2C_STOP);
delay_ms(200);
```

Waveform đo được:

![I2C test case 1 — write to 0x68 but NACK](image/image28.png)

Kết quả decode:

```
Setup Write to [0x68] + NAK
```

Ý nghĩa:

- Master đã phát START và gửi address frame với `DEVICE_ADDR = 0x68`, bit R/W = 0.
- Byte address trên bus tương ứng là `(0x68 << 1) | 0 = 0xD0`.
- Sau address byte, master nhả SDA ở clock ACK thứ 9.
- Không có target nào kéo SDA xuống LOW để ACK, nên logic analyzer decode là `NAK`.
- Vì address phase đã bị NACK, payload `"hello lucas"` không được truyền như một transaction hợp lệ.

Kết luận:

`status1` nên trả về `STATUS_ERROR` nếu driver có kiểm tra `AF` (Acknowledge Failure) đúng cách trong lúc chờ `ADDR`.

Các nguyên nhân thường gặp:

- Không có thiết bị thật ở địa chỉ `0x68` trên bus.
- Thiết bị có địa chỉ khác `0x68`.
- Dây `SCL/SDA` nối sai hoặc thiếu GND chung.
- Pull-up resistor chưa có hoặc giá trị không phù hợp.
- Target chưa được cấp nguồn hoặc chưa init chế độ I2C.
- Nhầm địa chỉ 7-bit và địa chỉ 8-bit đã shift.

Điểm cần nhớ:

`0x68` trong API driver đang là **địa chỉ 7-bit**. Driver sẽ tự shift trái và ghép bit R/W:

```c
pI2Cx->DR = (uint8_t)((SlaveAddr << 1U) | I2C_WRITE);
```

Vì vậy không truyền `0xD0` vào tham số `SlaveAddr` nếu driver đang expect địa chỉ 7-bit.

## 7. Interrupt mode — truyền nhận không blocking

Các hàm polling như `I2C_MasterSendData()` và `I2C_MasterReceiveData()` giữ CPU trong vòng `while` để chờ từng flag (`SB`, `ADDR`, `TXE`, `RXNE`, `BTF`). Cách này dễ hiểu nhưng CPU bị kẹt trong transaction.

Phần dưới đây là **thiết kế lý thuyết** cho interrupt mode. Trong repo hiện tại,
I2C interrupt chưa có implementation hoàn chỉnh; tài liệu này mô tả luồng chuẩn
để dùng khi triển khai sau này.

Đặc tả triển khai chuẩn nằm trong [i2c_plan.md](i2c_plan.md). File đó đã chuyển
toàn bộ nội dung cần thiết của `image25`, `image26`, `image30`, `image31` thành
văn bản để model viết code không cần OCR. Nếu skeleton trong chương này thiếu
chi tiết, phải ưu tiên sequence và ràng buộc trong `i2c_plan.md`.

Interrupt mode chuyển phần chờ flag sang ISR:

```
Application gọi API non-blocking
→ Driver lưu buffer/length/state vào handle
→ Driver bật I2C interrupt
→ Hardware set flag khi có event
→ ISR xử lý từng bước truyền/nhận
→ Xong transaction thì callback báo hoàn tất
```

### 7.1 Ba nhóm ngắt của I2C

STM32F4 I2C có 3 bit enable ngắt chính trong `CR2`:

| Bit | Tên | Nhóm flag liên quan | Vai trò |
|-----|-----|---------------------|---------|
| `ITEVTEN` | Event interrupt enable | `SB`, `ADDR`, `BTF`, `STOPF` | Bật ngắt sự kiện I2C chính |
| `ITBUFEN` | Buffer interrupt enable | `TXE`, `RXNE` | Bật ngắt khi data register rỗng/có data |
| `ITERREN` | Error interrupt enable | `AF`, `BERR`, `ARLO`, `OVR`, `TIMEOUT` | Bật ngắt lỗi |

Tách ra như vậy vì không phải lúc nào cũng muốn ngắt theo từng byte. Ví dụ:

- Muốn xử lý `SB`, `ADDR`, `BTF` thì bật `ITEVTEN`.
- Muốn ISR chạy khi `TXE/RXNE` đổi trạng thái thì bật thêm `ITBUFEN`.
- Muốn bắt lỗi NACK, bus error, arbitration lost thì bật `ITERREN`.

Trong NVIC, I2C dùng hai IRQ riêng cho mỗi peripheral:

- `I2C1_EV_IRQn` / `I2C1_ER_IRQn`
- `I2C2_EV_IRQn` / `I2C2_ER_IRQn`
- `I2C3_EV_IRQn` / `I2C3_ER_IRQn`

Với Controller 7-bit phase 1, Event IRQ xử lý `SB`, `ADDR`, `TXE`, `RXNE`,
`BTF`; `STOPF` để dành cho Target mode. Error IRQ xử lý `AF`, `BERR`, `ARLO`,
`OVR`, `TIMEOUT` theo phạm vi được triển khai.

### 7.2 Các flag quan trọng trong interrupt mode

| Flag | Thanh ghi | Hướng | Ý nghĩa trong ISR |
|------|-----------|-------|-------------------|
| `SB` | `SR1` | Master TX/RX | START đã phát xong, ghi address vào `DR` |
| `ADDR` | `SR1` | Master TX/RX | Target đã ACK address, clear bằng đọc `SR1` rồi `SR2` |
| `TXE` | `SR1` | TX | `DR` rỗng, ghi byte kế tiếp |
| `RXNE` | `SR1` | RX | `DR` có byte mới, đọc vào buffer |
| `BTF` | `SR1` | Controller TX/RX | Kết thúc TX hoặc điều khiển 2/3 byte cuối của RX |
| `STOPF` | `SR1` | Target receiver | Controller đã phát STOP |
| `AF` | `SR1` | Controller TX/RX / Target TX | Controller bị NACK address/data là lỗi; Target TX nhận NACK cuối có thể là hoàn tất |

> Trong master mode, `STOPF` không dùng để báo STOP do chính master phát. `STOPF` chủ yếu dùng khi MCU là slave và master bên ngoài kết thúc transaction.

### 7.3 State cần thêm vào `i2c_driver_t`

Polling function nhận buffer và length trong stack của hàm. Interrupt function thì khác: API return ngay, nên driver phải lưu context vào handle.

Ví dụ các trường cần có:

```c
{
    I2C_TypeDef *pI2Cx;
    I2C_Config_t I2CConfig;

    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxRxState;
    uint8_t DevAddr;
    uint8_t EndPolicy;
} i2c_driver_t;
```

State cơ bản:

| State | Ý nghĩa |
|-------|---------|
| `I2C_READY` | Driver rảnh, có thể bắt đầu transaction mới |
| `I2C_BUSY_IN_TX` | Đang master transmit bằng interrupt |
| `I2C_BUSY_IN_RX` | Đang master receive bằng interrupt |

### 7.4 API non-blocking

Hai API phase 1 là `I2C_MasterSendDataIT()` và
`I2C_MasterReceiveDataIT()`. Trước khi thay đổi state, API phải validate handle,
buffer, `Len>0`, địa chỉ 7-bit và policy kết thúc. API lưu context, bật interrupt,
phát START rồi return; không polling.

Phase 1 chỉ hỗ trợ transaction kết thúc bằng `I2C_STOP`. `I2C_NO_STOP` phải bị
reject cho đến khi có chained-transaction state machine quản lý repeated START;
không được close handle về READY trong khi vẫn giữ bus.

Signature, context đầy đủ và acceptance criteria nằm trong `i2c_plan.md`.

### 7.5 Luồng ISR event cho Master Transmit

Với `I2C_BUSY_IN_TX`, ISR xử lý các flag theo thứ tự:

| Flag | Việc làm |
|------|----------|
| `SB` | Ghi `(DevAddr << 1) | 0` vào `DR` |
| `ADDR` | Clear bằng đọc `SR1` rồi `SR2` |
| `TXE` | Nếu còn data, ghi byte kế vào `DR` |
| `BTF` + `TXE` | Nếu hết data, phát STOP rồi close TX |

Nếu không có target trả lời, `AF` sẽ được xử lý ở error IRQ thay vì đi tiếp
trong event IRQ.

Event ISR nên xử lý mỗi lần một event rồi `return`. Thứ tự ưu tiên đề xuất:

```text
SB → ADDR → BTF nếu state/length xử lý được → TXE → RXNE
```

Không đọc `SR2` ở đầu ISR vì chuỗi đọc `SR1` rồi `SR2` sẽ clear `ADDR` trước
khi Controller RX kịp cấu hình `ACK/POS`. Cũng không ưu tiên `BTF` vô điều
kiện: nếu `BTF=1`, `TXE=1` và `TxLen>0`, handler phải cho `TXE` nạp byte tiếp
theo thay vì return mà không thay đổi flag.

```c
void I2C_EV_IRQHandling(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint32_t sr1 = pI2Cx->SR1;

    if ((sr1 & I2C_SR1_SB) != 0U)
    {
        I2C_HandleSB(pI2CDriver);
        return;
    }

    if ((sr1 & I2C_SR1_ADDR) != 0U)
    {
        I2C_HandleADDR(pI2CDriver);
        return;
    }

    if ((sr1 & I2C_SR1_BTF) != 0U)
    {
        if ((pI2CDriver->TxRxState == I2C_BUSY_IN_TX) &&
            (pI2CDriver->TxLen == 0U))
        {
            I2C_HandleTxBTF(pI2CDriver);
            return;
        }

        if ((pI2CDriver->TxRxState == I2C_BUSY_IN_RX) &&
            (pI2CDriver->RxLen <= 3U))
        {
            I2C_HandleRxBTF(pI2CDriver);
            return;
        }
    }

    if (((sr1 & I2C_SR1_TXE) != 0U) &&
        (pI2CDriver->TxRxState == I2C_BUSY_IN_TX))
    {
        I2C_HandleTXE(pI2CDriver);
        return;
    }

    if (((sr1 & I2C_SR1_RXNE) != 0U) &&
        (pI2CDriver->TxRxState == I2C_BUSY_IN_RX) &&
        ((pI2CDriver->RxLen == 1U) || (pI2CDriver->RxLen > 3U)))
    {
        I2C_HandleRXNE(pI2CDriver);
        return;
    }
}
```

Các helper trên là tên mô tả, chưa phải symbol hiện có. Với RX và `RxLen>3`,
`BTF` không được chặn nhánh `RXNE`; đọc một byte theo đường thường để giải phóng
pipeline. Chi tiết helper và điều kiện `ITEVTEN/ITBUFEN` nằm trong
`i2c_plan.md`.

### 7.6 Luồng ISR event cho Master Receive

Receive bằng interrupt phức tạp hơn transmit vì driver phải quyết định thời điểm
tắt ACK trước khi byte cuối được ACK/NACK trên bus. State tối thiểu cần biết:

- `RxLen`: số byte còn phải nhận.
- `RxSize`: tổng số byte ban đầu, nếu muốn phân biệt case đặc biệt.
- `pRxBuffer`: nơi lưu byte đọc từ `DR`.
- Phase 1 luôn kết thúc raw receive transaction bằng STOP.

Luồng event cơ bản:

| Flag | Việc làm |
|------|----------|
| `SB` | Ghi `(DevAddr << 1) | 1` vào `DR` |
| `ADDR` + `RxLen == 1` | `POS=0`, `ACK=0`, clear `ADDR`, lập trình STOP |
| `ADDR` + `RxLen == 2` | `ACK=0`, `POS=1`, clear `ADDR`, tắt `ITBUFEN` để đợi `BTF` |
| `ADDR` + `RxLen > 2` | `POS=0`, `ACK=1`, sau đó clear `ADDR` |
| `RXNE` + `RxLen > 3` | Đọc byte thường vào buffer; khi còn 3 byte thì đợi `BTF` |
| `RXNE` + `RxLen == 1` | Đọc byte duy nhất, restore ACK/POS và close RX |
| `BTF` + `RxLen == 3` | `ACK=0`, đọc byte N-2, tiếp tục đợi `BTF` |
| `BTF` + `RxLen == 2` | Lập trình STOP, đọc byte N-1 và N, restore ACK/POS, close RX |

Ba sequence bắt buộc:

```text
N=1: ADDR → POS=0, ACK=0 → clear ADDR → STOP → RXNE → đọc DR

N=2: ADDR → ACK=0, POS=1 → clear ADDR → tắt ITBUFEN → BTF
     → STOP → đọc DR hai lần → POS=0, restore ACK

N>2: ADDR → POS=0, ACK=1 → clear ADDR
     → RXNE khi còn >3 byte
     → còn 3 byte: BTF → ACK=0 → đọc byte N-2
     → còn 2 byte: BTF → STOP → đọc byte N-1 và N → restore ACK
```

Khi còn ba byte, không được tiếp tục đọc `DR` theo nhánh `RXNE` thông thường;
có thể disable `ITBUFEN`, giữ `ITEVTEN` và đợi `BTF`. Mọi lần clear `ADDR` của
RX chỉ được thực hiện sau khi đã cấu hình `ACK/POS` tương ứng.

Với `N=2`, cũng phải disable `ITBUFEN` sau khi clear `ADDR` để `RXNE` của byte
đầu không chen ngang sequence chờ `BTF`; hai byte chỉ được đọc tại `BTF=1`.

### 7.7 Close transaction và callback

Khi truyền xong, driver cần:

1. Tắt các bit interrupt không còn dùng.
2. Phát STOP theo policy phase 1 trước khi close transaction.
3. Với RX, restore `CR1.POS=0` và ACK theo `I2CConfig.I2C_ACKControl`.
4. Reset `TxRxState = I2C_READY` và clear context runtime.
5. Gọi callback sau khi handle đã trở về trạng thái READY.

Ví dụ callback event:

```c
typedef enum
{
    I2C_EV_TX_CMPLT,
    I2C_EV_RX_CMPLT,
    I2C_ERROR_AF,
    I2C_ERROR_BERR,
    I2C_ERROR_ARLO,
    I2C_ERROR_OVR
} I2C_AppEvent_t;

void I2C_ApplicationEventCallback(i2c_driver_t *pI2CDriver,
                                  I2C_AppEvent_t AppEvent)
{
    /* Application tự override/hook hàm này */
}
```

### 7.8 Error interrupt

Error interrupt xử lý các lỗi trong `SR1`:

| Flag lỗi | Ý nghĩa | Cách xử lý thường dùng |
|----------|---------|------------------------|
| `AF` | Controller TX/RX bị Target NACK address, hoặc TX bị NACK data | Clear `AF`, phát STOP nếu còn quyền bus, close và callback lỗi |
| `BERR` | Bus error, START/STOP sai vị trí | Clear `BERR`, STOP nếu hợp lệ, close; recovery theo policy |
| `ARLO` | Arbitration lost trong multi-controller | Clear `ARLO`, nhường bus, không tự phát STOP |
| `OVR` | Overrun/underrun do đọc/ghi DR không kịp | Đọc `SR1`, truy cập `DR` theo hướng RX/TX để clear, rồi close transaction |
| `TIMEOUT` | Hardware timeout/Tlow error | Clear và close theo policy; không đồng nhất với software timeout |

Error IRQ có thể dùng nhiều `if` độc lập để thu thập các cờ cùng set, nhưng
không được abort tất cả lỗi theo cùng một cách. Đặc biệt, `ARLO` nghĩa là
Controller đã mất quyền bus nên không được tự phát STOP. `BTF` chỉ giúp phòng
overrun/underrun bằng flow control; nó không clear trực tiếp `OVR` đã set.
`OVR` không dùng helper ghi 0 bit giống `AF/BERR/ARLO`; phải theo access sequence
`SR1` rồi `DR` của RM0090, với thao tác `DR` phù hợp hướng receiver/transmitter.

Với `BERR`, sequence thực tế nên là: clear flag, phát STOP nếu bus còn owned,
reset peripheral bằng `SWRST`, rồi init lại cấu hình. Nếu bus bị kẹt vật lý,
phải xử lý ở tầng GPIO như đã nêu ở phần `BERR` của polling mode.

Trong test case `Setup Write to [0x68] + NAK`, nếu chạy bằng interrupt mode thì lỗi tương ứng là `AF`. ISR error phải clear `AF`, đóng transaction và báo callback `I2C_ERROR_AF`.

Target mode chưa nằm trong phase triển khai đầu. Khi bổ sung Target transmitter,
`AF` do Controller receiver NACK byte cuối phải được xử lý như kết thúc bình
thường, sau đó Target chờ STOP/repeated START; không dùng semantics lỗi của
Controller transmitter cho trường hợp đó.
