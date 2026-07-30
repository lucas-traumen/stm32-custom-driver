#include "lis3dsh.h"

static DriverStatus_t LIS3DSH_Validate(LIS3DSH_t *dev)
{
    if ((dev == 0) || (dev->bus.write == 0) || (dev->bus.read == 0)) {
        return STATUS_ERROR;
    }

    if (dev->timeout_ms == 0U) {
        dev->timeout_ms = LIS3DSH_TIMEOUT_DEFAULT_MS;
    }

    return STATUS_OK;
}

static DriverStatus_t LIS3DSH_UpdateRegBits(LIS3DSH_t *dev,
                                            uint8_t reg,
                                            uint8_t mask,
                                            uint8_t value)
{
    uint8_t tmp;
    DriverStatus_t st = LIS3DSH_ReadReg(dev, reg, &tmp);

    if (st != STATUS_OK) {
        return st;
    }

    tmp = (uint8_t)((tmp & (uint8_t)~mask) | (value & mask));
    return LIS3DSH_WriteReg(dev, reg, tmp);
}


DriverStatus_t LIS3DSH_EnableAddressAutoIncrement(LIS3DSH_t *dev, uint8_t enable)
{
    DriverStatus_t st = LIS3DSH_UpdateRegBits(dev,
                                             LIS3DSH_REG_CTRL_REG6,
                                             LIS3DSH_CTRL_REG6_ADD_INC,
                                             enable ? LIS3DSH_CTRL_REG6_ADD_INC : 0U);

    return st;
}

void LIS3DSH_DefaultConfig(LIS3DSH_Config_t *cfg)
{
    if (cfg == 0) {
        return;
    }

    cfg->odr = LIS3DSH_ODR_100HZ;
    cfg->scale = LIS3DSH_SCALE_2G;
    cfg->axes_enable = LIS3DSH_AXIS_XYZ_EN;
    cfg->block_data_update = 1U;
}

DriverStatus_t LIS3DSH_ReadReg(LIS3DSH_t *dev, uint8_t reg, uint8_t *value)
{
    if ((LIS3DSH_Validate(dev) != STATUS_OK) || (value == 0)) {
        return STATUS_ERROR;
    }

    return dev->bus.read(dev->bus_ctx, dev->dev_addr, reg, value, 1U, dev->timeout_ms);
}

DriverStatus_t LIS3DSH_WriteReg(LIS3DSH_t *dev, uint8_t reg, uint8_t value)
{
    if (LIS3DSH_Validate(dev) != STATUS_OK) {
        return STATUS_ERROR;
    }

    return dev->bus.write(dev->bus_ctx, dev->dev_addr, reg, &value, 1U, dev->timeout_ms);
}

DriverStatus_t LIS3DSH_ReadMulti(LIS3DSH_t *dev, uint8_t start_reg, uint8_t *buf, uint16_t len)
{
    if ((LIS3DSH_Validate(dev) != STATUS_OK) || (buf == 0) || (len == 0U)) {
        return STATUS_ERROR;
    }

    return dev->bus.read(dev->bus_ctx, dev->dev_addr, start_reg, buf, len, dev->timeout_ms);
}

DriverStatus_t LIS3DSH_WriteMulti(LIS3DSH_t *dev, uint8_t start_reg, const uint8_t *buf, uint16_t len)
{
    if ((LIS3DSH_Validate(dev) != STATUS_OK) || (buf == 0) || (len == 0U)) {
        return STATUS_ERROR;
    }

    return dev->bus.write(dev->bus_ctx, dev->dev_addr, start_reg, buf, len, dev->timeout_ms);
}

DriverStatus_t LIS3DSH_CheckDeviceId(LIS3DSH_t *dev)
{
    uint8_t whoami = 0U;
    DriverStatus_t st = LIS3DSH_ReadReg(dev, LIS3DSH_REG_WHO_AM_I, &whoami);

    if (st != STATUS_OK) {
        return st;
    }

    return (whoami == LIS3DSH_WHO_AM_I_VALUE) ? STATUS_OK : STATUS_ERROR;
}

DriverStatus_t LIS3DSH_Init(LIS3DSH_t *dev)
{
    DriverStatus_t st;

    if (LIS3DSH_Validate(dev) != STATUS_OK) {
        return STATUS_ERROR;
    }

    if (dev->cfg.odr == LIS3DSH_ODR_POWER_DOWN) {
        dev->cfg.odr = LIS3DSH_ODR_100HZ;
    }
    if ((dev->cfg.axes_enable & LIS3DSH_AXIS_XYZ_EN) == 0U) {
        dev->cfg.axes_enable = LIS3DSH_AXIS_XYZ_EN;
    }

    st = LIS3DSH_CheckDeviceId(dev);
    if (st != STATUS_OK) {
        return st;
    }

    /* LIS3DSH không dùng bit command để auto-increment như LIS3DH.
     * Multi-byte sequential access được bật bằng CTRL_REG6.ADD_INC. */
    st = LIS3DSH_EnableAddressAutoIncrement(dev, 1U);
    if (st != STATUS_OK) {
        return st;
    }

    /* Power-down trong lúc cấu hình. CTRL_REG4: ODR[7:4], BDU bit3, Zen/Yen/Xen bits[2:0]. */
    st = LIS3DSH_WriteReg(dev, LIS3DSH_REG_CTRL_REG4, LIS3DSH_AXIS_XYZ_EN);
    if (st != STATUS_OK) {
        return st;
    }

    if (dev->bus.delay_ms != 0) {
        dev->bus.delay_ms(2U);
    }

    st = LIS3DSH_SetScale(dev, dev->cfg.scale);
    if (st != STATUS_OK) {
        return st;
    }

    st = LIS3DSH_EnableBlockDataUpdate(dev, dev->cfg.block_data_update);
    if (st != STATUS_OK) {
        return st;
    }

    st = LIS3DSH_SetAxes(dev, dev->cfg.axes_enable);
    if (st != STATUS_OK) {
        return st;
    }

    st = LIS3DSH_SetODR(dev, dev->cfg.odr);
    if (st == STATUS_OK) {
        dev->initialized = 1U;
    }

    return st;
}

DriverStatus_t LIS3DSH_DeInit(LIS3DSH_t *dev)
{
    DriverStatus_t st;

    if (LIS3DSH_Validate(dev) != STATUS_OK) {
        return STATUS_ERROR;
    }

    st = LIS3DSH_UpdateRegBits(dev, LIS3DSH_REG_CTRL_REG4, 0xF0U, LIS3DSH_ODR_POWER_DOWN);
    if (st == STATUS_OK) {
        dev->initialized = 0U;
    }

    return st;
}

DriverStatus_t LIS3DSH_SetODR(LIS3DSH_t *dev, LIS3DSH_ODR_t odr)
{
    DriverStatus_t st = LIS3DSH_UpdateRegBits(dev, LIS3DSH_REG_CTRL_REG4, 0xF0U, (uint8_t)odr);

    if (st == STATUS_OK) {
        dev->cfg.odr = odr;
    }

    return st;
}

DriverStatus_t LIS3DSH_SetScale(LIS3DSH_t *dev, LIS3DSH_Scale_t scale)
{
    DriverStatus_t st = LIS3DSH_UpdateRegBits(dev, LIS3DSH_REG_CTRL_REG5, 0x38U, (uint8_t)scale);

    if (st == STATUS_OK) {
        dev->cfg.scale = scale;
    }

    return st;
}

DriverStatus_t LIS3DSH_SetAxes(LIS3DSH_t *dev, uint8_t axes_enable)
{
    DriverStatus_t st;

    axes_enable &= LIS3DSH_AXIS_XYZ_EN;
    st = LIS3DSH_UpdateRegBits(dev, LIS3DSH_REG_CTRL_REG4, 0x07U, axes_enable);
    if (st == STATUS_OK) {
        dev->cfg.axes_enable = axes_enable;
    }

    return st;
}

DriverStatus_t LIS3DSH_EnableBlockDataUpdate(LIS3DSH_t *dev, uint8_t enable)
{
    DriverStatus_t st = LIS3DSH_UpdateRegBits(dev,
                                             LIS3DSH_REG_CTRL_REG4,
                                             LIS3DSH_CTRL_REG4_BDU,
                                             enable ? LIS3DSH_CTRL_REG4_BDU : 0U);

    if (st == STATUS_OK) {
        dev->cfg.block_data_update = enable ? 1U : 0U;
    }

    return st;
}

DriverStatus_t LIS3DSH_ReadStatus(LIS3DSH_t *dev, uint8_t *status)
{
    return LIS3DSH_ReadReg(dev, LIS3DSH_REG_STATUS, status);
}

DriverStatus_t LIS3DSH_ReadRaw(LIS3DSH_t *dev, LIS3DSH_AxesRaw_t *raw)
{
    uint8_t buf[6];
    DriverStatus_t st;

    if ((dev == 0) || (raw == 0)) {
        return STATUS_ERROR;
    }

    st = LIS3DSH_ReadMulti(dev, LIS3DSH_REG_OUT_X_L, buf, 6U);
    if (st != STATUS_OK) {
        return st;
    }

    raw->x = (int16_t)(((uint16_t)buf[1] << 8U) | buf[0]);
    raw->y = (int16_t)(((uint16_t)buf[3] << 8U) | buf[2]);
    raw->z = (int16_t)(((uint16_t)buf[5] << 8U) | buf[4]);

    return STATUS_OK;
}

int32_t LIS3DSH_GetSensitivityUgPerLsb(const LIS3DSH_t *dev)
{
    if (dev == 0) {
        return 0;
    }

    switch (dev->cfg.scale) {
        case LIS3DSH_SCALE_4G:  return 120;
        case LIS3DSH_SCALE_6G:  return 180;
        case LIS3DSH_SCALE_8G:  return 240;
        case LIS3DSH_SCALE_16G: return 730;
        case LIS3DSH_SCALE_2G:
        default:                return 60;
    }
}

DriverStatus_t LIS3DSH_ReadAccelerationMg(LIS3DSH_t *dev, LIS3DSH_AxesMg_t *mg)
{
    LIS3DSH_AxesRaw_t raw;
    int32_t ug_lsb;
    DriverStatus_t st;

    if ((dev == 0) || (mg == 0)) {
        return STATUS_ERROR;
    }

    st = LIS3DSH_ReadRaw(dev, &raw);
    if (st != STATUS_OK) {
        return st;
    }

    ug_lsb = LIS3DSH_GetSensitivityUgPerLsb(dev);
    mg->x = ((int32_t)raw.x * ug_lsb) / 1000;
    mg->y = ((int32_t)raw.y * ug_lsb) / 1000;
    mg->z = ((int32_t)raw.z * ug_lsb) / 1000;

    return STATUS_OK;
}
