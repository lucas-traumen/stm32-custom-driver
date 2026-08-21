# I2C Interrupt Driver - Ke hoach trien khai

## 1. Muc tieu

Tai lieu nay la specification ban giao cho session/model trien khai code I2C.
Model trien khai khong can OCR cac hinh trong thu muc `image/`; cac sequence can
thiet tu RM0090 da duoc chuyen thanh noi dung chu trong file nay.

Muc tieu giai doan dau:

- Trien khai interrupt cho Controller 7-bit transmitter va receiver.
- Giu nguyen cac API polling neu khong co yeu cau sua rieng.
- Ho tro callback hoan tat TX/RX va bao loi toi thieu.
- Kiem thu truoc hai luong: Controller write va Controller read.

Chua nam trong pham vi giai doan dau:

- Target transmitter/receiver interrupt.
- Dia chi 10-bit, DMA va SMBus/PEC.
- Recovery hoan chinh cho `ARLO`, `OVR`, `TIMEOUT`.
- Software timeout va GPIO bus recovery.

## 2. Nguon tham chieu va thuat ngu

- Reference manual: STM32F405/407/415/417 RM0090, I2C chapter.
- `Controller` tuong duong thuat ngu cu `master`.
- `Target` tuong duong thuat ngu cu `slave`.
- `Transmitter` la ben gui data byte; `receiver` la ben phat ACK/NACK cho data
  byte do.
- Controller la ben tao START, repeated START va STOP trong transaction thong
  thuong.

Tai lieu giai thich driver hien tai:

- `document/driver/i2c/i2c.md`: nguyen ly bus va waveform.
- `document/driver/i2c/i2c_driver.md`: peripheral STM32F4 va driver polling.
- `Driver/Core/Inc/i2c_driver.h`: API va handle hien tai.
- `Driver/Core/Src/i2c_driver.c`: implementation polling hien tai.

## 3. Hai vai tro va bon huong truyen

Khong duoc chi chia I2C thanh TX/RX. Phai xet dong thoi vai tro tren bus va
huong data:

| Mode cua STM32 | Huong data | Sequence diagram | Cach ket thuc |
|----------------|------------|------------------|---------------|
| Controller transmitter | STM32 -> Target | `image31.png` | STM32 cho byte cuoi duoc ACK, sau do phat STOP |
| Controller receiver | Target -> STM32 | `image30.png` | STM32 NACK byte cuoi, sau do phat STOP |
| Target transmitter | STM32 -> Controller | `image25.png` | STM32 nhan NACK tu Controller, sau do nhan STOP |
| Target receiver | Controller -> STM32 | `image26.png` | STM32 ACK data va nhan STOP qua `STOPF` |

Hai cap hinh mo ta cung mot transaction nhung tu hai dau bus:

```text
Controller write: image31 (Controller TX) <-> image26 (Target RX)
Controller read : image30 (Controller RX) <-> image25 (Target TX)
```

## 4. Noi dung chu cua cac sequence diagram

### 4.1 image31 - Controller transmitter

```text
START -> Address+W -> ACK -> Data1 -> ACK -> ... -> DataN -> ACK -> STOP
```

Event:

- `EV5`: `SB=1`; clear bang doc `SR1`, sau do ghi address vao `DR`.
- `EV6`: `ADDR=1`; clear bang doc `SR1`, sau do doc `SR2`.
- `EV8_1`: `TXE=1`, shift register va data register deu rong; ghi Data1 vao
  `DR`.
- `EV8`: `TXE=1`, data register rong nhung shift register dang truyen; ghi byte
  tiep theo vao `DR`.
- `EV8_2`: `TXE=1` va `BTF=1`; Controller lap trinh STOP. STOP clear `TXE` va
  `BTF` bang hardware.

### 4.2 image30 - Controller receiver

```text
START -> Address+R -> ACK -> Data1 -> ACK -> ... -> DataN -> NACK -> STOP
```

Event:

- `EV5`: `SB=1`; clear bang doc `SR1`, sau do ghi address+R vao `DR`.
- `EV6`: `ADDR=1`; clear bang doc `SR1`, sau do doc `SR2`.
- `EV7`: `RXNE=1`; clear bang doc `DR`.
- `EV7_1`: giai doan byte cuoi, lap trinh `ACK=0` va yeu cau STOP dung sequence.

Voi reception 1 byte, `ACK=0` phai duoc lap trinh trong `EV6`, truoc khi clear
`ADDR`.

### 4.3 image25 - Target transmitter

```text
START -> Address+R -> ACK -> Data1 -> ACK -> ... -> DataN -> NACK -> STOP
```

Event:

- `EV1`: `ADDR=1`; clear bang doc `SR1`, sau do doc `SR2`.
- `EV3_1`: `TXE=1`, shift register va data register deu rong; ghi Data1 vao
  `DR`.
- `EV3`: `TXE=1`; ghi byte tiep theo vao `DR`.
- `EV3_2`: `AF=1` vi Controller receiver NACK byte cuoi.

Trong Target transmitter, `AF` tai `EV3_2` thuong la ket thuc binh thuong:
Target clear `AF`, ngung nap data, sau do cho STOP hoac repeated START tu
Controller. Target khong tu phat STOP.

### 4.4 image26 - Target receiver

```text
START -> Address+W -> ACK -> Data1 -> ACK -> ... -> DataN -> ACK -> STOP
```

Event:

- `EV1`: `ADDR=1`; clear bang doc `SR1`, sau do doc `SR2`.
- `EV2`: `RXNE=1`; clear bang doc `DR`.
- `EV4`: `STOPF=1`; clear bang doc `SR1`, sau do ghi `CR1`.

Trong transaction thanh cong, Target receiver ACK byte cuoi. Controller phat
STOP, con Target phat hien STOP bang `STOPF`.

## 5. Ownership cua ACK, NACK va STOP

ACK/NACK cua data byte do receiver phat. START/STOP do Controller phat.

| Luong | Ben gui byte cuoi | Ben phan hoi | Phan hoi | Ben phat STOP |
|-------|-------------------|--------------|----------|---------------|
| Controller TX -> Target RX | Controller | Target receiver | ACK | Controller |
| Target TX -> Controller RX | Target | Controller receiver | NACK | Controller |

NACK khong tu dong la STOP. NACK la SDA HIGH tai clock ACK thu 9; STOP la canh
SDA LOW -> HIGH khi SCL dang HIGH.

Target receiver van co the NACK address/data neu tu choi transaction. Khi do
Controller transmitter nhan `AF`, dung truyen va phat STOP. Dieu nay khac voi
`AF` o Target transmitter khi nhan NACK cuoi binh thuong tu Controller.

## 6. Trang thai code hien tai

### 6.1 Da xac nhan

- Driver hien co cac API polling Controller TX/RX va memory read/write.
- Chua co `I2C_MasterSendDataIT()`, `I2C_MasterReceiveDataIT()`.
- Chua co `I2C_EV_IRQHandling()`, `I2C_ER_IRQHandling()` va callback I2C.
- Cac I2C EV/ER IRQ trong NVIC chua duoc enable cho implementation nay.

### 6.2 Technical debt cua polling receive

Da sua (cap nhat): `I2C_ReceivePhase()` hien da tuan thu day du sequence RM0090:

- `Len == 2` set `POS=1` va `ACK=0` truoc khi clear `ADDR`.
- `Len > 2` chuyen sang sequence `BTF` khi con 3 byte.
- STOP duoc program ben trong helper truoc khi doc cac byte cuoi, theo dung thoi
  diem SCL dang bi stretch ma RM0090 yeu cau.
- `ACK` duoc restore theo config sau khi receive; `POS` duoc clear ve 0 sau case
  `Len == 2`.

Khong con technical debt nao trong polling receive. Implementation interrupt
van phai tuan thu sequence rieng trong file nay, khong sao chep nguyen ban.

## 7. Context va state can them

API interrupt return ngay, vi vay `i2c_driver_t` phai luu context transaction:

```c
uint8_t  *pTxBuffer;
uint8_t  *pRxBuffer;
uint32_t TxLen;
uint32_t RxLen;
uint32_t RxSize;
uint16_t TargetAddr;
uint32_t ErrorCode;
uint8_t  State;
uint8_t  RepeatedStart;
```

State toi thieu cua phase 1:

```text
I2C_STATE_READY
I2C_STATE_BUSY_TX
I2C_STATE_BUSY_RX
```

Ten state tren chi la de xuat. Model trien khai phai theo convention hien co
cua repo neu da co ten tuong duong.

`ErrorCode` phai reset ve `I2C_ERROR_NONE` khi bat dau transaction moi.

## 8. API non-blocking phase 1

Them hai API Controller 7-bit:

```c
DriverStatus_t I2C_MasterSendDataIT(i2c_driver_t *pDriver,
                                    uint8_t *pTxBuffer,
                                    uint32_t Len,
                                    uint16_t TargetAddr,
                                    uint8_t RepeatedStart);

DriverStatus_t I2C_MasterReceiveDataIT(i2c_driver_t *pDriver,
                                       uint8_t *pRxBuffer,
                                       uint32_t Len,
                                       uint16_t TargetAddr,
                                       uint8_t RepeatedStart);
```

API phai:

1. Validate handle, buffer, `Len > 0` va dia chi 7-bit.
2. Chi bat dau khi `State == READY`.
3. Luu buffer, length, address, repeated-start policy va reset error.
4. Set state TX hoac RX.
5. Bat `ITEVTEN`, `ITBUFEN`, `ITERREN`; rieng RX 2 byte se tat `ITBUFEN` tai
   event `ADDR` de doi `BTF` ma khong bi `RXNE` chen ngang.
6. Lap trinh START va return, khong polling trong API.

Phase 1 chi chap nhan policy ket thuc `I2C_STOP` cho hai raw interrupt API.
`I2C_NO_STOP` phai return loi/unsupported cho den khi co state machine chained
transaction quy dinh ro luc nao lap trinh repeated START va phase nao tiep quan
ly bus. Khong duoc bo STOP, close handle ve READY roi de bus van bi owned.

## 9. Event IRQ

Phase 1 chi xu ly:

| Flag | Su dung |
|------|---------|
| `SB` | Gui address 7-bit + R/W |
| `ADDR` | Xu ly address ACK va clear dung sequence |
| `TXE` | Nap byte TX tiep theo |
| `RXNE` | Doc byte RX khi sequence cho phep |
| `BTF` | Ket thuc TX hoac xu ly cac byte cuoi cua RX |

Khong xu ly trong phase 1:

- `ADD10`: chi dung cho dia chi 10-bit.
- `STOPF`: chi can khi STM32 la Target.

Event handler nen xu ly moi lan mot event roi `return`. Neu flag van set va
nguon interrupt van enable, peripheral tiep tuc giu interrupt request va CPU se
vao ISR lai.

Thu tu uu tien:

```text
SB -> ADDR -> BTF neu state/length xu ly duoc -> TXE -> RXNE
```

Pseudo-code:

```c
void I2C_EV_IRQHandling(i2c_driver_t *pDriver)
{
    I2C_TypeDef *I2Cx = pDriver->pI2Cx;
    uint32_t sr1 = I2Cx->SR1;

    if ((sr1 & I2C_SR1_SB) != 0U)
    {
        I2C_HandleSB(pDriver);
        return;
    }

    if ((sr1 & I2C_SR1_ADDR) != 0U)
    {
        I2C_HandleADDR(pDriver);
        return;
    }

    if ((sr1 & I2C_SR1_BTF) != 0U)
    {
        if ((pDriver->State == I2C_STATE_BUSY_TX) &&
            (pDriver->TxLen == 0U))
        {
            I2C_HandleTxBTF(pDriver);
            return;
        }

        if ((pDriver->State == I2C_STATE_BUSY_RX) &&
            (pDriver->RxLen <= 3U))
        {
            I2C_HandleRxBTF(pDriver);
            return;
        }
    }

    if (((sr1 & I2C_SR1_TXE) != 0U) &&
        (pDriver->State == I2C_STATE_BUSY_TX))
    {
        I2C_HandleTXE(pDriver);
        return;
    }

    if (((sr1 & I2C_SR1_RXNE) != 0U) &&
        (pDriver->State == I2C_STATE_BUSY_RX) &&
        ((pDriver->RxLen == 1U) || (pDriver->RxLen > 3U)))
    {
        I2C_HandleRXNE(pDriver);
        return;
    }
}
```

Khong uu tien `BTF` vo dieu kien. Neu TX dang co `BTF=1`, `TXE=1` va
`TxLen > 0`, handler phai cho phep `TXE` nap byte tiep theo. Neu handler chon
`BTF` roi return ma khong clear flag/nap data, no se vao lap IRQ.

Tuong tu, Controller RX chi uu tien helper `BTF` dac biet khi `RxLen<=3`. Neu
`BTF=1` khi `RxLen>3`, dispatcher phai cho nhanh `RXNE` doc mot byte thong
thuong; lan doc `DR` do giai phong pipeline va cho transaction tiep tuc.

Khong doc `SR2` o dau ISR. Doc `SR1` don le khong clear `ADDR`; `ADDR` chi clear
sau sequence doc `SR1` roi `SR2`. RX phai lap trinh `ACK/POS` truoc lan doc
`SR2` nay.

## 10. Controller transmitter interrupt

### 10.1 SB

```text
State = BUSY_TX -> DR = (TargetAddr << 1) | I2C_WRITE
```

Ghi `DR` sau khi doc `SR1` clear `SB`.

### 10.2 ADDR

Controller TX chi can clear `ADDR` bang doc `SR1`, sau do doc `SR2`.

### 10.3 TXE

Khi `TxLen > 0`, ghi mot byte vao `DR`, tang pointer va giam `TxLen`. Khi
`TxLen == 0`, disable `ITBUFEN` de khong lap interrupt `TXE`, nhung giu
`ITEVTEN` de doi `BTF`.

### 10.4 BTF

Chi close TX khi:

```text
State == BUSY_TX && TxLen == 0 && BTF == 1
```

Phase 1 luon lap trinh STOP, sau do disable interrupt can thiet, reset state va
context, goi callback TX complete. Chained transaction/repeated START de danh
cho API higher-level cua phase sau.

## 11. Controller receiver interrupt

Controller receiver phai tach rieng `N=1`, `N=2`, `N>2`.

### 11.1 N = 1

Tai `ADDR=1`, khi SCL dang bi stretch:

```text
POS = 0
ACK = 0
clear ADDR bang doc SR1 -> SR2
lap trinh STOP
cho RXNE
doc DR
RxLen = 0
restore ACK/POS
close RX va callback
```

`ACK=0` phai duoc set truoc khi clear `ADDR`; STOP duoc lap trinh ngay sau khi
clear `ADDR`, truoc khi cho `RXNE`.

### 11.2 N = 2

Sequence RM0090:

```text
cho ADDR = 1
ACK = 0
POS = 1
clear ADDR bang doc SR1 -> SR2
disable ITBUFEN de bo qua RXNE va doi event BTF
cho BTF = 1
  DR             = Data1
  shift register = Data2
  SCL bi stretch LOW
lap trinh STOP
doc DR -> Data1
doc DR -> Data2
RxLen = 0
POS = 0
restore ACK
close RX va callback
```

Khong duoc clear `ADDR`, cho `BTF`, roi moi set `ACK=0/POS=1`.
Khong duoc doc `DR` theo `RXNE` trong case nay; chi doc hai byte khi `BTF=1`.

### 11.3 N > 2

Tai `ADDR=1`:

```text
POS = 0
ACK = 1
clear ADDR bang doc SR1 -> SR2
```

Xu ly cac byte dau bang `RXNE` chi khi `RxLen > 3`. Khi `RxLen` giam con 3,
disable `ITBUFEN` neu can de khong doc `DR` qua som; giu `ITEVTEN` va doi
`BTF`.

Sequence ba byte cuoi:

```text
RxLen = 3, cho BTF = 1
  DR             = DataN-2
  shift register = DataN-1
ACK = 0
doc DR -> DataN-2
RxLen = 2

cho BTF = 1 lan nua
  DR             = DataN-1
  shift register = DataN
lap trinh STOP
doc DR -> DataN-1
doc DR -> DataN
RxLen = 0
restore ACK/POS
close RX va callback
```

Khong xu ly `RXNE` theo duong thong thuong khi `RxLen == 3`, vi doc `DR` qua
som se pha sequence `BTF` cua ba byte cuoi.

## 12. Close transaction va callback

Close TX/RX phai:

1. Disable `ITBUFEN`, `ITEVTEN` va `ITERREN` khi transaction da ket thuc.
2. Restore `CR1.POS=0` sau Controller RX.
3. Restore `CR1.ACK` theo `I2CConfig.I2C_ACKControl`.
4. Reset state ve READY va clear pointer/length runtime.
5. Goi callback sau khi handle da o trang thai READY.

Event callback toi thieu:

```text
I2C_EVENT_TX_COMPLETE
I2C_EVENT_RX_COMPLETE
I2C_EVENT_ERROR
```

Callback khong duoc blocking trong IRQ.

## 13. Error IRQ

Error handler duoc phep dung nhieu `if` doc lap de ghi nhan tat ca error flag
da set trong mot snapshot:

```text
BERR, ARLO, AF, OVR
```

`TIMEOUT` co the khai bao/defer ro rang trong phase 1. Neu header da cung cap bit
thi khong duoc nham hardware `SR1.TIMEOUT` voi software timeout cua API.

Quy trinh:

1. Snapshot `SR1`.
2. Thu thap va clear tung error flag.
3. OR vao `ErrorCode`.
4. Chon recovery theo loai loi, khong abort giong nhau cho moi flag.
5. Close state/context va callback error.

Hanh vi toi thieu:

| Error | Hanh vi |
|-------|----------|
| `AF` | Controller TX/RX bi Target NACK address, hoac TX bi NACK data: clear AF, STOP neu con so huu bus, close va bao loi |
| `BERR` | Clear BERR, STOP neu hop le, close; recovery bang SWRST la policy rieng |
| `ARLO` | Clear ARLO, nhan mat quyen bus, khong tu phat STOP |
| `OVR` | Doc `SR1`, truy cap `DR` theo huong RX/TX de clear, bo transaction/data khong con tin cay, close |
| `TIMEOUT` | Defer hoac clear/close theo policy duoc phe duyet; GPIO recovery la task rieng |

`BTF` khong clear truc tiep `OVR`. `BTF` va clock stretching giup phan mem phuc
vu `DR` dung luc de phong overrun/underrun; khi `OVR` da set thi phai clear va
abort/recover rieng.

`OVR` khong duoc clear bang helper ghi 0 bit dung cho `AF/BERR/ARLO`. Phai theo
access sequence RM0090: doc `SR1`, sau do doc hoac ghi `DR` phu hop voi huong
receiver/transmitter, roi bo transaction vi data khong con dang tin cay.

Trong Controller receiver, Target NACK Address+R cung set `AF`; khong duoc chi
kiem tra `AF` cho Controller transmitter. Trong phase 1 chi co Controller mode.
Ve sau khi them Target transmitter,
`AF` do Controller NACK byte cuoi phai duoc xem la completion binh thuong, khong
duoc dung chung semantics error cua Controller transmitter.

## 14. NVIC va IRQ forwarding

Moi peripheral co hai IRQ:

```text
I2C1_EV_IRQn / I2C1_ER_IRQn
I2C2_EV_IRQn / I2C2_ER_IRQn
I2C3_EV_IRQn / I2C3_ER_IRQn
```

Phase dau chi enable cap IRQ cua peripheral duoc application su dung. IRQ handler
o application/startup layer phai forward vao:

```c
I2C_EV_IRQHandling(&hi2c1);
I2C_ER_IRQHandling(&hi2c1);
```

Khong enable tat ca I2C1/I2C2/I2C3 neu project chi cau hinh mot instance.

## 15. Test toi thieu

### 15.1 Controller write

Kiem tra:

- API return ngay, state chuyen BUSY_TX.
- Waveform co START, Address+W, ACK, data ACK va STOP.
- `TXE` nap du byte; `BTF` ket thuc transaction.
- State ve READY va callback TX complete chi goi mot lan.

### 15.2 Controller read

Uu tien test voi length ma hardware target ho tro. Can kiem tra rieng khi co dieu
kien:

- `N=1`: NACK byte duy nhat, STOP va callback.
- `N=2`: `ACK=0/POS=1` truoc clear ADDR, `BTF`, NACK byte cuoi, STOP.
- `N>2`: chuyen sang `BTF` khi con 3 byte, NACK byte cuoi, STOP.
- Buffer dung thu tu va state/callback dung.

### 15.3 Error toi thieu

- Address NACK trong Controller TX tao `AF`.
- Driver clear AF, phat STOP, state ve READY va callback error.

Test nang cao `BERR`, `ARLO`, `OVR`, `TIMEOUT` duoc de lai cho phase sau.

## 16. Thay doi du kien theo file

- `Driver/Core/Inc/i2c_driver.h`: them state, context, error/event enum, IT API,
  IRQ handler va callback declaration.
- `Driver/Core/Src/i2c_driver.c`: them non-blocking API, event/error handler va
  close/abort logic toi thieu.
- `Driver/Core/Src/irq_config.c`: enable dung EV/ER IRQ cua instance dang dung.
- File IRQ application/startup tuong ung: forward hardware IRQ vao driver.
- Test/application: khoi dong mot transaction va quan sat callback/waveform.

Truoc khi sua bat ky function/class/method nao, phai chay GitNexus impact
analysis theo quy dinh cua repo. Truoc khi commit, phai chay GitNexus
`detect_changes()` va review diff.

## 17. Rang buoc cho model trien khai

### MUST

- Chi trien khai Controller 7-bit TX/RX trong phase 1.
- Chi ho tro `I2C_STOP` trong raw interrupt API; reject `I2C_NO_STOP` cho den
  khi co chained-transaction state machine.
- Tuan thu sequence chu trong file nay; khong phu thuoc OCR hinh.
- Cau hinh `ACK/POS` truoc khi clear `ADDR` trong Controller RX.
- Khong doc `SR2` som khi `ADDR` dang pending.
- Tach `N=1`, `N=2`, `N>2`.
- Chuyen sang sequence `BTF` khi con 3 byte voi `N>2`.
- Uu tien `BTF` theo state/length, khong uu tien vo dieu kien.
- Restore `POS=0` va ACK sau Controller RX.
- Phan biet `AF`, `ARLO`, `BERR`, `OVR` khi abort.
- Giu ISR ngan, khong polling va khong goi ham blocking.

### MUST NOT

- Khong implement Target mode trong cung phase.
- Khong doc `SR1` va `SR2` vo dieu kien o dau event ISR.
- Khong dung chung mot receive sequence cho moi `Len`.
- Khong xu ly `RXNE` thong thuong khi con 3 byte.
- Khong phat STOP sau `ARLO` khi Controller da mat quyen bus.
- Khong xem `BTF` la thao tac fix truc tiep `OVR`.
- Khong sao chep nguyen sequence polling receive hien tai vao ISR.
- Khong sua API polling ngoai pham vi neu chua duoc yeu cau.

## 18. Acceptance criteria

- Code build khong warning/error theo toolchain hien tai.
- Controller write/read khong blocking sau khi API return.
- Event IRQ khong lap vo han khi `BTF` va `TXE` cung set.
- `ADDR` RX khong bi clear truoc khi lap trinh `ACK/POS`.
- Receive `N=1`, `N=2`, `N>2` dung sequence RM0090.
- STOP/NACK dung ownership: Controller receiver NACK byte cuoi va Controller
  phat STOP.
- State va interrupt bits duoc close dung ca khi complete va error.
- Callback chi goi mot lan cho moi transaction.
- Target mode va advanced recovery van duoc danh dau deferred, khong co code nua
  voi trong phase 1.
