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
Found Circle - Center: (110, 77), Radius: 40 , Magnitude: 4080
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
#define OPENMVGN_XOFFSET 0
#define OPENMVGN_YOFFSET 0

uint8_t OpenMVGN_Xst=0;
uint8_t OpenMVGN_Yst=0;
bool OpenMVGN_ReceiveFlag=0;

void OpenMVGN_StUpd(OpenMV_tt *OpenMV)
{
    //if(!OpenMVGN_ReceiveFlag){return;}
    OpenMV->OpenMV_Receive(OpenMV);
    OpenMVGN_Data_Process(OpenMV->OpenMV_Rec);
    if(OpenMVGN_Data[1]>((OPENMV_RESX/2)+OPENMVGN_XOFFSET)+5)
    {
        OpenMVGN_Xst=2;
    }
    else if(OpenMVGN_Data[1]<((OPENMV_RESX/2)+OPENMVGN_YOFFSET)-5)
    {
        OpenMVGN_Xst=1;
    }
    else
    {
        OpenMVGN_Xst=3;
    }
    if(OpenMVGN_Data[2]>(OPENMV_RESY/2)+5)
    {
        OpenMVGN_Yst=1;
    }
    else if(OpenMVGN_Data[2]<(OPENMV_RESY/2)-5)
    {
        OpenMVGN_Yst=2;
    }
    else
    {
        OpenMVGN_Yst=3;
    }
}


void OpenMVGN_Adj(OpenMV_tt *OpenMV)
{
    OpenMV_Send(OpenMV,"PV",3);
    //OpenMVGN_ReceiveFlag=1;
    OpenMVGN_Xst=0;
    OpenMVGN_Yst=0;
    while((OpenMVGN_Yst!=3) || (OpenMVGN_Xst!=3))
    {
        OpenMVGN_StUpd(&OpenMV1);
        if(OpenMVGN_Xst==2)
        {
            Motortot_Backward(25,200);
        }
        else if(OpenMVGN_Xst==1)
        {
            
            Motortot_Forward(25,200);
        } 
        if(OpenMVGN_Yst==2)
        {
            Motortot_Right(25,200);

        }
        else if(OpenMVGN_Yst==1)
        {
            Motortot_Left(25,200);
        }
    }
    //OpenMVGN_ReceiveFlag=0;
    OpenMV_Send(OpenMV,"END",4);
}

bool OpenMVGN_Cor(OpenMV_tt *OpenMV,uint8_t Tar_cor)
{
    uint8_t temp;
    uint8_t temp1;
    switch(Tar_cor)
    {
        case 1:OpenMV_Send(OpenMV,"CRRED",6);break;
        case 2:OpenMV_Send(OpenMV,"CRGREEN",8);break;
        case 3:OpenMV_Send(OpenMV,"CRBLUE",7);break;
        default:break;
    }
    while(1)
    {
        OpenMVGN_Data_Process(OpenMV->OpenMV_Receive(OpenMV));
        temp=OpenMVGN_Data[0];
        HAL_Delay(500);
        OpenMVGN_Data_Process(OpenMV->OpenMV_Receive(OpenMV));
        temp1=OpenMVGN_Data[0];
        if(temp1==temp)
        {
            OpenMV_Send(OpenMV,"END",4);
            return 1;
        }
        HAL_Delay(200);
    }
    
}