#ifndef _GENERALDEF_H_
#define _GENERALDEF_H_
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdbool.h>
#define HIGH GPIO_PIN_SET       //高电平
#define LOW  GPIO_PIN_RESET     //低电平

#define ON  LOW                 //开
#define OFF HIGH                //关

#define CW  HIGH                //顺时针
#define CCW LOW                 //逆时针


#endif // !_GENERALDEF_H_
