#include "CallBack.h"

static uint8_t Scan_Rec_RX;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart==&SCANER_UARTX)
    {
        Scan_Rec_RX=Scan.Scan_Char_Buf;
        Scan.Scan_Rec_Process(Scan_Rec_RX);
    }
}

void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == OPS_auart_handle.Instance)
	{
		//解析HMI协议
		OPS.Protocol_Analysis();
		HAL_UART_Receive_DMA(&OPS_auart_handle,OPS.pucRxbuff,opsRxbuff_LENGTH); //串口3开启DMA接收
	}
}

void  HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static u32 j = 0;
//	static u32 j1 = 0; //计数器
	static u32 j2 = 0; //计数器
	if(htim==&htim13)
	{
		OPS_OLED_Status_Update();
	}
	else if(htim == &htim6)			//1ms
	{
		if(++j==10)  //每10ms执行一次
		{
			j = 0;
			PID_ARR_Dec();
		}
		if(++j2==3) //每3ms执行一次
		{
			j2 = 0;
		}
	}
	else if(htim == &htim7)			//5us
	{
		
	}	
	// if (htim->Instance == TIM6) {
    //     setState(true);
    // }
}
