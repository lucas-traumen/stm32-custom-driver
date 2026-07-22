# I2C Driver (Work In Progress)

## Trạng thái

Toàn bộ code trong `i2c_driver.c` hiện đang **comment out** — đang trong quá trình phát triển.

## Cấu trúc OOP/HAL (dự kiến)

```c
I2C_Config_t    // Config: SCL speed, device address, ACK control, FM duty cycle
I2C_Handle_t    // Handle: I2C_TypeDef* + config
```

## Trình tự Init (từ code commented)

```c
// 1. Bật clock
I2C_PeriClockControl(I2C1, ENABLE);

// 2. Set ACK bit trong CR1
// 3. Set FREQ field trong CR2 = PCLK1 / 1_000_000 (đơn vị MHz)
// 4. Set device own address trong OAR1 (7-bit, bit[7:1])
// 5. Tính CCR:
//    - Standard mode: CCR = PCLK1 / (2 * SCL_speed)
//    - Fast mode duty=0: CCR = PCLK1 / (3 * SCL_speed)
//    - Fast mode duty=1: CCR = PCLK1 / (25 * SCL_speed)
```

## Master Send Flow (dự kiến)

1. Generate START condition
2. Chờ SB flag (Start Bit) trong SR1
3. Gửi slave address + W bit
4. Chờ ADDR flag → clear bằng đọc SR1 + SR2
5. Gửi data byte-by-byte, chờ TXE mỗi lần
6. Chờ TXE=1 + BTF=1 (cả DR và shift register trống)
7. Generate STOP condition

## Lưu ý

- Cần hàm `RCC_GetPCLK1Value()` để tính CCR đúng — hàm này cũng đang comment out trong `i2c_driver.c`.
- I2C phụ thuộc APB1 clock → khi bật PLL phải tính lại.
- Code hiện tại chưa hoàn thiện phần `I2C_MasterSendData` (chỉ có comment mô tả flow).

## TODO khi triển khai

- [ ] Uncomment và hoàn thiện `RCC_GetPCLK1Value()`
- [ ] Hoàn thiện `I2C_Init()` — đặc biệt phần TRISE register
- [ ] Implement `I2C_MasterSendData()` theo flow ở trên
- [ ] Implement `I2C_MasterReceiveData()`
- [ ] Thêm interrupt mode (ITBUFEN, ITEVTEN, ITERREN)
