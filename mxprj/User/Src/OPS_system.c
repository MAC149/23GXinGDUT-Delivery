/**
  ******************************************************************************
  * @file    OPS_system.c
  * @author  LJL
  * @version V1.0
  * @date    2022-xx-xx
  * @brief   编码器相关函数文件
  ******************************************************************************
  * @note:
  *
  *
  * @note:
  *
  *
  ******************************************************************************
  * @attention
  *
  * 实验平台:LJL STM32F103xxx核心板
  * 论坛    	:xxx
  * github	:xxx
  *
  ******************************************************************************
  */
#include "OPS_system.h"
#include <math.h>

static uint8_t ops_ucRxbuff[opsRxbuff_LENGTH] = {0x00};	//接受的数据缓存

static void Stract(uint8_t strDestination[],uint8_t strSource[],int num);
static void Update_all(void);
static void Update_X(float New_X);
static void Update_Y(float New_Y);
static void Update_A(float New_A);
static void OPS_init(void);
static void Protocol_Analysis(void);

OPS_t OPS = 
{
	ops_ucRxbuff,
	0,0,0,0,0,0,

	Update_all,
	Update_X,
	Update_Y,
	Update_A,

	OPS_init,
	Protocol_Analysis
};


/**
	*@brief		字符串拼接
	*@param		
	*@note		无
	*@retval	无
*/
void Stract(uint8_t strDestination[],uint8_t strSource[],int num)
{
	int i = 0,j =0;
	while(strDestination[i]!='\0')i++;
	for(j = 0;j < num; j++)
		strDestination[i++] = strSource[j];
}

/**
	*@brief		ops清零
	*@param
	*@note
	*@retval
*/
void Update_all(void)
{	
	uint8_t all_buff[8] = "ACT0";
	HAL_UART_Transmit(&OPS_auart_handle,all_buff,4,1000);
}


/**
	*@brief		更新x轴坐标
	*@param
	*@note
	*@retval
*/
void Update_X(float New_X)
{	
	uint8_t Update_x[8] = "ACTX";
	static union
	{
		float X;
		uint8_t data[4];
	}New_setx;
	New_setx.X = New_X;
	Stract(Update_x,New_setx.data,4);
		HAL_UART_Transmit(&OPS_auart_handle,Update_x,8,1000);
}

/**
	*@brief		更新y轴坐标
	*@param
	*@note
	*@retval
*/
void Update_Y(float New_Y)
{	
	uint8_t Update_Y[8] = "ACTY";
	static union
	{
		float Y;
		uint8_t data[4];
	}New_sety;
	New_sety.Y = New_Y;
	Stract(Update_Y,New_sety.data,4);
		HAL_UART_Transmit(&OPS_auart_handle,Update_Y,8,1000);
	
}

/**
	*@brief		更新航向角
	*@param
	*@note
	*@retval
*/
void Update_A(float New_A)
{	
	uint8_t Update_a[8] = "ACTJ";
	static union
	{
		float A;
		uint8_t data[4];
	}New_seta;
	New_seta.A = New_A;
	Stract(Update_a,New_seta.data,4);
		HAL_UART_Transmit(&OPS_auart_handle,Update_a,8,1000);
	
}

/**
	*@brief		串口接受数据函数
	*@param
	*@note
	*@retval
*/
void OPS_init(void)
{
	__HAL_UART_ENABLE_IT(&OPS_auart_handle,UART_IT_IDLE);                         //使能空闲中断
	
	HAL_UART_Receive_DMA(&OPS_auart_handle,OPS.pucRxbuff,opsRxbuff_LENGTH); //开启DMA接收
	// HAL_Delay(7000);
	// HAL_Delay(6500);
//	Update_all();
}


/**
	* @name   Protocol_Analysis
	* @brief  协议分析
	* @param  
	* @retval None      
*/
static void Protocol_Analysis(void) 
{
	static union
	{
		uint8_t data[24];
		float ActVal[6];
	}posture;
	uint8_t i = 0,Index = 0;
	
  //串口3停止DMA接收
	HAL_UART_DMAStop(&OPS_auart_handle);
	
	//过滤干扰数据
	for(i=0;i<opsRxbuff_LENGTH;i++)
	{
		//检测键值起始数据0x0d,0x0a
		if(Index == 0)
		{
			if(OPS.pucRxbuff[i] != 0x0d)
				if(OPS.pucRxbuff[i+1] != 0x0a)
					continue;
		}
		
		OPS.pucRxbuff[Index] = OPS.pucRxbuff[i];

		//已读取28个字节
		if(Index == opsOrder_LENGTH)
			break;
		
		Index++;
	}
	/*赋值*/
	for(i=0;i<opsRxbuff_LENGTH-4;i++)
		{posture.data[i] = OPS.pucRxbuff[i+2];}
	if(fabs(posture.ActVal[0])>=1e-6){OPS.zangle=posture.ActVal[0];}
	if(fabs(posture.ActVal[1])>=1e-6){OPS.xangle=posture.ActVal[1];}
	if(fabs(posture.ActVal[2])>=1e-6){OPS.yangle=posture.ActVal[2];}
	if(fabs(posture.ActVal[3])>=1e-6){OPS.pos_x =posture.ActVal[3];}
	if(fabs(posture.ActVal[4])>=1e-6){OPS.pos_y =posture.ActVal[4];}
	if(fabs(posture.ActVal[5])>=1e-6){OPS.w_z   =posture.ActVal[5];}
	
	//清缓存
	for(i=0;i<opsRxbuff_LENGTH;i++)
	{
		OPS.pucRxbuff[i] = 0x00;
	}
}

void OPS_OLED_Status_Update()
{
	OLED_ShowFNum(1,6,OPS.pos_x,7,16);
    OLED_ShowFNum(2,6,OPS.pos_y,7,16);
    OLED_ShowFNum(3,8,OPS.zangle,7,16);
}

