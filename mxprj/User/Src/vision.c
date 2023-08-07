#include "Vision.h"
#include <stdlib.h>

static uint8_t Openmv_RxBuf[OPENMV_REC_BUF_LEN]={0};
static uint8_t Buf_pointer=0;
static uint8_t Data_pointer=0;
static uint8_t OpenMV_Rec_temp=0;
static bool Data_flag=0;
bool Rec_Flag=0;
uint8_t OpenMV_Rec[OPENMV_REC_BUF_LEN]={0};

int OpenMV_Data[4]={0};


void OpenMV_Init()
{
    OpenMV_Rec_temp=0;
    Rec_Flag=0;
    Buf_pointer=0;
    Data_pointer=0;
}

void OpenMV_SendCmd(uint8_t* CMD,uint8_t len)
{
    HAL_UART_Transmit(&OPENMV_UART,CMD,len,10);
}

void OpenMV_Receive_Start()
{
    Buf_pointer=0;
    Data_pointer=0;
    Rec_Flag=1;
    Data_flag=0;
    HAL_UART_Receive_IT(&OPENMV_UART,&OpenMV_Rec_temp,1);
}


void OpenMV_Receive_ProcessACC()
{
    Openmv_RxBuf[Buf_pointer]=OpenMV_Rec_temp;
    if(Openmv_RxBuf[Buf_pointer]=='A' && Openmv_RxBuf[Buf_pointer-1]=='D' &&Data_flag==0)
    {
        Data_flag=1;
    }
    else if(Openmv_RxBuf[Buf_pointer]=='\r')
    {
        OpenMV_Rec[Data_pointer]=Openmv_RxBuf[Buf_pointer];
        Rec_Flag=0;
        return;
    }
        else if(Data_flag)
    {
        OpenMV_Rec[Data_pointer++]=Openmv_RxBuf[Buf_pointer];
    }
    Buf_pointer++;
    HAL_UART_Receive_IT(&OPENMV_UART,&OpenMV_Rec_temp,1);
}


void OpenMV_Receive_Process()
{
    if(OpenMV_Rec_temp=='A' && Data_flag==0)
    {
        Data_flag=1;
    }
    else if(OpenMV_Rec_temp=='\r')
    {
        Rec_Flag=0;
        for(int i=0;i<=Buf_pointer;i++)
        {
            OpenMV_Rec[i]=Openmv_RxBuf[i];
        }
        return;
    }
        else if(Data_flag)
    {
        Openmv_RxBuf[Buf_pointer++]=OpenMV_Rec_temp;
    }
    HAL_UART_Receive_IT(&OPENMV_UART,&OpenMV_Rec_temp,1);
}

#define OPENMV_STDATA_BUF_LEN 8
void OpenMV_Data_Process()
{
    char temp[OPENMV_STDATA_BUF_LEN];
    uint8_t i,j=0;
    switch (OpenMV_Rec[0])
    {
    case 'R':OpenMV_Data[0]=1;
        break;
    case 'G':OpenMV_Data[0]=2;
        break;
    case 'B':OpenMV_Data[0]=3;
        break;
    default:OpenMV_Data[0]=0;
        break;
    }
    for(i=0;i<OPENMV_REC_BUF_LEN;i++)
    {
        if(OpenMV_Rec[i]=='(')
        {
            i++;
            while(OpenMV_Rec[i]!= ',')
            {
                temp[j]=OpenMV_Rec[i];
                i++;j++;
            }
            
            OpenMV_Data[1]=atoi(temp);
            j=0;
            i+=2;
            while(OpenMV_Rec[i]!= ')')
            {
                temp[j]=OpenMV_Rec[i];
                i++;j++;
            }
            OpenMV_Data[2]=atoi(temp);
            while(OpenMV_Rec[i]!=':'){i++;}
            j=0;i++;
            while(OpenMV_Rec[i]!= '\n')
            {
                temp[j]=OpenMV_Rec[i];
                i++;j++;
            }
            OpenMV_Data[3]=atoi(temp);
            break;
        } 
    }
}
