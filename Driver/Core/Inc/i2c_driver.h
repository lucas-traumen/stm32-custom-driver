#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include "stm32f407xx.h"
#include "stm32f4xx_common.h"
#include "rcc_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------------------
 * I2C configuration values
 * -------------------------------------------------------------------------- */
#define I2C_SCL_SPEED_SM       100000U
#define I2C_SCL_SPEED_FM       400000U

#define I2C_ACK_DISABLE        0U
#define I2C_ACK_ENABLE         1U

#define I2C_FM_DUTY_2          0U
#define I2C_FM_DUTY_16_9       1U

/* Address frame R/W bit */
#define I2C_WRITE              0U
#define I2C_READ               1U

/* STOP / Repeated-Start behaviour at the end of a transaction (Sr param) */
#define I2C_NO_STOP            0U
#define I2C_STOP               1U

/* --------------------------------------------------------------------------
 * START/STOP generation bits live in CR1 on STM32F4 (RM0090):
 *   I2C_CR1_START = bit 8, I2C_CR1_STOP = bit 9.
 * Already defined in stm32f407xx.h; aliases kept for driver readability.
 * -------------------------------------------------------------------------- */
#define I2C_CR2_START          I2C_CR1_START
#define I2C_CR2_STOP           I2C_CR1_STOP

/* OAR1 bit 14 is reserved and must always be kept at 1 (RM0090). */
#define I2C_OAR1_RES14         (0x1UL << 14U)

/* --------------------------------------------------------------------------
 * Status flag macros
 * Each macro encodes which status register the bit lives in:
 *   SR1 flags keep the raw value, SR2 flags set bit 31 as a marker.
 * I2C_GetFlagStatus() decodes the marker and reads the right register.
 * -------------------------------------------------------------------------- */
#define I2C_FLAG_SR1(f)        ((uint32_t)(f))
#define I2C_FLAG_SR2(f)        (0x80000000UL | (uint32_t)(f))

#define FLAG_I2C_SR1_SB        I2C_FLAG_SR1(I2C_SR1_SB)
#define FLAG_I2C_SR1_ADDR      I2C_FLAG_SR1(I2C_SR1_ADDR)
#define FLAG_I2C_SR1_BTF       I2C_FLAG_SR1(I2C_SR1_BTF)
#define FLAG_I2C_SR1_ADD10     I2C_FLAG_SR1(I2C_SR1_ADD10)
#define FLAG_I2C_SR1_RXNE      I2C_FLAG_SR1(I2C_SR1_RXNE)
#define FLAG_I2C_SR1_TXE       I2C_FLAG_SR1(I2C_SR1_TXE)
#define FLAG_I2C_SR1_BERR      I2C_FLAG_SR1(I2C_SR1_BERR)
#define FLAG_I2C_SR1_ARLO      I2C_FLAG_SR1(I2C_SR1_ARLO)
#define FLAG_I2C_SR1_AF        I2C_FLAG_SR1(I2C_SR1_AF)
#define FLAG_I2C_SR1_OVR       I2C_FLAG_SR1(I2C_SR1_OVR)

#define FLAG_I2C_SR2_BUSY      I2C_FLAG_SR2(I2C_SR2_BUSY)
#define FLAG_I2C_SR2_MSL       I2C_FLAG_SR2(I2C_SR2_MSL)
#define FLAG_I2C_SR2_TRA       I2C_FLAG_SR2(I2C_SR2_TRA)
#define FLAG_I2C_SR2_DUALF     I2C_FLAG_SR2(I2C_SR2_DUALF)

/* --------------------------------------------------------------------------
 * I2C interrupt transfer states
 * -------------------------------------------------------------------------- */
#define I2C_STATE_READY         0U
#define I2C_STATE_BUSY_TX       1U
#define I2C_STATE_BUSY_RX       2U

/* --------------------------------------------------------------------------
 * I2C error codes
 * -------------------------------------------------------------------------- */
#define I2C_ERROR_NONE          0U
#define I2C_ERROR_AF            (1U << 0U)
#define I2C_ERROR_BERR          (1U << 1U)
#define I2C_ERROR_ARLO          (1U << 2U)
#define I2C_ERROR_OVR           (1U << 3U)

/* --------------------------------------------------------------------------
 * I2C event codes for callback
 * -------------------------------------------------------------------------- */
#define I2C_EVENT_TX_COMPLETE   0U
#define I2C_EVENT_RX_COMPLETE   1U
#define I2C_EVENT_ERROR         2U

/* --------------------------------------------------------------------------
 * Driver structures
 * -------------------------------------------------------------------------- */
typedef struct
{
    uint32_t I2C_SCLSpeed;        /* I2C_SCL_SPEED_SM / I2C_SCL_SPEED_FM */
    uint8_t  I2C_DeviceAddress;   /* own address (MCU = target), 7-bit     */
    uint8_t  I2C_ACKControl;      /* I2C_ACK_DISABLE / I2C_ACK_ENABLE      */
    uint8_t  I2C_FMDutyCycle;     /* I2C_FM_DUTY_2 / I2C_FM_DUTY_16_9      */
} I2C_Config_t;

typedef struct i2c_driver_t i2c_driver_t;

typedef void (*I2C_Callback_t)(i2c_driver_t *pI2CDriver, uint8_t AppEvent);

typedef struct i2c_driver_t
{
    I2C_TypeDef  *pI2Cx;          /* I2C1 / I2C2 / I2C3                    */
    I2C_Config_t I2CConfig;

    /* Interrupt transfer context */
    uint8_t  *pTxBuffer;
    uint8_t  *pRxBuffer;
    volatile uint32_t TxLen;
    volatile uint32_t RxLen;
    volatile uint32_t RxSize;
    uint16_t TargetAddr;
    volatile uint32_t ErrorCode;
    volatile uint8_t  State;
    uint8_t  RepeatedStart;
    I2C_Callback_t Callback;
} i2c_driver_t;

/* --------------------------------------------------------------------------
 * Clock, init and control API
 * -------------------------------------------------------------------------- */
void I2C_PeriClockControl(i2c_driver_t *pI2CDriver, uint8_t EnorDi);
void I2C_Init(i2c_driver_t *pI2CDriver);
void I2C_DeInit(i2c_driver_t *pI2CDriver);
void I2C_PeripheralControl(i2c_driver_t *pI2CDriver, uint8_t EnorDi);

/* --------------------------------------------------------------------------
 * Status API
 * -------------------------------------------------------------------------- */
uint8_t I2C_GetFlagStatus(i2c_driver_t *pI2CDriver, uint32_t Flag);
void I2C_ClearFlag(i2c_driver_t *pI2CDriver, uint32_t Flag);
void I2C_ManageAck(i2c_driver_t *pI2CDriver, uint8_t EnorDi);
void I2C_ErrorRecovery(i2c_driver_t *pI2CDriver);

/* --------------------------------------------------------------------------
 * START / STOP generation
 * -------------------------------------------------------------------------- */
void I2C_GenerateSTART(i2c_driver_t *pI2CDriver);
void I2C_GenerateSTOP(i2c_driver_t *pI2CDriver);

/* --------------------------------------------------------------------------
 * Blocking master transactions (polling)
 *
 * SlaveAddr is the 7-bit target address; the R/W bit is appended internally.
 * Sr selects the transaction end: I2C_STOP (default) or I2C_NO_STOP when the
 * bus must stay owned for a following Repeated-Start phase.
 * -------------------------------------------------------------------------- */
DriverStatus_t I2C_MasterSendData(i2c_driver_t *pI2CDriver,
                                  uint8_t *pTxBuffer,
                                  uint16_t Len,
                                  uint16_t SlaveAddr,
                                  uint8_t Sr);

DriverStatus_t I2C_MemWriteData(i2c_driver_t *pI2CDriver,
                                uint16_t SlaveAddr,
                                uint8_t MemAddr,
                                uint8_t *pTxBuffer,
                                uint16_t Len);

DriverStatus_t I2C_MasterReceiveData(i2c_driver_t *pI2CDriver,
                                     uint8_t *pRxBuffer,
                                     uint16_t Len,
                                     uint16_t SlaveAddr,
                                     uint8_t Sr);

DriverStatus_t I2C_MemReadData(i2c_driver_t *pI2CDriver,
                               uint16_t SlaveAddr,
                               uint8_t MemAddr,
                               uint8_t *pRxBuffer,
                               uint16_t Len);

/* --------------------------------------------------------------------------
 * Non-blocking interrupt transfers (Controller 7-bit)
 *
 * The functions return immediately; data flows through the event/error IRQ
 * handlers. The transaction context lives in the handle. Only I2C_STOP is
 * supported as end-of-transaction policy; I2C_NO_STOP is rejected until the
 * chained-transaction state machine exists (see i2c_plan.md).
 * Callback (if registered) runs inside the IRQ: keep it short.
 * -------------------------------------------------------------------------- */
void I2C_RegisterCallback(i2c_driver_t *pI2CDriver, I2C_Callback_t Callback);

DriverStatus_t I2C_MasterSendDataIT(i2c_driver_t *pI2CDriver,
                                    uint8_t *pTxBuffer,
                                    uint32_t Len,
                                    uint16_t TargetAddr,
                                    uint8_t RepeatedStart);

DriverStatus_t I2C_MasterReceiveDataIT(i2c_driver_t *pI2CDriver,
                                       uint8_t *pRxBuffer,
                                       uint32_t Len,
                                       uint16_t TargetAddr,
                                       uint8_t RepeatedStart);

void I2C_EV_IRQHandling(i2c_driver_t *pI2CDriver);
void I2C_ER_IRQHandling(i2c_driver_t *pI2CDriver);

/* --------------------------------------------------------------------------
 * Board-level init (weak). Declared here so any module can call it; the
 * default implementation lives in main.c and can be overridden per project.
 * -------------------------------------------------------------------------- */
extern i2c_driver_t hi2c1;

__weak void MX_I2C_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* I2C_DRIVER_H */
