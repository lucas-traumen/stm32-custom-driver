# I2C Driver

## Mục lục

1. [Các mode của I2C](#1-các-mode-của-i2c)
2. [I2C Physical Layer](#2-i2c-physical-layer)
3. [I2C Protocol](#3-i2c-protocol)
   - [3.4 Clock stretching](#34-clock-stretching)
   - [3.5 Electrical specifications & pullup resistor sizing](#35-electrical-specifications--pullup-resistor-sizing)
     - [b1) Tính tRISE → RP(max)](#b1-tính-trise--rpmax)
     - [b2) Tính tLOW / tHIGH → fSCL](#b2-tính-tlow--thigh--fscl)
4. [Communication Frames](#4-communication-frames)
5. [Nâng cao I2C](#5-nâng-cao-i2c)
   - [5.1 Reserved addresses (địa chỉ dành riêng)](#51-reserved-addresses-địa-chỉ-dành-riêng)
   - [5.2 I²C buffer (bộ đệm bus)](#52-i2c-buffer-bộ-đệm-bus)
6. [Tài liệu tham khảo](#6-tài-liệu-tham-khảo)

---

## 1. Các mode của I2C

![I2C modes](image/image1.png)

I2C hỗ trợ nhiều tốc độ truyền nhận, mỗi mode có giới hạn baud khác nhau:

| Mode                          | Tốc độ tối đa | Ghi chú                                         |
|-------------------------------|---------------|--------------------------------------------------|
| **Standard-mode (Sm)**        | 100 kbit/s    | Mode phổ thông, tương thích mọi thiết bị I2C     |
| **Fast-mode (Fm)**            | 400 kbit/s    | Tăng tốc, vẫn giữ tính tương thích ngược        |
| **Fast-mode Plus (Fm+)**      | 1 Mbit/s      | Drive mạnh hơn, cho phép line capacitance cao hơn|
| **High-speed mode (Hs)**     | 3.4 Mbit/s    | Yêu cầu electrical setup riêng, ít dùng          |
| **Ultra Fast-mode (UFm)**     | 5 Mbit/s      | Một chiều (unidirectional), không có ACK         |

### Lưu ý khi chọn mode

- **Sm / Fm / Fm+** là các mode hai chiều (bidirectional) có cơ chế ACK — **implement gần như giống nhau**, chỉ khác thông số CCR/TRISE và cấu hình `DUTY` bit trong `I2C_CCR`. Cùng dùng chung flow: START → gửi address → data → STOP.
- **UFm** truyền một chiều, không có ACK nên không an toàn bằng các mode kia — cần xử lý khác.
- **Hs-mode** cần có bộ khuếch đại/driver riêng trên bus, STM32F4 thường không dùng.
- Tốc độ thực tế phụ thuộc vào **xung clock nguồn** ( Peripheral Clock PCLK1 cho STM32F4) và **duty cycle** cấu hình trong peripheral. Chi tiết tính CCR/TRISE có trong RM0009 và sẽ có sample code riêng.

---

## 2. I2C Physical Layer

![I2C Physical Layer](image/image2.png)

> Phần này chỉ cover **I2C tiêu chuẩn**. Các biến thể đặc biệt như **SMBus**, **PMBus**, **10-bit addressing**, **Hs-mode**... sẽ để ở mục riêng sau.

### 2.1 Two-Wire Communication

I2C dùng **2 đường truyền chung** (shared bus) cho mọi thiết bị trên bus:

- **SCL** (Serial Clock) — xung nhịp, do **controller** (master) điều khiển, dùng để clock data vào/ra target.
- **SDA** (Serial Data) — đường data hai chiều, truyền config/code giữa controller và target.

Đặc điểm:

- **Half-duplex**: tại một thời điểm chỉ có 1 thiết bị (controller hoặc target) gửi data trên bus.
- **Multi-controller + multi-target**: nhiều master và nhiều slave cùng chia sẻ bus. Master bắt đầu/kết thúc giao tiếp → loại trừ bus contention. Mỗi target có một **địa chỉ (address) duy nhất** 7-bit.
- Cả 2 đường SDA + SCL đều cần **pullup resistor** lên VDD (do kết nối **open-drain**).

So với SPI (full-duplex, 4 dây: SCLK + 2 data + CS), I2C đánh đổi tốc độ/độ phức tạp để chỉ dùng 2 dây.

### 2.2 Open-Drain Connection

Cả SDA và SCL dùng kết nối **open-drain** qua transistor NMOS. Thiết bị **không thể chủ động kéo đường lên cao** — chỉ có thể **kéo low** (NMOS ON) hoặc **nhả đường** (NMOS OFF) để pullup resistor kéo lên VDD. Đây là điểm khác biệt cốt lõi so với push-pull (vừa kéo high vừa kéo low).

Trạng thái mức logic trên bus hoàn toàn do NMOS ON/OFF quyết định:

#### a) NMOS ON — kéo đường LOW

![Open-drain NMOS ON — kéo line low](image/image3.png)

Khi NMOS **ON**, transistor dẫn dòng → dòng chạy qua pullup resistor xuống GND, kéo đường SDA/SCL xuống **mức LOW**.

- Chuyển high→low **nhanh** vì NMOS chủ động kéo (active drive), xả nhanh điện tích trên bus capacitance.
- Tốc độ chuyển phụ thuộc vào **drive strength** của NMOS và **bus capacitance**.

#### b) NMOS OFF — pullup kéo đường HIGH

![Open-drain NMOS OFF — pullup kéo line high](image/image4.png)

Khi NMOS **OFF**, thiết bị ngừng kéo dòng → pullup resistor kéo đường SDA/SCL lên **VDD**.

- Chuyển low→high **chậm hơn** vì đường được kéo thụ động qua resistor, phải nạp lại bus capacitance.
- Bị giới hạn bởi **RC time constant** (R = pullup resistor, C = tổng capacitance trên bus) → đây là nguyên nhân chính giới hạn tốc độ tối đa của bus và là lý do phải tính pullup resistor cẩn thận.

#### Bảng tổng kết hai trạng thái

| Trạng thái NMOS | Mức logic | Ai kéo?                     | Tốc độ chuyển              |
|-----------------|-----------|-----------------------------|-----------------------------|
| **ON**          | LOW       | NMOS kéo xuống GND          | Nhanh (NMOS active drive)  |
| **OFF**         | HIGH      | Pullup resistor kéo lên VDD | Chậm (phụ thuộc RC bus)    |

### 2.3 Vì sao open-drain là bắt buộc

I2C có nhiều thiết bị cùng chia sẻ 1 đường (multi-controller, multi-target). Nếu dùng kết nối **push-pull** (vừa kéo high vừa kéo low chủ động) thì sẽ có nguy cơ **short-circuit** khi hai thiết bị cùng lúc kéo đường về hai mức khác nhau.

![Push-pull contention → short-circuit](image/image5.png)

Như hình minh hoạ: một thiết bị kéo đường lên **VDD** (PMOS ON), thiết bị khác kéo đường xuống **GND** (NMOS ON) cùng lúc. Kết quả là dòng chạy thẳng từ VDD qua PMOS → NMOS xuống GND, không qua pullup resistor → **ngắn mạch (contention)**, có thể làm hỏng transistor và đường bus bị kẹt ở mức không xác định.

**Open-drain giải quyết vấn đề này** bằng cách **chỉ cho phép kéo low hoặc nhả** (không bao giờ kéo high chủ động):

- Mức HIGH: tất cả thiết bị đều nhả (NMOS OFF) → pullup resistor kéo đường lên VDD.
- Mức LOW: chỉ cần **một** thiết bị kéo low (NMOS ON) → đường bị kéo low.

Đây chính là logic **wired-AND**: đường chỉ HIGH khi **tất cả** thiết bị đều OFF; chỉ cần 1 thiết bị ON là cả đường bị LOW. Không bao giờ có tình trạng hai thiết bị đánh nhau, vì không ai "ép" đường lên high — chỉ có pullup resistor thụ động.

**Tradeoff**: vì rise time (low→high) phải đi qua pullup + bus capacitance → bị giới hạn bởi **RC time constant** → đây là lý do pullup resistor phải tính cẩn thận:
- Quá lớn → rise chậm → vi phạm spec tốc độ mode.
- Quá nhỏ → dòng qua NMOS khi ON quá cao → tiêu tốn điện + vi phạm spec mức LOW.

---

## 3. I2C Protocol

### 3.1 START and STOP condition

![I2C START and STOP](image/image6.png)

START và STOP là 2 điều kiện đặc biệt do **controller** (master) tạo ra để **chiếm bus** (START) và **nhả bus** (STOP). Chúng không phải là bit data mà là **sự thay đổi SDA trong khi SCL đang HIGH** — điều mà data bit thông thường không bao giờ làm. Controller nhận biết START hay STOP dựa vào **hướng chuyển của SDA** trong khoảng SCL HIGH đó:

| Điều kiện | SDA đổi khi SCL HIGH | Ý nghĩa           |
|-----------|----------------------|-------------------|
| **START** | High → Low           | Chiếm bus, bắt đầu|
| **STOP**  | Low → High           | Nhả bus, kết thúc |

**START condition** (controller chiếm bus):
1. Bus idle: cả SDA và SCL đều HIGH.
2. Controller kéo **SDA xuống LOW** trước.
3. Sau đó kéo **SCL xuống LOW**.
→ Khoảng chuyển high→low của SDA khi SCL đang HIGH = START. Sau đó SCL kéo low để bắt đầu clock bit đầu tiên, ép các controller khác phải giữ giao tiếp (bus đã bị chiếm).

**STOP condition** (controller nhả bus):
1. Controller nhả **SCL lên HIGH** trước.
2. Sau đó nhả **SDA lên HIGH**.
→ Khoảng chuyển low→high của SDA khi SCL đang HIGH = STOP. Bus trở về idle (cả 2 đường HIGH).

### 3.2 Logical Ones and Zeros

![I2C Digital One and Zero](image/image7.png)

I2C truyền data theo bit, dùng SDA làm đường data và SCL làm xung clock định thời bit:

- **Logical 1**: controller **nhả SDA** (NMOS OFF) → pullup resistor kéo đường lên mức HIGH.
- **Logical 0**: controller **kéo SDA xuống** (NMOS ON) → đường ở mức LOW gần GND.

**Khi nào lấy mẫu (sample) / khi nào đổi SDA:**

- Data được **lấy mẫu tại cạnh lên của SCL** (rising edge), và giá trị SDA **phải giữ nguyên** từ cạnh lên đến cạnh xuống của SCL trong cùng một bit.
- SDA **chỉ được phép đổi khi SCL đang LOW** để chuẩn bị bit kế tiếp.
- Nếu SDA **đổi khi SCL đang HIGH** → đây không phải data bit, mà là **điều kiện điều khiển** (START hoặc STOP — xem 3.1).

> Quy tắc nhớ: **SCL HIGH = SDA phải đứng yên** (lúc này mới lấy mẫu data); **SCL LOW = SDA được đổi** (chuẩn bị bit tiếp theo). Phá quy tắc = phát START/STOP.

### 3.3 Bus arbitration — tranh chấp giữa 2 controller

I2C cho phép **nhiều controller** cùng nằm trên bus. Khi 2 controller cùng muốn chiếm bus cùng lúc, phải có cơ chế phân giải mà không làm hỏng giao tiếp. Nhờ **open-drain + wired-AND** (đã nói ở 2.3), I2C giải quyết được bằng **clock synchronization** + **arbitration**.

#### a) Tổng quan tranh chấp bus

![I2C Bus Contention With Multiple Controllers](image/image8.png)

Khi 2 controller cùng cố chiếm bus, cần cơ chế phân giải mà không làm gián đoạn giao tiếp. I2C dùng wired-AND của SDA và SCL (do open-drain) để đồng bộ và phân giải.

#### b) Clock synchronization (đồng bộ xung)

SCL cũng là open-drain → **wired-AND**: SCL chỉ HIGH khi **tất cả** controller đều nhả, và bị LOW ngay khi **một** controller kéo low.

| Controller 1 SCL | Controller 2 SCL | SCL bus (wired-AND) |
|-------------------|-------------------|----------------------|
| 0                 | 0                 | 0                    |
| 0                 | 1                 | 0                    |
| 1                 | 0                 | 0                    |
| 1                 | 1                 | 1                    |

![Clock Sync — SCL Going Low](image/image9.png)

Khi 2 controller cùng phát START, controller nào kéo SCL low **trước** sẽ ép cả bus low ngay lập tức (wired-AND). Controller còn lại phát hiện SCL đã low sớm hơn dự kiến → biết có controller khác.

![Clock Sync — SCL Returning High](image/image10.png)

Khi nhả, controller nào giữ SCL low **lâu hơn** sẽ quyết định khi nào bus mới lên high. Mỗi controller phải **monitor SCL thực tế** và chỉ tiếp tục khi SCL thật sự lên high → đồng bộ nhịp clock.

![Clock Sync — Monitoring SCL](image/image11.png)

Controller phải tiếp tục theo dõi SCL: nếu SCL thực tế khác với mức mình mong đợi → phải điều chỉnh. Chu kỳ low = controller có low-period dài nhất; chu kỳ high = controller có high-period ngắn nhất.

![Clock Sync — Resulting Wired-AND SCL](image/image12.png)

Kết quả: chu kỳ SCL tổng hợp là "union" của các chu kỳ controller — chậm hơn hoặc bằng mỗi controller đơn lẻ. Clock sync tiếp tục qua mọi chu kỳ cho đến khi một controller thắng arbitration.

#### c) Arbitration trên SDA

![I2C Controller Arbitration](image/image13.png)

Sau khi SCL đã đồng bộ, cả 2 controller truyền data song song trên SDA. SDA cũng là wired-AND → nếu một controller gửi **0** và controller kia gửi **1** cùng lúc, bus sẽ là **0** (0 "thắng").

- Cả 2 controller đều **monitor SDA** trong khi truyền.
- Khi một controller phát ra **1** nhưng đọc lại thấy SDA đang **0** → biết là có controller khác đang gửi 0 → controller gửi 1 **thua arbitration**, phải **nhả bus** (ngừng truyền) để không phá giao tiếp.
- Controller gửi 0 tiếp tục truyền bình thường, target không thấy gián đoạn.

Arbitration chỉ kết thúc khi các controller gửi data khác nhau; nếu chúng gửi cùng byte hệt nhau thì không phát sinh tranh chấp và sẽ tiếp tục cho đến khi khác bit. Trong hệ thống chỉ có **1 controller** (như đa số ứng dụng STM32 đơn giản) thì cơ chế này không bao giờ kích hoạt.

### 3.4 Clock stretching

#### a) Clock stretching (target giữ SCL)

![I2C Target Clock Stretching](image/image14.png)

Bình thường SCL do controller điều khiển. Nhưng có những lúc target cần **chậm lại** và nó sẽ **giữ SCL ở mức low hoặc kéo SCL xuống low sớm** để ép controller phải chờ. Đây là **lần duy nhất target được điều khiển SCL**.

Theo spec I2C: **không có giới hạn thời gian** target được phép kéo SCL low (các biến thể như SMBus có timeout 35 ms). Hầu hết MCU I2C peripheral (kể cả STM32F4) đều có bit cho phép/không cho phép tính năng này (vd `CLKSTRETCH` trong `I2C_CR1`).

Có 2 tình huống stretching phổ biến:

**Stretch ở chu kỳ HIGH — để xác thực data:**

Target giữ SCL ở mức **HIGH lâu hơn dự kiến** (không nhả SCL low ngay) hoặc kéo SCL xuống low sớm trước khi controller kịp tạo xung clock kế tiếp. Mục đích: cho target thêm thời gian để **xác thực data byte vừa nhận** (kiểm tra parity, viết vào register, chuẩn bị byte trả lời...) trước khi byte kế tiếp được clock ra.

→ Trong thực tế, controller không được giả định SCL sẽ nhả low ngay sau khi nó nhả high; phải **monitor SCL thực tế** và chỉ chuyển bit khi SCL thật sự đổi.

**Stretch ở chu kỳ ACK — để chờ xử lý:**

Sau khi nhận xong 8 bit data, controller nhả SDA ở clk thứ 9 để target gửi ACK. Target có thể **kéo SCL xuống low tại thời điểm ACK** và giữ low cho đến khi sẵn sàng phản hồi → ép controller phải chờ. Đây là điểm phổ biến nhất của clock stretching vì:

- Target vừa nhận address → cần thời gian để đối chiếu địa chỉ, chuẩn bị mode read/write.
- Target vừa nhận data byte → cần thời gian ghi vào register nội, hoặc chuẩn bị byte tiếp theo để gửi обратно controller.
- Nếu là ADC/DAC → cần thời gian chuyển đổi analog trước khi trả data.

> Controller phải chờ SCL thật sự lên high rồi mới tiếp tục. Nếu cố phát SCL pulse trong khi target đang giữ low → sẽ vi phạm protocol và data bị sai.

#### b) Phân tích dạng sóng với số liệu

Trích TI SBAA565: *"Khi target bắt đầu clock stretching, SCL vẫn ở low mặc dù controller đã nhả SCL. Vì target nắm clock, controller không thể tiếp tục SCL pulse cho đến khi target nhả SCL. Controller tiếp tục monitor SCL. Khi SCL thật sự lên high, controller mới đi qua ACK của target và truyền byte tiếp. Kết nối wired-AND của SCL cho thấy SCL bị kéo dài. Truyền data bị trễ do target mà không làm gián đoạn giao tiếp."*

**Khi không có clock stretching** — giả sử cấu hình danh định:

```
tLOW  = 5 µs
tHIGH = 5 µs
→ T_SCL  = tLOW + tHIGH = 10 µs
→ f_SCL  = 1 / 10 µs = 100 kHz   (đúng chuẩn Standard-mode)
```

Dạng sóng: `SCL: LOW 5 µs → HIGH 5 µs → LOW 5 µs → HIGH 5 µs ...`

> Lưu ý đơn vị: µs hoặc hàng trăm ns, không phải ns. Chu kỳ 5 ns ≈ 200 MHz, vượt xa spec I2C.

**Khi target thực hiện clock stretching** — vì open-drain, cả controller và target chỉ có 2 lựa chọn: kéo SCL low bằng NMOS, hoặc nhả để pullup kéo high. Do wired-AND:

| Controller | Target    | SCL thực tế |
|------------|-----------|-------------|
| Nhả        | Nhả       | HIGH        |
| Kéo LOW    | Nhả       | LOW         |
| Nhả        | Kéo LOW   | LOW         |
| Kéo LOW    | Kéo LOW   | LOW         |

→ Chỉ cần 1 thiết bị kéo LOW thì cả bus bị LOW.

Giả sử: `tLOW do controller = 5 µs`, `target kéo thêm = 20 µs`, `tHIGH = 5 µs`:

```
T_SCL thực tế = 5 + 20 + 5 = 30 µs
f_SCL thực tế = 1 / 30 µs ≈ 33 kHz   (chậm hơn 100 kHz danh định)
```

Target **không tạo thêm xung mới** — nó chỉ kéo dài pha LOW của cùng 1 xung. Khi controller nhả SCL nhưng target vẫn kéo LOW → SCL thực tế giữ LOW cho đến khi target mới nhả → xung clock này dài hơn bình thường, toàn bộ quá trình truyền byte bị chậm lại nhưng **không mất data** — target chỉ mượn thời gian, controller đi theo nhịp thật sự của bus.

### 3.5 Electrical specifications & pullup resistor sizing

#### a) Electrical specifications

Mỗi thiết bị I2C có spec electrical cho SDA/SCL. Bảng dưới là **ví dụ** lấy từ datasheet ADS1119 (TI) — mỗi thiết bị có datasheet riêng, nhưng các thông số chính đều tương tự vì tuân theo cùng I2C spec.

![Electrical characteristics — ví dụ ADS1119](image/image15.png)

| Thông số | Ý nghĩa                                   | Standard-mode | Fast-mode | Fast-mode+ | Đơn vị |
|----------|--------------------------------------------|---------------|-----------|------------|--------|
| `fSCL`   | Tần số SCL                                 | 0–100         | 0–400     | 0–1000     | kHz    |
| `tr`     | Rise time (cả SDA và SCL)                  | 1000          | 300       | 120        | ns     |
| `Cb`     | Tải điện dung tối đa mỗi đường bus        | 400            | 400       | 550        | pF     |
| `VIL`    | Mức vào LOW (max)                          | 0.3×VCC       | 0.3×VCC   | 0.3×VCC    | V      |
| `VIH`    | Mức vào HIGH (min)                         | 0.7×VCC       | 0.7×VCC   | 0.7×VCC    | V      |
| `VOL`    | Mức ra LOW (max, IOL=3 mA)                 | 0.4           | 0.4       | 0.4        | V      |

→ Spec này là cơ sở để tính pullup resistor (xem 3.5-b dưới) và chọn mode phù hợp với peripheral clock (PCLK1) của MCU.

#### a1) Phân tích thông số — ý nghĩa thực tế

Bảng spec electrical là **giới hạn tối đa/tối thiểu** của protocol, không phải giá trị dùng thực tế. Khi thiết kế board, cần hiểu rõ ý nghĩa từng thông số để chọn RP phù hợp:

**`fSCL`** — tần số danh định của mode. Đây là **tốc độ tối đa** mà mode cho phép, không phải tốc độ bắt buộc. Có thể chạy Standard-mode ở 50 kHz nếu muốn — chỉ cần đảm bảo timing không vi phạm spec.

**`tr` (rise time)** — thời gian chuyển low→high tối đa cho phép. Đây là spec "hard limit": nếu rise time thực tế > `tr` max → vi phạm protocol, data có thể bị sai. Rise time phụ thuộc vào **RP × Cb** (xem 3.5-b1).

**`Cb` (bus capacitance)** — đây là thông số **khó nắm bắt nhất** trong thực tế:

- `Cb` trong spec là **giới hạn tối đa** cho phép (400 pF Standard/Fast, 550 pF Fm+).
- `Cb` thực tế = tổng điện dung ký sinh của mọi thứ trên bus: pin của MCU + pin của mỗi target + điện dung trace trên PCB + điện dung connector.
- **Nếu thiết kế board PCB riêng**: có thể tính/tương đối biết Cb (datasheet thiết bị ghi pin capacitance ~10 pF, trace phụ thuộc độ dài ~1 pF/cm...). → tính được RP(max) chính xác.
- **Nếu dùng module rời** (LCD, sensor breakout cắm qua dây jump): Cb thực tế **rất khó biết chính xác** — phụ thuộc chiều dài dây, loại dây, connector, số thiết bị cắm. Thường không có datasheet ghi rõ. → thường phải **đo bằng LCR meter** để có giá trị Cb thực tế, hoặc **thử giá trị RP rồi kiểm sóng thực tế bằng oscilloscope** xem rise time có đạt spec không.

**`VIL` / `VIH` / `VOL`** — ngưỡng mức logic, phụ thuộc VCC. Đây là cơ sở cho công thức RP(min) (xem 3.5-b2) — nếu RP quá nhỏ, dòng qua NMOS quá lớn → VOL bị kéo cao quá 0.4 V → vi phạm spec mức LOW → thiết bị khác hiểu nhầm là HIGH.

→ Hệ quả cho thực tế: với board PCB tính kỹ, RP(max) có thể tính chính xác. Với module rời, thường chọn RP **theo khuyến nghị** (4.7 kΩ hoặc 10 kΩ phổ thông), sau đó verify bằng sóng nếu tốc độ cao.

#### b) Tính toán timing

![Factors affecting pullup resistor sizing](image/image16.png)

Các đại lượng cần tính khi thiết kế I2C:

- **tRISE** (rise time) → xác định **RP(max)** — không được để rise time quá chậm.
- **RP(min)** → giới hạn dưới từ VOL/IOL — không được nhỏ quá.
- **tLOW / tHIGH** (chu kỳ SCL) → xác định **fSCL** — không được để tần số quá spec.

#### b1) Tính tRISE → RP(max)

Khi NMOS OFF, điện áp trên bus nạp theo:
```
V(t) = (1 − e^(−t/RC)) × VCC
```

Rise time = thời gian V đi từ **0.3×VCC** (ngưỡng VIL max) → **0.7×VCC** (ngưỡng VIH min). Đây là 2 ngưỡng logic trong spec electrical (xem bảng 3.5-a).

![Maximum pullup resistance based on exponential voltage settling](image/image18.png)

Giải mã phương trình nạp RC:

```
Tại V = 0.3×VCC:  0.3 = 1 − e^(−t1/RC)  →  t1 = −RC × ln(0.7)
Tại V = 0.7×VCC:  0.7 = 1 − e^(−t2/RC)  →  t2 = −RC × ln(0.3)

→ tRISE = t2 − t1 = RC × [ln(0.7) − ln(0.3)] = RC × ln(0.7/0.3) = RC × ln(2.333)
        ≈ RC × 0.8473
```

→ **tRISE = 0.8473 × RP × Cb** → **RP(max) = tRISE / (0.8473 × Cb)**

Bảng giá trị RP(max) cho từng mode (với Cb = 400 pF):

| Mode            | tRISE max (ns) | RP(max) (kΩ) |
|-----------------|----------------|--------------|
| Standard-mode   | 1000           | 2.95         |
| Fast-mode       | 300            | 0.88         |
| Fast-mode Plus  | 120            | 0.35         |

→ Mode càng cao, tRISE max càng nhỏ → RP(max) càng thấp → dòng qua pullup phải mạnh hơn. Cb thực tế càng cao → RP(max) càng thấp. **Nếu có đo Cb bằng LCR meter → dùng Cb thực tế** thay vì 400 pF của spec.

#### b2) Tính RP(min)

Khi NMOS ON, pin kéo về GND — dòng tải hút từ nguồn qua pullup:

![Current path when NMOS pulls the line LOW](image/image19.png)

Điện áp rơi trên RP phải đủ nhỏ để pin đạt **≤ VOL** (mức thấp hợp lệ). Dòng càng mạnh thì điện áp rơi trên RP càng lớn → RP càng nhỏ thì càng khó giữ pin dưới VOL:

```
RP(min) = (VCC − VOL) / IOL
```

Trong đó:
- **VCC** — điện áp nguồn pullup.
- **VOL** — điện áp thấp tối đa khi chốt mức LOW (tra datasheet, chuẩn I2C quy 0.4 V).
- **IOL** — dòng sink tối đa mà NMOS hút về GND trong khi vẫn giữ pin ≤ VOL (chuẩn I2C quy 3 mA cho Standard/Fast-mode).

→ RP phải **≥ RP(min)**: nhỏ hơn nữa thì mạch không kéo được xuống VOL, ngưỡng logic 0 không hợp lệ và NMOS vượt khả năng dòng sink (nóng/hỏng).

Với mạch ví dụ STM32F4 (VCC = 3.3 V):

```
RP(min) = (3.3 − 0.4) / 3 mA = 0.967 kΩ = 967 Ω
```

→ Kết hợp b1: **967 Ω ≤ RP ≤ 2.95 kΩ** (Standard-mode, Cb = 400 pF). Chọn giữa khoảng này theo cân bằng: gần RP(min) → rise nhanh nhưng dòng đứng (VCC/RP) lớn; gần RP(max) → tiết kiệm dòng nhưng rise chậm, dễ bị nhiễu.

#### b3) Tính tLOW / tHIGH → fSCL

Chu kỳ SCL chia làm 2 pha:
```
T_SCL = tLOW + tHIGH
fSCL = 1 / T_SCL
```

Spec I2C yêu cầu:

| Mode            | tLOW min (µs) | tHIGH min (µs) | T_SCL min (µs) | fSCL max (kHz) |
|-----------------|---------------|----------------|-----------------|-----------------|
| Standard-mode   | 4.7           | 4.0            | 8.7             | ~115 (cap 100) |
| Fast-mode       | 1.3           | 0.6            | 1.9             | ~526 (cap 400) |
| Fast-mode Plus  | 0.5           | 0.26           | 0.76            | ~1316 (cap 1000)|

→ Tổng tLOW + tHIGH min < T_SCL của fSCL max → có "biên độ" cho tRISE + tLOW/thIGH thêm dư. Nhưng nếu tRISE quá lớn → ăn vào tHIGH → vi phạm tHIGH min.

**Trong STM32F4**, tLOW/tHIGH được tính từ **PCLK1** (xung clock APB1 cấp cho I2C peripheral) và **CCR** (thanh ghi `I2C_CCR`):

- **Standard-mode** (CCR ≥ 0x01, DUTY=0):
  ```
  tLOW  ≈ CCR × (1/PCLK1)
  tHIGH ≈ CCR × (1/PCLK1)
  → tỷ lệ 1:1
  ```
- **Fast-mode, DUTY=0**:
  ```
  tLOW  ≈ 2 × CCR × (1/PCLK1)   → tỷ lệ 2:1
  tHIGH ≈ 1 × CCR × (1/PCLK1)
  ```
- **Fast-mode, DUTY=1** (duty cycle 16/9):
  ```
  tLOW:tHIGH = 16:9
  ```

→ CCR càng cao → T_SCL càng dài → fSCL càng thấp. Phải chọn CCR sao cho fSCL ≤ spec mode.

#### b4) Tổng kết logic chọn RP

```
Cb (đo bằng LCR meter hoặc ước lượng)
   ↓
RP(max) = tRISE_max / (0.8473 × Cb)     ← không được vượt quá
RP(min) = (VCC − VOL) / IOL             ← không được nhỏ quá
   ↓
Chọn RP trong khoảng [RP(min), RP(max)]
   ↓
Verify thực tế: đo tRISE bằng oscilloscope
   ↓
Tính CCR:
    CCR = PCLK1 / (2 × fSCL)      (Standard)
    CCR = PCLK1 / (3 × fSCL)      (Fast, DUTY=0)
    CCR = PCLK1 / (25 × fSCL)     (Fast, DUTY=1)
    ↓

tLOW/tHIGH do CCR quyết định → fSCL ≤ spec mode
```

→ **Khoảng pullup hợp lệ cho Standard-mode, Cb=400 pF: 967 Ω ≤ RP ≤ 2.95 kΩ**. Cb thấp hơn thì RP max cao hơn (ít dòng tiêu tốn hơn).

> **Lưu ý (dạng sóng vs lập trình thực tế):** Phần dạng sóng ở 3.1–3.5 là góc nhìn electrical của protocol. Khi dùng MCU có hardware I2C peripheral (như STM32F4), ta **không tự toggle SDA/SCL** — hardware lo toàn bộ timing, sampling, arbitration, clock stretching. Pullup resistor là phần **board hardware** — phải tính trước, không flash firmware được. Chi tiết thanh ghi/flag và sample code sẽ ở file riêng.

---

## 4. Communication Frames

### 4.1 Cấu trúc frame

I2C chia data thành các **frame**. Một giao tiếp cơ bản gồm:

```
START | Address frame (7-bit addr + R/W + ACK) | Data frame(s) (8-bit data + ACK) | STOP
```

Có 2 loại frame chính:

- **Address frame** — frame đầu tiên sau START, chứa 7-bit địa chỉ target + 1 bit R/W.
- **Data frame** — các frame kế tiếp, mỗi frame 1 byte data + 1 bit ACK.

### 4.2 Address frame (7-bit + R/W + ACK)

Mỗi target có 1 địa chỉ 7-bit duy nhất → 128 địa chỉ (nhưng có reserved, thực tế ít hơn). Address frame gồm 9 bit:

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| A6    | A5    | A4    | A3    | A2    | A1    | A0    | R/W   |

- 7 bit cao (A6:A0) = địa chỉ target.
- Bit thấp nhất = R/W: `1` = Read, `0` = Write.
- Sau 8 bit, controller **nhả SDA** ở clk thứ 9 để target kéo SDA xuống = **ACK** (xác nhận địa chỉ đúng). Nếu không có target nào ACK → bit ở mức HIGH = **NACK** → controller phát STOP.

### 4.3 Data frame (8-bit + ACK)

Sau address frame là 1 hoặc nhiều data frame:

- Mỗi data frame = **8 bit data** (MSB trước) + 1 bit ACK ở clk thứ 9.
- **Write**: target kéo SDA low để ACK mỗi byte nhận được.
- **Read**: controller kéo SDA low để ACK mỗi byte nhận được. Controller gửi **NACK** ở byte cuối cùng để báo "đủ rồi, ngừng gửi đi" → sau đó controller phát STOP.

### 4.4 Hai loại địa chỉ khi lập trình I2C

Khi viết driver hoặc dùng HAL, cần phân biệt rõ **hai loại địa chỉ khác nhau**:

| Loại địa chỉ | Tên trong code | Nằm ở đâu | Ý nghĩa |
|--------------|----------------|-----------|---------|
| Địa chỉ Target/Slave trên bus | `DEVICE_ADDR`, `SlaveAddr` | Address frame | Chọn đúng thiết bị I2C trên bus |
| Địa chỉ thanh ghi bên trong Target | `REG_ADDR`, `MemAddr` | Data frame | Chọn thanh ghi nội bộ của target |

Ví dụ STM32 muốn giao tiếp với cảm biến có địa chỉ `0x68` và đọc thanh ghi `WHO_AM_I = 0x0F`:

```
DEVICE_ADDR = 0x68    // địa chỉ thiết bị trên bus I2C
REG_ADDR    = 0x0F    // địa chỉ thanh ghi bên trong cảm biến
```

I2C hardware chỉ hiểu address frame để chọn target. Nó **không tự biết** byte `0x0F` có phải địa chỉ thanh ghi hay không. Byte đó chỉ có ý nghĩa là `REG_ADDR` nếu firmware/hardware của target được thiết kế để hiểu như vậy.

### 4.5 Bốn kiểu giao dịch phổ biến

Từ hai loại địa chỉ trên, có thể chia API I2C thành 4 kiểu chính:

| Hàm kiểu HAL | Chuỗi truyền trên bus | Ý nghĩa |
|--------------|-----------------------|---------|
| `Master_Transmit()` | `Address + W → Data` | Gửi dữ liệu thô tới target |
| `Master_Receive()` | `Address + R → Data` | Nhận dữ liệu thô từ target |
| `Mem_Write()` | `Address + W → Register → Data` | Ghi dữ liệu vào thanh ghi nội bộ của target |
| `Mem_Read()` | `Address + W → Register → Repeated START → Address + R → Data` | Đọc dữ liệu từ thanh ghi nội bộ của target |

**STM32 giao tiếp STM32:** nếu hai MCU chỉ trao đổi buffer thô, không có bản đồ thanh ghi, dùng `Master_Transmit()` và `Master_Receive()` là đúng. Master chọn đúng target bằng `DEVICE_ADDR`, sau đó data chỉ là buffer do hai firmware tự quy ước.

**STM32 đọc cảm biến/EEPROM/register map:** nếu target có bản đồ thanh ghi, dùng `Mem_Write()` hoặc `Mem_Read()`. Ví dụ đọc register `0x05` cần chuỗi:

```
START
→ Address + Write
→ 0x05
→ REPEATED START
→ Address + Read
→ Data
→ STOP
```

Kết luận ngắn:

| Nhu cầu | API phù hợp |
|---------|-------------|
| Đọc dữ liệu thô từ target | `Master_Receive()` |
| Đọc thanh ghi cụ thể bên trong target | `Mem_Read()` |

`Master_Receive()` có thể chọn đúng target bằng `DEVICE_ADDR`, nhưng **không tự chọn được thanh ghi bên trong target**. Muốn chọn thanh ghi, phải gửi thêm `REG_ADDR` trước phase read, thường bằng Repeated START.

Các sự kiện EV trong RM0009 như EV5, EV6, EV7, EV8, EV9 chỉ mô tả trạng thái phần cứng I2C. Chúng không quyết định byte data có phải địa chỉ thanh ghi hay không.

![I²C — GHI MỘT BYTE](image/image20.png)

![I²C — GHI NHIỀU BYTE](image/image21.png)

![I²C — ĐỌC MỘT BYTE](image/image22.png)

![I²C — ĐỌC NHI��U BYTE](image/image23.png)

![I²C — GHI RỒI ĐỌC TRONG CÙNG TRANSACTION](image/image24.png)

![I²C — GHI MỘT BYTE](image/image20.png)

![I²C — GHI NHIỀU BYTE](image/image21.png)

![I²C — ĐỌC MỘT BYTE](image/image22.png)

![I²C — ĐỌC NHIỀU BYTE](image/image23.png)

![I²C — GHI RỒI ĐỌC TRONG CÙNG TRANSACTION](image/image24.png)

### 4.6 Flow tổng quát

```
START → [address + R/W] → ACK → [data byte 1] → ACK → ... → [data byte N] → NACK/ACK → STOP
```

- Nếu muốn **read** sau khi **write** (vd: chỉ định register rồi mới đọc), controller dùng **Repeated START** (Sr) — phát START mới mà không phát STOP, trong cùng 1 giao tiếp.
- Tổng quát: có thể có nhiều data frame liên tiếp, không giới hạn số byte giữa START và STOP (chỉ giới hạn bởi timeout hoặc target NACK).

> Trong MCU có I2C peripheral (như STM32F4), address + R/W ghi vào thanh ghi data (vd `I2C_DR`) sau khi START phát xong (flag start bit set). Mỗi byte data cũng ghi/đọc qua thanh ghi data, kèm poll flag transfer-finished để chờ byte xong trước khi nạp byte kế tiếp. Sample code sẽ để ở file riêng.

---

## 5. Nâng cao I2C

### 5.1 Reserved addresses (địa chỉ dành riêng)

#### a) Vì sao không dùng được toàn bộ 0x00–0x7F

Địa chỉ I²C chuẩn là 7-bit → về mặt lý thuyết có 128 giá trị (0x00–0x7F). Tuy nhiên, spec I²C (UM10204 của NXP) **dành riêng 16 địa chỉ** ở hai đầu dải cho các mục đích đặc biệt của chính giao thức. Nếu gán nhầm các địa chỉ này cho slave thông thường, bus có thể xung đột với các tính năng chuẩn (General Call, 10-bit addressing, Hs-mode...).

Hai vùng bị dành riêng:

- **0x00–0x07** (0000 0xx – 0000 1xx)
- **0x78–0x7F** (1111 0xx – 1111 1xx)

Bảng chi tiết từng địa chỉ:

| Địa chỉ 7-bit | Mẫu nhị phân | Mục đích                                    |
|---------------|--------------|---------------------------------------------|
| 0x00          | 0000 000     | General Call hoặc START byte                |
| 0x01          | 0000 001     | Địa chỉ CBUS                                |
| 0x02          | 0000 010     | Dành cho bus format khác                    |
| 0x03          | 0000 011     | Dành cho tương lai                          |
| 0x04–0x07     | 0000 1xx     | Hs-mode master code                         |
| 0x78–0x7B     | 1111 0xx     | Tiền tố địa chỉ I²C 10-bit                  |
| 0x7C–0x7F     | 1111 1xx     | Dành cho tương lai                          |

Giải thích nhanh một số mục quan trọng:

- **General Call (0x00)**: cho phép master gửi một lệnh đến *tất cả* slave cùng lúc (broadcast), thay vì từng slave một.
- **Hs-mode master code (0x04–0x07)**: khi master muốn chuyển bus sang High-speed mode (3.4 Mbit/s), nó phát mã này sau START để báo cho toàn bus chuẩn bị đổi tốc độ. Mỗi master Hs-mode có một mã riêng → 4 địa chỉ dành cho tối đa 8 mã (0000 1000 – 0000 1111).
- **Tiền tố 10-bit (0x78–0x7B)**: với thiết bị dùng địa chỉ 10-bit, byte đầu tiên mang mẫu `1111 0xx` — 2 bit `xx` là 2 bit cao nhất của địa chỉ 10-bit, 8 bit còn lại nằm ở byte thứ hai. Đây là lý do 7-bit và 10-bit có thể tồn tại trên cùng một bus mà không nhầm lẫn.

→ Kết luận: vùng địa chỉ **an toàn** để gán cho slave thông thường là **0x08 đến 0x77** (112 địa chỉ khả dụng).

#### b) Ví dụ General Call

Master muốn reset đồng loạt mọi thiết bị trên bus:

```
START | 0000 0000 (0x00) | ACK | <command byte> | ACK | STOP
```

- Master gửi 7-bit address = `0000000` + bit W = 0.
- Byte thực tế trên bus: `00000000` = **0x00**.
- Mọi slave có bật tính năng General Call đều ACK và đọc byte lệnh tiếp theo (vd: `0x06` = reset + ghi lại địa chỉ, `0x04` = chỉ ghi lại địa chỉ...).

Ứng dụng thực tế: reset đồng bộ, nạp lại địa chỉ, hoặc gửi một lệnh chung (vd: "sleep") đến nhiều slave chỉ bằng một transaction.

#### c) Lưu ý: địa chỉ 7-bit vs byte địa chỉ trên bus

Đây là lỗi nhầm lẫn kinh điển khi đọc datasheet. Địa chỉ slave chỉ có **7 bit**; khi truyền trên bus, phần cứng ghép thêm bit R/W thành byte thứ 8:

```
Address byte = (address_7bit << 1) | R/W
```

Ví dụ với cảm biến MPU6050 (địa chỉ 7-bit 0x68):

| Thao tác | Tính toán          | Byte trên bus |
|----------|--------------------|---------------|
| Write    | 0x68 << 1          | 0xD0          |
| Read     | (0x68 << 1) \| 1   | 0xD1          |

⚠️ **Không được coi 0xD0 là địa chỉ 7-bit** — địa chỉ thật vẫn là 0x68. Một số datasheet ghi địa chỉ dạng 8-bit (đã shift sẵn), một số ghi dạng 7-bit (chưa shift); khi lập trình cần kiểm tra kỹ driver/HAL đang expect dạng nào (vd: HAL STM32 expect địa chỉ **đã shift**, tức 0xD0).

---

### 5.2 I²C buffer (bộ đệm bus)

#### a) I²C buffer là gì

I²C buffer là một IC nằm giữa hai đoạn bus, chia một bus lớn thành các đoạn nhỏ độc lập về mặt điện:

```
Master ── Bus A ── [ I²C Buffer ] ── Bus B ── Slave(s)
```

Ví dụ linh kiện: P82B96, PCA9600, PCA9515...

Chức năng chính:

- **Cách ly điện dung (capacitance isolation)**: spec I²C giới hạn tổng bus capacitance 400 pF. Buffer chia bus thành 2 đoạn, mỗi đoạn chỉ cần thoả 400 pF → tổng hệ thống được gần 800 pF → gắn được nhiều thiết bị hơn hoặc dây dài hơn.
- **Mỗi phía có pull-up riêng**: điện trở pull-up được tính độc lập theo capacitance của từng đoạn (xem lại mục 3.5).
- **Chuyển mức điện áp (level shifting)**: một số buffer cho phép Bus A chạy 3.3V, Bus B chạy 5V.
- **Tăng khả năng drive**: buffer lái dòng mạnh hơn chân IO của MCU → kéo dài cáp (P82B96 có thể đi cáp dài hàng mét).
- **Truyền LOW hai chiều**: bên nào kéo LOW thì bên kia cũng bị kéo LOW.

#### b) Nguyên lý truyền trạng thái

Buffer hoạt động hoàn toàn ở **tầng điện**, không giải mã giao thức:

**Khi phía A kéo SDA xuống LOW:**

```
SDA_A = LOW
  → buffer phát hiện mức LOW ở đầu A
  → buffer chủ động kéo SDA_B = LOW
```

**Khi phía A nhả SDA:**

```
buffer ngừng kéo SDA_B
  → pull-up phía B kéo SDA_B lên HIGH
```

Chiều ngược lại (B → A) hoạt động tương tự. Vì bản chất open-drain của I²C là "ai kéo LOW cũng được, không ai kéo thì HIGH", nên buffer chỉ cần lan truyền trạng thái LOW qua lại là đủ.

> ⚠️ Vấn đề kỹ thuật thực tế của buffer là **chống latch-up/vòng lặp**: nếu A kéo B xuống LOW, rồi B thấy LOW lại kéo A xuống → hai bên giữ nhau ở LOW mãi. Các IC buffer thật giải quyết bằng cách dùng **hai ngưỡng điện áp khác nhau** (phân biệt "LOW do bên mình kéo" và "LOW do bên kia kéo") hoặc cơ chế offset điện áp — chi tiết này thuộc thiết kế bên trong IC, ngườ dùng chỉ cần biết khi chọn linh kiện.

#### c) Buffer phải bảo toàn tính chất I²C

Một I²C buffer đúng nghĩa phải truyền trong suốt mọi cơ chế của protocol:

- Giao tiếp hai chiều (bidirectional).
- Open-drain / wired-AND.
- ACK/NACK (slave kéo SDA xuống ở bit thứ 9 phải truyền được về master).
- **Clock stretching** (slave kéo SCL xuống để bắt master chờ — SCL không còn là một chiều thuần tuý nên buffer phải hỗ trợ SCL hai chiều).
- Multi-master arbitration (nếu linh kiện hỗ trợ).

#### d) Reserved address có liên quan đến buffer không?

**Không.** Đây là điểm hay bị hiểu nhầm:

- Buffer làm việc ở tầng điện: `LOW phía A ↔ LOW phía B`.
- Nó **không đọc** byte address, **không quan tâm** địa chỉ nào đang được truyền trên bus.

Hệ quả:

- Buffer **không có địa chỉ riêng**.
- **Không chiếm** bất kỳ địa chỉ I²C nào trên bus.
- **Không giải quyết** được xung đột địa chỉ giữa các slave.

#### e) Bài toán trùng địa chỉ — buffer không cứu được

Giả sử hai cảm biến giống hệt nhau, cùng địa chỉ cố định 0x68, đặt ở hai phía của buffer:

```
Master ── Bus A ── [ Buffer ] ── Bus B ── Sensor 0x68
      └────────────────────────── Sensor 0x68 (cùng bus A)
```

Khi master gửi address 0x68, buffer truyền trong suốt sang Bus B → **cả hai sensor cùng ACK, cùng trả data đồng thồi** → data trên bus bị trộn lẫn (wired-AND) → **xung đột địa chỉ**.

#### f) Giải pháp: I²C multiplexer/switch

Muốn dùng nhiều thiết bị trùng địa chỉ, cần một IC **có địa chỉ riêng** và **chọn kênh bằng phần mềm**, vd: TCA9548A (8 kênh), PCA9548A:

```
                ┌── Kênh 0 ── Sensor 0x68
Master ── [ TCA9548A ] ── Kênh 1 ── Sensor 0x68
                └── Kênh 2 ── ...
```

Cách dùng:

1. Master ghi vào thanh ghi control của TCA9548A (địa chỉ mặc định 0x70, đổi được bằng chân A0–A2) để chọn kênh.
2. Chỉ kênh được chọn mới được nối về phía master.
3. Master giao tiếp với sensor 0x68 trên kênh đó như bình thường.
4. Muốn nói chuyện với sensor kế tiếp → đổi kênh → lặp lại.

#### g) So sánh nhanh buffer vs multiplexer

| Tiêu chí                | I²C Buffer              | I²C Multiplexer (TCA9548A)      |
|-------------------------|-------------------------|----------------------------------|
| Tầng hoạt động          | Điện (electrical)       | Protocol (đọc/ghi thanh ghi)     |
| Có địa chỉ I²C riêng    | Không                   | Có (vd 0x70)                     |
| Cách ly capacitance     | Có                      | Có (từng kênh)                   |
| Giải quyết trùng địa chỉ| Không                   | Có (chọn kênh)                   |
| Trong suốt với master   | Hoàn toàn               | Không (phải ghi lệnh chọn kênh)  |

→ Nói ngắn gọn: **buffer chỉ lo chuyện điện**, còn **multiplexer là một thiết bị I²C thật sự** có thể được lập trình để định tuyến bus.

---

## 6. Tài liệu tham khảo

- [TI SBAA565 – A Basic Guide to I2C](https://www.ti.com/lit/an/sbaa565/sbaa565.pdf) — Application note của Texas Instruments, tổng quan I2C (physical layer, protocol, examples, advanced topics).
- **ST RM0009** – *STM32F405/415, F407/417 Reference Manual*, chương I2C — mô tả thanh ghi `I2C_CR1/CR2`, `I2C_OAR1/OAR2`, `I2C_DR`, `I2C_SR1/SR2`, `I2C_CCR`, `I2C_TRISE` và timing calc cho Sm/Fm/Fm+.
