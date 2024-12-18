#ifndef __STM32F4XX_HAL_RCC_H__
#define __STM32F4XX_HAL_RCC_H__

#define RCC_MODULE_ID    0x01u

/* **************** Peripheral Clock Enable start ************************************* */
#define __RCC_GPIOA_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 0)); \
                                                            tmpreg = RCC->AHB1ENR & (1 << 0); \
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_GPIOB_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 1)); \
                                                            tmpreg = (RCC->AHB1ENR & (1 << 1)) >> 1; \
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_GPIOC_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 2)); \
                                                            tmpreg = (RCC->AHB1ENR & (1 << 2)) >> 2; \
                                                            (void) tmpreg; \
                                                        } while(0u)
                                                        
#define __RCC_GPIOD_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 3)); \
                                                            tmpreg = (RCC->AHB1ENR & (1 << 3)) >> 3; \
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_GPIOE_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 4)); \
                                                            tmpreg = (RCC->AHB1ENR & (1 << 4)) >> 4; \
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_GPIOF_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 5)); \
                                                            tmpreg = (RCC->AHB1ENR & (1 << 5)) >> 5; \
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_GPIOG_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 6)); \
                                                            tmpreg = (RCC->AHB1ENR & (1 << 6)) >> 6; \
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_GPIOH_CLK_ENABLE()                    do  {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->AHB1ENR) |= (1 << 7)); \
                                                            tmpreg = (RCC->AHB1ENR & (1 << 7)) >> 7; \
                                                            (void) tmpreg; \
                                                        } while(0u)
                                                 
#define __RCC_SPI1_CLK_ENABLE()                     do {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->APB2ENR) |= (1 << 12)); \
                                                            tmpreg = (RCC->APB2ENR & (1 << 12)) >> 12;\
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_SPI2_CLK_ENABLE()                     do {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->APB1ENR) |= (1 << 14)); \
                                                            tmpreg = (RCC->APB1ENR & (1 << 14)) >> 14;\
                                                            (void) tmpreg; \
                                                        } while(0u)
#define __RCC_SPI3_CLK_ENABLE()                     do {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->APB1ENR) |= (1 << 15)); \
                                                            tmpreg = (RCC->APB1ENR & (1 << 15)) >> 15;\
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_SPI4_CLK_ENABLE()                     do {\
                                                            __IO uint32_t tmpreg = 0ul; \
                                                            ((RCC->APB2ENR) |= (1 << 13)); \
                                                            tmpreg = (RCC->APB2ENR & (1 << 13)) >> 13;\
                                                            (void) tmpreg; \
                                                        } while(0u)

#define __RCC_SYSCFG_CLK_ENABLE()                   do { \
                                                             __IO uint32_t tmpreg = 0x00U; \
                                                             ((RCC->APB2ENR) |= (1 << 14));\
                                                             /* Delay after an RCC peripheral clock enabling */ \
                                                             tmpreg = ((RCC->APB2ENR) & (1 << 14)) >> 14;\
                                                             (void)tmpreg; \
                                                        } while(0U)

#define __RCC_GPIOA_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 0)))   
#define __RCC_GPIOB_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 1)))
#define __RCC_GPIOC_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 2)))
#define __RCC_GPIOD_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 3)))
#define __RCC_GPIOE_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 4)))
#define __RCC_GPIOF_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 5)))
#define __RCC_GPIOG_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 6)))
#define __RCC_GPIOH_CLK_DISABLE()                   ((RCC->AHB1ENR) &= (~(1 << 7)))

#define __RCC_SPI1_CLK_DISABLE()                    ((RCC->APB2ENR) &= (~(1 << 12)))
#define __RCC_SPI2_CLK_DISABLE()                    ((RCC->APB1ENR) &= (~(1 << 14)))
#define __RCC_SPI3_CLK_DISABLE()                    ((RCC->APB1ENR) &= (~(1 << 15)))
#define __RCC_SPI4_CLK_DISABLE()                    ((RCC->APB2ENR) &= (~(1 << 13)))

#define __RCC_SYSCFG_CLK_DISABLE()                  ((RCC->APB2ENR) &= ~(1 << 14))

/* **************** Peripheral Clock Enable end ************************************* */

#endif /* __STM32F4XX_HAL_RCC_H__ */
