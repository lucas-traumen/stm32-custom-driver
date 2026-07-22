# GPIO Driver

## Cấu trúc OOP/HAL

```c
GPIO_PinConfig_t   // Config struct - cấu hình 1 pin
GPIO_Handle_t      // Handle struct - chứa base address + config
```

### GPIO_PinConfig_t

| Field              | Ý nghĩa                        | Giá trị                                                    |
|--------------------|--------------------------------|------------------------------------------------------------|
| GPIO_PinNumber     | Số pin (0-15)                  | `GPIO_PIN_NO_0` ... `GPIO_PIN_NO_15`                       |
| GPIO_PinMode       | Chế độ pin                     | `GPIO_MODE_IN`, `OUT`, `ALTFN`, `ANALOG`, `IT_FT/RT/RFT`  |
| GPIO_PinSpeed      | Tốc độ output                  | `GPIO_SPEED_LOW`, `MEDIUM`, `FAST`, `HIGH`                 |
| GPIO_PinPuPdControl| Pull-up/Pull-down              | `GPIO_NO_PUPD`, `GPIO_PIN_PU`, `GPIO_PIN_PD`              |
| GPIO_PinOPType     | Output type                    | `GPIO_OP_TYPE_PP` (push-pull), `GPIO_OP_TYPE_OD` (open-drain) |
| GPIO_PinAltFunMode | Alternate function (AF0-AF15)  | `AF0` ... `AF15`                                           |

### GPIO_Handle_t

| Field          | Ý nghĩa                  |
|----------------|--------------------------|
| pGPIOx         | Con trỏ tới GPIO port (GPIOA, GPIOB...) |
| GPIO_PinConfig | Struct config ở trên     |

## Trình tự khởi tạo

```c
// 1. Khai báo handle
GPIO_Handle_t hgpio;

// 2. Gán port
hgpio.pGPIOx = GPIOD;

// 3. Cấu hình pin
hgpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
hgpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
hgpio.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
hgpio.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
hgpio.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

// 4. Gọi Init (tự bật clock bên trong)
GPIO_Init(&hgpio);

// 5. Nếu cần thêm pin cùng port, chỉ đổi PinNumber rồi Init lại
hgpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
GPIO_Init(&hgpio);
```

## API

| Hàm                    | Mô tả                                           |
|------------------------|--------------------------------------------------|
| `GPIO_PeriClockControl`| Bật/tắt clock cho port (được gọi tự động trong Init) |
| `GPIO_Init`            | Cấu hình pin theo handle: mode, speed, pupd, optype, altfn, interrupt |
| `GPIO_DeInit`          | Reset toàn bộ port về mặc định qua RCC reset    |
| `GPIO_Write_Pin`       | Ghi HIGH/LOW qua thanh ghi BSRR                 |
| `GPIO_Write_Port`      | Ghi giá trị 16-bit ra toàn port qua ODR         |
| `GPIO_Read_Pin`        | Đọc 1 pin từ IDR, trả về 0 hoặc 1              |
| `GPIO_Read_Port`       | Đọc toàn port từ IDR                            |
| `GPIO_Toggle_Pin`      | XOR bit tương ứng trong ODR                      |

## Interrupt mode

Khi `GPIO_PinMode` là `IT_FT`, `IT_RT`, hoặc `IT_RFT`:
1. `GPIO_Init` tự cấu hình EXTI (FTSR/RTSR)
2. Cấu hình SYSCFG_EXTICR để map port → EXTI line
3. Bật EXTI interrupt mask (IMR)
4. Sau Init, cần gọi `NVIC_ICSR()` để enable IRQ trong NVIC

## Debug tips

- Nếu pin không output: kiểm tra clock đã bật chưa → đọc `RCC->AHB1ENR`
- Nếu dùng Alternate Function mà không hoạt động: kiểm tra đúng AF number (tra datasheet Table "Alternate function mapping")
- Toggle không thấy: kiểm tra MODER đã set đúng OUTPUT (01), không phải INPUT (00)
- LED trên Discovery board: PD12 (green), PD13 (orange), PD14 (red), PD15 (blue)
