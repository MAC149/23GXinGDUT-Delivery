#ifndef _OPENMV_H_
#define _OPENMV_H_
#include "GeneralDef.h"

#define OPENMV_REC_BUF_LEN 64

#define OPENMV_UART huart4

void OpenMV_Receive_Process();
void OpenMV_Init();
void OpenMV_Receive_Start();
void OpenMV_Data_Process();

#endif // 