#ifndef _DELAY_H_
#define _DELAY_H_
#include "GeneralDef.h"
void setState(bool state);
void HAL_Delay_us(uint32_t us);
void Delay_Init();
#endif // !_DELAY_H_
