#ifndef _GENERALDEF_H_
#define _GENERALDEF_H_
#include "stm32f4xx_hal.h"
// #include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdbool.h>
#include "misc.h"


#define u64 uint64_t 
#define u32 uint32_t 
#define u16 uint16_t 
#define u8  uint8_t  
#define s64 int64_t
#define s32 int32_t
#define s16 int16_t
#define s8  int8_t


#define HIGH GPIO_PIN_SET       //高电平
#define LOW  GPIO_PIN_RESET     //低电平

#define ON  LOW                 //开
#define OFF HIGH                //关

#define CW  HIGH                //顺时针
#define CCW LOW                 //逆时针


#endif // !_GENERALDEF_H_
