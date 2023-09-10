#include "step.h"

void Full_Step()
{
    OLED_Init();
    Motortot_Init();
    Delay_Init();
    Motortot_SetEn_Off();
    OLED_ShowString(1,1,"INIT...",16);
    OPS.OPS_Init();
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_Clear();
	Motortot_SetEn_On();
	HAL_Delay(200);
	//去扫码区
	//cargo
	//扫码
	uint8_t *QRCode;
	do
	{
		QRCode=Scan_GetCode();
        HAL_UART_Transmit(&DEBUG_UART,QRCode,(uint16_t)Scan_Data_Length,1000);
	}
    while(!strcmp(QRCode,"TO"));
	//转盘
	//cargo
	//舵机动作组

	//路口
	//cargo
	//粗加工
	//cargo
	//矫正
	//OPENMV
	//舵机动作组

	//路口
	//cargo
	//半成品
	//cargo
	//矫正
	//OPENMV
	//舵机动作组

	//回路口
	//cargo
	//回路口
	//cargo
	//回转盘
	//cargo
	//舵机动作组
	
	//路口
	//cargo
	//粗加工
	//cargo
	//矫正
	//OPENMV
	//舵机动作组

	//路口
	//cargo
	//半成品
	//cargo
	//矫正
	//OPENMV
	//舵机动作组

	//路口
	//cargo
	//结束
	//cargo
}
