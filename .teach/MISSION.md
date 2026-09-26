# Mission: Tự viết driver bare-metal STM32F407

## Why
Bạn đang học STM32F407 Discovery bare-metal qua khóa Udemy (viết driver kiểu OOP/HAL: handle struct, config struct, peripheral API, kèm CMSIS-DSP). Mục tiêu thật: không chỉ copy-paste mà **hiểu sâu từng ngoại vi ở mức register** để tự mình đọc datasheet và tự viết driver cho bất kỳ ngoại vi nào — và làm ra những thứ chạy được thật trên board Discovery.

## Success looks like
- Tự viết driver cho một ngoại vi mới (VD: Timer, DMA, CAN) **không cần mở lại driver cũ để sao chép** — chỉ dùng RM0090 + datasheet.
- Giải thích được register flow của từng ngoại vi (cấu hình, bật, truyền dữ liệu, xử lý lỗi) cho người khác.
- Có bộ driver của riêng mình chạy ổn định trên board, kèm tài liệu markdown trong `document/`.
- Khi gặp lỗi trên board, tự debug được (biết nhìn flag, error bit, NVIC priority, v.v.) thay vì hỏi.
- Kết nối DSP: lấy dữ liệu cảm biến thật qua driver tự viết, xử lý bằng CMSIS-DSP.

## Constraints
- Học theo khóa Udemy hiện tại; mỗi module mới được viết lại theo phong cách driver riêng của mình.
- Giao tiếp bằng tiếng Việt.
- Mỗi hàm phải có doc comment; mỗi chủ đề xong phải có file markdown trong `document/`.
- Tiết kiệm token: bài học ngắn, một bước nhỏ mỗi lần.
- Build bằng CubeIDE Debug; không tự clean/rebuild khi lỗi — chỉ chỉ ra lỗi.

## Out of scope
- Học lập trình C căn bản (đã biết).
- So sánh với HAL/LL phức tạp (khóa Udemy đã có HAL; ở đây chỉ giữ phong cách, không bê API HAL nguyên xi).
- Các ngoại vi không có trên board Discovery hoặc ngoài khóa (trừ khi bạn muốn thêm sau).
