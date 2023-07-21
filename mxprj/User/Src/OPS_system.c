/**
  ******************************************************************************
  * @file    OPS_system.c
  * @author  LJL
  * @version V1.0
  * @date    2022-xx-xx
  * @brief   ��������غ����ļ�
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
  * ʵ��ƽ̨:LJL STM32F103xxx���İ�
  * ��̳    	:xxx
  * github	:xxx
  *
  ******************************************************************************
  */
#include "OPS_system.h"


static uint8_t ops_ucRxbuff[opsRxbuff_LENGTH] = {0x00};	//���ܵ����ݻ���

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
	*@brief		�ַ���ƴ��
	*@param		
	*@note		��
	*@retval	��
*/
void Stract(uint8_t strDestination[],uint8_t strSource[],int num)
{
	int i = 0,j =0;
	while(strDestination[i]!='\0')i++;
	for(j = 0;j < num; j++)
		strDestination[i++] = strSource[j];
}

/**
	*@brief		ops����
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
	*@brief		����x������
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
	*@brief		����y������
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
	*@brief		���º����
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
	*@brief		���ڽ������ݺ���
	*@param
	*@note
	*@retval
*/
void OPS_init(void)
{
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);                         //ʹ�ܴ���3�Ŀ����ж�
	HAL_UART_Receive_DMA(&huart1,OPS.pucRxbuff,opsRxbuff_LENGTH); //����3����DMA����
//	GUI_ShowCHinese(0,0,16,"�������ڳ�ʼ����",1);
	HAL_Delay(7000);
	HAL_Delay(6000);
//	Update_all();
//	OLED_Clear(0);
}

/**
	* @name   Protocol_Analysis
	* @brief  Э�����
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
	
  //����3ֹͣDMA����
	HAL_UART_DMAStop(&huart1);
	
	//���˸�������
	for(i=0;i<opsRxbuff_LENGTH;i++)
	{
		//����ֵ��ʼ����0x0d,0x0a
		if(Index == 0)
		{
			if(OPS.pucRxbuff[i] != 0x0d)
				if(OPS.pucRxbuff[i+1] != 0x0a)
					continue;
		}
		
		OPS.pucRxbuff[Index] = OPS.pucRxbuff[i];

		//�Ѷ�ȡ28���ֽ�
		if(Index == opsOrder_LENGTH)
			break;
		
		Index++;
	}
	/*��ֵ*/
	for(i=0;i<opsRxbuff_LENGTH-4;i++)
		posture.data[i] = OPS.pucRxbuff[i+2];
	OPS.zangle=posture.ActVal[0];
	OPS.xangle=posture.ActVal[1];
	OPS.yangle=posture.ActVal[2];
	OPS.pos_x =posture.ActVal[3];
	OPS.pos_y =posture.ActVal[4];
	OPS.w_z   =posture.ActVal[5];
	
	//�建��
	for(i=0;i<opsRxbuff_LENGTH;i++)
	{
		OPS.pucRxbuff[i] = 0x00;
	}
}



