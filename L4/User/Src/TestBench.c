#include "tftlcd.h"



void BILCD_Test()
{
    LCD_Init();
	LCD_Clear(RED); 		//清屏
	BACK_COLOR=RED;
	POINT_COLOR=CYAN;	
	LCD_ShowString(0, 0, 320, 12, 32, "WEIyi STM32L431RCT6");
	LCD_ShowString(0, 32, 320, 12, 32, "1.47TFTLCD 320*173");
	LCD_ShowString(0, 64, 320, 16, 32, "QQqun:127580435");
}




void MID_Test()
{
    BILCD_Test();
}