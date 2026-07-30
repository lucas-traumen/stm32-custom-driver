#include "exti_driver.h"

/**
 * @brief Trap for an EXTI line whose callback was never registered
 *
 * Halts execution so a debugger session shows exactly which line fired
 * without a real handler attached. This is the default entry in
 * exti_callbacks[] for every line until EXTI_RegisterCallback() is called.
 */
static void EXTI_DefaultCallback(uint8_t line)
{
    (void)line;
    while (1) {
        /* Unregistered EXTI line fired. Check EXTI_Line in the debugger. */
    }
}

static EXTI_Callback_t exti_callbacks[16] = {
    EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback,
    EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback,
    EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback,
    EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback, EXTI_DefaultCallback,
};

void EXTI_DeInit(void)
{
    EXTI->IMR = 0x00000000;
    EXTI->EMR = 0x00000000;
    EXTI->RTSR = 0x00000000;
    EXTI->FTSR = 0x00000000;
    EXTI->PR = 0xFFFFFFFF;
}

void EXTI_IRQHandling(uint8_t EXTI_Line)
{
    if(EXTI->PR & (1 << EXTI_Line)) {
        EXTI->PR |= (1 << EXTI_Line);
        exti_callbacks[EXTI_Line](EXTI_Line);
    }
}

/**
 * @brief Register the handler to run when EXTI_Line fires
 * @param EXTI_Line Line number 0-15
 * @param callback  Function invoked from EXTI_IRQHandling() with EXTI_Line
 *                  as its argument; pass NULL to revert to the trap
 * @note  Called from application/init code, not from an ISR. Until this
 *        is called for a given line, that line's IRQ traps in
 *        EXTI_DefaultCallback() so an unhandled interrupt is caught
 *        immediately instead of silently doing nothing.
 */
void EXTI_RegisterCallback(uint8_t EXTI_Line, EXTI_Callback_t callback)
{
    if (EXTI_Line > 15 || callback == NULL) {
        return;
    }
    exti_callbacks[EXTI_Line] = callback;
}

void EXTI_ClearPendingBit(uint8_t EXTI_Line)
{
    EXTI->PR |= (1 << EXTI_Line);
}

uint8_t EXTI_GetPendingBit(uint8_t EXTI_Line)
{
    return ((EXTI->PR >> EXTI_Line) & 1);
}
