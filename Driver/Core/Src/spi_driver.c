#include "spi_driver.h"
#include "rcc_driver.h"

/* 1 ms counter incremented by SysTick_Handler(). */
extern volatile uint32_t uwTick;

/* ========================================================================== */
/* Internal helpers                                                           */
/* ========================================================================== */

static inline uint8_t SPI_FrameBytes(const SPI_TypeDef *pSPIx)
{
    return (pSPIx->CR1 & SPI_CR1_DFF) ? 2U : 1U;
}

static inline void SPI_WriteDR8(SPI_TypeDef *pSPIx, uint8_t Data)
{
    *(__IO uint8_t *)&pSPIx->DR = Data;
}

static inline void SPI_WriteDR16(SPI_TypeDef *pSPIx, uint16_t Data)
{
    *(__IO uint16_t *)&pSPIx->DR = Data;
}

static inline uint8_t SPI_ReadDR8(SPI_TypeDef *pSPIx)
{
    return *(__IO uint8_t *)&pSPIx->DR;
}

static inline uint16_t SPI_ReadDR16(SPI_TypeDef *pSPIx)
{
    return *(__IO uint16_t *)&pSPIx->DR;
}


static DriverStatus_t SPI_WaitFlag(SPI_TypeDef *pSPIx,
                                   uint32_t Flag,
                                   uint32_t TickStart,
                                   uint32_t Timeout)
{
    while ((pSPIx->SR & Flag) == 0U)
    {
        if ((uwTick - TickStart) >= Timeout)
        {
            return STATUS_TIMEOUT;
        }
    }

    return STATUS_OK;
}

static DriverStatus_t SPI_WaitNotBusy(SPI_TypeDef *pSPIx,
                                      uint32_t TickStart,
                                      uint32_t Timeout)
{
    while ((pSPIx->SR & SPI_SR_BSY) != 0U)
    {
        if ((uwTick - TickStart) >= Timeout)
        {
            return STATUS_TIMEOUT;
        }
    }

    return STATUS_OK;
}

/* Used only from ISR. Do not depend on SysTick because SPI IRQ priority may be
 * higher than SysTick. */
static void SPI_WaitNotBusyFromISR(SPI_TypeDef *pSPIx)
{
    uint32_t Guard = 10000U;

    while (((pSPIx->SR & SPI_SR_BSY) != 0U) && (Guard > 0U))
    {
        Guard--;
    }
}

/* Clear stale RXNE/OVR before a new interrupt transaction. OVR clear sequence
 * on STM32F4 is DR read followed by SR read. */
static void SPI_ClearPendingRx(SPI_TypeDef *pSPIx)
{
    volatile uint32_t Dummy;

    if ((pSPIx->SR & (SPI_SR_RXNE | SPI_SR_OVR)) != 0U)
    {
        Dummy = pSPIx->DR;
        Dummy = pSPIx->SR;
        (void)Dummy;
    }
}

/* ========================================================================== */
/* Clock, reset and GPIO                                                       */
/* ========================================================================== */

void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
    }
    else
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_DI();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_DI();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_DI();
        }
    }
}

void SPI_DeInit(SPI_TypeDef *pSPIx)
{
    if (pSPIx == SPI1)
    {
        SPI1_PCLK_RESET();
    }
    else if (pSPIx == SPI2)
    {
        SPI2_PCLK_RESET();
    }
    else if (pSPIx == SPI3)
    {
        SPI3_PCLK_RESET();
    }
}

void SPI_GpioConfig(SPI_TypeDef *pSPIx)
{
    GPIO_Handle_t Gpio = {0};

    Gpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    Gpio.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    Gpio.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    Gpio.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

    if (pSPIx == SPI1)
    {
        /* SPI1: PA5=SCK, PA6=MISO, PA7=MOSI, AF5.
         * PA4 is not configured because this driver uses a separate software CS. */
        GPIO_PeriClockControl(GPIOA, ENABLE);
        Gpio.pGPIOx = GPIOA;
        Gpio.GPIO_PinConfig.GPIO_PinAltFunMode = AF5;

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
        GPIO_Init(&Gpio);

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
        GPIO_Init(&Gpio);

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
        GPIO_Init(&Gpio);
    }
    else if (pSPIx == SPI2)
    {
        /* SPI2: PB13=SCK, PB14=MISO, PB15=MOSI, AF5. */
        GPIO_PeriClockControl(GPIOB, ENABLE);
        Gpio.pGPIOx = GPIOB;
        Gpio.GPIO_PinConfig.GPIO_PinAltFunMode = AF5;

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
        GPIO_Init(&Gpio);

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
        GPIO_Init(&Gpio);

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
        GPIO_Init(&Gpio);
    }
    else if (pSPIx == SPI3)
    {
        /* SPI3: PC10=SCK, PC11=MISO, PC12=MOSI, AF6. */
        GPIO_PeriClockControl(GPIOC, ENABLE);
        Gpio.pGPIOx = GPIOC;
        Gpio.GPIO_PinConfig.GPIO_PinAltFunMode = AF6;

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
        GPIO_Init(&Gpio);

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
        GPIO_Init(&Gpio);

        Gpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
        GPIO_Init(&Gpio);
    }
}

/* ========================================================================== */
/* Peripheral configuration and control                                        */
/* ========================================================================== */

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    SPI_TypeDef *pSPIx;
    uint32_t Temp;

    if ((pSPIHandle == NULL) || (pSPIHandle->pSPIx == NULL))
    {
        return;
    }

    pSPIx = pSPIHandle->pSPIx;
    SPI_PeriClockControl(pSPIx, ENABLE);

    /* Disable before changing CR1. */
    pSPIx->CR1 &= ~SPI_CR1_SPE;
    Temp = pSPIx->CR1;

    Temp &= ~(SPI_CR1_MSTR |
              SPI_CR1_BIDIMODE |
              SPI_CR1_BIDIOE |
              SPI_CR1_RXONLY |
              SPI_CR1_DFF |
              SPI_CR1_LSBFIRST |
              SPI_CR1_CPOL |
              SPI_CR1_CPHA |
              SPI_CR1_SSM |
              SPI_CR1_BR_Msk);

    Temp |= ((uint32_t)pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR_Pos);
    Temp |= ((uint32_t)pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF_Pos);
    Temp |= ((uint32_t)pSPIHandle->SPIConfig.SPI_Frame_format << SPI_CR1_LSBFIRST_Pos);
    Temp |= ((uint32_t)pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL_Pos);
    Temp |= ((uint32_t)pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA_Pos);
    Temp |= ((uint32_t)pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM_Pos);
    Temp |= ((uint32_t)pSPIHandle->SPIConfig.speed << SPI_CR1_BR_Pos);

    switch (pSPIHandle->SPIConfig.SPI_BusConfig)
    {
        case SPI_BUS_CONFIG_FD:
            /* 2-line full duplex: BIDIMODE=0, RXONLY=0. */
            break;

        case SPI_BUS_CONFIG_HD:
            /* 1-line bidirectional. Default direction is transmit. */
            Temp |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;
            break;

        case SPI_BUS_CONFIG_SIMPLEX_RXONLY:
            /* 2-line receive-only: BIDIMODE=0, RXONLY=1. */
            Temp |= SPI_CR1_RXONLY;
            break;

        default:
            return;
    }

    pSPIx->CR1 = Temp;
    pSPIx->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE);

    pSPIHandle->pTxBuffer = NULL;
    pSPIHandle->pRxBuffer = NULL;
    pSPIHandle->TxLen = 0U;
    pSPIHandle->RxLen = 0U;
    pSPIHandle->TxDummyLen = 0U;
    pSPIHandle->RxDiscardLen = 0U;
    pSPIHandle->TxState = SPI_READY;
    pSPIHandle->RxState = SPI_READY;
    pSPIHandle->ITMode = SPI_IT_MODE_NONE;
    pSPIHandle->AutoCS = 0U;
    pSPIHandle->pPendingTxBuffer = NULL;
    pSPIHandle->pPendingRxBuffer = NULL;
    pSPIHandle->PendingTxLen = 0U;
    pSPIHandle->PendingRxLen = 0U;
    pSPIHandle->PendingITMode = SPI_IT_MODE_NONE;
    pSPIHandle->PendingActive = 0U;

    /* Software NSS requires SSI=1 in master mode to avoid MODF. */
    if (pSPIHandle->SPIConfig.SPI_SSM == SPI_SSM_EN)
    {
        SPI_SSI_Config(pSPIx, ENABLE);
    }

    /* Software CS is active low; idle state must be high before first frame. */
    SPI_ChipSelect(pSPIHandle, DISABLE);
    SPI_PeripheralControl(pSPIx, ENABLE);
}

void SPI_PeripheralControl(SPI_TypeDef *pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        pSPIx->CR1 |= SPI_CR1_SPE;
    }
    else
    {
        pSPIx->CR1 &= ~SPI_CR1_SPE;
    }
}

void SPI_SSI_Config(SPI_TypeDef *pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        pSPIx->CR1 |= SPI_CR1_SSI;
    }
    else
    {
        pSPIx->CR1 &= ~SPI_CR1_SSI;
    }
}

void SPI_SSOE_Config(SPI_TypeDef *pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        pSPIx->CR2 |= SPI_CR2_SSOE;
    }
    else
    {
        pSPIx->CR2 &= ~SPI_CR2_SSOE;
    }
}

void SPI_ChipSelect(SPI_Handle_t *pSPIHandle, uint8_t Select)
{
    if ((pSPIHandle == NULL) || (pSPIHandle->CS_Port == NULL))
    {
        return;
    }

    if (Select == ENABLE)
    {
        /* CS low: select slave. */
        pSPIHandle->CS_Port->BSRR = (1UL << ((uint32_t)pSPIHandle->CS_Pin + 16UL));
    }
    else
    {
        /* CS high: deselect slave. */
        pSPIHandle->CS_Port->BSRR = (1UL << pSPIHandle->CS_Pin);
    }
}

uint8_t SPI_GetFlagStatus(SPI_TypeDef *pSPIx, uint32_t Flag)
{
    return ((pSPIx->SR & Flag) != 0U) ? FLAG_SET : FLAG_RESET;
}

/* ========================================================================== */
/* Blocking API                                                               */
/* ========================================================================== */

DriverStatus_t SPI_Transmit(SPI_Handle_t *pSPIHandle,
                            const uint8_t *pTxData,
                            uint16_t Size,
                            uint32_t Timeout)
{
    SPI_TypeDef *pSPIx;
    uint8_t FrameBytes;
    uint32_t TickStart;
    DriverStatus_t Status = STATUS_OK;

    if ((pSPIHandle == NULL) || (pTxData == NULL) || (Size == 0U))
    {
        return STATUS_ERROR;
    }

    pSPIx = pSPIHandle->pSPIx;
    FrameBytes = SPI_FrameBytes(pSPIx);

    if ((FrameBytes == 2U) && ((Size & 1U) != 0U))
    {
        return STATUS_ERROR;
    }

    TickStart = uwTick;
    while (Size > 0U)
    {
        Status = SPI_WaitFlag(pSPIx, SPI_SR_TXE, TickStart, Timeout);
        if (Status != STATUS_OK)
        {
            break;
        }

        if (FrameBytes == 2U)
        {
            SPI_WriteDR16(pSPIx, (uint16_t)pTxData[0] |
                          (uint16_t)((uint16_t)pTxData[1] << 8U));
            pTxData += 2U;
            Size -= 2U;
        }
        else
        {
            SPI_WriteDR8(pSPIx, *pTxData++);
            Size--;
        }

        /* Every transmitted frame also produces a received frame. Read and
         * discard it so RXNE does not become OVR. */
        Status = SPI_WaitFlag(pSPIx, SPI_SR_RXNE, TickStart, Timeout);
        if (Status != STATUS_OK)
        {
            break;
        }
        if (FrameBytes == 2U)
        {
            (void)SPI_ReadDR16(pSPIx);
        }
        else
        {
            (void)SPI_ReadDR8(pSPIx);
        }
    }

    if (Status == STATUS_OK)
    {
        Status = SPI_WaitNotBusy(pSPIx, TickStart, Timeout);
    }

    return Status;
}

DriverStatus_t SPI_Receive(SPI_Handle_t *pSPIHandle,
                           uint8_t *pRxData,
                           uint16_t Size,
                           uint32_t Timeout)
{
    SPI_TypeDef *pSPIx;
    uint8_t FrameBytes;
    uint32_t TickStart;
    DriverStatus_t Status = STATUS_OK;

    if ((pSPIHandle == NULL) || (pRxData == NULL) || (Size == 0U))
    {
        return STATUS_ERROR;
    }

    pSPIx = pSPIHandle->pSPIx;
    FrameBytes = SPI_FrameBytes(pSPIx);

    if ((FrameBytes == 2U) && ((Size & 1U) != 0U))
    {
        return STATUS_ERROR;
    }

    TickStart = uwTick;
    while (Size > 0U)
    {
        Status = SPI_WaitFlag(pSPIx, SPI_SR_TXE, TickStart, Timeout);
        if (Status != STATUS_OK)
        {
            break;
        }

        if (FrameBytes == 2U)
        {
            SPI_WriteDR16(pSPIx, 0xFFFFU);
        }
        else
        {
            SPI_WriteDR8(pSPIx, 0xFFU);
        }

        Status = SPI_WaitFlag(pSPIx, SPI_SR_RXNE, TickStart, Timeout);
        if (Status != STATUS_OK)
        {
            break;
        }

        if (FrameBytes == 2U)
        {
            uint16_t Value = SPI_ReadDR16(pSPIx);
            pRxData[0] = (uint8_t)(Value & 0xFFU);
            pRxData[1] = (uint8_t)((Value >> 8U) & 0xFFU);
            pRxData += 2U;
            Size -= 2U;
        }
        else
        {
            *pRxData++ = SPI_ReadDR8(pSPIx);
            Size--;
        }
    }

    if (Status == STATUS_OK)
    {
        Status = SPI_WaitNotBusy(pSPIx, TickStart, Timeout);
    }

    return Status;
}

DriverStatus_t SPI_TransmitReceive(SPI_Handle_t *pSPIHandle,
                                   const uint8_t *pTxData,
                                   uint8_t *pRxData,
                                   uint16_t Size,
                                   uint32_t Timeout)
{
    SPI_TypeDef *pSPIx;
    uint8_t FrameBytes;
    uint32_t TickStart;
    DriverStatus_t Status = STATUS_OK;

    if ((pSPIHandle == NULL) || (pTxData == NULL) ||
        (pRxData == NULL) || (Size == 0U))
    {
        return STATUS_ERROR;
    }

    pSPIx = pSPIHandle->pSPIx;
    FrameBytes = SPI_FrameBytes(pSPIx);

    if ((FrameBytes == 2U) && ((Size & 1U) != 0U))
    {
        return STATUS_ERROR;
    }

    TickStart = uwTick;
    SPI_ChipSelect(pSPIHandle, ENABLE);

    while (Size > 0U)
    {
        Status = SPI_WaitFlag(pSPIx, SPI_SR_TXE, TickStart, Timeout);
        if (Status != STATUS_OK)
        {
            break;
        }

        if (FrameBytes == 2U)
        {
            SPI_WriteDR16(pSPIx, (uint16_t)pTxData[0] |
                          (uint16_t)((uint16_t)pTxData[1] << 8U));
        }
        else
        {
            SPI_WriteDR8(pSPIx, *pTxData);
        }

        Status = SPI_WaitFlag(pSPIx, SPI_SR_RXNE, TickStart, Timeout);
        if (Status != STATUS_OK)
        {
            break;
        }

        if (FrameBytes == 2U)
        {
            uint16_t Value = SPI_ReadDR16(pSPIx);
            pRxData[0] = (uint8_t)(Value & 0xFFU);
            pRxData[1] = (uint8_t)((Value >> 8U) & 0xFFU);
            pTxData += 2U;
            pRxData += 2U;
            Size -= 2U;
        }
        else
        {
            *pRxData++ = SPI_ReadDR8(pSPIx);
            pTxData++;
            Size--;
        }
    }

    if (Status == STATUS_OK)
    {
        Status = SPI_WaitNotBusy(pSPIx, TickStart, Timeout);
    }

    SPI_ChipSelect(pSPIHandle, DISABLE);
    return Status;
}

/* ========================================================================== */
/* Interrupt API                                                              */
/* ========================================================================== */

static void SPI_DefaultCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent)
{
    (void)pSPIHandle;
    (void)AppEvent;
}

static SPI_Callback_t SPI_Callbacks[3] =
{
    SPI_DefaultCallback,
    SPI_DefaultCallback,
    SPI_DefaultCallback
};

static uint8_t SPI_GetIndex(SPI_TypeDef *pSPIx)
{
    if (pSPIx == SPI1)
    {
        return 0U;
    }
    if (pSPIx == SPI2)
    {
        return 1U;
    }
    if (pSPIx == SPI3)
    {
        return 2U;
    }

    return 0xFFU;
}

void SPI_RegisterCallback(SPI_TypeDef *pSPIx, SPI_Callback_t Callback)
{
    uint8_t Index = SPI_GetIndex(pSPIx);

    if ((Index != 0xFFU) && (Callback != NULL))
    {
        SPI_Callbacks[Index] = Callback;
    }
}

static void SPI_ResetITState(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pTxBuffer = NULL;
    pSPIHandle->pRxBuffer = NULL;
    pSPIHandle->TxLen = 0U;
    pSPIHandle->RxLen = 0U;
    pSPIHandle->TxDummyLen = 0U;
    pSPIHandle->RxDiscardLen = 0U;
    pSPIHandle->TxState = SPI_READY;
    pSPIHandle->RxState = SPI_READY;
    pSPIHandle->ITMode = SPI_IT_MODE_NONE;
    pSPIHandle->AutoCS = 0U;
    pSPIHandle->pPendingTxBuffer = NULL;
    pSPIHandle->pPendingRxBuffer = NULL;
    pSPIHandle->PendingTxLen = 0U;
    pSPIHandle->PendingRxLen = 0U;
    pSPIHandle->PendingITMode = SPI_IT_MODE_NONE;
    pSPIHandle->PendingActive = 0U;
}

static void SPI_StartQueuedReceiveFromISR(SPI_Handle_t *pSPIHandle)
{
    SPI_TypeDef *pSPIx = pSPIHandle->pSPIx;
    uint8_t FrameBytes = SPI_FrameBytes(pSPIx);

    pSPIHandle->pTxBuffer = NULL;
    pSPIHandle->pRxBuffer = pSPIHandle->pPendingRxBuffer;
    pSPIHandle->TxLen = 0U;
    pSPIHandle->RxLen = pSPIHandle->PendingRxLen;
    pSPIHandle->TxDummyLen = pSPIHandle->PendingRxLen;
    pSPIHandle->RxDiscardLen = 0U;
    pSPIHandle->TxState = SPI_BUSY_IN_TX;
    pSPIHandle->RxState = SPI_BUSY_IN_RX;
    pSPIHandle->ITMode = SPI_IT_MODE_RX;

    pSPIHandle->pPendingTxBuffer = NULL;
    pSPIHandle->pPendingRxBuffer = NULL;
    pSPIHandle->PendingTxLen = 0U;
    pSPIHandle->PendingRxLen = 0U;
    pSPIHandle->PendingITMode = SPI_IT_MODE_NONE;
    pSPIHandle->PendingActive = 0U;

    pSPIx->CR2 |= SPI_CR2_RXNEIE;

    if ((pSPIHandle->TxDummyLen != 0U) && ((pSPIx->SR & SPI_SR_TXE) != 0U))
    {
        if (FrameBytes == 2U)
        {
            SPI_WriteDR16(pSPIx, 0xFFFFU);
            pSPIHandle->TxDummyLen -= 2U;
        }
        else
        {
            SPI_WriteDR8(pSPIx, 0xFFU);
            pSPIHandle->TxDummyLen--;
        }
    }

    if (pSPIHandle->TxDummyLen != 0U)
    {
        pSPIx->CR2 |= SPI_CR2_TXEIE;
    }
}

static void SPI_CompleteIT(SPI_Handle_t *pSPIHandle)
{
    SPI_TypeDef *pSPIx = pSPIHandle->pSPIx;
    SPI_ITMode_t CompletedMode = pSPIHandle->ITMode;
    uint8_t Index = SPI_GetIndex(pSPIx);

    pSPIx->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE);
    SPI_WaitNotBusyFromISR(pSPIx);
    if (pSPIHandle->AutoCS != 0U)
    {
        SPI_ChipSelect(pSPIHandle, DISABLE);
    }
    SPI_ResetITState(pSPIHandle);

    if (Index == 0xFFU)
    {
        return;
    }

    if (CompletedMode == SPI_IT_MODE_TX)
    {
        SPI_Callbacks[Index](pSPIHandle, SPI_EVENT_TX_CMPLT);
    }
    else if (CompletedMode == SPI_IT_MODE_RX)
    {
        SPI_Callbacks[Index](pSPIHandle, SPI_EVENT_RX_CMPLT);
    }
    else if (CompletedMode == SPI_IT_MODE_TXRX)
    {
        SPI_Callbacks[Index](pSPIHandle, SPI_EVENT_TXRX_CMPLT);
    }
}

static void SPI_AbortIT(SPI_Handle_t *pSPIHandle)
{
    SPI_TypeDef *pSPIx = pSPIHandle->pSPIx;

    pSPIx->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE);
    SPI_ClearPendingRx(pSPIx);
    SPI_WaitNotBusyFromISR(pSPIx);
    if (pSPIHandle->AutoCS != 0U)
    {
        SPI_ChipSelect(pSPIHandle, DISABLE);
    }
    SPI_ResetITState(pSPIHandle);
}

static DriverStatus_t SPI_StartIT(SPI_Handle_t *pSPIHandle,
                                  uint8_t *pTxData,
                                  uint8_t *pRxData,
                                  uint16_t Size,
                                  SPI_ITMode_t Mode)
{
    SPI_TypeDef *pSPIx;
    uint8_t FrameBytes;

    if ((pSPIHandle == NULL) || (pSPIHandle->pSPIx == NULL) || (Size == 0U))
    {
        return STATUS_ERROR;
    }

    if (pSPIHandle->ITMode != SPI_IT_MODE_NONE)
    {
        return STATUS_BUSY;
    }

    if (((Mode == SPI_IT_MODE_TX) || (Mode == SPI_IT_MODE_TXRX)) &&
        (pTxData == NULL))
    {
        return STATUS_ERROR;
    }

    if (((Mode == SPI_IT_MODE_RX) || (Mode == SPI_IT_MODE_TXRX)) &&
        (pRxData == NULL))
    {
        return STATUS_ERROR;
    }

    pSPIx = pSPIHandle->pSPIx;
    FrameBytes = SPI_FrameBytes(pSPIx);

    if ((FrameBytes == 2U) && ((Size & 1U) != 0U))
    {
        return STATUS_ERROR;
    }

    /* Configure context while interrupt sources are disabled. */
    pSPIx->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE);
    SPI_ClearPendingRx(pSPIx);

    pSPIHandle->pTxBuffer = pTxData;
    pSPIHandle->pRxBuffer = pRxData;

    if (Mode == SPI_IT_MODE_TX)
    {
        /* TX-only still receives one dummy frame per transmitted frame.
         * Read/discard those RX frames before completing the transaction. */
        pSPIHandle->TxLen = Size;
        pSPIHandle->RxLen = 0U;
        pSPIHandle->TxDummyLen = 0U;
        pSPIHandle->RxDiscardLen = Size;
    }
    else if (Mode == SPI_IT_MODE_RX)
    {
        /* Master RX requires transmitting dummy frames to generate SCK. */
        pSPIHandle->TxLen = 0U;
        pSPIHandle->RxLen = Size;
        pSPIHandle->TxDummyLen = Size;
        pSPIHandle->RxDiscardLen = 0U;
    }
    else /* SPI_IT_MODE_TXRX */
    {
        pSPIHandle->TxLen = Size;
        pSPIHandle->RxLen = Size;
        pSPIHandle->TxDummyLen = 0U;
        pSPIHandle->RxDiscardLen = 0U;
    }

    pSPIHandle->ITMode = Mode;

    pSPIHandle->TxState = ((pSPIHandle->TxLen != 0U) ||
                           (pSPIHandle->TxDummyLen != 0U)) ? SPI_BUSY_IN_TX : SPI_READY;

    pSPIHandle->RxState = ((pSPIHandle->RxLen != 0U) ||
                           (pSPIHandle->RxDiscardLen != 0U)) ? SPI_BUSY_IN_RX : SPI_READY;

    pSPIHandle->AutoCS = 0U;

    /* Enable RX/error interrupts first. TXE interrupt normally starts the
     * transfer. In RX-only master mode, prime the first dummy frame here as
     * well; this avoids depending on an immediate TXE interrupt just to create
     * the first SCK pulse. Remaining dummy frames are queued by TXE IRQ. */
    pSPIx->CR2 |= SPI_CR2_RXNEIE;

    if ((Mode == SPI_IT_MODE_RX) && ((pSPIx->SR & SPI_SR_TXE) != 0U))
    {
        if (FrameBytes == 2U)
        {
            SPI_WriteDR16(pSPIx, 0xFFFFU);
            pSPIHandle->TxDummyLen -= 2U;
        }
        else
        {
            SPI_WriteDR8(pSPIx, 0xFFU);
            pSPIHandle->TxDummyLen--;
        }
    }

    if ((pSPIHandle->TxLen != 0U) || (pSPIHandle->TxDummyLen != 0U))
    {
        pSPIx->CR2 |= SPI_CR2_TXEIE;
    }

    return STATUS_OK;
}

DriverStatus_t SPI_Transmit_IT(SPI_Handle_t *pSPIHandle,
                               uint8_t *pTxData,
                               uint16_t Size)
{
    return SPI_StartIT(pSPIHandle, pTxData, NULL, Size, SPI_IT_MODE_TX);
}

DriverStatus_t SPI_Receive_IT(SPI_Handle_t *pSPIHandle,
                              uint8_t *pRxData,
                              uint16_t Size)
{
    uint8_t FrameBytes;

    if ((pSPIHandle == NULL) || (pSPIHandle->pSPIx == NULL) ||
        (pRxData == NULL) || (Size == 0U))
    {
        return STATUS_ERROR;
    }

    FrameBytes = SPI_FrameBytes(pSPIHandle->pSPIx);
    if ((FrameBytes == 2U) && ((Size & 1U) != 0U))
    {
        return STATUS_ERROR;
    }

    if (pSPIHandle->ITMode == SPI_IT_MODE_TX)
    {
        if (pSPIHandle->PendingActive != 0U)
        {
            return STATUS_BUSY;
        }

        /* Queue RX after the active TX phase. CS will be kept low, the TX
         * dummy RX bytes will be discarded, then dummy TX bytes will clock
         * the requested RX bytes. */
        pSPIHandle->pPendingTxBuffer = NULL;
        pSPIHandle->pPendingRxBuffer = pRxData;
        pSPIHandle->PendingTxLen = 0U;
        pSPIHandle->PendingRxLen = Size;
        pSPIHandle->PendingITMode = SPI_IT_MODE_RX;
        pSPIHandle->PendingActive = 1U;
        return STATUS_OK;
    }

    return SPI_StartIT(pSPIHandle, NULL, pRxData, Size, SPI_IT_MODE_RX);
}

DriverStatus_t SPI_TransmitReceive_IT(SPI_Handle_t *pSPIHandle,
                                      uint8_t *pTxData,
                                      uint16_t TxSize,
                                      uint8_t *pRxData,
                                      uint16_t RxSize)
{
    SPI_TypeDef *pSPIx;
    uint8_t FrameBytes;

    if ((pSPIHandle == NULL) || (pSPIHandle->pSPIx == NULL) ||
        (pTxData == NULL) || (pRxData == NULL) ||
        (TxSize == 0U) || (RxSize == 0U))
    {
        return STATUS_ERROR;
    }

    if (pSPIHandle->ITMode != SPI_IT_MODE_NONE)
    {
        return STATUS_BUSY;
    }

    pSPIx = pSPIHandle->pSPIx;
    FrameBytes = SPI_FrameBytes(pSPIx);

    if ((FrameBytes == 2U) && (((TxSize | RxSize) & 1U) != 0U))
    {
        return STATUS_ERROR;
    }

    pSPIx->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE | SPI_CR2_ERRIE);
    SPI_ClearPendingRx(pSPIx);

    /* Command-then-read transaction:
     * - Transmit TxSize bytes from pTxData.
     * - Discard the Rx frames generated during that transmit phase.
     * - Transmit RxSize dummy bytes to generate SCK.
     * - Store those RxSize response bytes into pRxData.
     */
    pSPIHandle->pTxBuffer = pTxData;
    pSPIHandle->pRxBuffer = pRxData;
    pSPIHandle->TxLen = TxSize;
    pSPIHandle->RxLen = RxSize;
    pSPIHandle->TxDummyLen = RxSize;
    pSPIHandle->RxDiscardLen = TxSize;
    pSPIHandle->TxState = SPI_BUSY_IN_TX;
    pSPIHandle->RxState = SPI_BUSY_IN_RX;
    pSPIHandle->ITMode = SPI_IT_MODE_TXRX;
    pSPIHandle->AutoCS = 1U;

    SPI_ChipSelect(pSPIHandle, ENABLE);
    pSPIx->CR2 |= SPI_CR2_TXEIE | SPI_CR2_RXNEIE;

    return STATUS_OK;
}

static void SPI_HandleTXE(SPI_Handle_t *pSPIHandle)
{
    SPI_TypeDef *pSPIx = pSPIHandle->pSPIx;
    uint8_t FrameBytes = SPI_FrameBytes(pSPIx);
    uint8_t SendDummy = 0U;

    if (pSPIHandle->TxLen == 0U)
    {
        if (pSPIHandle->TxDummyLen == 0U)
        {
            pSPIx->CR2 &= ~SPI_CR2_TXEIE;
            return;
        }
        SendDummy = 1U;
    }

    if (FrameBytes == 2U)
    {
        uint16_t Value;

        if (SendDummy != 0U)
        {
            Value = 0xFFFFU;
            pSPIHandle->TxDummyLen -= 2U;
        }
        else
        {
            Value = (uint16_t)pSPIHandle->pTxBuffer[0] |
                    (uint16_t)((uint16_t)pSPIHandle->pTxBuffer[1] << 8U);
            pSPIHandle->pTxBuffer += 2U;
            pSPIHandle->TxLen -= 2U;
        }

        SPI_WriteDR16(pSPIx, Value);
    }
    else
    {
        uint8_t Value;

        if (SendDummy != 0U)
        {
            Value = 0xFFU;
            pSPIHandle->TxDummyLen--;
        }
        else
        {
            Value = *pSPIHandle->pTxBuffer++;
            pSPIHandle->TxLen--;
        }

        SPI_WriteDR8(pSPIx, Value);
    }

    if ((pSPIHandle->TxLen == 0U) && (pSPIHandle->TxDummyLen == 0U))
    {
        /* Stop TXE requests after the final real/dummy frame is queued.
         * RXNEIE remains enabled until the final received frame is read/discarded. */
        pSPIx->CR2 &= ~SPI_CR2_TXEIE;
    }
}

static void SPI_HandleRXNE(SPI_Handle_t *pSPIHandle)
{
    SPI_TypeDef *pSPIx = pSPIHandle->pSPIx;
    uint8_t FrameBytes = SPI_FrameBytes(pSPIx);

    if (pSPIHandle->RxDiscardLen > 0U)
    {
        if (FrameBytes == 2U)
        {
            (void)SPI_ReadDR16(pSPIx);
            pSPIHandle->RxDiscardLen -= 2U;
        }
        else
        {
            (void)SPI_ReadDR8(pSPIx);
            pSPIHandle->RxDiscardLen--;
        }

        if ((pSPIHandle->RxDiscardLen == 0U) &&
            (pSPIHandle->ITMode == SPI_IT_MODE_TX) &&
            (pSPIHandle->TxLen == 0U) &&
            (pSPIHandle->TxDummyLen == 0U))
        {
            if ((pSPIHandle->PendingActive != 0U) &&
                (pSPIHandle->PendingITMode == SPI_IT_MODE_RX))
            {
                SPI_StartQueuedReceiveFromISR(pSPIHandle);
            }
            else
            {
                SPI_CompleteIT(pSPIHandle);
            }
        }
        return;
    }

    if (pSPIHandle->RxLen == 0U)
    {
        (void)SPI_ReadDR8(pSPIx);
        return;
    }

    if (FrameBytes == 2U)
    {
        uint16_t Value = SPI_ReadDR16(pSPIx);

        if ((pSPIHandle->ITMode == SPI_IT_MODE_RX) ||
            (pSPIHandle->ITMode == SPI_IT_MODE_TXRX))
        {
            pSPIHandle->pRxBuffer[0] = (uint8_t)(Value & 0xFFU);
            pSPIHandle->pRxBuffer[1] = (uint8_t)((Value >> 8U) & 0xFFU);
            pSPIHandle->pRxBuffer += 2U;
        }

        pSPIHandle->RxLen -= 2U;
    }
    else
    {
        uint8_t Value = SPI_ReadDR8(pSPIx);

        if ((pSPIHandle->ITMode == SPI_IT_MODE_RX) ||
            (pSPIHandle->ITMode == SPI_IT_MODE_TXRX))
        {
            *pSPIHandle->pRxBuffer++ = Value;
        }

        pSPIHandle->RxLen--;
    }

    if (pSPIHandle->RxLen == 0U)
    {
        SPI_CompleteIT(pSPIHandle);
    }
}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
    SPI_TypeDef *pSPIx;
    uint32_t Status;
    uint32_t Control2;
    uint8_t Index;

    if ((pSPIHandle == NULL) || (pSPIHandle->pSPIx == NULL))
    {
        return;
    }

    pSPIx = pSPIHandle->pSPIx;
    Index = SPI_GetIndex(pSPIx);
    Status = pSPIx->SR;
    Control2 = pSPIx->CR2;

    if (((Status & SPI_SR_OVR) != 0U) &&
        ((Control2 & SPI_CR2_ERRIE) != 0U))
    {
        SPI_AbortIT(pSPIHandle);

        if (Index != 0xFFU)
        {
            SPI_Callbacks[Index](pSPIHandle, SPI_EVENT_OVR_ERR);
        }
        return;
    }

    /* Read received data first to minimize overrun risk. */
    if (((Status & SPI_SR_RXNE) != 0U) &&
        ((Control2 & SPI_CR2_RXNEIE) != 0U))
    {
        SPI_HandleRXNE(pSPIHandle);

        if (pSPIHandle->ITMode == SPI_IT_MODE_NONE)
        {
            return;
        }
    }

    /* Flags may have changed after reading DR. */
    Status = pSPIx->SR;
    Control2 = pSPIx->CR2;

    if (((Status & SPI_SR_TXE) != 0U) &&
        ((Control2 & SPI_CR2_TXEIE) != 0U))
    {
        SPI_HandleTXE(pSPIHandle);
    }
}