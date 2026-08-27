# UART/USART Driver - Ke hoach trien khai

## 1. Muc tieu

Tai lieu nay la specification ban giao cho session/model trien khai code UART/USART.
Pattern theo dung convention driver hien co (SPI, I2C): handle + config struct,
blocking API truoc, interrupt API sau, callback qua bang con tro ham.

Muc tieu giai doan dau:

- Trien khai polling TX/RX cho USART bat ky (USART1..3, UART4/5, USART6).
- Ho tro 8N1 mac dinh, word length/parity/stop bits cau hinh qua config struct.
- Baud rate tinh tu PCLK thuc (RCC_GetPCLK1Freq/PCLK2Freq), ho tro OVER16 va OVER8.
- GPIO alternate function config tu dong trong Init (AF7/AF8 tuy peripheral).

Giai doan hai (interrupt):

- TX interrupt: TXEIE nap data, TCIE bao hoan tat, disable TXEIE khi het buffer.
- RX interrupt: RXNEIE nhan data; IDLEIE phat het goi bien do dai (optional).
- Error handling: PE/FE/NE/ORE — set ErrorCode, goi callback voi event ERROR.
- Callback pattern: bang con trỏ ham theo instance, trap default while(1),
  theo mau exti_driver.c (khong dung __weak function ten co dinh).

Chua nam trong pham vi:

- DMA, synchronous mode (CLK), LIN, IrDA, smartcard, half-duplex single-wire.
- Hardware flow control RTS/CTS (co the them sau qua CR3).
- printf/scanf retarget qua USART (thuoc application, khong thuoc driver).

## 2. Nguon tham chieu

- Reference manual: RM0090, USART chapter (Section 27).
- Hinh minh hoa (neu co) dat trong `document/driver/uart/image/`.
- Pattern code: `Driver/Core/Inc/spi_driver.h`, `i2c_driver.h`.
- Clock: `rcc_driver.h` — USART1/6 dung PCLK2, USART2/3 + UART4/5 dung PCLK1.

## 3. File se tao

| File | Noi dung |
|------|----------|
| `Driver/Core/Inc/usart_driver.h` | Config/handle struct, macro, prototype API |
| `Driver/Core/Src/usart_driver.c` | Implementation |
| `stm32f4xx_drivers.h` | Them `#include "usart_driver.h"` |
| `stm32f4xx_it.h/.c` | Them USARTx_IRQHandler (khi lam interrupt) |
| `irq_config.c` | Uncomment/cau hinh USART NVIC priority (slot da co san) |
| `Examples/example_usart.c` | Vong echo hoac TX demo |

## 4. Trinh tu trien khai

1. Viet header: macro config, flag, state, struct, prototype.
2. Clock control + DeInit + GpioConfig (AF7/AF8, push-pull, pull-up tuy chon).
3. BRR calculation: helper tinh USARTDIV, luu y lam tron fraction, OVER8 giu bit3=0.
4. Init: ghi CR2 (STOP) → CR1 (M, PCE, PS, OVER8, UE, TE/RE) → CR3 (flow control).
   Luu y RM0090: khong duoc thay doi M/PCE/OVER8/UE trong luc dang truyen/nhan.
5. Blocking TX: doi TXE → ghi DR; doi TC neu can. Blocking RX: doi RXNE → doc DR.
   Timeout dung vong dem nhu SPI/I2C driver hien tai.
6. Kiem thu polling: echo USART2 (PA2/PA3) voi USB-UART 115200 8N1.
7. Interrupt TX/RX + callback + error code.
8. Kiem thu interrupt: echo IT, goi bien do dài voi IDLE detection.

## 5. Diem can luu y (gotchas)

- USART1/6 tren APB2 (max 84 MHz), con lai tren APB1 (max 42 MHz) — chon PCLK
  dung khi tinh BRR.
- OVER8: chi dung khi PCLK khong du cho baud cao; fraction chi 3 bit.
- ORE co the set ngay ca khi RXNEIE=0 neu data den lien tuc; clear bang doc SR
  roi doc DR. Trong interrupt mode, doc SR truoc khi doc DR de biet co loi khong.
- USART4/5 (UART4, UART5) khong co synchronous mode va khong co smartcard;
  dung USART_TypeDef van duoc vi register layout tuong thich phan async.
- 9-bit data + parity: DR giu 9 bit; neu dung parity thi payload thuc te van 8 bit.
- Khi TX 9-bit: ghi DR 16-bit mot lan (khong ghi 2 lan vi shift register se
  nap sai).

## 6. Kiem thu

- Polling: PC terminal 115200-8-N-1, echo ky tu, kiem tra khong loi frame.
- Do baud thuc te bang logic analyzer hoac oscilloscope (dung trong 1-2%).
- Interrupt: truyen buffer 256 byte, dem so byte nhan duoc, khong mat/khung byte.
- Error: gui parity sai → ErrorCode phai set PE, callback ERROR goi 1 lan.

## 7. Task: viet li thuyet tong quat vao uart.md (giu trang thai qua cac phien)

### Quy trinh lam viec

- Nguon li thuyet: **TI SPRUGP1** — KeyStone Architecture UART User Guide, Nov 2010
  (https://www.ti.com/lit/ug/sprugp1/sprugp1.pdf). Ban PDF da luu tai
  `document/driver/uart/ref/sprugp1.pdf` (trich text: `pdftotext ref/sprugp1.pdf`).
  Chi lay **khai niem pho quat**
  (dinh nghia, protocol, frame, baud rate, flow control). KHONG lay register TI
  (RBR/THR/IER/IIR/FCR/LCR...) vi driver la STM32F4 — register STM32 nam o
  `uart_driver.md`.
- Cach lam: user doc/dan noi dung tung phan → viet ngay vao `uart.md` theo van phong
  `i2c.md` (tieng Viet, giu thuat ngu Anh, trich dan `(SPRUGP1, Ch.x)`). Phan nao
  user chua doc thi giu TODO, khong tu viet truoc.
- Sau moi phan viet xong, cap nhat bang Tien do ben duoi.

### Tien do

| Muc trong uart.md | Noi dung | Nguon | Trang thai |
|-------------------|----------|-------|------------|
| 1.1 UART la gi | Dinh nghia, serial↔parallel, interrupt system, baud generator | SPRUGP1 Preface + Ch.1 | DONE |
| 1.2 UART vs USART | Asynchronous vs synchronous | Tai lieu pho quat | DONE |
| 1.3 Dat ten USART vs UART trong cac ho MCU | STM32, NXP, TI, Renesas | Tai lieu pho quat | DONE |
| 2. UART Physical Layer | Signals, wiring, idle HIGH, start LOW, push-pull | SPRUGP1 Ch.2.2 (image3) | 2.1 + 2.2 + 2.3 + 2.4 DONE |
| 3. UART Frame Format | Start, data bits (M), parity (PCE/PS), stop bits (STOP), LSB first | Tai lieu pho quat | DONE |
| 4. Baud rate & clocking | Clock generation, BCLK, oversampling 13×/16× | SPRUGP1 Ch.2.1 (image1, image2) | 4.1 + 4.2 DONE |
| 5. Flow control | Hardware RTS/CTS (autoflow), software XON/XOFF | SPRUGP1 Ch.2.5.4 (image4, image5, image6) | 5.1 + 5.2 + 5.3 DONE |
| 6. Cac mode nang cao | HDSEL, sync, LIN, IrDA, smartcard | Tai lieu pho quat | DONE |
| 7. Driver design theory | Handle/Config, blocking/IT/DMA, callback, state, error, pitfalls | Tong hop | DONE |
| 8. Tai lieu tham khao | SPRUGP1 + RM0090 + datasheet | — | DONE |

### Noi dung F407 da chuyen sang uart_driver.md

- §1.3 cu (bang so sanh USART1/2/3/6 vs UART4/5) → uart_driver.md §9
- Cac bang "Ánh xạ STM32F4" trong §2/§3/§4/§5 → uart_driver.md §10 + §11
- §6 cu (bit name STM32 cua advanced modes) → uart_driver.md §11

### Bang anh RM0090 da them vao uart_driver.md

| Anh | Figure | Noi dung | Vi tri chèn |
|-----|--------|----------|--------------|
| image7 | 296 | USART block diagram (TDR/RDR, CR1/2/3, GTPR, baud gen, IrDA, HW flow) | §2 Register map — ngay sau gioi thieu |
| image8 | 297 | Word length programming (M=0 8-bit vs M=1 9-bit, idle frame, break frame) | §10.1 Frame config — sau dong `CR1.M` |
| image9 | 298 | Configurable stop bits (1, 1.5, 2, 0.5) | §10.1 Frame config — sau dong `STOP[1:0]` |
| image10 | 299 | TC/TXE behavior khi truyền (3 frame) | §10.5 Transmit timing (MỚI) |
| image11 | 300 | Start bit detection (OVER16/8, 3-of-3 vote) | §10.6 Receiver timing (MỚI) |
| image12 | 301 | Data sampling OVER16 (clock 8/9/10, majority vote) | §10.6 Receiver timing |
| image13 | 302 | Data sampling OVER8 (clock 4/5/6) | §10.6 Receiver timing |

### Ghi chu phien gan nhat

- Phien 2026-08-26:
  - Them image7-13 (Figure 296-302, RM0090) vao uart_driver.md voi noi dung chi tiet.
  - Cau truc uart_driver.md sau cap nhat:
    - §2 — them image7 (block diagram) ngay sau gioi thieu, truoc bang register map.
    - §10.1 — them image8 (word length) va image9 (stop bits) voi bang STOP mode.
    - Them §10.5 (Transmit timing TC/TXE) moi voi image10, gom 6 subsection:
      10.5.1 idle preamble, 10.5.2 ghi F1, 10.5.3 F2, 10.5.4 F3, 10.5.5 clear TC,
      10.5.6 pitfall.
    - Them §10.6 (Receiver timing) moi voi image11/12/13, gom 6 subsection:
      10.6.1 start bit detection, 10.6.2 OVER16 sampling, 10.6.3 OVER8 sampling,
      10.6.4 bang tong hop, 10.6.5 luu y OVER8, 10.6.6 ORE.
  - Ngon ngu: tieng Viet, giu thuat ngu Anh.
  - Trang thai hien tai: uart.md 8 section, uart_driver.md 13 section (1-11, them 10.5, 10.6),
    khong con TODO.
- Phien 2026-08-21:
  - viet lan luot §1.1, §4.1+§4.2, §2.1, §5.1+5.2+5.3, §3, §6 (lan dau).
  - User yeu cau sua: uart.md = ly thuyet chung (khong phu thuoc tai lieu cu the),
    uart_driver.md = F407-specific. Tach lai:
    - Xoa §1.3 (F407 comparison) → uart_driver.md §9.
    - Xoa cac bang STM32F4-specific trong §2/§3/§4/§5.
    - §6 (advanced modes) giu mo ta khai niem, chuyen bit name STM32 → uart_driver.md §11.
    - Them §1.3 moi: dat ten USART/UART trong cac ho MCU (STM32, NXP, TI, Renesas).
    - Them §7 moi: Driver design theory (handle/config, blocking/IT/DMA, callback,
      state machine, error handling, pitfalls).
    - uart_driver.md them §9 (instance comparison), §10 (frame/baud/flow register
      mapping), §11 (advanced modes bit names).
  - Trang thai hien tai: uart.md 8 section, uart_driver.md 11 section, khong con TODO.
