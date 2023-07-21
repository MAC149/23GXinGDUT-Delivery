#include "Scan.h"

const static uint8_t Scan_Trigger_buf[]={0x7E,0x00,0x08,0x01,0x00,0x02,0x01,0xAB,0xCD};
static uint8_t Scan_Res[SCAN_RES_BUF_LENGTH]={0};
static uint8_t count=0;
static uint8_t c_count=0;
static uint8_t d_count=0;
static uint8_t scan_buf[]={0};
static bool Scan_Rec_Flag=0;
static bool Scan_TO_Flag=0;
static bool Scan_Data_Flag=0;
uint8_t Scan_Data_Length=0;
//static uint8_t Scan_Data_Rev=0;

uint8_t* Scan_GetCode()
{
    Scan_Rec_Flag = 0;
    Scan_TO_Flag=0;
    Scan_Data_Flag=0;
    c_count=0;
    d_count=0;
    HAL_UART_Transmit(&DEBUG_UART,(uint8_t *)"SCAN START",10,1000);
    HAL_UART_Transmit(&SCANER_UARTX,Scan_Trigger_buf,9,1000);
    HAL_UART_Receive_IT(&SCANER_UARTX,&Scan.Scan_Char_Buf,1);
    while(1)
    {
        HAL_Delay(100);
        if(Scan_Rec_Flag == 1)
		{	
			count=0;
            Scan_Data_Length=d_count;
            //HAL_UART_Transmit(&huart1,Scan_Res,d_count,1000);
            return Scan_Res;
            break;
		}
		else if(count >= 50)		//每0.5秒重新发一次数据
		{
			count=0;
			Scan_TO_Flag=1;
            Scan_Data_Length=2;
            return (uint8_t *)"TO";
            break;
		}
		count++;
	}
}

/* void Scan_Rec_Process(uint8_t Scan_Char_Buf)
{
	scan_buf[c_count]=Scan_Char_Buf;	
	if(scan_buf[c_count++] == '\r')
	{
		for(uint8_t i=0;i<Scan_Data_Rev-1;i++)
			Scan.Scan_Res[i] = scan_buf[c_count-Scan_Data_Rev+i];
		Scan.Scan_Rec_Flag = 1;
		c_count=0;
	}
    if(!Scan.Scan_Rec_Flag)
    {
        HAL_UART_Receive_IT(&SCANER_UARTX,&Scan.Scan_Char_Buf,1);
    }
} */

 void Scan_Rec_Process(uint8_t Scan_Char_Buf)
{
    if(Scan_Char_Buf==0x31)
    {
        HAL_UART_Receive_IT(&SCANER_UARTX,&Scan.Scan_Char_Buf,1);
        return;
    }

	scan_buf[c_count]=Scan_Char_Buf;
    if(scan_buf[c_count]== 0x0D)
    {
        Scan_Rec_Flag=1;
    }
    else if(Scan_Data_Flag)
    {
        Scan_Res[d_count++] = scan_buf[c_count];
    }
    else if(scan_buf[c_count] == 0x41 && scan_buf[c_count-1] == 0x44)
	{
		Scan_Data_Flag=1;
	}
    if(!Scan_Rec_Flag)
    {
        HAL_UART_Receive_IT(&SCANER_UARTX,&Scan.Scan_Char_Buf,1);
    }
    c_count++; 
}

Scan_t Scan =
{
    0,
    Scan_Rec_Process
};