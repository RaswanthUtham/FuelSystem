#ifndef __ARM_CM4_H__
#define __ARM_CM4_H__

#define     __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

#define CM4_NVIC_ISER_BASE_ADDR                                                       ((__IO uint32_t *)(0xE000E100u))
#define CM4_NVIC_ICER_BASE_ADDR                                                       ((__IO uint32_t *)(0XE000E180u))
#define CM4_NVIC_IPR_BASE_ADDR                                                        ((__IO uint32_t *)(0xE000E400u))

void NVIC_EnableIRQ(IRQn_Type IRQn);
void NVIC_DisableIRQ(IRQn_Type IRQn);
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority);

#endif /* __ARM_CM4_H__ */
