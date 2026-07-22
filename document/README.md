# Document

Thư mục này lưu tài liệu theo từng topic/module trong quá trình học và viết driver STM32F407.

Mỗi file markdown mô tả một peripheral hoặc chủ đề DSP đang được triển khai, bao gồm:
- Lý thuyết register và dataflow
- Cách project code triển khai (handle struct, config, API)
- Ghi chú và lưu ý khi debug

## Danh sách tài liệu hiện có

| File             | Peripheral / Module         | Trạng thái       |
|------------------|-----------------------------|------------------|
| `gpio.md`        | GPIO driver                 | Hoàn chỉnh       |
| `spi.md`         | SPI driver                  | Hoàn chỉnh       |
| `i2c.md`         | I2C driver                  | WIP (code comment)|
| `rcc.md`         | RCC / Clock macros          | Hoàn chỉnh       |
| `exti_nvic.md`   | EXTI + NVIC interrupt       | Hoàn chỉnh       |
