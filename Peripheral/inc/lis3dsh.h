#ifndef LIS3DSH_H
#define LIS3DSH_H

/*
 * LIS3DSH MEMS digital output motion sensor driver
 * Version: 1.0
 * Date:    2026-07-30
 *
 * Driver cho accelerometer onboard STM32F407 Discovery revision mới.
 * WHO_AM_I = 0x3F. Driver tách bus bằng function pointer giống pattern
 * peripheral driver: application/board layer cấp read/write/delay callbacks.
 */

#include <stdint.h>
#include "stm32f4xx_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ======================== Register map ======================== */
#define LIS3DSH_REG_OUT_T            0x0CU
#define LIS3DSH_REG_INFO1            0x0DU
#define LIS3DSH_REG_INFO2            0x0EU
#define LIS3DSH_REG_WHO_AM_I         0x0FU
#define LIS3DSH_REG_OFF_X            0x10U
#define LIS3DSH_REG_OFF_Y            0x11U
#define LIS3DSH_REG_OFF_Z            0x12U
#define LIS3DSH_REG_CS_X             0x13U
#define LIS3DSH_REG_CS_Y             0x14U
#define LIS3DSH_REG_CS_Z             0x15U
#define LIS3DSH_REG_LC_L             0x16U
#define LIS3DSH_REG_LC_H             0x17U
#define LIS3DSH_REG_STAT             0x18U
#define LIS3DSH_REG_PEAK1            0x19U
#define LIS3DSH_REG_PEAK2            0x1AU
#define LIS3DSH_REG_VFC_1            0x1BU
#define LIS3DSH_REG_VFC_2            0x1CU
#define LIS3DSH_REG_VFC_3            0x1DU
#define LIS3DSH_REG_VFC_4            0x1EU
#define LIS3DSH_REG_THRS3            0x1FU
#define LIS3DSH_REG_CTRL_REG4        0x20U
#define LIS3DSH_REG_CTRL_REG1        0x21U
#define LIS3DSH_REG_CTRL_REG2        0x22U
#define LIS3DSH_REG_CTRL_REG3        0x23U
#define LIS3DSH_REG_CTRL_REG5        0x24U
#define LIS3DSH_REG_CTRL_REG6        0x25U
#define LIS3DSH_REG_STATUS           0x27U
#define LIS3DSH_REG_OUT_X_L          0x28U
#define LIS3DSH_REG_OUT_X_H          0x29U
#define LIS3DSH_REG_OUT_Y_L          0x2AU
#define LIS3DSH_REG_OUT_Y_H          0x2BU
#define LIS3DSH_REG_OUT_Z_L          0x2CU
#define LIS3DSH_REG_OUT_Z_H          0x2DU

#define LIS3DSH_WHO_AM_I_VALUE       0x3FU

/* SPI command bits */
#define LIS3DSH_SPI_READ_BIT         (1U << 7)  /* RW=1: read */
#define LIS3DSH_SPI_AUTO_INC_BIT     (1U << 6)  /* Not used by this driver; LIS3DSH multi-byte uses CTRL_REG6.ADD_INC */

#define LIS3DSH_AXIS_X_EN            0x01U
#define LIS3DSH_AXIS_Y_EN            0x02U
#define LIS3DSH_AXIS_Z_EN            0x04U
#define LIS3DSH_AXIS_XYZ_EN          (LIS3DSH_AXIS_X_EN | LIS3DSH_AXIS_Y_EN | LIS3DSH_AXIS_Z_EN)

#define LIS3DSH_CTRL_REG4_BDU        (1U << 3)
#define LIS3DSH_CTRL_REG6_ADD_INC    (1U << 4)
#define LIS3DSH_TIMEOUT_DEFAULT_MS   100U

/* ======================== Configuration enums ======================== */
typedef enum {
    LIS3DSH_ODR_POWER_DOWN = 0x00U,
    LIS3DSH_ODR_3_125HZ    = 0x10U,
    LIS3DSH_ODR_6_25HZ     = 0x20U,
    LIS3DSH_ODR_12_5HZ     = 0x30U,
    LIS3DSH_ODR_25HZ       = 0x40U,
    LIS3DSH_ODR_50HZ       = 0x50U,
    LIS3DSH_ODR_100HZ      = 0x60U,
    LIS3DSH_ODR_400HZ      = 0x70U,
    LIS3DSH_ODR_800HZ      = 0x80U,
    LIS3DSH_ODR_1600HZ     = 0x90U
} LIS3DSH_ODR_t;

/* CTRL_REG5 FSCALE bits [5:3] */
typedef enum {
    LIS3DSH_SCALE_2G  = (0U << 3),
    LIS3DSH_SCALE_4G  = (1U << 3),
    LIS3DSH_SCALE_6G  = (2U << 3),
    LIS3DSH_SCALE_8G  = (3U << 3),
    LIS3DSH_SCALE_16G = (4U << 3)
} LIS3DSH_Scale_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} LIS3DSH_AxesRaw_t;

typedef struct {
    int32_t x;
    int32_t y;
    int32_t z;
} LIS3DSH_AxesMg_t;

typedef struct {
    DriverStatus_t (*write)(void *bus_ctx,
                            uint8_t dev_addr,
                            uint8_t reg,
                            const uint8_t *data,
                            uint16_t len,
                            uint32_t timeout_ms);

    DriverStatus_t (*read)(void *bus_ctx,
                           uint8_t dev_addr,
                           uint8_t reg,
                           uint8_t *data,
                           uint16_t len,
                           uint32_t timeout_ms);

    void (*delay_ms)(uint32_t ms);
} LIS3DSH_BusOps_t;

typedef struct {
    LIS3DSH_ODR_t   odr;
    LIS3DSH_Scale_t scale;
    uint8_t         axes_enable;
    uint8_t         block_data_update;
} LIS3DSH_Config_t;

typedef struct {
    void             *bus_ctx;
    uint8_t           dev_addr;
    LIS3DSH_BusOps_t  bus;
    LIS3DSH_Config_t  cfg;
    uint32_t          timeout_ms;
    uint8_t           initialized;
} LIS3DSH_t;

void LIS3DSH_DefaultConfig(LIS3DSH_Config_t *cfg);
DriverStatus_t LIS3DSH_Init(LIS3DSH_t *dev);
DriverStatus_t LIS3DSH_DeInit(LIS3DSH_t *dev);
DriverStatus_t LIS3DSH_CheckDeviceId(LIS3DSH_t *dev);

DriverStatus_t LIS3DSH_ReadReg(LIS3DSH_t *dev, uint8_t reg, uint8_t *value);
DriverStatus_t LIS3DSH_WriteReg(LIS3DSH_t *dev, uint8_t reg, uint8_t value);
DriverStatus_t LIS3DSH_ReadMulti(LIS3DSH_t *dev, uint8_t start_reg, uint8_t *buf, uint16_t len);
DriverStatus_t LIS3DSH_WriteMulti(LIS3DSH_t *dev, uint8_t start_reg, const uint8_t *buf, uint16_t len);

DriverStatus_t LIS3DSH_SetODR(LIS3DSH_t *dev, LIS3DSH_ODR_t odr);
DriverStatus_t LIS3DSH_SetScale(LIS3DSH_t *dev, LIS3DSH_Scale_t scale);
DriverStatus_t LIS3DSH_SetAxes(LIS3DSH_t *dev, uint8_t axes_enable);
DriverStatus_t LIS3DSH_EnableAddressAutoIncrement(LIS3DSH_t *dev, uint8_t enable);
DriverStatus_t LIS3DSH_EnableBlockDataUpdate(LIS3DSH_t *dev, uint8_t enable);

DriverStatus_t LIS3DSH_ReadStatus(LIS3DSH_t *dev, uint8_t *status);
DriverStatus_t LIS3DSH_ReadRaw(LIS3DSH_t *dev, LIS3DSH_AxesRaw_t *raw);
DriverStatus_t LIS3DSH_ReadAccelerationMg(LIS3DSH_t *dev, LIS3DSH_AxesMg_t *mg);
int32_t LIS3DSH_GetSensitivityUgPerLsb(const LIS3DSH_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* LIS3DSH_H */
