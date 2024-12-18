#ifndef __STM32F446RE_H__
#define __STM32F446RE_H__

typedef enum
{
    /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
    NonMaskableInt_IRQn = -14,   /*!< 2 Non Maskable Interrupt                                          */
    MemoryManagement_IRQn = -12, /*!< 4 Cortex-M4 Memory Management Interrupt                           */
    BusFault_IRQn = -11,         /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
    UsageFault_IRQn = -10,       /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
    SVCall_IRQn = -5,            /*!< 11 Cortex-M4 SV Call Interrupt                                    */
    DebugMonitor_IRQn = -4,      /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
    PendSV_IRQn = -2,            /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
    SysTick_IRQn = -1,           /*!< 15 Cortex-M4 System Tick Interrupt                                */
    /******  STM32 specific Interrupt Numbers **********************************************************************/
    WWDG_IRQn = 0,                /*!< Window WatchDog Interrupt                                         */
    PVD_IRQn = 1,                 /*!< PVD through EXTI Line detection Interrupt                         */
    TAMP_STAMP_IRQn = 2,          /*!< Tamper and TimeStamp interrupts through the EXTI line             */
    RTC_WKUP_IRQn = 3,            /*!< RTC Wakeup interrupt through the EXTI line                        */
    FLASH_IRQn = 4,               /*!< FLASH global Interrupt                                            */
    RCC_IRQn = 5,                 /*!< RCC global Interrupt                                              */
    EXTI0_IRQn = 6,               /*!< EXTI Line0 Interrupt                                              */
    EXTI1_IRQn = 7,               /*!< EXTI Line1 Interrupt                                              */
    EXTI2_IRQn = 8,               /*!< EXTI Line2 Interrupt                                              */
    EXTI3_IRQn = 9,               /*!< EXTI Line3 Interrupt                                              */
    EXTI4_IRQn = 10,              /*!< EXTI Line4 Interrupt                                              */
    DMA1_Stream0_IRQn = 11,       /*!< DMA1 Stream 0 global Interrupt                                    */
    DMA1_Stream1_IRQn = 12,       /*!< DMA1 Stream 1 global Interrupt                                    */
    DMA1_Stream2_IRQn = 13,       /*!< DMA1 Stream 2 global Interrupt                                    */
    DMA1_Stream3_IRQn = 14,       /*!< DMA1 Stream 3 global Interrupt                                    */
    DMA1_Stream4_IRQn = 15,       /*!< DMA1 Stream 4 global Interrupt                                    */
    DMA1_Stream5_IRQn = 16,       /*!< DMA1 Stream 5 global Interrupt                                    */
    DMA1_Stream6_IRQn = 17,       /*!< DMA1 Stream 6 global Interrupt                                    */
    ADC_IRQn = 18,                /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
    CAN1_TX_IRQn = 19,            /*!< CAN1 TX Interrupt                                                 */
    CAN1_RX0_IRQn = 20,           /*!< CAN1 RX0 Interrupt                                                */
    CAN1_RX1_IRQn = 21,           /*!< CAN1 RX1 Interrupt                                                */
    CAN1_SCE_IRQn = 22,           /*!< CAN1 SCE Interrupt                                                */
    EXTI9_5_IRQn = 23,            /*!< External Line[9:5] Interrupts                                     */
    TIM1_BRK_TIM9_IRQn = 24,      /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
    TIM1_UP_TIM10_IRQn = 25,      /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
    TIM1_TRG_COM_TIM11_IRQn = 26, /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
    TIM1_CC_IRQn = 27,            /*!< TIM1 Capture Compare Interrupt                                    */
    TIM2_IRQn = 28,               /*!< TIM2 global Interrupt                                             */
    TIM3_IRQn = 29,               /*!< TIM3 global Interrupt                                             */
    TIM4_IRQn = 30,               /*!< TIM4 global Interrupt                                             */
    I2C1_EV_IRQn = 31,            /*!< I2C1 Event Interrupt                                              */
    I2C1_ER_IRQn = 32,            /*!< I2C1 Error Interrupt                                              */
    I2C2_EV_IRQn = 33,            /*!< I2C2 Event Interrupt                                              */
    I2C2_ER_IRQn = 34,            /*!< I2C2 Error Interrupt                                              */
    SPI1_IRQn = 35,               /*!< SPI1 global Interrupt                                             */
    SPI2_IRQn = 36,               /*!< SPI2 global Interrupt                                             */
    USART1_IRQn = 37,             /*!< USART1 global Interrupt                                           */
    USART2_IRQn = 38,             /*!< USART2 global Interrupt                                           */
    USART3_IRQn = 39,             /*!< USART3 global Interrupt                                           */
    EXTI15_10_IRQn = 40,          /*!< External Line[15:10] Interrupts                                   */
    RTC_Alarm_IRQn = 41,          /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
    OTG_FS_WKUP_IRQn = 42,        /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
    TIM8_BRK_TIM12_IRQn = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
    TIM8_UP_TIM13_IRQn = 44,      /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
    TIM8_TRG_COM_TIM14_IRQn = 45, /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
    TIM8_CC_IRQn = 46,            /*!< TIM8 Capture Compare global interrupt                             */
    DMA1_Stream7_IRQn = 47,       /*!< DMA1 Stream7 Interrupt                                            */
    FMC_IRQn = 48,                /*!< FMC global Interrupt                                              */
    SDIO_IRQn = 49,               /*!< SDIO global Interrupt                                             */
    TIM5_IRQn = 50,               /*!< TIM5 global Interrupt                                             */
    SPI3_IRQn = 51,               /*!< SPI3 global Interrupt                                             */
    UART4_IRQn = 52,              /*!< UART4 global Interrupt                                            */
    UART5_IRQn = 53,              /*!< UART5 global Interrupt                                            */
    TIM6_DAC_IRQn = 54,           /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
    TIM7_IRQn = 55,               /*!< TIM7 global interrupt                                             */
    DMA2_Stream0_IRQn = 56,       /*!< DMA2 Stream 0 global Interrupt                                    */
    DMA2_Stream1_IRQn = 57,       /*!< DMA2 Stream 1 global Interrupt                                    */
    DMA2_Stream2_IRQn = 58,       /*!< DMA2 Stream 2 global Interrupt                                    */
    DMA2_Stream3_IRQn = 59,       /*!< DMA2 Stream 3 global Interrupt                                    */
    DMA2_Stream4_IRQn = 60,       /*!< DMA2 Stream 4 global Interrupt                                    */
    CAN2_TX_IRQn = 63,            /*!< CAN2 TX Interrupt                                                 */
    CAN2_RX0_IRQn = 64,           /*!< CAN2 RX0 Interrupt                                                */
    CAN2_RX1_IRQn = 65,           /*!< CAN2 RX1 Interrupt                                                */
    CAN2_SCE_IRQn = 66,           /*!< CAN2 SCE Interrupt                                                */
    OTG_FS_IRQn = 67,             /*!< USB OTG FS global Interrupt                                       */
    DMA2_Stream5_IRQn = 68,       /*!< DMA2 Stream 5 global interrupt                                    */
    DMA2_Stream6_IRQn = 69,       /*!< DMA2 Stream 6 global interrupt                                    */
    DMA2_Stream7_IRQn = 70,       /*!< DMA2 Stream 7 global interrupt                                    */
    USART6_IRQn = 71,             /*!< USART6 global interrupt                                           */
    I2C3_EV_IRQn = 72,            /*!< I2C3 event interrupt                                              */
    I2C3_ER_IRQn = 73,            /*!< I2C3 error interrupt                                              */
    OTG_HS_EP1_OUT_IRQn = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
    OTG_HS_EP1_IN_IRQn = 75,      /*!< USB OTG HS End Point 1 In global interrupt                        */
    OTG_HS_WKUP_IRQn = 76,        /*!< USB OTG HS Wakeup through EXTI interrupt                          */
    OTG_HS_IRQn = 77,             /*!< USB OTG HS global interrupt                                       */
    DCMI_IRQn = 78,               /*!< DCMI global interrupt                                             */
    FPU_IRQn = 81,                /*!< FPU global interrupt                                              */
    SPI4_IRQn = 84,               /*!< SPI4 global Interrupt                                             */
    SAI1_IRQn = 87,               /*!< SAI1 global Interrupt                                             */
    SAI2_IRQn = 91,               /*!< SAI2 global Interrupt                                             */
    QUADSPI_IRQn = 92,            /*!< QuadSPI global Interrupt                                          */
    CEC_IRQn = 93,                /*!< CEC global Interrupt                                              */
    SPDIF_RX_IRQn = 94,           /*!< SPDIF-RX global Interrupt                                          */
    FMPI2C1_EV_IRQn = 95,         /*!< FMPI2C1 Event Interrupt                                           */
    FMPI2C1_ER_IRQn = 96          /*!< FMPI2C1 Error Interrupt                                           */
} IRQn_Type;

#include <stdint.h>
#include "std_defines.h"
#include "arm_cm4.h"

typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} PORT_TypeDef;

typedef struct
{
  __IO uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __IO uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __IO uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __IO uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __IO uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __IO uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __IO uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __IO uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __IO uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __IO uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __IO uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __IO uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __IO uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
  __IO uint32_t PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                           Address offset: 0x88 */
  __IO uint32_t DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
  __IO uint32_t CKGATENR;      /*!< RCC Clocks Gated ENable Register,                            Address offset: 0x90 */
  __IO uint32_t DCKCFGR2;      /*!< RCC Dedicated Clocks configuration register 2,               Address offset: 0x94 */
} RCC_TypeDef;

typedef struct
{
  __IO uint32_t IMR;    /*!< EXTI Interrupt mask register,            Address offset: 0x00 */
  __IO uint32_t EMR;    /*!< EXTI Event mask register,                Address offset: 0x04 */
  __IO uint32_t RTSR;   /*!< EXTI Rising trigger selection register,  Address offset: 0x08 */
  __IO uint32_t FTSR;   /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
  __IO uint32_t SWIER;  /*!< EXTI Software interrupt event register,  Address offset: 0x10 */
  __IO uint32_t PR;     /*!< EXTI Pending register,                   Address offset: 0x14 */
} EXTI_TypeDef;

typedef struct
{
  __IO uint32_t MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
  __IO uint32_t PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
  __IO uint32_t EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
  uint32_t      RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */
  __IO uint32_t CMPCR;        /*!< SYSCFG Compensation cell control register,         Address offset: 0x20      */
  uint32_t      RESERVED1[2]; /*!< Reserved, 0x24-0x28                                                          */
  __IO uint32_t CFGR;         /*!< SYSCFG Configuration register,                     Address offset: 0x2C      */
} SYSCFG_TypeDef;

typedef struct
{
  __IO uint32_t CPHA:1;
  __IO uint32_t CPOL:1;
  __IO uint32_t MSTR:1;
  __IO uint32_t BR:3;
  __IO uint32_t SPE:1;
  __IO uint32_t LSBFIRST:1;
  __IO uint32_t SSI:1;
  __IO uint32_t SSM:1;
  __IO uint32_t RXONLY:1;
  __IO uint32_t DFF:1;
  __IO uint32_t CRCNEXT:1;
  __IO uint32_t CRCEN:1;
  __IO uint32_t BIDIOE:1;
  __IO uint32_t BIDIMODE:1;
  __IO uint32_t : 16;
}SPI_CR1_Bits;

typedef union
{
  __IO uint32_t U;
  __IO SPI_CR1_Bits B;
}SPI_CR1_RegDef;

typedef struct
{
  __IO uint32_t RXDMAEN:1;
  __IO uint32_t TXDMAEN:1;
  __IO uint32_t SSOE:1;
  __IO uint32_t :1;
  __IO uint32_t FRF:1;
  __IO uint32_t ERRIE:1;
  __IO uint32_t RXNEIE:1;
  __IO uint32_t TXEIE:1;
  __IO uint32_t : 24;
}SPI_CR2_Bits;

typedef union
{
  __IO uint32_t U;
  __IO SPI_CR2_Bits B;
}SPI_CR2_RegDef;

typedef struct
{
  __IO uint32_t RXNE:1;
  __IO uint32_t TXE:1;
  __IO uint32_t CHSIDE:1;
  __IO uint32_t UDR:1;
  __IO uint32_t CRCERR:1;
  __IO uint32_t MODF:1;
  __IO uint32_t OVR:1;
  __IO uint32_t BSY:1;
  __IO uint32_t FRE:1;
  __IO uint32_t : 23;
}SPI_SR_Bits;

typedef union
{
  __IO uint32_t U;
  __IO SPI_SR_Bits B;
}SPI_SR_RegDef;

typedef struct
{
  __IO SPI_CR1_RegDef CR1;        /*!< SPI control register 1 (not used in I2S mode),      Address offset: 0x00 */
  __IO SPI_CR2_RegDef CR2;        /*!< SPI control register 2,                             Address offset: 0x04 */
  __IO SPI_SR_RegDef SR;         /*!< SPI status register,                                Address offset: 0x08 */
  __IO uint32_t DR;         /*!< SPI data register,                                  Address offset: 0x0C */
  __IO uint32_t CRCPR;      /*!< SPI CRC polynomial register (not used in I2S mode), Address offset: 0x10 */
  __IO uint32_t RXCRCR;     /*!< SPI RX CRC register (not used in I2S mode),         Address offset: 0x14 */
  __IO uint32_t TXCRCR;     /*!< SPI TX CRC register (not used in I2S mode),         Address offset: 0x18 */
  __IO uint32_t I2SCFGR;    /*!< SPI_I2S configuration register,                     Address offset: 0x1C */
  __IO uint32_t I2SPR;      /*!< SPI_I2S prescaler register,                         Address offset: 0x20 */
} SPI_TypeDef;

/* **************** base addresses start ************************************* */
/* Peripheral memory map */
#define PERIPH_BASE           0x40000000UL 
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000UL)

/* GPIO AHB1 base address */
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE            (AHB1PERIPH_BASE + 0x1000UL)
#define GPIOF_BASE            (AHB1PERIPH_BASE + 0x1400UL)
#define GPIOG_BASE            (AHB1PERIPH_BASE + 0x1800UL)
#define GPIOH_BASE            (AHB1PERIPH_BASE + 0x1C00UL)

/* SPI base address */
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800UL)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00UL)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000UL)
#define SPI4_BASE             (APB2PERIPH_BASE + 0x3400UL)

/* EXTI base address */
#define EXTI_BASE             (APB2PERIPH_BASE + 0x3C00UL)

/* RCC base address */
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800UL)

/* SYSCFG base address */
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800UL)
/* **************** base addresses end ************************************* */

/* **************** Peripheral devlaration end ************************************* */
/* SPI Peripheral_declaration */
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)
#define SPI4                ((SPI_TypeDef *) SPI4_BASE)
/* SPI Peripheral_declaration End */

/* SYSCFG Peripheral_declaration */
#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
/* SYSCFG Peripheral_declaration End */

/* EXTI Peripheral_declaration */
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
/* EXTI Peripheral_declaration End */

/* PORT Peripheral_declaration */
#define GPIOA               ((PORT_TypeDef *) GPIOA_BASE)
#define GPIOB               ((PORT_TypeDef *) GPIOB_BASE)
#define GPIOC               ((PORT_TypeDef *) GPIOC_BASE)
#define GPIOD               ((PORT_TypeDef *) GPIOD_BASE)
#define GPIOE               ((PORT_TypeDef *) GPIOE_BASE)
#define GPIOF               ((PORT_TypeDef *) GPIOF_BASE)
#define GPIOG               ((PORT_TypeDef *) GPIOG_BASE)
#define GPIOH               ((PORT_TypeDef *) GPIOH_BASE)
/* PORT Peripheral_declaration End */

/* RCC Peripheral_declaration */
#define RCC                 ((RCC_TypeDef *)RCC_BASE)
/* RCC Peripheral_declaration End */

/* **************** Peripheral declaration end ************************************* */

/******************************* GPIO Instances *******************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == GPIOA) || \
                                        ((INSTANCE) == GPIOB) || \
                                        ((INSTANCE) == GPIOC) || \
                                        ((INSTANCE) == GPIOD) || \
                                        ((INSTANCE) == GPIOE) || \
                                        ((INSTANCE) == GPIOF) || \
                                        ((INSTANCE) == GPIOG) || \
                                        ((INSTANCE) == GPIOH))

/******************************** SPI Instances *******************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE) (((INSTANCE) == SPI1) || \
                                       ((INSTANCE) == SPI2) || \
                                       ((INSTANCE) == SPI3) || \
                                       ((INSTANCE) == SPI4))
#endif /* __STM32F446RE_H__ */
