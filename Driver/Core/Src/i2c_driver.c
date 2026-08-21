#include "i2c_driver.h"

/* --------------------------------------------------------------------------
 * Clock control
 * -------------------------------------------------------------------------- */
void I2C_PeriClockControl(i2c_driver_t *pI2CDriver, uint8_t EnorDi)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    if (EnorDi == ENABLE)
    {
        if (pI2Cx == I2C1)
        {
            I2C1_PCLK_EN();
        }
        else if (pI2Cx == I2C2)
        {
            I2C2_PCLK_EN();
        }
        else if (pI2Cx == I2C3)
        {
            I2C3_PCLK_EN();
        }
    }
    else
    {
        if (pI2Cx == I2C1)
        {
            I2C1_PCLK_DI();
        }
        else if (pI2Cx == I2C2)
        {
            I2C2_PCLK_DI();
        }
        else if (pI2Cx == I2C3)
        {
            I2C3_PCLK_DI();
        }
    }
}

/* --------------------------------------------------------------------------
 * Status flags
 * The flag macro encodes the source register in bit 31 (see i2c_driver.h):
 *   FLAG_I2C_SR1_x  -> read SR1
 *   FLAG_I2C_SR2_x  -> read SR2
 * Usage: while (I2C_GetFlagStatus(&i2c1, FLAG_I2C_SR2_BUSY) == FLAG_SET);
 * -------------------------------------------------------------------------- */
uint8_t I2C_GetFlagStatus(i2c_driver_t *pI2CDriver, uint32_t Flag)
{
    uint32_t statusReg;

    if (Flag & 0x80000000UL)
    {
        statusReg = pI2CDriver->pI2Cx->SR2;
        Flag &= 0x7FFFFFFFUL;
    }
    else
    {
        statusReg = pI2CDriver->pI2Cx->SR1;
    }

    return (statusReg & Flag) ? FLAG_SET : FLAG_RESET;
}

/* --------------------------------------------------------------------------
 * Init
 * Order follows RM0009: FREQ -> OAR1 -> CCR -> TRISE -> ACK -> PE last.
 * All configuration registers must be written while PE = 0.
 * -------------------------------------------------------------------------- */
void I2C_Init(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    I2C_Config_t *pConfig = &pI2CDriver->I2CConfig;
    uint32_t pclk1 = RCC_GetPCLK1Freq();
    uint32_t temp = 0;
    uint32_t ccr_value = 0;

    /* 1. Enable peripheral clock */
    I2C_PeriClockControl(pI2CDriver, ENABLE);

    /* 2. Tắt PE trước khi cấu hình: RM0090 yêu cầu CR2.FREQ, OAR1, CCR và
     *    TRISE chỉ được ghi khi PE = 0. */
    pI2Cx->CR1 &= ~I2C_CR1_PE;

    /* 3. CR2.FREQ = PCLK1 in MHz (I2C is on APB1) */
    temp = (pclk1 / 1000000U) & I2C_CR2_FREQ_Msk;
    pI2Cx->CR2 = temp;

    /* 4. OAR1: own address, 7-bit mode.
     *    ADDMODE[15] = 0 (7-bit), bit 14 = 1 (always), ADD0 = 0. */
    temp = 0;
    temp |= ((uint32_t)pConfig->I2C_DeviceAddress << 1) & I2C_OAR1_ADD1_7;
    temp |= I2C_OAR1_RES14;
    pI2Cx->OAR1 = temp;

    /* 5. CCR and TRISE based on I2C_SCLSpeed */
    temp = 0;
    if (pConfig->I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        /* Standard-mode: FS = 0, DUTY ignored, tLOW = tHIGH = t/2 */
        ccr_value = pclk1 / (2U * pConfig->I2C_SCLSpeed);
        temp = ccr_value & I2C_CCR_CCR_Msk;
        pI2Cx->CCR = temp;
        /* tr_max = 1000 ns -> TRISE = PCLK1(MHz) + 1 */
        pI2Cx->TRISE = (pclk1 / 1000000U) + 1U;
    }
    else
    {
        /* Fast-mode: FS = 1, DUTY selects 2:1 or 16:9 */
        temp = I2C_CCR_FS;
        temp |= ((uint32_t)pConfig->I2C_FMDutyCycle << I2C_CCR_DUTY_Pos)
                & I2C_CCR_DUTY_Msk;

        if (pConfig->I2C_FMDutyCycle == I2C_FM_DUTY_2)
        {
            ccr_value = pclk1 / (3U * pConfig->I2C_SCLSpeed);
        }
        else
        {
            ccr_value = pclk1 / (25U * pConfig->I2C_SCLSpeed);
        }
        temp |= ccr_value & I2C_CCR_CCR_Msk;
        pI2Cx->CCR = temp;
        /* tr_max = 300 ns -> TRISE = (300 ns * PCLK1) + 1, rounded up */
        pI2Cx->TRISE = (uint32_t)(((uint64_t)pclk1 * 300U
                                   + 999999999U) / 1000000000U) + 1U;
    }

    /* 6. ACK control (CR1.ACK) */
    temp = 0;
    if (pConfig->I2C_ACKControl == I2C_ACK_ENABLE)
    {
        temp = I2C_CR1_ACK;
    }
    pI2Cx->CR1 = temp;

    /* 7. Enable peripheral (PE) — always last */
    pI2Cx->CR1 |= I2C_CR1_PE;
}

/* --------------------------------------------------------------------------
 * DeInit: reset the peripheral via RCC
 * -------------------------------------------------------------------------- */
void I2C_DeInit(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    if (pI2Cx == I2C1)
    {
        I2C1_PCLK_RESET();
    }
    else if (pI2Cx == I2C2)
    {
        I2C2_PCLK_RESET();
    }
    else if (pI2Cx == I2C3)
    {
        I2C3_PCLK_RESET();
    }
}

/* --------------------------------------------------------------------------
 * Enable/disable the peripheral (CR1.PE)
 * -------------------------------------------------------------------------- */
void I2C_PeripheralControl(i2c_driver_t *pI2CDriver, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        pI2CDriver->pI2Cx->CR1 |= I2C_CR1_PE;
    }
    else
    {
        pI2CDriver->pI2Cx->CR1 &= ~I2C_CR1_PE;
    }
}

/* --------------------------------------------------------------------------
 * START condition (CR1.START, bit 8 — see RM0090)
 * -------------------------------------------------------------------------- */
void I2C_GenerateSTART(i2c_driver_t *pI2CDriver)
{
    pI2CDriver->pI2Cx->CR1 |= I2C_CR1_START;
}

/* --------------------------------------------------------------------------
 * STOP condition (CR1.STOP, bit 9 — see RM0090)
 * -------------------------------------------------------------------------- */
void I2C_GenerateSTOP(i2c_driver_t *pI2CDriver)
{
    pI2CDriver->pI2Cx->CR1 |= I2C_CR1_STOP;
}

/* --------------------------------------------------------------------------
 * Clear a software-cleared SR1 flag by writing 0 (AF, BERR, ARLO, OVR).
 * SR2 flags (bit 31 marker set) are read-only and are ignored.
 * -------------------------------------------------------------------------- */
void I2C_ClearFlag(i2c_driver_t *pI2CDriver, uint32_t Flag)
{
    if (!(Flag & 0x80000000UL))
    {
        pI2CDriver->pI2Cx->SR1 &= ~(Flag & 0x7FFFFFFFUL);
    }
}

/* --------------------------------------------------------------------------
 * ACK control (CR1.ACK) — disable ACK before the last byte of a read to
 * force NACK, re-enable it at the end of the transaction.
 * -------------------------------------------------------------------------- */
void I2C_ManageAck(i2c_driver_t *pI2CDriver, uint8_t EnorDi)
{
    if (EnorDi == I2C_ACK_ENABLE)
    {
        pI2CDriver->pI2Cx->CR1 |= I2C_CR1_ACK;
    }
    else
    {
        pI2CDriver->pI2Cx->CR1 &= ~I2C_CR1_ACK;
    }
}

/* --------------------------------------------------------------------------
 * Error recovery after a bus fault (BERR / ARLO / stuck state machine).
 * RM0090 §27.6.1: pulsing CR1.SWRST forces a full peripheral reset, then the
 * working configuration must be re-applied because SWRST clears CR1/CR2/OAR.
 * This does NOT fix a physically stuck SDA/SCL line (dead slave shorting the
 * bus) — that needs GPIO-level clock-stretching recovery at the board layer.
 * -------------------------------------------------------------------------- */
void I2C_ErrorRecovery(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    /* 1. Pulse SWRST (set then clear) to reset the I2C state machine */
    pI2Cx->CR1 |= I2C_CR1_SWRST;
    pI2Cx->CR1 &= ~I2C_CR1_SWRST;

    /* 2. Re-apply configuration lost during SWRST */
    I2C_Init(pI2CDriver);
}

/* --------------------------------------------------------------------------
 * Master transmit (blocking)
 * Sequence: START -> Addr+W -> data... -> STOP
 * Events: EV1 (ADDR), EV3/EV3-1 (TXE), EV3-2 (AF), BTF before STOP.
 * With Sr = I2C_NO_STOP no STOP is issued, leaving the bus owned for a
 * following Repeated-Start read (see I2C_MemReadData).
 * -------------------------------------------------------------------------- */
DriverStatus_t I2C_MasterSendData(i2c_driver_t *pI2CDriver,
                                  uint8_t *pTxBuffer,
                                  uint16_t Len,
                                  uint16_t SlaveAddr,
                                  uint8_t Sr)
{
    I2C_TypeDef *pI2Cx;

    if ((pI2CDriver == NULL) || (pTxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }
    pI2Cx = pI2CDriver->pI2Cx;

    /* Step 1 — wait for bus idle, then issue START */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR2_BUSY) == FLAG_SET);
    I2C_GenerateSTART(pI2CDriver);

    /* Step 2 — wait for START issued (SB) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_SB) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 3 — send slave address, R/W = 0 (write) */
    pI2Cx->DR = (uint8_t)((SlaveAddr << 1U) | I2C_WRITE);

    /* Step 4 — wait for address ACKed by target (EV1) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 5 — clear ADDR: read SR1 then SR2 (mandatory order) */
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Step 6 — send each byte, wait TXE before writing DR (EV3 / EV3-1) */
    while (Len > 0U)
    {
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
        {
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
            {
                I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
                I2C_GenerateSTOP(pI2CDriver);
                return STATUS_ERROR;
            }
        }
        pI2Cx->DR = *pTxBuffer++;
        Len--;
    }

    /* Step 7 — wait for BTF: last byte fully shifted out. AF vẫn phải được
     * kiểm tra ở đây: target có thể NACK byte data cuối. */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 8 — release the bus, unless a Repeated-Start read follows */
    if (Sr == I2C_STOP)
    {
        I2C_GenerateSTOP(pI2CDriver);
    }

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Memory write (blocking)
 * Sequence: START -> Addr+W -> REG_ADDR -> data... -> STOP
 * Same polling flow as I2C_MasterSendData, with MemAddr sent as the first
 * payload byte and the user data appended in the same transaction, so no
 * extra buffer is needed.
 * -------------------------------------------------------------------------- */
DriverStatus_t I2C_MemWriteData(i2c_driver_t *pI2CDriver,
                                uint16_t SlaveAddr,
                                uint8_t MemAddr,
                                uint8_t *pTxBuffer,
                                uint16_t Len)
{
    I2C_TypeDef *pI2Cx;

    if ((pI2CDriver == NULL) || (pTxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }
    pI2Cx = pI2CDriver->pI2Cx;

    /* Step 1 — wait for bus idle, then issue START */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR2_BUSY) == FLAG_SET);
    I2C_GenerateSTART(pI2CDriver);

    /* Step 2 — wait for START issued (SB) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_SB) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 3 — send slave address, R/W = 0 (write) */
    pI2Cx->DR = (uint8_t)((SlaveAddr << 1U) | I2C_WRITE);

    /* Step 4 — wait for address ACKed by target (EV1) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 5 — clear ADDR: read SR1 then SR2 (mandatory order) */
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Step 6 — send REG_ADDR as first payload byte */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
    }
    pI2Cx->DR = MemAddr;

    /* Step 7 — send the data bytes, wait TXE before each DR write */
    while (Len > 0U)
    {
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
        {
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
            {
                I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
                I2C_GenerateSTOP(pI2CDriver);
                return STATUS_ERROR;
            }
        }
        pI2Cx->DR = *pTxBuffer++;
        Len--;
    }

    /* Step 8 — wait for BTF, then release the bus. AF vẫn phải được kiểm tra:
     * target có thể NACK byte data cuối. */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
    }
    I2C_GenerateSTOP(pI2CDriver);

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Receive phase (static helper, shared by both read functions)
 * Caller must be already addressed (ADDR set) — this routine programs the
 * ACK strategy, clears ADDR and collects Len bytes following RM0090 §27.3.6:
 *
 *   Len == 1 : ACK off before clear ADDR → STOP → chờ RXNE → đọc DR
 *   Len == 2 : POS=1 + ACK=0 trước clear ADDR → chờ BTF → STOP → đọc DR × 2
 *   Len >= 3 : ACK on → clear ADDR → đọc (N-3) byte qua RXNE → chờ BTF →
 *              ACK off → đọc DR (byte N-2) → chờ BTF → STOP → đọc DR × 2
 *
 * STOP được program TRƯỚC khi đọc byte cuối để phần cứng thả clock stretching
 * đúng thời điểm, tránh nhận byte thừa. Nếu Sr == I2C_NO_STOP, bỏ qua STOP
 * (giữ bus owned cho Repeated-Start kế tiếp).
 * -------------------------------------------------------------------------- */
static DriverStatus_t I2C_ReceivePhase(i2c_driver_t *pI2CDriver,
                                       uint8_t *pRxBuffer,
                                       uint16_t Len,
                                       uint8_t Sr)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint16_t remaining = Len;

    if (Len == 1U)
    {
        /* NACK byte duy nhất trước khi clear ADDR */
        I2C_ManageAck(pI2CDriver, I2C_ACK_DISABLE);
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;
        if (Sr == I2C_STOP)
        {
            I2C_GenerateSTOP(pI2CDriver);
        }
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_RXNE) != FLAG_SET)
        {
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
            {
                I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
                I2C_GenerateSTOP(pI2CDriver);
                I2C_ErrorRecovery(pI2CDriver);
                return STATUS_ERROR;
            }
        }
        *pRxBuffer = (uint8_t)pI2Cx->DR;
    }
    else if (Len == 2U)
    {
        /* POS=1: NACK tác động vào byte thứ 2 (byte cuối) */
        pI2Cx->CR1 |= I2C_CR1_POS;
        I2C_ManageAck(pI2CDriver, I2C_ACK_DISABLE);
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET)
        {
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
            {
                I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
                I2C_GenerateSTOP(pI2CDriver);
                pI2Cx->CR1 &= ~I2C_CR1_POS;
                I2C_ErrorRecovery(pI2CDriver);
                return STATUS_ERROR;
            }
        }
        if (Sr == I2C_STOP)
        {
            I2C_GenerateSTOP(pI2CDriver);
        }
        *pRxBuffer++ = (uint8_t)pI2Cx->DR;
        *pRxBuffer++ = (uint8_t)pI2Cx->DR;
        pI2Cx->CR1 &= ~I2C_CR1_POS;
    }
    else
    {
        I2C_ManageAck(pI2CDriver, I2C_ACK_ENABLE);
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;

        /* Đọc bình thường cho đến khi còn đúng 3 byte */
        while (remaining > 3U)
        {
            while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_RXNE) != FLAG_SET)
            {
                if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
                {
                    I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
                    I2C_GenerateSTOP(pI2CDriver);
                    I2C_ErrorRecovery(pI2CDriver);
                    return STATUS_ERROR;
                }
            }
            *pRxBuffer++ = (uint8_t)pI2Cx->DR;
            remaining--;
        }

        /* Còn 3 byte: DR chứa N-2, shift register chứa N-1 */
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET)
        {
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
            {
                I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
                I2C_GenerateSTOP(pI2CDriver);
                I2C_ErrorRecovery(pI2CDriver);
                return STATUS_ERROR;
            }
        }
        I2C_ManageAck(pI2CDriver, I2C_ACK_DISABLE);

        /* Đọc byte N-2 → N-1 chuyển vào DR, N vào shift register */
        *pRxBuffer++ = (uint8_t)pI2Cx->DR;
        remaining--;

        /* Chờ BTF: N-1 trong DR, N trong shift register */
        while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET)
        {
            if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
            {
                I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
                I2C_GenerateSTOP(pI2CDriver);
                I2C_ErrorRecovery(pI2CDriver);
                return STATUS_ERROR;
            }
        }
        if (Sr == I2C_STOP)
        {
            I2C_GenerateSTOP(pI2CDriver);
        }
        *pRxBuffer++ = (uint8_t)pI2Cx->DR;   /* byte N-1 */
        *pRxBuffer++ = (uint8_t)pI2Cx->DR;   /* byte N   */
    }

    /* Khôi phục ACK cho transaction kế tiếp */
    if (pI2CDriver->I2CConfig.I2C_ACKControl == I2C_ACK_ENABLE)
    {
        I2C_ManageAck(pI2CDriver, I2C_ACK_ENABLE);
    }

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Master receive (blocking)
 * Sequence: START -> Addr+R -> data... -> STOP
 * Events: EV1 (ADDR), EV6 (clear ADDR), EV7 (RXNE), EV8 (BTF) — see helper.
 * With Sr = I2C_NO_STOP no STOP is issued, leaving the bus owned for a
 * following Repeated-Start phase (see I2C_MemReadData).
 * -------------------------------------------------------------------------- */
DriverStatus_t I2C_MasterReceiveData(i2c_driver_t *pI2CDriver,
                                     uint8_t *pRxBuffer,
                                     uint16_t Len,
                                     uint16_t SlaveAddr,
                                     uint8_t Sr)
{
    I2C_TypeDef *pI2Cx;

    if ((pI2CDriver == NULL) || (pRxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }
    pI2Cx = pI2CDriver->pI2Cx;

    /* Step 1 — wait for bus idle, then issue START */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR2_BUSY) == FLAG_SET);
    I2C_GenerateSTART(pI2CDriver);

    /* Step 2 — wait for START issued (SB) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_SB) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 3 — send slave address, R/W = 1 (read) */
    pI2Cx->DR = (uint8_t)((SlaveAddr << 1U) | I2C_READ);

    /* Step 4 — wait for address ACKed by target (EV1) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 5 — ACK strategy + clear ADDR + collect data (EV7 / EV8)
     * Helper tự phát STOP khi Sr == I2C_STOP (theo đúng trình tự RM0090:
     * STOP phải được program trước khi đọc byte cuối). */
    if (I2C_ReceivePhase(pI2CDriver, pRxBuffer, Len, Sr) != STATUS_OK)
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Memory read (blocking)
 * Sequence: START -> Addr+W -> REG_ADDR -> Repeated START -> Addr+R -> data... -> STOP
 * The REG_ADDR is written in a short write phase, then the bus is kept owned
 * (no STOP) and a Repeated-Start switches to the receive phase.
 * -------------------------------------------------------------------------- */
DriverStatus_t I2C_MemReadData(i2c_driver_t *pI2CDriver,
                               uint16_t SlaveAddr,
                               uint8_t MemAddr,
                               uint8_t *pRxBuffer,
                               uint16_t Len)
{
    I2C_TypeDef *pI2Cx;

    if ((pI2CDriver == NULL) || (pRxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }
    pI2Cx = pI2CDriver->pI2Cx;

    /* Step 1 — wait for bus idle, then issue START */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR2_BUSY) == FLAG_SET);
    I2C_GenerateSTART(pI2CDriver);

    /* Step 2 — wait for START issued (SB) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_SB) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 3 — send slave address, R/W = 0 (write) */
    pI2Cx->DR = (uint8_t)((SlaveAddr << 1U) | I2C_WRITE);

    /* Step 4 — wait for address ACKed by target (EV1) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 5 — clear ADDR: read SR1 then SR2 (mandatory order) */
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Step 6 — send REG_ADDR, wait TXE before writing DR */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
    }
    pI2Cx->DR = MemAddr;

    /* Step 7 — wait for REG_ADDR fully shifted out (BTF), then Repeated START.
     * TXE chỉ báo DR rỗng; BTF đảm bảo byte đã rời shift register → an toàn Sr. */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
    }
    I2C_GenerateSTART(pI2CDriver);

    /* Step 8 — wait for Repeated START issued (SB) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_SB) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 9 — send slave address, R/W = 1 (read) */
    pI2Cx->DR = (uint8_t)((SlaveAddr << 1U) | I2C_READ);

    /* Step 10 — wait for address ACKed by target (EV1) */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_ADDR) != FLAG_SET)
    {
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_AF) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_AF);
            I2C_GenerateSTOP(pI2CDriver);
            return STATUS_ERROR;
        }
        if (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BERR) == FLAG_SET)
        {
            I2C_ClearFlag(pI2CDriver, FLAG_I2C_SR1_BERR);
            I2C_GenerateSTOP(pI2CDriver);
            I2C_ErrorRecovery(pI2CDriver);
            return STATUS_ERROR;
        }
    }

    /* Step 11 — ACK strategy + clear ADDR + collect data (EV7 / EV8).
     * Helper tự phát STOP theo đúng trình tự RM0090. */
    if (I2C_ReceivePhase(pI2CDriver, pRxBuffer, Len, I2C_STOP) != STATUS_OK)
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Callback registration
 * -------------------------------------------------------------------------- */
void I2C_RegisterCallback(i2c_driver_t *pI2CDriver, I2C_Callback_t Callback)
{
    if ((pI2CDriver != NULL) && (Callback != NULL))
    {
        pI2CDriver->Callback = Callback;
    }
}

/* --------------------------------------------------------------------------
 * Interrupt helpers — close/abort
 * -------------------------------------------------------------------------- */
static void I2C_CloseIT(i2c_driver_t *pI2CDriver, uint8_t AppEvent)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    pI2Cx->CR2 &= ~(I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN);

    pI2Cx->CR1 &= ~I2C_CR1_POS;
    if (pI2CDriver->I2CConfig.I2C_ACKControl == I2C_ACK_ENABLE)
    {
        pI2Cx->CR1 |= I2C_CR1_ACK;
    }
    else
    {
        pI2Cx->CR1 &= ~I2C_CR1_ACK;
    }

    pI2CDriver->pTxBuffer = NULL;
    pI2CDriver->pRxBuffer = NULL;
    pI2CDriver->TxLen = 0U;
    pI2CDriver->RxLen = 0U;
    pI2CDriver->RxSize = 0U;
    pI2CDriver->TargetAddr = 0U;
    /* ErrorCode giữ nguyên để callback đọc được nguyên nhân lỗi; chỉ reset
     * khi bắt đầu transaction mới (trong hai API IT). */
    pI2CDriver->State = I2C_STATE_READY;
    pI2CDriver->RepeatedStart = 0U;

    if (pI2CDriver->Callback != NULL)
    {
        pI2CDriver->Callback(pI2CDriver, AppEvent);
    }
}

/* --------------------------------------------------------------------------
 * Non-blocking: I2C_MasterSendDataIT
 * -------------------------------------------------------------------------- */
DriverStatus_t I2C_MasterSendDataIT(i2c_driver_t *pI2CDriver,
                                    uint8_t *pTxBuffer,
                                    uint32_t Len,
                                    uint16_t TargetAddr,
                                    uint8_t RepeatedStart)
{
    I2C_TypeDef *pI2Cx;

    if ((pI2CDriver == NULL) || (pTxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }

    if (TargetAddr > 0x7FU)
    {
        return STATUS_ERROR;
    }

    if (RepeatedStart != I2C_STOP)
    {
        return STATUS_ERROR;
    }

    if (pI2CDriver->State != I2C_STATE_READY)
    {
        return STATUS_BUSY;
    }

    pI2Cx = pI2CDriver->pI2Cx;

    pI2CDriver->pTxBuffer = pTxBuffer;
    pI2CDriver->pRxBuffer = NULL;
    pI2CDriver->TxLen = Len;
    pI2CDriver->RxLen = 0U;
    pI2CDriver->RxSize = 0U;
    pI2CDriver->TargetAddr = TargetAddr;
    pI2CDriver->ErrorCode = I2C_ERROR_NONE;
    pI2CDriver->State = I2C_STATE_BUSY_TX;
    pI2CDriver->RepeatedStart = RepeatedStart;

    /* Clear RXNE tồn đọng từ transaction trước (đọc DR). */
    if ((pI2Cx->SR1 & I2C_SR1_RXNE) != 0U)
    {
        (void)pI2Cx->DR;
    }

    /* ITBUFEN chưa bật ở đây — TXE đang set sẵn sẽ làm ISR TXE nạp byte đầu
     * trước khi SB phát xong. ITBUFEN được bật trong I2C_TxHandleADDR(). */
    pI2Cx->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITERREN;

    I2C_GenerateSTART(pI2CDriver);

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Non-blocking: I2C_MasterReceiveDataIT
 * -------------------------------------------------------------------------- */
DriverStatus_t I2C_MasterReceiveDataIT(i2c_driver_t *pI2CDriver,
                                       uint8_t *pRxBuffer,
                                       uint32_t Len,
                                       uint16_t TargetAddr,
                                       uint8_t RepeatedStart)
{
    I2C_TypeDef *pI2Cx;

    if ((pI2CDriver == NULL) || (pRxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }

    if (TargetAddr > 0x7FU)
    {
        return STATUS_ERROR;
    }

    if (RepeatedStart != I2C_STOP)
    {
        return STATUS_ERROR;
    }

    if (pI2CDriver->State != I2C_STATE_READY)
    {
        return STATUS_BUSY;
    }

    pI2Cx = pI2CDriver->pI2Cx;

    pI2CDriver->pTxBuffer = NULL;
    pI2CDriver->pRxBuffer = pRxBuffer;
    pI2CDriver->TxLen = 0U;
    pI2CDriver->RxLen = Len;
    pI2CDriver->RxSize = Len;
    pI2CDriver->TargetAddr = TargetAddr;
    pI2CDriver->ErrorCode = I2C_ERROR_NONE;
    pI2CDriver->State = I2C_STATE_BUSY_RX;
    pI2CDriver->RepeatedStart = RepeatedStart;

    /* Clear RXNE tồn đọng từ transaction trước (đọc DR). */
    if ((pI2Cx->SR1 & I2C_SR1_RXNE) != 0U)
    {
        (void)pI2Cx->DR;
    }

    pI2Cx->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN;

    I2C_GenerateSTART(pI2CDriver);

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Controller TX helpers
 * -------------------------------------------------------------------------- */
static void I2C_TxHandleSB(i2c_driver_t *pI2CDriver)
{
    pI2CDriver->pI2Cx->DR = (uint8_t)((pI2CDriver->TargetAddr << 1U) | I2C_WRITE);
}

static void I2C_TxHandleADDR(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* ITBUFEN chỉ bật sau khi clear ADDR: TXE đang set sẵn từ trước (DR rỗng)
     * nên nếu bật trong API, ISR TXE sẽ nạp byte đầu vào DR trước cả SB và
     * byte đó bị ghi đè khi SB handler ghi address. */
    pI2Cx->CR2 |= I2C_CR2_ITBUFEN;
}

static void I2C_TxHandleTXE(i2c_driver_t *pI2CDriver)
{
    if (pI2CDriver->TxLen > 0U)
    {
        pI2CDriver->pI2Cx->DR = *pI2CDriver->pTxBuffer++;
        pI2CDriver->TxLen--;

        if (pI2CDriver->TxLen == 0U)
        {
            pI2CDriver->pI2Cx->CR2 &= ~I2C_CR2_ITBUFEN;
        }
    }
}

static void I2C_TxHandleBTF(i2c_driver_t *pI2CDriver)
{
    I2C_GenerateSTOP(pI2CDriver);
    I2C_CloseIT(pI2CDriver, I2C_EVENT_TX_COMPLETE);
}

/* --------------------------------------------------------------------------
 * Controller RX helpers
 * -------------------------------------------------------------------------- */
static void I2C_RxHandleSB(i2c_driver_t *pI2CDriver)
{
    pI2CDriver->pI2Cx->DR = (uint8_t)((pI2CDriver->TargetAddr << 1U) | I2C_READ);
}

static void I2C_RxHandleADDR(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint32_t Len = pI2CDriver->RxSize;

    if (Len == 1U)
    {
        I2C_ManageAck(pI2CDriver, I2C_ACK_DISABLE);
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;
        I2C_GenerateSTOP(pI2CDriver);
    }
    else if (Len == 2U)
    {
        pI2Cx->CR1 |= I2C_CR1_POS;
        I2C_ManageAck(pI2CDriver, I2C_ACK_DISABLE);
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;
        pI2Cx->CR2 &= ~I2C_CR2_ITBUFEN;
    }
    else
    {
        I2C_ManageAck(pI2CDriver, I2C_ACK_ENABLE);
        (void)pI2Cx->SR1;
        (void)pI2Cx->SR2;
    }
}

static void I2C_RxHandleRXNE(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    if (pI2CDriver->RxLen == 1U)
    {
        *pI2CDriver->pRxBuffer = (uint8_t)pI2Cx->DR;
        pI2CDriver->RxLen = 0U;
        I2C_CloseIT(pI2CDriver, I2C_EVENT_RX_COMPLETE);
    }
    else
    {
        *pI2CDriver->pRxBuffer++ = (uint8_t)pI2Cx->DR;
        pI2CDriver->RxLen--;

        if (pI2CDriver->RxLen == 3U)
        {
            pI2Cx->CR2 &= ~I2C_CR2_ITBUFEN;
        }
    }
}

static void I2C_RxHandleBTF(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint32_t remaining = pI2CDriver->RxLen;

    if (remaining == 2U)
    {
        I2C_GenerateSTOP(pI2CDriver);
        *pI2CDriver->pRxBuffer++ = (uint8_t)pI2Cx->DR;
        *pI2CDriver->pRxBuffer++ = (uint8_t)pI2Cx->DR;
        pI2CDriver->RxLen = 0U;
        pI2Cx->CR1 &= ~I2C_CR1_POS;
        I2C_CloseIT(pI2CDriver, I2C_EVENT_RX_COMPLETE);
    }
    else if (remaining == 3U)
    {
        I2C_ManageAck(pI2CDriver, I2C_ACK_DISABLE);
        *pI2CDriver->pRxBuffer++ = (uint8_t)pI2Cx->DR;
        pI2CDriver->RxLen = 2U;
    }
    else if (remaining == 1U)
    {
        /* Nhánh defensive: N=1 bình thường kết thúc qua RXNE (STOP đã program
         * tại ADDR), BTF không set. Nếu chạm tới đây thì DR chỉ chứa 1 byte
         * cuối — đọc đúng 1 byte để không overrun buffer. */
        I2C_GenerateSTOP(pI2CDriver);
        *pI2CDriver->pRxBuffer = (uint8_t)pI2Cx->DR;
        pI2CDriver->RxLen = 0U;
        I2C_CloseIT(pI2CDriver, I2C_EVENT_RX_COMPLETE);
    }
}

/* --------------------------------------------------------------------------
 * I2C_EV_IRQHandling — event interrupt dispatcher
 *
 * Priority: SB -> ADDR -> BTF (state/length-dependent) -> TXE -> RXNE
 * -------------------------------------------------------------------------- */
void I2C_EV_IRQHandling(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx;
    uint32_t sr1;

    if ((pI2CDriver == NULL) || (pI2CDriver->pI2Cx == NULL))
    {
        return;
    }

    pI2Cx = pI2CDriver->pI2Cx;

    /* Không có transaction đang chạy: interrupt còn pending chỉ có thể là cờ
     * tồn đọng (flag set ngay trước khi CloseIT tắt interrupt). Tắt ngắt và
     * return để tránh ghi DR/STOP sai trạng thái. */
    if (pI2CDriver->State == I2C_STATE_READY)
    {
        pI2Cx->CR2 &= ~(I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN);
        return;
    }

    sr1 = pI2Cx->SR1;

    if ((sr1 & I2C_SR1_SB) != 0U)
    {
        if (pI2CDriver->State == I2C_STATE_BUSY_TX)
        {
            I2C_TxHandleSB(pI2CDriver);
        }
        else
        {
            I2C_RxHandleSB(pI2CDriver);
        }
        return;
    }

    if ((sr1 & I2C_SR1_ADDR) != 0U)
    {
        if (pI2CDriver->State == I2C_STATE_BUSY_TX)
        {
            I2C_TxHandleADDR(pI2CDriver);
        }
        else
        {
            I2C_RxHandleADDR(pI2CDriver);
        }
        return;
    }

    if ((sr1 & I2C_SR1_BTF) != 0U)
    {
        if ((pI2CDriver->State == I2C_STATE_BUSY_TX) &&
            (pI2CDriver->TxLen == 0U))
        {
            I2C_TxHandleBTF(pI2CDriver);
            return;
        }

        if ((pI2CDriver->State == I2C_STATE_BUSY_RX) &&
            (pI2CDriver->RxLen <= 3U) &&
            (pI2CDriver->RxLen > 0U))
        {
            I2C_RxHandleBTF(pI2CDriver);
            return;
        }
    }

    if (((sr1 & I2C_SR1_TXE) != 0U) &&
        (pI2CDriver->State == I2C_STATE_BUSY_TX))
    {
        I2C_TxHandleTXE(pI2CDriver);
        return;
    }

    if (((sr1 & I2C_SR1_RXNE) != 0U) &&
        (pI2CDriver->State == I2C_STATE_BUSY_RX) &&
        ((pI2CDriver->RxLen == 1U) || (pI2CDriver->RxLen > 3U)))
    {
        I2C_RxHandleRXNE(pI2CDriver);
        return;
    }
}

/* --------------------------------------------------------------------------
 * I2C_ER_IRQHandling — error interrupt handler
 * -------------------------------------------------------------------------- */
void I2C_ER_IRQHandling(i2c_driver_t *pI2CDriver)
{
    I2C_TypeDef *pI2Cx;
    uint32_t sr1;

    if ((pI2CDriver == NULL) || (pI2CDriver->pI2Cx == NULL))
    {
        return;
    }

    pI2Cx = pI2CDriver->pI2Cx;

    /* Không có transaction đang chạy: cờ lỗi tồn đọng từ trước khi CloseIT
     * tắt interrupt. Clear cờ, tắt ngắt và return — không phát STOP, không
     * gọi callback lỗi. */
    if (pI2CDriver->State == I2C_STATE_READY)
    {
        pI2Cx->SR1 &= ~(I2C_SR1_AF | I2C_SR1_BERR | I2C_SR1_ARLO);
        if ((pI2Cx->SR1 & I2C_SR1_OVR) != 0U)
        {
            (void)pI2Cx->SR1;
            (void)pI2Cx->DR;
        }
        pI2Cx->CR2 &= ~(I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN);
        return;
    }

    sr1 = pI2Cx->SR1;

    if ((sr1 & I2C_SR1_AF) != 0U)
    {
        pI2Cx->SR1 &= ~I2C_SR1_AF;
        pI2CDriver->ErrorCode |= I2C_ERROR_AF;
    }

    if ((sr1 & I2C_SR1_BERR) != 0U)
    {
        pI2Cx->SR1 &= ~I2C_SR1_BERR;
        pI2CDriver->ErrorCode |= I2C_ERROR_BERR;
    }

    if ((sr1 & I2C_SR1_ARLO) != 0U)
    {
        pI2Cx->SR1 &= ~I2C_SR1_ARLO;
        pI2CDriver->ErrorCode |= I2C_ERROR_ARLO;
    }

    if ((sr1 & I2C_SR1_OVR) != 0U)
    {
        /* Clear OVR theo access sequence RM0090: đọc SR1 (đã snapshot ở trên)
         * rồi truy cập DR theo hướng — RX đọc DR, TX ghi DR. */
        if (pI2CDriver->State == I2C_STATE_BUSY_RX)
        {
            (void)pI2Cx->DR;
        }
        else
        {
            pI2Cx->DR = 0U;
        }
        pI2CDriver->ErrorCode |= I2C_ERROR_OVR;
    }

    if ((pI2CDriver->ErrorCode & I2C_ERROR_ARLO) == 0U)
    {
        I2C_GenerateSTOP(pI2CDriver);
    }

    I2C_CloseIT(pI2CDriver, I2C_EVENT_ERROR);
}
