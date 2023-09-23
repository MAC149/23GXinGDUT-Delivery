#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "GeneralDef.h"
#include "Scan.h"
#include "OPS_system.h"
#include "Delay.h"
#include "Motor.h"
#include "vision.h"
#include "imu.h"

void HAL_UART_IdleCallback(UART_HandleTypeDef *huart);

#endif // !_CALLBACK_H_