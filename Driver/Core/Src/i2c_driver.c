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

    /* 2. CR2.FREQ = PCLK1 in MHz (I2C is on APB1) */
    temp = (pclk1 / 1000000U) & I2C_CR2_FREQ_Msk;
    pI2Cx->CR2 = temp;

    /* 3. OAR1: own address, 7-bit mode.
     *    ADDMODE[15] = 0 (7-bit), bit 14 = 1 (always), ADD0 = 0. */
    temp = 0;
    temp |= ((uint32_t)pConfig->I2C_DeviceAddress << 1) & I2C_OAR1_ADD1_7;
    temp |= I2C_OAR1_RES14;
    pI2Cx->OAR1 = temp;

    /* 4. CCR and TRISE based on I2C_SCLSpeed */
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

    /* 5. ACK control (CR1.ACK) */
    temp = 0;
    if (pConfig->I2C_ACKControl == I2C_ACK_ENABLE)
    {
        temp = I2C_CR1_ACK;
    }
    pI2Cx->CR1 = temp;

    /* 6. Enable peripheral (PE) — always last */
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
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    if ((pI2CDriver == NULL) || (pTxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }

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

    /* Step 7 — wait for BTF: last byte fully shifted out */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET);

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
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    if ((pI2CDriver == NULL) || (pTxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }

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

    /* Step 8 — wait for BTF, then release the bus */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_BTF) != FLAG_SET);
    I2C_GenerateSTOP(pI2CDriver);

    return STATUS_OK;
}

/* --------------------------------------------------------------------------
 * Receive phase (static helper, shared by both read functions)
 * Caller must be already addressed (ADDR set) — this routine programs the
 * ACK strategy, clears ADDR and collects Len bytes:
 *   Len == 1 : ACK off before ADDR is cleared, so the target sends one byte
 *   Len >  1 : EV7 (RXNE) for the first Len-2 bytes, then EV8 (BTF + ACK off)
 *              for the last two bytes read back-to-back from DR.
 * -------------------------------------------------------------------------- */
static DriverStatus_t I2C_ReceivePhase(i2c_driver_t *pI2CDriver,
                                       uint8_t *pRxBuffer,
                                       uint16_t Len)
{
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;
    uint16_t i;

    /* Step A — ACK strategy (must be set before ADDR is cleared for Len == 1) */
    if (Len == 1U)
    {
        I2C_ManageAck(pI2CDriver, I2C_ACK_DISABLE);
    }
    else
    {
        I2C_ManageAck(pI2CDriver, I2C_ACK_ENABLE);
    }

    /* Step B — clear ADDR: read SR1 then SR2 (mandatory order) */
    (void)pI2Cx->SR1;
    (void)pI2Cx->SR2;

    /* Step C — receive the data bytes */
    if (Len == 1U)
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
    }
    else
    {
        /* EV7 — receive Len-2 bytes with ACK enabled */
        for (i = 0U; i < (Len - 2U); i++)
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
        }

        /* EV8 — last two bytes: wait BTF, NACK the final byte, read DR twice */
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
        *pRxBuffer++ = (uint8_t)pI2Cx->DR;   /* (Len-1)th byte, clears BTF */
        *pRxBuffer++ = (uint8_t)pI2Cx->DR;   /* Len-th byte                */
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
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    if ((pI2CDriver == NULL) || (pRxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }

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

    /* Step 5 — ACK strategy + clear ADDR + collect data (EV7 / EV8) */
    if (I2C_ReceivePhase(pI2CDriver, pRxBuffer, Len) != STATUS_OK)
    {
        return STATUS_ERROR;
    }

    /* Step 6 — release the bus, unless a Repeated-Start read follows */
    if (Sr == I2C_STOP)
    {
        I2C_GenerateSTOP(pI2CDriver);
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
    I2C_TypeDef *pI2Cx = pI2CDriver->pI2Cx;

    if ((pI2CDriver == NULL) || (pRxBuffer == NULL) || (Len == 0U))
    {
        return STATUS_ERROR;
    }

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

    /* Step 7 — wait for REG_ADDR shifted out (TXE), then Repeated START */
    while (I2C_GetFlagStatus(pI2CDriver, FLAG_I2C_SR1_TXE) != FLAG_SET)
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

    /* Step 11 — ACK strategy + clear ADDR + collect data (EV7 / EV8) */
    if (I2C_ReceivePhase(pI2CDriver, pRxBuffer, Len) != STATUS_OK)
    {
        return STATUS_ERROR;
    }

    /* Step 12 — release the bus */
    I2C_GenerateSTOP(pI2CDriver);

    return STATUS_OK;
}
