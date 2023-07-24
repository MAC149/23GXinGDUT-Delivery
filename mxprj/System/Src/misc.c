#include "misc.h"

KEY_t  KEY1 = {KEY1_GPIO_Port,KEY1_Pin,FALSE,FALSE};      
KEY_t  KEY2 = {KEY2_GPIO_Port,KEY2_Pin,FALSE,FALSE}; 
KEY_t  KEY3 = {KEY3_GPIO_Port,KEY3_Pin,FALSE,FALSE}; 


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
				
				//LED_TogglePin;
			}
			//按键3单击动作
			else if(COM->GPIOx == KEY3.GPIOx && COM->GPIO_Pin == KEY3_Pin)
			{}
			
		}
		
		if(COM->Press == TRUE)
		{
			//printf("检测到触摸按键长按\r\n");
			
			//按键1长按动作
			if(COM->GPIOx == KEY1.GPIOx && COM->GPIO_Pin == KEY1_Pin)
			{
				
				//LED_TogglePin;
				HAL_Delay(200);
				//LED_TogglePin;
			}
			//按键2长按动作
			else if(COM->GPIOx == KEY2.GPIOx && COM->GPIO_Pin == KEY2_Pin)
			{
				
				//LED_TogglePin;
				HAL_Delay(200);
				//LED_TogglePin;
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

