#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include "system.h"
#include "gpio.h"
/*
    @SPI_DeviceMode Config
*/
#define SPI_DEVICE_MODE_SLAVE  0
#define SPI_DEVICE_MODE_MASTER 1
/*
    @SPI_BusConfig
    #define SPI_BUS_CONFIG_SIMPLEX_TXONLY 
*/
#define SPI_BUS_CONFIG_FD             1
#define SPI_BUS_CONFIG_HD             2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 3
/*
    @SPI_Speed Config
*/
#define SPI_SCLK_SPEED_DIV2      0
#define SPI_SCLK_SPEED_DIV4      1
#define SPI_SCLK_SPEED_DIV8      2
#define SPI_SCLK_SPEED_DIV16     3
#define SPI_SCLK_SPEED_DIV32     4
#define SPI_SCLK_SPEED_DIV64     5
#define SPI_SCLK_SPEED_DIV128    6
#define SPI_SCLK_SPEED_DIV256    7

/*
    @SPI_DFF CONFIG
*/
#define SPI_DFF_8bits    0
#define SPI_DFF_16bits   1

/*
    @SPI_Frame_Format
*/
#define MSB_TRANSMITTED_FIRST 0
#define LSB_TRANSMITTED_FIRST 1
/* 
    @CPOL Config
*/
#define SPI_CPOL_HIGH       1
#define SPI_CPOL_LOW        0
/*  
    @CPHA Config
*/
#define SPI_CPHA_HIGH       1
#define SPI_CPHA_LOW        0
/*
    @SPI_SSM
    @SSM=1 -> hardware else 

*/
#define SPI_SSM_DI          0
#define SPI_SSM_EN          1

/*
    Configuration structure for SPIx 
*/
/* 
    bits name of the CR1 registers  in SPI peripheral 
*/
// #define SPI_CR1_CPHA        0
// #define SPI_CR1_CPOL        1
// #define SPI_CR1_MSTR        2
// #define SPI_CR1_BR          3
// #define SPI_CR1_SPE         6
// #define SPI_CR1_LSBFIRST    7
// #define SPI_CR1_SSI         8
// #define SPI_CR1_SSM         9
// #define SPI_CR1_RXONLY      10
// #define SPI_CR1_DFF         11
// #define SPI_CR1_CRCNEXT     12
// #define SPI_CR1_CRCEN       13
// #define SPI_CR1_BIDIOE      14
// #define SPI_CR1_BIDIMODE    15

/*
   @ bits name of the SR registers in SPI peripheral
   
*/
// #define SPI_SR_RXNE     0 
// #define SPI_SR_TXE      1
// #define SPI_SR_CHSIDE   2
// #define SPI_SR_UDR      3
// #define SPI_SR_CRCERR   4
// #define SPI_SR_MODF     5
// #define SPI_SR_OVR      6
// #define SPI_SR_BSY      7
// #define SPI_SR_FRE      8

#define FLAG_SPI_SR_RXNE (1<<SPI_SR_RXNE_Pos)
#define FLAG_SPI_SR_TXE  (1<<SPI_SR_TXE_Pos)
#define FLAG_SPI_SR_BSY  (1<<SPI_SR_BSY_Pos)

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
}SPI_Config_t;

/*
    Handle structure for SPIx peripheral
*/

typedef struct
{
    SPI_TypeDef *pSPIx;
    SPI_Config_t SPIConfig;
}SPI_Handle_t;

void SPI_PeriClockControl( SPI_TypeDef *pSPIx, uint8_t EnorDi);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_TypeDef *pSPIx);
void SPI_SendData(SPI_TypeDef *pSPIx,uint8_t *pTxbuffer, uint8_t len);
void SPI_ReceiveData(SPI_TypeDef *pSPIx,uint8_t *pRxbuffer, uint8_t len);
void SPI_SSI_Config(SPI_TypeDef *pSPIx,uint8_t EnorDi);
void SPI_SSOE_Config(SPI_TypeDef *pSPIx,uint8_t EnorDi);
void SPI_PeripheralControl(SPI_TypeDef *pSPIx,uint8_t EnorDi);
void SPI_GpioConfig(SPI_TypeDef *pSPIx);

#endif

