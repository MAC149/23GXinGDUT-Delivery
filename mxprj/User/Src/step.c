#include "step.h"

#define SERVO_PAD_TIM htim12
#define SERVO_PAD_CH TIM_CHANNEL_1
#define SERVO_PAW_TIM htim12
#define SERVO_PAW_CH TIM_CHANNEL_1


Servo_t Servo_Pad;


const double Pos_Target[8][2]=
{
-133,800,                           //扫码
-130,1400,                        //转盘
-960,1906,                        //粗加工
-1750,1120,                     //半成品
-1750,1850,                      //左上路口
-100,1700,                        //右上路口
-1689,80,                         //左下路口
-120,0                               //右下路口
};


void Step_Init()
{
    OLED_Init();
    Motortot_Init();
	Servo_Set(Servo_Pad,&SERVO_PAD_TIM,SERVO_PAD_CH);
    Delay_Init();
    Motortot_SetEn_Off();
    OLED_ShowString(1,1,"INIT...",16);
    OPS.OPS_Init();
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_Clear();
	Motortot_SetEn_On();
	HAL_Delay(2000);//----------------DELETE WHEN ON STAGE
}

uint8_t *QRCode;
uint8_t Act_Order1[3]={0};
uint8_t Act_Order2[3]={0};
void Code_Scan()
{
	do
	{
		QRCode=Scan_GetCode();
        HAL_UART_Transmit(&DEBUG_UART,QRCode,(uint16_t)Scan_Data_Length,1000);
	}
    while(!strcmp(QRCode,"TO"));
	OLED_ShowString(1,1,QRCode,164);
	for (uint8_t i = 0; i < 3; i++)
	{
		Act_Order1[i]=QRCode[i];
		Act_Order2[i]=QRCode[i+4];
	}
	
}

void Pad_Switch(char target)
{
  switch(target)
  {
    case '2':Servo_SetDeg(Servo_Pad,105);break;
    case '3':Servo_SetDeg(Servo_Pad,165);break;
    case '1':Servo_SetDeg(Servo_Pad,45);break;
  }
}


void OG_Action(int Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      switch(QRCode[i])
      {
        case 1:Pad_Switch(QRCode[i]);
		//识别红色
		//抓
		break;
        case 2:Pad_Switch(QRCode[i]);
		//识别绿色
		//抓
		break;
        case 3:Pad_Switch(QRCode[i]);
		//识别蓝色
		//抓
		break;
        default:break;
      }
    }
}

void RM_Action(int Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      switch(QRCode[i])
      {
        case '1'://放左
		break;
        case '2'://放中
		break;
        case '3'://放右
		break;
        default:break;
      }
    }
    for(int i=0;i<3;i++)
    {
      switch(QRCode[i])
      {
        case '1'://拿左
		break;
        case '2'://拿中
		break;
        case '3'://拿右
		break;
        default:break;
      }
    }
}

void SM_Action(int Phase)
{
  if(Phase==1)
  {
    for(int i=0;i<3;i++)
    {
      switch(QRCode[i])
      {
        case '1'://放左
		break;
        case '2'://放中
		break;
        case '3'://放右
		break;
        default:break;
      }
    }
  }
  else if(Phase==2)
  {
    for(int i=4;i<7;i++)
    {
      switch(QRCode[i])
      {
        case '1'://垒放左
		break;
        case '2'://垒放中
		break;
        case '3'://垒放右
		break;
        default:break;
      }
    }
  }
}


void car_goA(uint8_t place,double yawang)
{
  car_go(1,Pos_Target[place][0],Pos_Target[place][1],yawang);
}

void Rout1(uint8_t round)
{
	//去转盘
	car_go(1,Pos_Target[1][0],Pos_Target[1][1],0);
	HAL_Delay(2000);
	//识别任务

	//舵机动作组

	//路口
	car_go(1,Pos_Target[5][0],Pos_Target[5][1],0);
	HAL_Delay(2000);
	//粗加工
	 car_go(1,Pos_Target[2][0],Pos_Target[2][1],90);
	 HAL_Delay(2000);
	//矫正
	//OPENMV
	//舵机动作组

	//路口
	car_go(1,Pos_Target[4][0],Pos_Target[4][1],180);
	HAL_Delay(2000);
	//半成品
	car_go(1,Pos_Target[3][0],Pos_Target[3][1],180);
	HAL_Delay(2000);
	//矫正
	//OPENMV
	//舵机动作组

	//回路口
	car_go(1,Pos_Target[6][0],Pos_Target[6][1],180);
	HAL_Delay(2000);
	car_go(1,Pos_Target[7][0],Pos_Target[7][1],0);
	HAL_Delay(2000);
}


void Full_Step()
{
  while(1);
	Step_Init();



	OLED_ShowString(1,1,"OPSx:",16);
  OLED_ShowString(2,1,"OPSy:",16);
  OLED_ShowString(3,1,"OPSyaw:",16);
  HAL_TIM_Base_Start_IT(&htim13);
	//去扫码区
	car_go(1,Pos_Target[0][0],Pos_Target[0][1],0);
	HAL_Delay(2000);
	//扫码
	//Code_Scan();

	//---------------------------------r1
	Rout1(1);
	//---------------------------------r2
	Rout1(2);
	//结束
	HAL_Delay(2000);
	car_go(1,0,0,180);
	while(1);
}
