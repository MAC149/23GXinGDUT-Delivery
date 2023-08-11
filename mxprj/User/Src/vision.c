#include "vision.h"
#include <stdlib.h>
#include "Motor.h"



void OpenMV_Send(OpenMV_tt* that,uint8_t* CMD,uint8_t len)
{
    HAL_UART_Transmit(that->OpenMV_huart,CMD,len,10);
}

void OpenMV_Receive_Start(OpenMV_tt* that)
{
    that->Buf_pointer=0;
    that->Data_pointer=0;
    that->Rec_Flag=1;
    that->Data_flag=0;
    that->Rec_temp=0;
    HAL_UART_Receive_IT(that->OpenMV_huart,&that->Rec_temp,1);
}

uint8_t* OpenMV_Receive(OpenMV_tt* that)
{
    that->Buf_pointer=0;
    that->Data_pointer=0;
    that->Rec_Flag=1;
    that->Data_flag=0;
    that->Rec_temp=0;
    HAL_UART_Receive_IT(that->OpenMV_huart,&that->Rec_temp,1);
    while(that->Rec_Flag);
    return that->OpenMV_Rec;
}

void OpenMV_Receive_ProcessACC(OpenMV_tt* that)
{
    that->Openmv_RxBuf[that->Buf_pointer]=that->Rec_temp;
    if(that->Openmv_RxBuf[that->Buf_pointer]=='A' && that->Openmv_RxBuf[that->Buf_pointer-1]=='D' &&that->Data_flag==0)
    {
        that->Data_flag=1;
    }
    else if(that->Openmv_RxBuf[that->Buf_pointer]=='\r')
    {
        that->OpenMV_Rec[that->Data_pointer]=that->Openmv_RxBuf[that->Buf_pointer];
        that->Rec_Flag=0;
        return;
    }
        else if(that->Data_flag)
    {
        that->OpenMV_Rec[that->Data_pointer++]=that->Openmv_RxBuf[that->Buf_pointer];
    }
    that->Buf_pointer++;
    HAL_UART_Receive_IT(that->OpenMV_huart,&that->Rec_temp,1);
}



void OpenMV_Receive_ProcessNCB(OpenMV_tt* that)
{
    if(that->Rec_temp=='A' && that->Data_flag==0)
    {
       that->Data_flag=1;
    }
    else if(that->Rec_temp=='\r')
    {
        that->Rec_Flag=0;
        for(int i=0;i<=that->Buf_pointer;i++)
        {
            that->OpenMV_Rec[i]=that->Openmv_RxBuf[i];
        }
        return;
    }
        else if(that->Data_flag)
    {
        that->Openmv_RxBuf[that->Buf_pointer++]=that->Rec_temp;
    }
    HAL_UART_Receive_IT(that->OpenMV_huart,&that->Rec_temp,1);
}

OpenMV_tt* _OpenMV_tt_Init(OpenMV_tt *that,UART_HandleTypeDef *MVhuart)
{
    that->OpenMV_huart=MVhuart;
    that->Rec_temp=0;
    that->Rec_Flag=0;
    that->Data_flag=0;
    that->Buf_pointer=0;
    that->Data_pointer=0;
    that->OpenMV_Receive_Process=OpenMV_Receive_ProcessACC;
    that->OpenMV_Receive_Start=OpenMV_Receive_Start;
    that->OpenMV_Receive=OpenMV_Receive;
    that->OpenMV_Send=OpenMV_Send;
    return that;
}


OpenMV_tt OpenMV1;


int OpenMVGN_Data[4]={0};
#define OPENMVGN_STDATA_BUF_LEN 8
/* Rec example
Blue Circle - Center: (265, 230), Radius: 54
*/
void OpenMVGN_Str2int(const char strch,const char endch,uint8_t *str,uint8_t* pointer,int *intdes)
{
    uint8_t i=0;
    char temp[OPENMVGN_STDATA_BUF_LEN]={0};
    while((*pointer)<OPENMV_REC_BUF_LEN && str[(*pointer)]!='\0' && str[(*pointer)++]!=strch);
    while((*pointer)<OPENMV_REC_BUF_LEN && str[(*pointer)]!='\0' && str[*pointer]!=endch)
    {
        if(str[*pointer]==' '){(*pointer)++;continue;}
        temp[i++]=str[(*pointer)++];
    }
    *intdes=atoi(temp);
}

void OpenMVGN_Data_Process(uint8_t *str)
{
    uint8_t i=0;
    switch (str[0])
    {
    case 'R':OpenMVGN_Data[0]=1;
        break;
    case 'G':OpenMVGN_Data[0]=2;
        break;
    case 'B':OpenMVGN_Data[0]=3;
        break;
    default:OpenMVGN_Data[0]=0;
        break;
    }
    OpenMVGN_Str2int('(',',',str,&i,&OpenMVGN_Data[1]);
    OpenMVGN_Str2int(',',')',str,&i,&OpenMVGN_Data[2]);
    OpenMVGN_Str2int(':','\n',str,&i,&OpenMVGN_Data[3]);
}


#define OPENMV_RESX 320
#define OPENMV_RESY 240

void OpenMVGN_Adj(OpenMV_tt *that)
{
    bool x_ok,y_ok=0;
    while((!x_ok) && (!y_ok))
    {
        that->OpenMV_Receive(that);
        OpenMVGN_Data_Process(that->OpenMV_Rec);
        if(OpenMVGN_Data[1]>(OPENMV_RESX/2)+3)
        {
            Motortot_Left(25,200);
        }
        else if(OpenMVGN_Data[1]<(OPENMV_RESX/2)-3)
        {
            Motortot_Right(25,200);
        }
        else
        {
            x_ok=1;
        }
        if(OpenMVGN_Data[2]>(OPENMV_RESY/2)+3)
        {
            Motortot_Backward(25,200);
        }
        else if(OpenMVGN_Data[2]<(OPENMV_RESY/2)-3)
        {
            Motortot_Forward(25,200);
        }
        else
        {
            y_ok=1;
        }
    }
}