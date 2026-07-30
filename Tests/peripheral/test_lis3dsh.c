#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lis3dsh.h"

#define ASSERT_EQ(exp, act) do { if ((long)(exp) != (long)(act)) { \
    printf("FAIL %s:%d expected %ld got %ld\n", __FILE__, __LINE__, (long)(exp), (long)(act)); return 1; } } while (0)
#define ASSERT_OK(st) ASSERT_EQ(STATUS_OK, (st))

typedef struct {
    uint8_t reg[256];
    DriverStatus_t next_read_status;
    DriverStatus_t next_write_status;
    uint8_t last_reg;
    uint16_t last_len;
} MockBus_t;

static void Mock_Reset(MockBus_t *m)
{
    memset(m, 0, sizeof(*m));
    m->reg[LIS3DSH_REG_WHO_AM_I] = LIS3DSH_WHO_AM_I_VALUE;
    m->next_read_status = STATUS_OK;
    m->next_write_status = STATUS_OK;
}

static DriverStatus_t Mock_Read(void *ctx, uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len, uint32_t timeout)
{
    MockBus_t *m = (MockBus_t *)ctx;
    (void)addr; (void)timeout;
    m->last_reg = reg;
    m->last_len = len;
    if (m->next_read_status != STATUS_OK) { DriverStatus_t st = m->next_read_status; m->next_read_status = STATUS_OK; return st; }
    for (uint16_t i = 0; i < len; i++) data[i] = m->reg[(uint8_t)(reg + i)];
    return STATUS_OK;
}

static DriverStatus_t Mock_Write(void *ctx, uint8_t addr, uint8_t reg, const uint8_t *data, uint16_t len, uint32_t timeout)
{
    MockBus_t *m = (MockBus_t *)ctx;
    (void)addr; (void)timeout;
    m->last_reg = reg;
    m->last_len = len;
    if (m->next_write_status != STATUS_OK) { DriverStatus_t st = m->next_write_status; m->next_write_status = STATUS_OK; return st; }
    for (uint16_t i = 0; i < len; i++) m->reg[(uint8_t)(reg + i)] = data[i];
    return STATUS_OK;
}

static void MakeDev(LIS3DSH_t *dev, MockBus_t *m)
{
    memset(dev, 0, sizeof(*dev));
    LIS3DSH_DefaultConfig(&dev->cfg);
    dev->bus_ctx = m;
    dev->bus.read = Mock_Read;
    dev->bus.write = Mock_Write;
    dev->timeout_ms = 10U;
}

static void PutRaw(MockBus_t *m, int16_t x, int16_t y, int16_t z)
{
    m->reg[LIS3DSH_REG_OUT_X_L] = (uint8_t)(x & 0xFF);
    m->reg[LIS3DSH_REG_OUT_X_H] = (uint8_t)(((uint16_t)x >> 8) & 0xFF);
    m->reg[LIS3DSH_REG_OUT_Y_L] = (uint8_t)(y & 0xFF);
    m->reg[LIS3DSH_REG_OUT_Y_H] = (uint8_t)(((uint16_t)y >> 8) & 0xFF);
    m->reg[LIS3DSH_REG_OUT_Z_L] = (uint8_t)(z & 0xFF);
    m->reg[LIS3DSH_REG_OUT_Z_H] = (uint8_t)(((uint16_t)z >> 8) & 0xFF);
}

static int test_id_default_and_init(void)
{
    MockBus_t m; LIS3DSH_t d;
    Mock_Reset(&m); MakeDev(&d, &m);
    ASSERT_EQ(0x3F, m.reg[LIS3DSH_REG_WHO_AM_I]);
    ASSERT_OK(LIS3DSH_CheckDeviceId(&d));
    ASSERT_OK(LIS3DSH_Init(&d));
    ASSERT_EQ(1, d.initialized);
    ASSERT_EQ((uint8_t)(LIS3DSH_ODR_100HZ | LIS3DSH_CTRL_REG4_BDU | LIS3DSH_AXIS_XYZ_EN), m.reg[LIS3DSH_REG_CTRL_REG4]);
    ASSERT_EQ(LIS3DSH_CTRL_REG6_ADD_INC, m.reg[LIS3DSH_REG_CTRL_REG6] & LIS3DSH_CTRL_REG6_ADD_INC);
    return 0;
}

static int test_bad_id_rejected(void)
{
    MockBus_t m; LIS3DSH_t d;
    Mock_Reset(&m); MakeDev(&d, &m);
    m.reg[LIS3DSH_REG_WHO_AM_I] = 0x33;
    ASSERT_EQ(STATUS_ERROR, LIS3DSH_CheckDeviceId(&d));
    ASSERT_EQ(STATUS_ERROR, LIS3DSH_Init(&d));
    return 0;
}

static int test_setters(void)
{
    MockBus_t m; LIS3DSH_t d;
    Mock_Reset(&m); MakeDev(&d, &m);
    m.reg[LIS3DSH_REG_CTRL_REG4] = LIS3DSH_AXIS_XYZ_EN;
    ASSERT_OK(LIS3DSH_SetODR(&d, LIS3DSH_ODR_400HZ));
    ASSERT_EQ(0x77, m.reg[LIS3DSH_REG_CTRL_REG4]);
    ASSERT_OK(LIS3DSH_EnableBlockDataUpdate(&d, 1));
    ASSERT_EQ(0x7F, m.reg[LIS3DSH_REG_CTRL_REG4]);
    ASSERT_OK(LIS3DSH_SetAxes(&d, LIS3DSH_AXIS_X_EN));
    ASSERT_EQ(0x79, m.reg[LIS3DSH_REG_CTRL_REG4]);
    ASSERT_OK(LIS3DSH_SetScale(&d, LIS3DSH_SCALE_16G));
    ASSERT_EQ(LIS3DSH_SCALE_16G, m.reg[LIS3DSH_REG_CTRL_REG5] & 0x38);
    return 0;
}

static int test_raw_and_mg(void)
{
    MockBus_t m; LIS3DSH_t d; LIS3DSH_AxesRaw_t raw; LIS3DSH_AxesMg_t mg;
    Mock_Reset(&m); MakeDev(&d, &m);
    d.cfg.scale = LIS3DSH_SCALE_2G;
    PutRaw(&m, 1000, -1000, 16667);
    ASSERT_OK(LIS3DSH_ReadRaw(&d, &raw));
    ASSERT_EQ(1000, raw.x); ASSERT_EQ(-1000, raw.y); ASSERT_EQ(16667, raw.z);
    ASSERT_OK(LIS3DSH_ReadAccelerationMg(&d, &mg));
    ASSERT_EQ(60, mg.x); ASSERT_EQ(-60, mg.y); ASSERT_EQ(1000, mg.z);
    ASSERT_EQ(LIS3DSH_REG_OUT_X_L, m.last_reg);
    ASSERT_EQ(6, m.last_len);
    return 0;
}

static int test_sensitivity(void)
{
    MockBus_t m; LIS3DSH_t d;
    Mock_Reset(&m); MakeDev(&d, &m);
    d.cfg.scale = LIS3DSH_SCALE_2G;  ASSERT_EQ(60, LIS3DSH_GetSensitivityUgPerLsb(&d));
    d.cfg.scale = LIS3DSH_SCALE_4G;  ASSERT_EQ(120, LIS3DSH_GetSensitivityUgPerLsb(&d));
    d.cfg.scale = LIS3DSH_SCALE_6G;  ASSERT_EQ(180, LIS3DSH_GetSensitivityUgPerLsb(&d));
    d.cfg.scale = LIS3DSH_SCALE_8G;  ASSERT_EQ(240, LIS3DSH_GetSensitivityUgPerLsb(&d));
    d.cfg.scale = LIS3DSH_SCALE_16G; ASSERT_EQ(730, LIS3DSH_GetSensitivityUgPerLsb(&d));
    return 0;
}

int main(void)
{
    int failed = 0;
    failed += test_id_default_and_init();
    failed += test_bad_id_rejected();
    failed += test_setters();
    failed += test_raw_and_mg();
    failed += test_sensitivity();
    printf("LIS3DSH tests: %s\n", failed ? "FAILED" : "OK");
    return failed ? 1 : 0;
}
