# Document

Thư mục này lưu tài liệu theo từng topic/module trong quá trình học và viết driver STM32F407.

Mỗi file markdown mô tả một peripheral hoặc chủ đề DSP đang được triển khai, bao gồm:
- Lý thuyết register và dataflow
- Cách project code triển khai (handle struct, config, API)
- Ghi chú và lưu ý khi debug
- **Version & ngày thực hiện** (riêng cho tài liệu ngoại vi rời — LCD, sensor, module cắm ngoài): mỗi lần cập nhật đáng kể ghi lại version + ngày ở đầu file, kèm changelog ngắn
- **Hình ảnh**: chèn ảnh module/kết quả thực tế (chụp board, ảnh màn hình LCD...) vào mục riêng trong file, giúp đối chiếu với mô tả lý thuyết

## Cấu trúc thư mục

```
document/
├── driver/       # Driver nền: GPIO, SPI, RCC, EXTI/NVIC, I2C (register trực tiếp)
└── peripheral/   # Ngoại vi: LCD, sensor, module cắm ngoài (có thể dùng function pointer)
```

## Danh sách tài liệu hiện có

### `driver/`

| File                     | Module                | Trạng thái        |
|--------------------------|------------------------|-------------------|
| `driver/gpio.md`        | GPIO driver            | Hoàn chỉnh        |
| `driver/spi.md`         | SPI driver             | Hoàn chỉnh        |
| `driver/i2c.md`         | I2C driver             | WIP (code comment)|
| `driver/rcc.md`         | RCC / Clock macros     | Hoàn chỉnh        |
| `driver/exti_nvic.md`   | EXTI + NVIC interrupt  | Hoàn chỉnh        |

### `peripheral/`

| File                     | Module                | Trạng thái        |
|--------------------------|------------------------|-------------------|
| `peripheral/ili9486.md` | ILI9486 LCD            | Hoàn chỉnh        |
