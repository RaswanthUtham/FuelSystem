#ifndef __STM32F4XX_HAL_PORT_H__
#define __STM32F4XX_HAL_PORT_H__

#define PORT_MODULE_ID                     (124U)

typedef uint16_t Port_PinType;
typedef uint32_t Port_PinModeType;

typedef struct
{

    PORT_TypeDef *Port; /*!< Specifies the GPIO Port to be configured.
                          This parameter can be any value of @ref PORT Peripheral_declaration */

    Port_PinType Pin; /*!< Specifies the GPIO pins to be configured.
                     This parameter can be any value of @ref GPIO_pins_define */

    Port_PinModeType Mode; /*!< Specifies the operating mode for the selected pins.
                        This parameter can be a value of @ref GPIO_mode_define */

    uint32_t Pull; /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                        This parameter can be a value of @ref GPIO_pull_define */

    uint32_t Speed; /*!< Specifies the speed for the selected pins.
                         This parameter can be a value of @ref GPIO_speed_define */

    uint32_t Alternate; /*!< Peripheral to be connected to the selected pins.
                             This parameter can be a value of @ref GPIO_Alternate_function_selection */

} Port_ConfigType;

typedef enum
{
  PORT_PIN_IN = 0x00U,
  PORT_PIN_OUT = 0x01U
} Port_PinDirectionType;

typedef enum
{
  PORT_PIN_RESET = 0,
  PORT_PIN_SET
}Port_PinState;

#define IS_PORT_PIN_ACTION(ACTION) (((ACTION) == PORT_PIN_RESET) || ((ACTION) == PORT_PIN_SET))

/* GPIO_pins_define */
#define PORT_PIN_0                 ((Port_PinType)0x0001)  /* Pin 0 selected    */
#define PORT_PIN_1                 ((Port_PinType)0x0002)  /* Pin 1 selected    */
#define PORT_PIN_2                 ((Port_PinType)0x0004)  /* Pin 2 selected    */
#define PORT_PIN_3                 ((Port_PinType)0x0008)  /* Pin 3 selected    */
#define PORT_PIN_4                 ((Port_PinType)0x0010)  /* Pin 4 selected    */
#define PORT_PIN_5                 ((Port_PinType)0x0020)  /* Pin 5 selected    */
#define PORT_PIN_6                 ((Port_PinType)0x0040)  /* Pin 6 selected    */
#define PORT_PIN_7                 ((Port_PinType)0x0080)  /* Pin 7 selected    */
#define PORT_PIN_8                 ((Port_PinType)0x0100)  /* Pin 8 selected    */
#define PORT_PIN_9                 ((Port_PinType)0x0200)  /* Pin 9 selected    */
#define PORT_PIN_10                ((Port_PinType)0x0400)  /* Pin 10 selected   */
#define PORT_PIN_11                ((Port_PinType)0x0800)  /* Pin 11 selected   */
#define PORT_PIN_12                ((Port_PinType)0x1000)  /* Pin 12 selected   */
#define PORT_PIN_13                ((Port_PinType)0x2000)  /* Pin 13 selected   */
#define PORT_PIN_14                ((Port_PinType)0x4000)  /* Pin 14 selected   */
#define PORT_PIN_15                ((Port_PinType)0x8000)  /* Pin 15 selected   */
#define PORT_PIN_All               ((Port_PinType)0xFFFF)  /* All pins selected */
#define PORT_PIN_MASK              0x0000FFFFU /* PIN mask for assert test */
#define IS_PORT_PIN(PIN)           (((((uint32_t)PIN) & PORT_PIN_MASK ) != 0x00U) && ((((uint32_t)PIN) & ~PORT_PIN_MASK) == 0x00U))
/* GPIO_pins_define End */

#define PORT_PIN_POS_TO_NUMBER(_POS)  (_POS ==  PORT_PIN_0)   ? 0U : \
                                      (_POS ==  PORT_PIN_1)   ? 1U : \
                                      (_POS ==  PORT_PIN_2)   ? 2U : \
                                      (_POS ==  PORT_PIN_3)   ? 3U : \
                                      (_POS ==  PORT_PIN_4)   ? 4U : \
                                      (_POS ==  PORT_PIN_5)   ? 5U : \
                                      (_POS ==  PORT_PIN_6)   ? 6U : \
                                      (_POS ==  PORT_PIN_7)   ? 7U : \
                                      (_POS ==  PORT_PIN_8)   ? 8U : \
                                      (_POS ==  PORT_PIN_9)   ? 9U : \
                                      (_POS ==  PORT_PIN_10)  ? 10U : \
                                      (_POS ==  PORT_PIN_11)  ? 11U : \
                                      (_POS ==  PORT_PIN_12)  ? 12U : \
                                      (_POS ==  PORT_PIN_13)  ? 13U : \
                                      (_POS ==  PORT_PIN_14)  ? 14U : 15

#define PORT_MODE_POS               ((Port_PinModeType)(0U))
#define PORT_MODE                   ((Port_PinModeType)(0x3UL << PORT_MODE_POS))
#define MODE_INPUT                  ((Port_PinModeType)(0x0UL << PORT_MODE_POS))
#define MODE_OUTPUT                 ((Port_PinModeType)(0x1UL << PORT_MODE_POS))
#define MODE_AF                     ((Port_PinModeType)(0x2UL << PORT_MODE_POS))
#define MODE_ANALOG                 ((Port_PinModeType)(0x3UL << PORT_MODE_POS))

#define OUTPUT_TYPE_POS              ((Port_PinModeType)(4U))
#define OUTPUT_TYPE                  ((Port_PinModeType)(0x1UL << OUTPUT_TYPE_POS))
#define OUTPUT_PP                    ((Port_PinModeType)(0x0UL << OUTPUT_TYPE_POS))
#define OUTPUT_OD                    ((Port_PinModeType)(0x1UL << OUTPUT_TYPE_POS))

#define EXTI_MODE_POS                ((Port_PinModeType)(16U))
#define EXTI_MODE                    ((Port_PinModeType)(0x3UL << EXTI_MODE_POS))
#define EXTI_IT                      ((Port_PinModeType)(0x1UL << EXTI_MODE_POS))
#define EXTI_EVT                     ((Port_PinModeType)(0x2UL << EXTI_MODE_POS))

#define TRIGGER_MODE_POS             ((Port_PinModeType)(20U))
#define TRIGGER_MODE                 ((Port_PinModeType)(0x7UL << TRIGGER_MODE_POS))
#define TRIGGER_RISING               ((Port_PinModeType)(0x1UL << TRIGGER_MODE_POS))
#define TRIGGER_FALLING              ((Port_PinModeType)(0x2UL << TRIGGER_MODE_POS))

/* GPIO_mode_define */
#define PORT_PIN_MODE_INPUT                 ((Port_PinModeType)(MODE_INPUT))
#define PORT_PIN_MODE_ANALOG                ((Port_PinModeType)(MODE_ANALOG))
#define PORT_PIN_MODE_OUTPUT_PP             ((Port_PinModeType)(MODE_OUTPUT | OUTPUT_PP))
#define PORT_PIN_MODE_OUTPUT_OD             ((Port_PinModeType)(MODE_OUTPUT | OUTPUT_OD))
#define PORT_PIN_MODE_AF_PP                 ((Port_PinModeType)(MODE_AF | OUTPUT_PP))
#define PORT_PIN_MODE_AF_OD                 ((Port_PinModeType)(MODE_AF | OUTPUT_OD))
#define PORT_PIN_MODE_IT_RISING             ((Port_PinModeType)(MODE_INPUT | EXTI_IT | TRIGGER_RISING))
#define PORT_PIN_MODE_IT_FALLING            ((Port_PinModeType)(MODE_INPUT | EXTI_IT | TRIGGER_FALLING))
#define PORT_PIN_MODE_IT_RISING_FALLING     ((Port_PinModeType)(MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING))
#define PORT_PIN_MODE_EVT_RISING            ((Port_PinModeType)(MODE_INPUT | EXTI_EVT | TRIGGER_RISING))
#define PORT_PIN_MODE_EVT_FALLING           ((Port_PinModeType)(MODE_INPUT | EXTI_EVT | TRIGGER_FALLING))
#define PORT_PIN_MODE_EVT_RISING_FALLING    ((Port_PinModeType)(MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING))
#define IS_PORT_PIN_MODE(MODE) (((MODE) == PORT_PIN_MODE_INPUT)              ||\
                                ((MODE) == PORT_PIN_MODE_OUTPUT_PP)          ||\
                                ((MODE) == PORT_PIN_MODE_OUTPUT_OD)          ||\
                                ((MODE) == PORT_PIN_MODE_AF_PP)              ||\
                                ((MODE) == PORT_PIN_MODE_AF_OD)              ||\
                                ((MODE) == PORT_PIN_MODE_IT_RISING)          ||\
                                ((MODE) == PORT_PIN_MODE_IT_FALLING)         ||\
                                ((MODE) == PORT_PIN_MODE_IT_RISING_FALLING)  ||\
                                ((MODE) == PORT_PIN_MODE_EVT_RISING)         ||\
                                ((MODE) == PORT_PIN_MODE_EVT_FALLING)        ||\
                                ((MODE) == PORT_PIN_MODE_EVT_RISING_FALLING) ||\
                                ((MODE) == PORT_PIN_MODE_ANALOG))
/* GPIO_mode_define End*/

/* GPIO_speed_define */
#define  PORT_PIN_SPEED_FREQ_LOW         0x00000000U  /*!< IO works at 2 MHz, please refer to the product datasheet */
#define  PORT_PIN_SPEED_FREQ_MEDIUM      0x00000001U  /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
#define  PORT_PIN_SPEED_FREQ_HIGH        0x00000002U  /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
#define  PORT_PIN_SPEED_FREQ_VERY_HIGH   0x00000003U  /*!< range 50 MHz to 200 MHz, please refer to the product datasheet  */
#define  IS_PORT_SPEED(_SPEED) (((_SPEED) == PORT_PIN_SPEED_FREQ_LOW) || ((_SPEED) == PORT_PIN_SPEED_FREQ_MEDIUM) || \
                               ((_SPEED) == PORT_PIN_SPEED_FREQ_HIGH) || ((_SPEED) == PORT_PIN_SPEED_FREQ_VERY_HIGH))
/* GPIO_speed_define */

/* GPIO_pull_define */
#define  PORT_PIN_NOPULL        0x00000000U   /*!< No Pull-up or Pull-down activation  */
#define  PORT_PIN_PULLUP        0x00000001U   /*!< Pull-up activation                  */
#define  PORT_PIN_PULLDOWN      0x00000002U   /*!< Pull-down activation                */
#define IS_PORT_PIN_PULL(PULL) (((PULL) == PORT_PIN_NOPULL) || \
                                ((PULL) == PORT_PIN_PULLUP) || \
                                ((PULL) == PORT_PIN_PULLDOWN))
/* GPIO_pull_define End*/

/* GPIO_Alternate_function_selection */
#define PORT_SPI1_AF5            ((uint8_t)0x05)
#define PORT_SPI2_AF5            ((uint8_t)0x05)
#define PORT_SPI3_AF5            ((uint8_t)0x05)
#define PORT_SPI4_AF5            ((uint8_t)0x05)
#define PORT_SPI1_AF6            ((uint8_t)0x06)
#define PORT_SPI2_AF6            ((uint8_t)0x06)
#define PORT_SPI3_AF6            ((uint8_t)0x06)
#define PORT_SPI4_AF6            ((uint8_t)0x06)
#define IS_PORT_AF(PORT_AF)      ((PORT_AF == PORT_SPI1_AF5) ||\
                                  (PORT_AF == PORT_SPI2_AF5) ||\
                                  (PORT_AF == PORT_SPI3_AF5) ||\
                                  (PORT_AF == PORT_SPI4_AF5) ||\
                                  (PORT_AF == PORT_SPI1_AF6) ||\
                                  (PORT_AF == PORT_SPI2_AF6) ||\
                                  (PORT_AF == PORT_SPI3_AF6) ||\
                                  (PORT_AF == PORT_SPI4_AF6))
/* GPIO_Alternate_function_selection End */

#define PORT_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U :\
                                               ((__GPIOx__) == (GPIOF))? 5U :\
                                               ((__GPIOx__) == (GPIOG))? 6U : 7U)


/* PORT Error Codes */
#define PORT_E_INVALID_PORT                  (1)
#define PORT_E_INVALID_PIN                   (2)
#define PORT_E_INVALID_MODE                  (3)
#define PORT_E_INVALID_SPEED                 (4)
#define PORT_E_INVALID_PULL                  (5)
#define PORT_E_INVALID_AF                    (6)
#define PORT_E_INVALID_ACTION                (7)

/* PORT Service Ids */
#define PORT_SID_INIT                     (1)
#define PORT_SID_DEINIT                   (2)
#define PORT_SID_READPIN                  (3)
#define PORT_SID_WRITEPIN                 (4)
#define PORT_SID_TOGGLEPIN                (5)
#define PORT_SID_CLOCKCONTROL             (6)


uint8_t Port_Init (const Port_ConfigType* ConfigPtr);
uint8_t Port_DeInit (const Port_ConfigType* ConfigPtr);
uint8_t Port_TogglePin(PORT_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t Port_WritePin(PORT_TypeDef *GPIOx, uint16_t GPIO_Pin, Port_PinState PinState);
uint8_t Port_ReadPin(PORT_TypeDef *GPIOx, uint16_t GPIO_Pin, Port_PinState *result);
uint8_t Port_ClockControl(PORT_TypeDef *GPIOx, uint8_t Enable);

void Port_EXTI0_IRQHandler(Port_PinType Port_Pin);
void Port_EXTI15_10_IRQHandler(Port_PinType Port_Pin);

__attribute__((weak)) void Port_EXTI0_IRQ_CB(void);
__attribute__((weak)) void Port_EXTI15_10_IRQ_CB(void);

#endif /* __STM32F4XX_HAL_PORT_H__ */
