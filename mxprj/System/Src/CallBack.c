#include "CallBack.h"
#include <string.h>

static uint8_t Scan_Rec_RX;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t Res5;
	if (huart == &SCANER_UARTX)
	{
		Scan_Rec_RX = Scan.Scan_Char_Buf;
		Scan.Scan_Rec_Process(Scan_Rec_RX);
	}
	else if (huart == OpenMV1.OpenMV_huart)
	{
		OpenMV1.OpenMV_Receive_Process(&OpenMV1);
	}
	else if (huart == &IMU_UART)
	{
		imuRec();
	}
}


void  HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static u32 j = 0;
	static u32 j1 = 0; //计数器
	static u32 j2 = 0; //计数器
	static u16 temp=0;
	if(htim==&htim13)
	{
		OLED_ShowYaw();
	}
	else if(htim == &htim6)			//1ms
	{
		if(++j==200)  //每10ms执行一次
		{
			j = 0;
			YawKeep();
		}
		if(++j2==3) //每3ms执行一次
		{
			j2 = 0;
		}
		if(++j1==5)
		{
			//OpenMVGN_StUpd(&OpenMV1);
		}
	}
	else if(htim == &htim7)			//5us
	{
	}	
	// if (htim->Instance == TIM6) {
    //     setState(true);
    // }
}
