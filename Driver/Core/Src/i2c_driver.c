//#include "i2c_driver.h"
//
//uint32_t AHB_PreScaler[8] = {2,4,8.16,64,128,256,512};
//uint32_t APB1_PreScaler[4] = {2,4,6,16};
//
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//void I2C_PeriClockControl( I2C_TypeDef *pI2Cx, uint8_t EnorDi)
//{
//    if(EnorDi==ENABLE){
//        if(pI2Cx==I2C1){
//            I2C1_PCLK_EN();
//        }else if(pI2Cx==I2C2){
//            I2C2_PCLK_EN();
//        }else if(pI2Cx==I2C3){
//            I2C3_PCLK_EN();
//        }
//    }else{
//        if(pI2Cx==I2C1){
//            I2C1_PCLK_DI();
//        }else if(pI2Cx==I2C2){
//            I2C2_PCLK_DI();
//        }else if(pI2Cx==I2C3){
//            I2C3_PCLK_DI();
//        }
//    }
//}
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//uint32_t RCC_GetPLLOutputClock()
//{
//
//}
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//uint32_t RCC_GetPLCK1Value()
//{
//	uint32_t pclk1,systemclk,ahbp,apbp1;
//	uint8_t clksrc;
//
//	clksrc = (RCC->CFGR >> 2) & 0x03;
//	if( clksrc == RCC_CFGR_SW_HSI)
//	{
//		systemclk = 16000000;
//	}else if(clksrc == RCC_CFGR_SW_HSE)
//	{
//		systemclk = 8000000;
//	}else if(clksrc == RCC_CFGR_SW_PLL)
//	{
//		systemclk = RCC_GetPLLOutputClock();
//	}
//	// ahb
//	temp = ((RCC->CFGR >> 4) & 0x0F);
//	if(temp <8)
//	{
//		ahbp=1;
//	}else
//	{
//		ahbp=AHB_PreScaler[temp-8];
//	}
//	// apb1
//	temp = ((RCC->CFGR >> 10) & 0x07);
//	if(temp <4)
//	{
//		apbp1=1;
//	}else
//	{
//		apbp1=APB1_PreScaler[temp-4];
//	}
//	pclk1=(systemclk/ahbp)/apbp1;
//	return pclk1;
//}
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//void I2C_Init(I2C_Handle_t *pI2CHandle)
//{
//	// ack control bit
//    I2C_PeriClockControl(pI2CHandle->pI2Cx,ENABLE);
//	uint32_t temp=0;
//	temp |=(pI2CHandle->I2CConfig.I2C_ACKControl << I2C_CR1_ACK_Msk);
//	pI2CHandle->pI2Cx->CR1 |=temp;
//
//	// configure the FREQ field of CR2
//	temp = RCC_GetPLCK1Value()/1000000U;
//	pI2CHandle->pI2Cx->CR2 |= (temp & 0x3F);
//
//	//program the device own address
//	temp = 0;
//	temp |= (pI2CHandle->I2CConfig.I2C_DeviceAddress <<1) & 0x7F;
//	temp |= (1<<14);
//	pI2CHandle->pI2Cx->OAR1 = temp;
//
//	// CCR caculations
//	uint16_t ccr_value =0;
//	temp=0;
//	if(pI2CHandle->I2CConfig.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
//	{
//		// standard mode
//		temp &= ~(1<<I2C_CCR_FS_Pos);
//		ccr_value = RCC_GetPLCK1Value()/ (2*pI2CHandle->I2CConfig.I2C_SCLSpeed);
//		pI2CHandle->pI2Cx->CCR |= temp | ccr_value ;
//
//	}else{
//		temp |=(1<<I2C_CCR_FS_Pos);
//		temp |= (pI2CHandle->I2CConfig.I2C_FMDutyCycle << I2C_CCR_DUTY_Pos);
//		if(pI2CHandle->I2CConfig.I2C_FMDutyCycle == I2C_FM_DUTY_2)
//		{
//			ccr_value = RCC_GetPLCK1Value()/ (3*pI2CHandle->I2CConfig.I2C_SCLSpeed);
//			temp |= ccr_value & 0xFFFF;
//
//		}else{
//			ccr_value = RCC_GetPLCK1Value()/ (25*pI2CHandle->I2CConfig.I2C_SCLSpeed);
//			temp |= ccr_value & 0xFFFF;
//		}
//		pI2CHandle->pI2Cx->CCR=temp;
//	}
//}
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//uint8_t I2C_GetFlagStatus(I2C_TypeDef *pI2Cx,uint8_t Flag)
//{
//    if(pI2Cx->SR & Flag)
//    {
//        return FLAG_SET;
//    }
//    return FLAG_RESET;
//}
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//void I2C_DeInit(I2C_TypeDef *pI2Cx)
//{
//    if(pI2Cx==I2C1){
//        I2C1_PCLK_RESET();
//    }else if(pI2Cx==I2C2){
//        I2C2_PCLK_RESET();
//    }else if(pI2Cx==I2C3){
//        I2C3_PCLK_RESET();
//    }
//}
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//void I2C_PeripheralControl(I2C_TypeDef *pI2Cx,uint8_t EnorDi)
//{
////    if(EnorDi==ENABLE)
////    {
////       pI2Cx->CR1 |= I2C_CR1_SPE;
////    }else{
////        pI2Cx->CR1 &= ~(I2C_CR1_SPE);
////    }
//}
///******************************************************
// * @fn
// * @brief
//
// * @param[]
// * @param[]
// * @param[]
//
// * @return
// * @Note
//*/
//
//void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t* pTxBuffer, uint16_t Len, uint16_t SlaveAddr, uint8_t Sr)
//{
//	// 1. Generator the start condition
//	// 2. Confirm that start generation is completed by checking the SB flag in the SR1
//	//Note: Until SB is cleared SCL will be stretched (pulled to LOW)
//
//	// 3. Send the address of slave with r/nw bit set to w(0) ( total 8 bits)
//	// 4. Confirm that address phase is completted by checking the ADDR flag in SR1
//	// 5. Clear the ADD flag according to its software sequence
//	// Note: Until ADDR is cleared, SCL will be stretched ( pulled to LOW)
//	// 6. Send the data until len becomes 0
//	// 7. When len becomes 0 wait until TXE=1, BTF=1, before generating the stop condition
//	// Note: TXE=1, BTF =1 its mean both SR, DR are empty and next transmission should begin
//	// When BTF=1, SCL will be stretched ( pulled to low)
//
//	// 8. Generate STOP condition and master need not to wait for completion of stop condition
//	// Note: generating STOP, automatically clears the BTF bit
//}
//
