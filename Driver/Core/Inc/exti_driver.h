#ifndef _EXTI_DRIVER_H_
#define _EXTI_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f4xx_common.h"

/**
 * @brief Callback signature for an EXTI line handler
 * @param EXTI_Line The line number (0-15) that fired, so one function
 *        can serve multiple lines (useful for EXTI9_5/EXTI15_10 groups).
 */
typedef void (*EXTI_Callback_t)(uint8_t EXTI_Line);

/**
 * @note EXTI lines 0-15 (GPIO-tied) are configured entirely through
 *       GPIO_Init() with GPIO_MODE_IT_FT/IT_RT/IT_RFT — it sets FTSR/RTSR,
 *       IMR, and SYSCFG_EXTICR in one place. This driver only covers the
 *       IRQ-side API (dispatch, pending flag, callback registration).
 *       Lines 16-22 (PVD, RTC, comparator) are not GPIO-tied and have no
 *       init helper yet; add one dedicated to that use case if needed
 *       instead of reusing the GPIO-line config path.
 */
void EXTI_DeInit(void);
void EXTI_IRQHandling(uint8_t EXTI_Line);
void EXTI_ClearPendingBit(uint8_t EXTI_Line);
uint8_t EXTI_GetPendingBit(uint8_t EXTI_Line);

/**
 * @brief Register the handler function to run when EXTI_Line fires
 * @param EXTI_Line Line number (0-15)
 * @param callback  Function pointer to run in ISR context. Passing a
 *        line without registering a callback leaves it pointed at an
 *        internal trap (infinite while(1)) so an unhandled interrupt
 *        is caught immediately in the debugger instead of silently
 *        doing nothing.
 * @note  Out-of-range EXTI_Line or NULL callback is ignored.
 */
void EXTI_RegisterCallback(uint8_t EXTI_Line, EXTI_Callback_t callback);

#endif
