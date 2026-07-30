# LIS3DSH Accelerometer Driver — STM32F407 Discovery onboard sensor

**Version: 1.0 — Ngày: 2026-07-30**

Driver cho **LIS3DSH MEMS digital output motion sensor** trên board **STM32F407 Discovery** revision mới. Board F407 Discovery không dùng LIS3DH onboard; các revision cũ có thể dùng LIS302DL, còn revision mới phổ biến dùng **LIS3DSH**.

Tài liệu ST:

- LIS3DSH datasheet: https://www.st.com/resource/en/datasheet/lis3dsh.pdf
- STM32F407 Discovery user manual: https://www.st.com/resource/en/user_manual/dm00039084.pdf

File chính:

- `Peripheral/inc/lis3dsh.h`
- `Peripheral/src/lis3dsh.c`

---

## Nhận dạng chip

Register:

```c
#define LIS3DSH_REG_WHO_AM_I    0x0FU
#define LIS3DSH_WHO_AM_I_VALUE  0x3FU
```

Đọc qua SPI:

```c
cmd = LIS3DSH_REG_WHO_AM_I | (1U << 7);
cmd = 0x0F | 0x80;
cmd = 0x8F;
```

Nếu debugger đọc được:

```c
lis3dsh_whoami == 0x3F
```

thì SPI/CS/MISO/MOSI/SCK đang giao tiếp được với LIS3DSH.

> Lưu ý: `0x33` là WHO_AM_I của **LIS3DH**, không phải LIS3DSH.

---

## Kiến trúc tách lớp

Driver LIS3DSH không gọi trực tiếp firmware driver SPI/I2C/GPIO. Application hoặc board layer cấp function pointer:

```c
typedef struct {
    DriverStatus_t (*write)(void *bus_ctx, uint8_t dev_addr, uint8_t reg,
                            const uint8_t *data, uint16_t len, uint32_t timeout_ms);

    DriverStatus_t (*read)(void *bus_ctx, uint8_t dev_addr, uint8_t reg,
                           uint8_t *data, uint16_t len, uint32_t timeout_ms);

    void (*delay_ms)(uint32_t ms);
} LIS3DSH_BusOps_t;
```

Handle chính:

```c
typedef struct {
    void             *bus_ctx;
    uint8_t           dev_addr;
    LIS3DSH_BusOps_t  bus;
    LIS3DSH_Config_t  cfg;
    uint32_t          timeout_ms;
    uint8_t           initialized;
} LIS3DSH_t;
```

Với SPI, `bus_ctx` thường là:

```c
SPI_Handle_t *
```

---

## SPI command

LIS3DSH dùng bit 7 để chọn read/write:

| Bit | Ý nghĩa |
|-----|---------|
| bit7 = 0 | Write |
| bit7 = 1 | Read |

Macro:

```c
#define LIS3DSH_SPI_READ_BIT  (1U << 7)
```

Ví dụ:

```c
WHO_AM_I reg = 0x0F
read command = 0x0F | (1U << 7) = 0x8F
```

### Multi-byte read/write

Với LIS3DSH, driver bật auto-increment bằng `CTRL_REG6.ADD_INC`:

```c
#define LIS3DSH_REG_CTRL_REG6      0x25U
#define LIS3DSH_CTRL_REG6_ADD_INC  (1U << 4)
```

Trong `LIS3DSH_Init()`:

```c
LIS3DSH_EnableAddressAutoIncrement(dev, 1U);
```

Sau đó đọc 6 byte từ `OUT_X_L`:

```c
LIS3DSH_ReadMulti(dev, LIS3DSH_REG_OUT_X_L, buf, 6U);
```

SPI command lúc đó là:

```c
0x28 | (1U << 7) = 0xA8
```

Không dùng command `0xE8` cho LIS3DSH trong driver này.

---

## Register dùng trong driver

| Register | Address | Mục đích |
|----------|---------|----------|
| `WHO_AM_I` | `0x0F` | ID chip, expected `0x3F` |
| `CTRL_REG4` | `0x20` | ODR, BDU, enable X/Y/Z |
| `CTRL_REG5` | `0x24` | Full-scale range |
| `CTRL_REG6` | `0x25` | Bật `ADD_INC` cho multi-byte |
| `STATUS` | `0x27` | trạng thái data ready/overrun |
| `OUT_X_L/H` | `0x28/0x29` | raw X |
| `OUT_Y_L/H` | `0x2A/0x2B` | raw Y |
| `OUT_Z_L/H` | `0x2C/0x2D` | raw Z |

---

## Config mặc định

```c
LIS3DSH_DefaultConfig(&cfg);
```

Default:

| Field | Giá trị |
|-------|---------|
| ODR | `LIS3DSH_ODR_100HZ` |
| Scale | `LIS3DSH_SCALE_2G` |
| Axis | X/Y/Z enabled |
| BDU | enabled |

---

## API chính

```c
void LIS3DSH_DefaultConfig(LIS3DSH_Config_t *cfg);
DriverStatus_t LIS3DSH_Init(LIS3DSH_t *dev);
DriverStatus_t LIS3DSH_DeInit(LIS3DSH_t *dev);
DriverStatus_t LIS3DSH_CheckDeviceId(LIS3DSH_t *dev);

DriverStatus_t LIS3DSH_ReadReg(LIS3DSH_t *dev, uint8_t reg, uint8_t *value);
DriverStatus_t LIS3DSH_WriteReg(LIS3DSH_t *dev, uint8_t reg, uint8_t value);
DriverStatus_t LIS3DSH_ReadMulti(LIS3DSH_t *dev, uint8_t start_reg, uint8_t *buf, uint16_t len);
DriverStatus_t LIS3DSH_WriteMulti(LIS3DSH_t *dev, uint8_t start_reg, const uint8_t *buf, uint16_t len);

DriverStatus_t LIS3DSH_SetODR(LIS3DSH_t *dev, LIS3DSH_ODR_t odr);
DriverStatus_t LIS3DSH_SetScale(LIS3DSH_t *dev, LIS3DSH_Scale_t scale);
DriverStatus_t LIS3DSH_SetAxes(LIS3DSH_t *dev, uint8_t axes_enable);
DriverStatus_t LIS3DSH_EnableAddressAutoIncrement(LIS3DSH_t *dev, uint8_t enable);
DriverStatus_t LIS3DSH_EnableBlockDataUpdate(LIS3DSH_t *dev, uint8_t enable);

DriverStatus_t LIS3DSH_ReadStatus(LIS3DSH_t *dev, uint8_t *status);
DriverStatus_t LIS3DSH_ReadRaw(LIS3DSH_t *dev, LIS3DSH_AxesRaw_t *raw);
DriverStatus_t LIS3DSH_ReadAccelerationMg(LIS3DSH_t *dev, LIS3DSH_AxesMg_t *mg);
int32_t LIS3DSH_GetSensitivityUgPerLsb(const LIS3DSH_t *dev);
```

---

## Ví dụ board adapter SPI1 PE3

`main.c` đang dùng SPI1 và CS PE3:

```c
hspi1.pSPIx = SPI1;
hspi1.CS_Port = GPIOE;
hspi1.CS_Pin = GPIO_PIN_NO_3;
```

SPI read callback:

```c
static DriverStatus_t Board_LIS3DSH_SPI_Read(void *bus_ctx,
                                             uint8_t dev_addr,
                                             uint8_t reg,
                                             uint8_t *data,
                                             uint16_t len,
                                             uint32_t timeout_ms)
{
    SPI_Handle_t *hspi = (SPI_Handle_t *)bus_ctx;
    uint8_t cmd = reg | LIS3DSH_SPI_READ_BIT;

    (void)dev_addr;

    SPI_ChipSelect(hspi, ENABLE);
    DriverStatus_t st = SPI_Transmit(hspi, &cmd, 1U, timeout_ms);
    if (st == STATUS_OK) {
        st = SPI_Receive(hspi, data, len, timeout_ms);
    }
    SPI_ChipSelect(hspi, DISABLE);

    return st;
}
```

---

## Biến global debug trong `main.c`

Không dùng UART. Xem trực tiếp bằng debugger:

```c
lis3dsh_whoami
lis3dsh_status_code
lis3dsh_last_error_step
lis3dsh_error_count
lis3dsh_sample_count

lis3dsh_x_raw
lis3dsh_y_raw
lis3dsh_z_raw

lis3dsh_x_mg
lis3dsh_y_mg
lis3dsh_z_mg

lis3dsh_last_spi_cmd
lis3dsh_last_spi_reg
lis3dsh_last_spi_len
lis3dsh_last_spi_data0
```

Expected:

```c
lis3dsh_whoami == 0x3F
lis3dsh_last_spi_cmd == 0x8F  /* khi đọc WHO_AM_I */
lis3dsh_status_code == STATUS_OK
lis3dsh_sample_count tăng liên tục
```

Khi poll raw XYZ:

```c
lis3dsh_last_spi_reg == 0x28
lis3dsh_last_spi_cmd == 0xA8
lis3dsh_last_spi_len == 6
```

---

## Debug nếu trục không đổi

1. Kiểm tra `lis3dsh_sample_count` có tăng không.
2. Kiểm tra `lis3dsh_status_code == STATUS_OK`.
3. Kiểm tra `lis3dsh_whoami == 0x3F`.
4. Kiểm tra khi đọc XYZ: `lis3dsh_last_spi_cmd == 0xA8`, không phải `0xE8`.
5. Nếu board đứng yên, giá trị sẽ chỉ dao động nhẹ. Hãy nghiêng/xoay board để thấy X/Y/Z đổi rõ.

