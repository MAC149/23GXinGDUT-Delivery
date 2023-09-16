#include "step.h"

#define SERVO_PAD_TIM htim3
#define SERVO_PAD_CH TIM_CHANNEL_4
#define SERVO_PAW_TIM htim3
#define SERVO_PAW_CH TIM_CHANNEL_3

#define SERVO_PAW_CLOSE 75
#define SERVO_PAW_OPEN 130
#define SERVO_PAD_RED 0
#define SERVO_PAD_GREEN 90
#define SERVO_PAD_BLUE 180

Servo_t Servo_Pad;
Servo_t Servo_Paw;

#define PAW_OPEN Servo_SetDeg(&Servo_Paw,SERVO_PAW_OPEN)
#define PAW_CLOSE Servo_SetDeg(&Servo_Paw,SERVO_PAW_CLOSE)
#define PAD_R Servo_SetDeg(&Servo_Pad,SERVO_PAD_RED)
#define PAD_G Servo_SetDeg(&Servo_Pad,SERVO_PAD_GREEN)
#define PAD_B Servo_SetDeg(&Servo_Pad,SERVO_PAD_BLUE)


const double Pos_Target[8][3]=
{
-170,1030,0,                           //扫码
-130,1410,0,                        //转盘
-940,1936,90,                        //粗加工
-1750,1120,180,                     //半成品
-1750,1850,180,                      //左上路口
-100,1700,0,                        //右上路口
-1689,80,180,                         //左下路口
-120,0,0                               //右下路口
};


void Step_Init()
{
    OLED_Init();
    Motortot_Init();
	  Servo_Set(&Servo_Pad,&SERVO_PAD_TIM,SERVO_PAD_CH);
    Servo_Set(&Servo_Paw,&SERVO_PAW_TIM,SERVO_PAW_CH);
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

void Pad_Put()
{
  lobotRunActionGroup(0,1000);
  HAL_Delay(1000);
  lobotRunActionGroup(2,1000);
  HAL_Delay(1000);
  PAW_OPEN;
  HAL_Delay(500);
  lobotRunActionGroup(0,1000);
  HAL_Delay(1000);
}

void Pad_Pick()
{
  PAW_OPEN;
  lobotRunActionGroup(0,1000);
  HAL_Delay(1200);
  lobotRunActionGroup(2,1000);
  HAL_Delay(1200);
  PAW_CLOSE;
  HAL_Delay(500);
  lobotRunActionGroup(0,1000);
  HAL_Delay(1200);
}

void Pick_Action(uint8_t pos)
{
  lobotRunActionGroup(0,1000);
  HAL_Delay(1200);
  switch(pos)
  {
    case 1:lobotRunActionGroup(4,1000);break;
    case 2:lobotRunActionGroup(3,1000);break;
    case 3:lobotRunActionGroup(5,1000);break;
  }
  HAL_Delay(1200);
  PAW_CLOSE;
  HAL_Delay(500);
  lobotRunActionGroup(0,1000);
  HAL_Delay(1200);
}

void Put_Action(bool phase,uint8_t pos)
{
  lobotRunActionGroup(0,1000);
  HAL_Delay(1000);
  if(phase)
  {
    switch(pos)
    {
      case 1:lobotRunActionGroup(4,1000);break;
      case 2:lobotRunActionGroup(3,1000);break;
      case 3:lobotRunActionGroup(5,1000);break;
    }
  }
  else
  {
      switch(pos)
    {
      case 1:lobotRunActionGroup(7,1000);break;
      case 2:lobotRunActionGroup(6,1000);break;
      case 3:lobotRunActionGroup(8,1000);break;
    }
  }
  HAL_Delay(1000);
  PAW_CLOSE;
  HAL_Delay(1000);
  lobotRunActionGroup(0,1000);
}

void Pad_Switch(char target)
{
  switch(target)
  {
    case '1':Servo_SetDeg(&Servo_Pad,SERVO_PAD_RED);break;
    case '2':Servo_SetDeg(&Servo_Pad,SERVO_PAD_GREEN);break;
    case '3':Servo_SetDeg(&Servo_Pad,SERVO_PAD_BLUE);break;
  }
}

void OG_Action(int Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      switch(QRCode[i])
      {
        case 1:Pad_Switch(QRCode[i]);
        while(!OpenMVGN_Cor(&OpenMV1,1));		//识别红色
		break;
        case 2:Pad_Switch(QRCode[i]);
		 while(!OpenMVGN_Cor(&OpenMV1,2));//识别绿色
		break;
        case 3:Pad_Switch(QRCode[i]);
		 while(!OpenMVGN_Cor(&OpenMV1,3));//识别蓝色
		break;
        default:break;
      }
      lobotRunActionGroup(9,500);//抓
      PAW_CLOSE;
      HAL_Delay(500);
      lobotRunActionGroup(0,1000);
      HAL_Delay(1200);
      Pad_Put();
      PAW_CLOSE;
      lobotRunActionGroup(0,1000);
      HAL_Delay(1200);
      lobotRunActionGroup(10,1000);
    }
}

void RM_Action(int Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_Switch(QRCode[i]);
      Pad_Pick();
      Put_Action(0,QRCode[i]);
    }
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_Switch(QRCode[i]);
      Pick_Action(QRCode[i]);
      Pad_Put();
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
        Pad_Switch(QRCode[i]);
        Pad_Pick();
        Put_Action(0,QRCode[i]);
      }
    }
  }
  else if(Phase==2)
  {
    for(int i=4;i<7;i++)
    {
        Pad_Switch(QRCode[i]);
        Pad_Pick();
        Put_Action(1,QRCode[i]);
    }
  }
}





void car_goA(uint8_t place)
{
  car_go(1,Pos_Target[place][0],Pos_Target[place][1],Pos_Target[place][2]);
}

void Rout1(uint8_t round)
{
	//去转盘
	car_goA(1);
	HAL_Delay(2000);
	//识别任务

	//舵机动作组

	//路口
	car_goA(5);
	HAL_Delay(2000);
	//粗加工
	 car_goA(2);
	 HAL_Delay(2000);
	//OpenMVGN_Adj(&OpenMV1);//矫正
	//OPENMV
	//舵机动作组

	//路口
	car_goA(4);
	HAL_Delay(2000);
	//半成品
	car_goA(3);
	HAL_Delay(2000);
	//矫正
	//OPENMV
	//舵机动作组

	//回路口
	car_goA(6);
	HAL_Delay(2000);
  if(round==1)
  {
    car_goA(7);
	  HAL_Delay(2000);
  }
}


void Full_Step()
{
	Step_Init();



	OLED_ShowString(1,1,"OPSx:",16);
  OLED_ShowString(2,1,"OPSy:",16);
  OLED_ShowString(3,1,"OPSyaw:",16);
  HAL_TIM_Base_Start_IT(&htim13);
	//去扫码区
	car_goA(0);
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
