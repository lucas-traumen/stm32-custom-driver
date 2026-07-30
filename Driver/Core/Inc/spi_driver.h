#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include "stm32f407xx.h"
#include "stm32f4xx_common.h"
#include "gpio_driver.h"

#ifdef __cplusplus
extern "C" {
#endif


/* --------------------------------------------------------------------------
 * SPI configuration values
 * Values are written into their corresponding register bit fields.
 * -------------------------------------------------------------------------- */
#define SPI_DEVICE_MODE_SLAVE          0U
#define SPI_DEVICE_MODE_MASTER         1U

#define SPI_BUS_CONFIG_FD              0U
#define SPI_BUS_CONFIG_HD              1U
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY  2U

#define SPI_DFF_8bits                  0U
#define SPI_DFF_16bits                 1U

#define MSB_TRANSMITTED_FIRST          0U
#define LSB_TRANSMITTED_FIRST          1U

#define SPI_CPOL_LOW                   0U
#define SPI_CPOL_HIGH                  1U

#define SPI_CPHA_LOW                   0U
#define SPI_CPHA_HIGH                  1U

#define SPI_SSM_DI                     0U
#define SPI_SSM_EN                     1U

#define SPI_SCLK_SPEED_DIV2            0U
#define SPI_SCLK_SPEED_DIV4            1U
#define SPI_SCLK_SPEED_DIV8            2U
#define SPI_SCLK_SPEED_DIV16           3U
#define SPI_SCLK_SPEED_DIV32           4U
#define SPI_SCLK_SPEED_DIV64           5U
#define SPI_SCLK_SPEED_DIV128          6U
#define SPI_SCLK_SPEED_DIV256          7U

/* --------------------------------------------------------------------------
 * SPI status flags
 * -------------------------------------------------------------------------- */
#define FLAG_SPI_SR_RXNE               SPI_SR_RXNE
#define FLAG_SPI_SR_TXE                SPI_SR_TXE
#define FLAG_SPI_SR_CHSIDE             SPI_SR_CHSIDE
#define FLAG_SPI_SR_UDR                SPI_SR_UDR
#define FLAG_SPI_SR_CRCERR             SPI_SR_CRCERR
#define FLAG_SPI_SR_MODF               SPI_SR_MODF
#define FLAG_SPI_SR_OVR                SPI_SR_OVR
#define FLAG_SPI_SR_BSY                SPI_SR_BSY
#define FLAG_SPI_SR_FRE                SPI_SR_FRE

/* --------------------------------------------------------------------------
 * Interrupt states and events
 * -------------------------------------------------------------------------- */
#define SPI_READY                      0U
#define SPI_BUSY_IN_TX                 1U
#define SPI_BUSY_IN_RX                 2U

#define SPI_EVENT_TX_CMPLT             1U
#define SPI_EVENT_RX_CMPLT             2U
#define SPI_EVENT_TXRX_CMPLT           3U
#define SPI_EVENT_OVR_ERR              4U

typedef enum
{
    SPI_IT_MODE_NONE = 0,
    SPI_IT_MODE_TX,
    SPI_IT_MODE_RX,
    SPI_IT_MODE_TXRX
} SPI_ITMode_t;

/* --------------------------------------------------------------------------
 * Driver structures
 * -------------------------------------------------------------------------- */
typedef struct
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_DFF;
    uint8_t SPI_Frame_format;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
    uint8_t speed;
} SPI_Config_t;

typedef struct
{
    SPI_TypeDef *pSPIx;
    SPI_Config_t SPIConfig;

    /* Software chip-select. Set CS_Port = NULL when not used. */
    GPIO_TypeDef *CS_Port;
    uint8_t CS_Pin;

    /* Interrupt transfer context. */
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    volatile uint16_t TxLen;
    volatile uint16_t RxLen;
    /* Number of dummy frames the TXE ISR must send to generate RX clock. */
    volatile uint16_t TxDummyLen;
    /* Discard RX frames produced while sending command/TX bytes. */
    volatile uint16_t RxDiscardLen;
    volatile uint8_t TxState;
    volatile uint8_t RxState;
    volatile SPI_ITMode_t ITMode;
    volatile uint8_t AutoCS;

    /* One-deep interrupt queue. Currently used to queue Receive_IT after
     * Transmit_IT so command + read can remain one CS-low transaction. */
    uint8_t *pPendingTxBuffer;
    uint8_t *pPendingRxBuffer;
    volatile uint16_t PendingTxLen;
    volatile uint16_t PendingRxLen;
    volatile SPI_ITMode_t PendingITMode;
    volatile uint8_t PendingActive;
} SPI_Handle_t;

typedef void (*SPI_Callback_t)(SPI_Handle_t *pSPIHandle, uint8_t AppEvent);

/* Handle is defined by the application, normally in main.c. */
extern SPI_Handle_t hspi1;
extern SPI_Handle_t hspi2;

/* --------------------------------------------------------------------------
 * Clock, GPIO and peripheral control
 * -------------------------------------------------------------------------- */
void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t EnorDi);
void SPI_DeInit(SPI_TypeDef *pSPIx);
void SPI_GpioConfig(SPI_TypeDef *pSPIx);
void SPI_Init(SPI_Handle_t *pSPIHandle);

void SPI_PeripheralControl(SPI_TypeDef *pSPIx, uint8_t EnorDi);
void SPI_SSI_Config(SPI_TypeDef *pSPIx, uint8_t EnorDi);
void SPI_SSOE_Config(SPI_TypeDef *pSPIx, uint8_t EnorDi);
void SPI_ChipSelect(SPI_Handle_t *pSPIHandle, uint8_t Select);
uint8_t SPI_GetFlagStatus(SPI_TypeDef *pSPIx, uint32_t Flag);

/* --------------------------------------------------------------------------
 * Blocking API
 * Size is always the number of bytes.
 * In 16-bit DFF mode, Size must be even.
 *
 * SPI_Transmit() and SPI_Receive() do not drive software CS automatically.
 * Use SPI_ChipSelect() around one or more separated blocking calls when a
 * slave transaction must remain continuous. SPI_TransmitReceive() manages
 * software CS automatically because it is a complete transaction.
 * -------------------------------------------------------------------------- */
DriverStatus_t SPI_Transmit(SPI_Handle_t *pSPIHandle,
                            const uint8_t *pTxData,
                            uint16_t Size,
                            uint32_t Timeout);

DriverStatus_t SPI_Receive(SPI_Handle_t *pSPIHandle,
                           uint8_t *pRxData,
                           uint16_t Size,
                           uint32_t Timeout);

DriverStatus_t SPI_TransmitReceive(SPI_Handle_t *pSPIHandle,
                                   const uint8_t *pTxData,
                                   uint8_t *pRxData,
                                   uint16_t Size,
                                   uint32_t Timeout);

/* --------------------------------------------------------------------------
 * Interrupt API
 * Callback executes inside SPIx_IRQHandler; keep it short and do not delay.
 * -------------------------------------------------------------------------- */
void SPI_RegisterCallback(SPI_TypeDef *pSPIx, SPI_Callback_t callback);

DriverStatus_t SPI_Transmit_IT(SPI_Handle_t *pSPIHandle,
                               uint8_t *pTxData,
                               uint16_t Size);

DriverStatus_t SPI_Receive_IT(SPI_Handle_t *pSPIHandle,
                              uint8_t *pRxData,
                              uint16_t Size);

/* Send TxSize command/data bytes first, discard the RX bytes generated during
 * that transmit phase, then send dummy bytes automatically to clock RxSize
 * response bytes into pRxData. This combined API manages software CS
 * automatically. SPI_Transmit_IT() and SPI_Receive_IT() do not. */
DriverStatus_t SPI_TransmitReceive_IT(SPI_Handle_t *pSPIHandle,
                                      uint8_t *pTxData,
                                      uint16_t TxSize,
                                      uint8_t *pRxData,
                                      uint16_t RxSize);

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DRIVER_H */
