# NOTES.md — ghi chú dạy học

## Hồ sơ người học
- Học STM32F407 Discovery bare-metal qua Udemy, viết driver kiểu OOP/HAL (config + handle struct), kèm CMSIS-DSP.
- Đã tự viết driver: GPIO, RCC, USART, SPI, I2C, EXTI, NVIC. → Zone of proximal development ở ngoại vi chưa viết (Timer, DMA, CAN) và kỹ năng debug.
- Giao tiếp bằng tiếng Việt. Thích giải thích "vì sao" + hướng dẫn tự viết lại, không chỉ đưa code (xem memory `feedback_workflow-guide`).

## Sở thích dạy học (từ câu trả lời AskUserQuestion)
- Chủ đề: Driver bare-metal STM32 (hiểu sâu register + làm thứ chạy được trên board).
- Phong cách: bài nhỏ + thực hành, kết hợp học qua dự án thật. Không chỉ lý thuyết suông.

## Quy tắc khi tạo bài học
- Mỗi hàm trong driver của họ phải có doc comment; mỗi chủ đề xong phải có file markdown trong `document/` (memory `feedback_documentation-rules`).
- Build bằng CubeIDE Debug; không tự clean/rebuild khi lỗi — chỉ chỉ ra lỗi (memory `feedback_no-auto-rebuild`).
- Tiết kiệm token: trả lời ngắn, một bước nhỏ mỗi lần (memory `feedback_token-saving`).

## Lộ trình đề xuất (chưa chốt, sẽ điều chỉnh theo tiến độ)
1. [x] Phương pháp datasheet→driver (Bài 1, dùng GPIO làm ví dụ)
2. [ ] Reference bản đồ register (đã có GPIO) + glossary
3. [ ] Timer (TIM) — kế tiếp tự nhiên: dùng để tạo delay/đo tần
4. [ ] DMA kết hợp
5. [ ] Ngắt + DMA kết hợp
6. [ ] Debug lỗi phần cứng thật

## Vị trí workspace
- `.teach/` trong repo (do shell sandbox chỉ cho ghi trong cây project). Không phải `~/.claude/skills/teach/` (chỉ đọc).
- Cấu trúc: `lessons/`, `reference/`, `assets/` (style.css, quiz.js), `learning-records/`, MISSION.md, RESOURCES.md.
