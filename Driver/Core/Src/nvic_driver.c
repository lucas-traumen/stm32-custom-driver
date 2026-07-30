#include "nvic_driver.h"

/**
 * @brief Enable a specific interrupt in the NVIC
 * @param IRQn Interrupt number (positive for device-specific IRQs)
 * @note  Writes to ISER[0..2] corresponding to IRQn/32. Negative IRQn
 *        (system exceptions) are ignored as they have no NVIC enable.
 */
void DRV_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)IRQn < 0) {
        return;
    }
    uint8_t temp1 = (uint8_t)IRQn / 32;
    uint8_t temp2 = (uint8_t)IRQn % 32;
    NVIC->ISER[temp1] |= (1 << temp2);
}

/**
 * @brief Disable a specific interrupt in the NVIC
 * @param IRQn Interrupt number (positive for device-specific IRQs)
 * @note  Writes to ICER[0..2]. Disabling an IRQ does not clear its
 *        pending flag; call DRV_NVIC_ClearPendingIRQ() if needed.
 */
void DRV_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)IRQn < 0) {
        return;
    }
    uint8_t temp1 = (uint8_t)IRQn / 32;
    uint8_t temp2 = (uint8_t)IRQn % 32;
    NVIC->ICER[temp1] |= (1 << temp2);
}

/**
 * @brief Set the priority grouping for the entire NVIC
 * @param PriorityGroup  NVIC_PRIORITY_GROUP_0..4 (0x07..0x03)
 *
 * Controls how many bits of the 8-bit priority field are used for
 * preemption priority vs subpriority:
 *   GROUP_0 : 0 preempt / 4 sub
 *   GROUP_4 : 4 preempt / 0 sub (recommended for most projects)
 *
 * @note  Requires the unlock sequence (0x5FA) in SCB->AIRCR.
 *        Changing the grouping affects ALL pending interrupts.
 */
void DRV_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    if (PriorityGroup < 0x03U) PriorityGroup = 0x03U;
    if (PriorityGroup > 0x07U) PriorityGroup = 0x07U;

    uint32_t val = SCB->AIRCR;
    val &= ~((0xFFFF0000UL) | (7UL << 8));
    val |= (0x5FAUL << 16) | (PriorityGroup << 8);
    SCB->AIRCR = val;
}

/**
 * @brief Get the current priority grouping
 * @return Priority group value (0x03..0x07), see DRV_NVIC_SetPriorityGrouping
 */
uint32_t DRV_NVIC_GetPriorityGrouping(void)
{
    return ((SCB->AIRCR & 0x700UL) >> 8);
}

/**
 * @brief Write an already-encoded priority value to NVIC->IP
 * @param IRQn             Interrupt number
 * @param encoded_priority 4-bit priority left-aligned in upper nibble
 *
 * NVIC->IP stores the priority in the upper 4 bits of each byte.
 * The lower 4 bits are RAZ/WI for STM32F4 (__NVIC_PRIO_BITS = 4).
 */
static void NVIC_SetPriority_Internal(IRQn_Type IRQn, uint8_t encoded_priority)
{
    NVIC->IP[(uint8_t)IRQn] = (encoded_priority << 4);
}

/**
 * @brief Get the maximum valid preemption/subpriority values for the current grouping
 * @return Struct with PreemptMax and SubMax (both inclusive)
 *
 * Example:
 * @code
 * DRV_NVIC_PriorityLimit_t lim = DRV_NVIC_GetPriorityLimit();
 * // lim.PreemptMax = 3, lim.SubMax = 3  (with GROUP_2)
 * @endcode
 */
DRV_NVIC_PriorityLimit_t DRV_NVIC_GetPriorityLimit(void)
{
    DRV_NVIC_PriorityLimit_t lim;
    uint8_t shift = (uint8_t)DRV_NVIC_GetPriorityGrouping() - 3;

    lim.PreemptMax = (uint8_t)(0x0F >> shift);
    lim.SubMax     = (uint8_t)(0x0F >> (4 - shift));
    return lim;
}

/**
 * @brief Set preemption and sub-priority for an interrupt
 * @param IRQn             Interrupt number (must be >= 0)
 * @param PreemptPriority  Preemption priority (0..lim.PreemptMax)
 * @param SubPriority      Subpriority (0..lim.SubMax)
 * @return true if values were valid and written, false otherwise
 *
 * Valid ranges depend on the priority grouping. Use DRV_NVIC_GetPriorityLimit()
 * to query valid ranges at runtime:
 *   GROUP_4: PreemptPriority [0..15], SubPriority ignored
 *   GROUP_2: PreemptPriority [0..3],  SubPriority [0..3]
 *   GROUP_0: PreemptPriority ignored, SubPriority [0..15]
 *
 * Returns false without modifying NVIC->IP if values are out of range.
 */
bool DRV_NVIC_SetPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority)
{
    if ((int32_t)IRQn < 0) {
        return false;
    }

    DRV_NVIC_PriorityLimit_t lim = DRV_NVIC_GetPriorityLimit();

    if (PreemptPriority > lim.PreemptMax) return false;
    if (SubPriority     > lim.SubMax)     return false;

    uint8_t shift = (uint8_t)DRV_NVIC_GetPriorityGrouping() - 3;
    uint8_t encoded_priority = (PreemptPriority << shift) | SubPriority;
    NVIC_SetPriority_Internal(IRQn, encoded_priority);
    return true;
}

/**
 * @brief Set priority for Cortex-M4 system exceptions (MemManage, BusFault, etc.)
 * @param IRQn             System exception IRQ number (negative: MemManage/BusFault/.../SysTick)
 * @param PreemptPriority  Preemption priority (0..15, grouping-dependent)
 * @param SubPriority      Subpriority (0..15, grouping-dependent)
 *
 * System exception priority registers (SCB->SHP) follow the same priority
 * encoding as NVIC->IP (upper 4 bits). Valid IRQn values:
 *   MemManage_IRQn (-12), BusFault_IRQn (-11), UsageFault_IRQn (-10),
 *   SVCall_IRQn    ( -5), DebugMonitor_IRQn (-4),
 *   PendSV_IRQn   ( -2), SysTick_IRQn      (-1)
 *
 * NonMaskableInt (-14) and HardFault (-13) have fixed priority and cannot be changed.
 */
void DRV_NVIC_SetSystemHandlerPriority(IRQn_Type IRQn, uint8_t PreemptPriority, uint8_t SubPriority)
{
    if ((int32_t)IRQn >= 0) {
        return;  /* peripheral IRQ, use DRV_NVIC_SetPriority instead */
    }

    DRV_NVIC_PriorityLimit_t lim = DRV_NVIC_GetPriorityLimit();

    if (PreemptPriority > lim.PreemptMax) return;
    if (SubPriority     > lim.SubMax)     return;

    uint8_t shift = (uint8_t)DRV_NVIC_GetPriorityGrouping() - 3;
    uint8_t encoded_priority = (PreemptPriority << shift) | SubPriority;

    /* Map IRQn to SCB->SHP index per CMSIS formula: SHP[((uint32_t)IRQn & 0xF) - 4] */
    uint32_t shp_idx = (((uint32_t)(int32_t)IRQn) & 0xFUL) - 4UL;
    SCB->SHP[shp_idx] = (uint8_t)(encoded_priority << 4);
}

/**
 * @brief Clear the pending flag of an interrupt
 * @param IRQn Interrupt number
 *
 * Writing 1 to ICPR[n] clears the pending status. Use before enabling
 * an IRQ that may have been left pending from a previous state.
 */
void DRV_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    if ((int32_t)IRQn < 0) {
        return;
    }
    uint8_t temp1 = (uint8_t)IRQn / 32;
    uint8_t temp2 = (uint8_t)IRQn % 32;
    NVIC->ICPR[temp1] = (1 << temp2);
}

/**
 * @brief Check whether an interrupt is pending
 * @param IRQn Interrupt number
 * @return 1 if pending, 0 otherwise
 *
 * Reads the ISPR (Interrupt Set Pending Register) for the given IRQn.
 * A pending bit can be set by hardware or by software (NVIC->ISPR).
 */
uint32_t DRV_NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    if ((int32_t)IRQn < 0) {
        return 0;
    }
    uint8_t temp1 = (uint8_t)IRQn / 32;
    uint8_t temp2 = (uint8_t)IRQn % 32;
    return ((NVIC->ISPR[temp1] >> temp2) & 1);
}
