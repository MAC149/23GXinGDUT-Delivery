#include "GeneralDef.h"
#include "Scan.h"
#include "Delay.h"
#include "Motor.h"
#include "vision.h"
#include "imu.h"
#include <string.h>
#include "OPS_system.h"

static uint8_t Scan_Rec_RX;
extern uint8_t scan_dmabuf_length;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart5_rx;
extern bool YawKeepFlag;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t Res5;
	if (huart == &SCANER_UARTX)
	{
		// Scan_Rec_RX = Scan.Scan_Char_Buf;
		// Scan.Scan_Rec_Process(Scan_Rec_RX);
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

static u32 j = 0;
static u32 j1 = 0; // 计数器
static u32 j2 = 0; // 计数器
static u16 temp = 0;

void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == OPS_auart_handle.Instance)
	{
		//解析HMI协议
		OPS.Protocol_Analysis();
		HAL_UART_Receive_DMA(&OPS_auart_handle,OPS.pucRxbuff,opsRxbuff_LENGTH); //串口3开启DMA接收
	}
	else if(huart->Instance == SCANER_UARTX.Instance)
	{
		scan_dmabuf_length=SCAN_DMA_MAX_LENGTH- __HAL_DMA_GET_COUNTER(&SCANER_UARTDMA);
		//scan_dmabuf[Scan_Data_Length]='\0';
		Scan_DMA_RecProcess();
	}
	else if(huart->Instance == IMU_UART.Instance)
	{
		FD_DMAbuflen=FD_DMABUF_MAXLEN- __HAL_DMA_GET_COUNTER(&IMU_UARTDMA);
		// imuDMAProc();
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim6) // 1ms
	{
		if(++j==10)  //每10ms执行一次
		{
			j = 0;
			position_control(); //底盘坐标控制
		}
		if(++j2==3) //每3ms执行一次
		{
			j2 = 0;
			speed_control();
		}
		// if(++j1==5)
		// {
		// 	//OpenMVGN_StUpd(&OpenMV1);
		// }
	}
	else if (htim == &htim13)
	{
		if(++j1==5)
		{
			j1=0;
			if(YawKeepFlag)
			{
				// YawKeep();
			}
		}
		// OLED_ShowYaw();
		// OPS_OLED_Status_Update();
	}
	else if (htim == &htim7) // 5us
	{
		move_motor_control();  //底盘电机控制
	}
	// if (htim->Instance == TIM6) {
	//     setState(true);
	// }
}
