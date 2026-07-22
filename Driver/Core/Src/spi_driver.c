#include "spi_driver.h"
#include "rcc_driver.h"

void SPI_PeriClockControl( SPI_TypeDef *pSPIx, uint8_t EnorDi)
{
    if(EnorDi==ENABLE){
        if(pSPIx==SPI1){
            SPI1_PCLK_EN();
        }else if(pSPIx==SPI2){
            SPI2_PCLK_EN();
        }else if(pSPIx==SPI3){
            SPI3_PCLK_EN();
        }
    }else{
        if(pSPIx==SPI1){
            SPI1_PCLK_DI();
        }else if(pSPIx==SPI2){
            SPI2_PCLK_DI();
        }else if(pSPIx==SPI3){
            SPI3_PCLK_DI();
        }
    }
}
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);
    uint32_t temp=0;
    temp &= ~(pSPIHandle->SPIConfig.SPI_DeviceMode<<SPI_CR1_MSTR_Pos);
    temp |= pSPIHandle->SPIConfig.SPI_DeviceMode<<SPI_CR1_MSTR_Pos;

    if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_FD)
    {
        // Bidirectional 
        temp &= ~( 1<<SPI_CR1_BIDIMODE_Pos);

    }else if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_HD)
    {
        // Undirectional
        temp |= 1<<SPI_CR1_BIDIMODE_Pos;

    }else if(pSPIHandle->SPIConfig.SPI_BusConfig==SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        temp &= ~(1 <<SPI_CR1_BIDIMODE_Pos);
        temp &= ~(1<< SPI_CR1_BIDIOE_Pos);
    }
    // Config DFF
    temp &= ~(pSPIHandle->SPIConfig.SPI_DFF<<SPI_CR1_DFF_Pos);
    temp |= (pSPIHandle->SPIConfig.SPI_DFF<<SPI_CR1_DFF_Pos);
    // Frame_format
    temp &= ~(pSPIHandle->SPIConfig.SPI_Frame_format<<SPI_CR1_LSBFIRST_Pos);
    temp |= (pSPIHandle->SPIConfig.SPI_Frame_format<<SPI_CR1_LSBFIRST_Pos);
    // CPOL
    temp &= ~(pSPIHandle->SPIConfig.SPI_CPOL<<SPI_CR1_CPOL_Pos);
    temp |= (pSPIHandle->SPIConfig.SPI_CPOL<<SPI_CR1_CPOL_Pos);
    // CPHA
    temp &= ~(pSPIHandle->SPIConfig.SPI_CPHA<<SPI_CR1_CPHA_Pos);
    temp |= (pSPIHandle->SPIConfig.SPI_CPHA<<SPI_CR1_CPHA_Pos);
    // SSM 
    temp &= ~(pSPIHandle->SPIConfig.SPI_SSM<<SPI_CR1_SSM_Pos);
    temp |= (pSPIHandle->SPIConfig.SPI_SSM<<SPI_CR1_SSM_Pos);
    // speed
    temp &= ~(pSPIHandle->SPIConfig.speed<<SPI_CR1_BR_Pos);
    temp |= (pSPIHandle->SPIConfig.speed<<SPI_CR1_BR_Pos);
    // // enable SPI 
    // temp &= ~(1<<SPI_CR1_SPE_Pos);
    // temp |= (1<<SPI_CR1_SPE_Pos);

    pSPIHandle->pSPIx->CR1=temp;
}
/*

*/
uint8_t SPI_GetFlagStatus(SPI_TypeDef *pSPIx,uint8_t Flag)
{
    if(pSPIx->SR & Flag)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}
void SPI_DeInit(SPI_TypeDef *pSPIx)
{
    if(pSPIx==SPI1){
        SPI1_PCLK_RESET();
    }else if(pSPIx==SPI2){
        SPI2_PCLK_RESET();
    }else if(pSPIx==SPI3){
        SPI3_PCLK_RESET();
    }
}
void SPI_PeripheralControl(SPI_TypeDef *pSPIx,uint8_t EnorDi)
{
    if(EnorDi==ENABLE)
    {
       pSPIx->CR1 |= SPI_CR1_SPE;
    }else{
        pSPIx->CR1 &= ~(SPI_CR1_SPE);
    }   
}
void SPI_SSI_Config(SPI_TypeDef *pSPIx,uint8_t EnorDi)
{
     if(EnorDi==ENABLE)
    {
       pSPIx->CR1 |= SPI_CR1_SSI;
    }else{
        pSPIx->CR1 &= ~(SPI_CR1_SSI);
    }  
}
void SPI_SSOE_Config(SPI_TypeDef *pSPIx,uint8_t EnorDi)
{
     if(EnorDi==ENABLE)
    {
       pSPIx->CR1 |= SPI_CR2_SSOE;
    }else{
        pSPIx->CR1 &= ~(SPI_CR2_SSOE);
    }  
}
void SPI_SendData(SPI_TypeDef *pSPIx,uint8_t *pTxbuffer, uint8_t len)
{
    while(len>0)
    {
        while(SPI_GetFlagStatus(pSPIx,FLAG_SPI_SR_TXE)==FLAG_RESET);
        if((pSPIx->CR1 >> SPI_CR1_DFF_Pos)&1)
        {
            pSPIx->DR=*(uint16_t*)pTxbuffer;
            len -=2;
            pTxbuffer+=2;
        }else
        {
            pSPIx->DR= *pTxbuffer;
            len--;
            pTxbuffer++;
        }
        // Read dummy data
        uint32_t temp = pSPIx->DR; 
        temp = pSPIx->SR; // Đọc SR là một cách để xóa cờ lỗi Overrun trên một số dòng chip
        (void)temp;
    }
    while(SPI_GetFlagStatus(pSPIx, FLAG_SPI_SR_BSY)== FLAG_SET);

}
void SPI_ReceiveData(SPI_TypeDef *pSPIx,uint8_t *pRxbuffer, uint8_t len)
{
    while(len>0)
    {
        
        while(SPI_GetFlagStatus(pSPIx,FLAG_SPI_SR_TXE)==FLAG_RESET);
        // 1.2 Gửi 0xFF (hoặc 0x00) để kích hoạt Clock
        // Lưu ý: Gửi 8-bit hay 16-bit phụ thuộc cấu hình, nhưng dummy thường chỉ cần 8bit 
        // nếu cấu hình DataSize là 8bit.
        if((pSPIx->CR1 >> SPI_CR1_DFF_Pos) & 1) // 16-bit mode
        {
             pSPIx->DR = 0xFFFF;
        }
        else // 8-bit mode
        {
             pSPIx->DR = 0xFF; 
        }
        while(SPI_GetFlagStatus(pSPIx, FLAG_SPI_SR_RXNE) == FLAG_RESET);

        if((pSPIx->CR1 >> SPI_CR1_DFF_Pos)&1)
        {
            pSPIx->DR=*(uint16_t*)pRxbuffer;
            len -=2;
            pRxbuffer+=2;
        }else
        {
            pSPIx->DR= *pRxbuffer;
            len--;
            pRxbuffer++;
        }
    }
    while(SPI_GetFlagStatus(pSPIx, FLAG_SPI_SR_BSY)== FLAG_SET);
}
void SPI_GpioConfig(SPI_TypeDef *pSPIx)
{
    if(pSPIx==SPI2)
    {
        // PB12 --> SPI2_NSS
    // PB13 ---> SPI2_SCK
    // PB14 --> SPi2_MISO
    // PB15 --> SPI2_MOSI
    GPIO_Handle_t gpio_spi2;
    GPIO_PeriClockControl(GPIOB,ENABLE);
    gpio_spi2.pGPIOx=GPIOB;
    gpio_spi2.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
    gpio_spi2.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_ALTFN;
    gpio_spi2.GPIO_PinConfig.GPIO_PinAltFunMode=AF5;
    gpio_spi2.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
    gpio_spi2.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PUPD;
    gpio_spi2.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_HIGH;
    GPIO_Init(&gpio_spi2);

    gpio_spi2.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_12;
    GPIO_Init(&gpio_spi2);
    gpio_spi2.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_14;
    GPIO_Init(&gpio_spi2);
    gpio_spi2.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_15;
    GPIO_Init(&gpio_spi2);
    }
    
}