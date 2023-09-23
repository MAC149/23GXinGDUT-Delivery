#include "misc.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
KEY_t  KEY1 = {KEY1_GPIO_Port,KEY1_Pin,FALSE,FALSE};      
KEY_t  KEY2 = {KEY2_GPIO_Port,KEY2_Pin,FALSE,FALSE}; 
KEY_t  KEY3 = {KEY3_GPIO_Port,KEY3_Pin,FALSE,FALSE}; 
KEY_t  KEY4 = {KEY4_GPIO_Port,KEY4_Pin,FALSE,FALSE}; 

uint8_t Key_Scan(KEY_t* KEY)
{			
	KEY_t* const  COM = KEY;
	uint8_t i = 0;
	
	/*检测是否有按键按下 */
	if(HAL_GPIO_ReadPin(COM->GPIOx,COM->GPIO_Pin) == KEY_ON )  
	{	 
		COM->Click = FALSE;
		COM->Press = TRUE;
		//触摸按键长按检测
		for(i=0;i<200;i++)
		{
			HAL_Delay(10);
			//如果2s内，按键状态出现高电平，此时按键为单击，跳出循环
			if(HAL_GPIO_ReadPin(COM->GPIOx,COM->GPIO_Pin) == KEY_OFF)
			{
				COM->Click = TRUE;
				COM->Press = FALSE;
				break; //跳出for循环
			}
		}
		if(COM->Click == TRUE)
		{
			//printf("检测到触摸按键单击\r\n");
			//按键1单击动作
			if(COM->GPIOx == KEY1.GPIOx && COM->GPIO_Pin == KEY1_Pin)
			{
				return 1;
			}
			//按键2单击动作
			else if(COM->GPIOx == KEY2.GPIOx && COM->GPIO_Pin == KEY2_Pin)
			{
			}
			//按键3单击动作
			else if(COM->GPIOx == KEY3.GPIOx && COM->GPIO_Pin == KEY3_Pin)
			{
			}
		}
		
		if(COM->Press == TRUE)
		{
			//printf("检测到触摸按键长按\r\n");
			//按键1长按动作
			if(COM->GPIOx == KEY1.GPIOx && COM->GPIO_Pin == KEY1_Pin)
			{
				HAL_Delay(200);
			}
			//按键2长按动作
			else if(COM->GPIOx == KEY2.GPIOx && COM->GPIO_Pin == KEY2_Pin)
			{
				HAL_Delay(200);
			}
			//按键3长按动作
			else if(COM->GPIOx == KEY3.GPIOx && COM->GPIO_Pin == KEY3_Pin)
			{
			}
		}
		//清除按键状态
		COM->Click = FALSE;
		COM->Press = FALSE;
	}
	return 0;
}

int fputc(int ch, FILE *f)
{
 HAL_UART_Transmit(&DEBUG_UART, (uint8_t *)&ch, 1, 0xFFFF);
 return ch;
}

int fgetc(FILE *f)
{
	uint8_t ch=0;
	HAL_UART_Receive(&DEBUG_UART, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

void UsartPrintf(UART_HandleTypeDef USARTx, char *fmt,...)
{
 
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != NULL)
	{
        HAL_UART_Transmit (&USARTx ,(uint8_t *)pStr++,1,HAL_MAX_DELAY );		
	}
 
}

uint16_t abs_(int a)
{
	if(a>=0)return a;
	else return -a;
}

float abs_ff(float x)//去绝对值
{
    return (x < 0) ? -x : x;
}