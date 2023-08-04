#ifndef _MISC_H_
#define _MISC_H_

#include "GeneralDef.h"

#define KEY_ON	1
#define KEY_OFF	0


#define KEY1_Pin GPIO_PIN_4
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_0
#define KEY2_GPIO_Port GPIOC
#define KEY3_Pin GPIO_PIN_5
#define KEY3_GPIO_Port GPIOC
#define KEY4_Pin GPIO_PIN_4
#define KEY4_GPIO_Port GPIOC

void UsartPrintf(UART_HandleTypeDef USARTx, char *fmt,...);
typedef struct
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	uint8_t  Click;              //单击
	uint8_t  Press;              //长按
} KEY_t;

//定义枚举类型 -> TRUE/FALSE位
typedef enum 
{
  FALSE = 0U, 
  TRUE = !FALSE
} FlagStatus_t;

uint8_t Key_Scan(KEY_t* KEY);

extern KEY_t  KEY1; 
extern KEY_t  KEY2; 
extern KEY_t  KEY3; 
extern KEY_t  KEY4; 

#endif // !_MISC_H_
