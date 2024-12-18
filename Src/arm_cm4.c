#include "stm32xxxx.h"

void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    *(CM4_NVIC_ISER_BASE_ADDR + (IRQn >> 5UL)) |= 1 << (IRQn & 0x1F);
}

void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    *(CM4_NVIC_ICER_BASE_ADDR + (IRQn >> 5UL)) |= 1 << (IRQn & 0x1F);
}

void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    *(CM4_NVIC_IPR_BASE_ADDR + (IRQn >> 2UL)) |= ((priority << 4) & 0xF0) << ((IRQn & 0x3) * 8);
} 
