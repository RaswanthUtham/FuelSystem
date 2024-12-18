#ifndef __STM32XXXX_H__
#define __STM32XXXX_H__

#ifndef STM32F466RE
#define STM32F466RE
#endif /* STM32F466RE */

#ifdef STM32F466RE
#include "stm32f446re.h"
#endif

extern uint8_t Error_Code_Index;
extern uint8_t DET_ErrorCode[50]; /* ErrCode */
extern uint8_t DET_ServiceId[50]; /* Sid */
extern uint8_t DET_ModuleId[50]; /* Mid */


#endif /* __STM32XXXX_H__ */
