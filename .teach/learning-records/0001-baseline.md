# Learning Record 0001 — Baseline: đã tự viết GPIO, SPI, I2C, EXTI, NVIC, USART driver

Người học đã có driver register-level tự viết cho GPIO, RCC, USART, SPI, I2C, EXTI, NVIC (trong `Driver/Core/Src`), viết theo phong cách OOP/HAL (config struct + handle struct) và đã từng tự sửa bug như "START/STOP bit nằm ở CR1 chứ không phải CR2" và "BSRR dùng để set/reset atomic". Điều này xác lập nền tảng: không cần dạy lại khái niệm "register là gì", "config/handle struct", hay "bật clock qua RCC".

**Implications:** Bài học phải nhắm vào tầng cao hơn — phương pháp tổng quát (từ datasheet → driver), rồi ngoại vi chưa viết (Timer, DMA, CAN) và các kỹ năng khó như debug lỗi phần cứng, ngắt + DMA kết hợp, clock tree chi tiết. Tránh dạy lại cơ bản GPIO/SPI/I2C.

**Evidence:** code trong `Driver/Core/Src/*.c`, git log (fix I2C START/STOP, thêm receive/error recovery).
