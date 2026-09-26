# STM32F407 Bare-metal Resources

## Knowledge

- [Reference Manual RM0090 (F405/407/427/437/429/439)](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
  **Nguồn chính đầu tiên.** Mô tả toàn bộ register của mọi ngoại vi. Dùng khi: tra bit/flag nào của GPIO, RCC, USART, SPI, I2C, TIM, DMA, NVIC... Đọc theo chương ngoại vi (chương 6 = GPIO/RCC, chương 27 = SPI, chương 28 = I2C...).
- [Datasheet STM32F407VG](https://www.st.com/resource/en/datasheet/dm00037051.pdf)
  Dùng khi: cần pinout, chân nào nối chức năng nào (AF), điện áp, clock tối đa, package.
- [Discovery schematic MB997-F407VGT6](https://www.st.com/resource/en/schematic_pack/mb997-f407vgt6-e01_schematic.pdf)
  Dùng khi: cần biết LED/button/cảm biến onboard nối vào chân nào, tụ/vtrở mạch ngoài.
- [User Manual UM1472 (Discovery kit)](https://www.st.com/resource/en/user_manual/um1472-discovery-kit-with-stm32f407vg-mcu-stmicroelectronics.pdf)
  Dùng khi: tổng quan board, jumper, LED, nút bấm, các ngoại vi onboard.
- [Programming Manual PM0214 (Cortex-M4)](https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)
  Dùng khi: cần hiểu core M4 — NVIC, SysTick, FPU, thứ tự interrupt, câu lệnh lõi (bit-banding, barriers...).
- [Khóa Udemy của bạn](https://www.udemy.com/)
  Nguồn chính để biết tiến độ & phong cách HAL. Dùng làm cầu nối: đối chiếu code HAL với cách viết register trực tiếp.

## Wisdom (Communities)

- [r/embedded](https://www.reddit.com/r/embedded/)
  Diễn đàn embedded lớn, có nhiều thảo luận về bare-metal STM32, debug, best practices. Dùng khi: hỏi ý kiến design, hay gặp lỗi khó không tự giải được.
- [STM32 Community (ST)](https://community.st.com/)
  Diễn đàn chính thức của ST, kỹ sư ST trả lời. Dùng khi: lỗi liên quan đặc thù phần cứng/errata của F4.
- [FastBit Embedded Brain Academy — STM32 bare-metal (YouTube)](https://www.youtube.com/@fastbit_embedded_brain_academy)
  Giải thích register trực quan. Dùng khi: cần hiểu trực giác về một ngoại vi trước khi đọc RM0090.
- [EEVblog forum](https://www.eevblog.com/forum/)
  Dùng khi: cần góc nhìn kỹ sư phần cứng về một vấn đề (nhất là power, clock, layout).

## Gaps
- Chưa có nguồn tiếng Việt uy tín đáng đưa vào; nếu bạn muốn, mình sẽ tìm thêm. Hiện ưu tiên tài liệu chính thức tiếng Anh để đúng thuật ngữ.
