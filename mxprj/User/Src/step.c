#include "step.h"

#define MOTOR_LIFT_DELAYUS 80

Servo_t Servo_Pad;
Servo_t Servo_Paw;
Servo_t Servo_Rot;



void Step_Init()
{
    OLED_Init();
    Motortot_Init();
	  Servo_Set(&Servo_Pad,&SERVO_PAD_TIM,SERVO_PAD_CH);
    Servo_Set(&Servo_Paw,&SERVO_PAW_TIM,SERVO_PAW_CH);
    Servo_Set(&Servo_Rot,&SERVO_ROT_TIM,SERVO_ROT_CH);
    Servo_Init(&Servo_Pad);
    Servo_Init(&Servo_Paw);
    Servo_Init(&Servo_Rot);
    // Delay_Init();
    HAL_TIM_Base_Start_IT(&htim13);
    Motortot_SetEn_Off();
    OLED_ShowString(1,1,"INIT...",16);
    HAL_Delay(3000);
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_Clear();
	Motortot_SetEn_On();
  _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
	HAL_Delay(500);//----------------DELETE WHEN ON STAGE
}

uint8_t *QRCode;
uint8_t Act_Order1[3]={0};
uint8_t Act_Order2[3]={0};

void Code_Scan()
{
  do
	{
		QRCode=Scan_GetCode();
    //HAL_UART_Transmit(&DEBUG_UART,QRCode,(uint16_t)Scan_Data_Length,1000);
  }
  while(!strcmp(QRCode,"TO"));
  // printf("%s",QRCode);
  // QRCode="123+321";
	OLED_ShowString(1,1,QRCode,164);
	// for (uint8_t i = 0; i < 3; i++)
	// {
	// 	Act_Order1[i]=QRCode[i];
	// 	Act_Order2[i]=QRCode[i+4];
	// }
	
}

void PreAction()
{
  PAW_OPEN;
  ROT_GND;
  PAD_R;
  HAL_Delay(500);
  Motor_Lift_Reset(MOTOR_LIFT_DELAYUS);
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
}

void Pad_Put()
{
  PAW_CLOSE;
  Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  ROT_PAD;
  HAL_Delay(600);
  Motor_Lift_GoPos(MOTOR_LIFT_PAD,MOTOR_LIFT_DELAYUS);
  PAW_OPEN;
  HAL_Delay(600);
  Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  ROT_GND;
  HAL_Delay(600);
}

void Pad_Pick()
{
  PAW_OPEN;
  Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  ROT_PAD;
  HAL_Delay(600);
  Motor_Lift_GoPos(MOTOR_LIFT_PAD,MOTOR_LIFT_DELAYUS);
  PAW_CLOSE;
  HAL_Delay(600);
  Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  ROT_GND;
  HAL_Delay(600);
}

void Pick_Action()
{
  Motor_Lift_GoPos(MOTOR_LIFT_2XGND,MOTOR_LIFT_DELAYUS);
  PAW_OPEN;
  ROT_GND;
  HAL_Delay(500);
  Motor_Lift_GoPos(MOTOR_LIFT_UPGROUD,MOTOR_LIFT_DELAYUS);
  Motor_Lift_Reset(MOTOR_LIFT_DELAYUS);
  PAW_CLOSE;
  HAL_Delay(500);
  Motor_Lift_GoPos(MOTOR_LIFT_2XGND,MOTOR_LIFT_DELAYUS);
}

void Put_Action(uint8_t phase)
{
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
  PAW_CLOSE;
  ROT_GND;
  HAL_Delay(200);
  if(phase==1)
  {
    Motor_Lift_Reset(MOTOR_LIFT_DELAYUS);
  }
  else if(phase==2)
  {
    Motor_Lift_GoPos(MOTOR_LIFT_2XGND,MOTOR_LIFT_DELAYUS);
  }
  PAW_OPEN;
  HAL_Delay(500);
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
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

void Pad_SwitchInt(int target)
{
  switch(target)
  {
    case 0:Servo_SetDeg(&Servo_Pad,SERVO_PAD_RED);break;
    case 1:Servo_SetDeg(&Servo_Pad,SERVO_PAD_GREEN);break;
    case 2:Servo_SetDeg(&Servo_Pad,SERVO_PAD_BLUE);break;
    case 4:Servo_SetDeg(&Servo_Pad,SERVO_PAD_RED);break;
    case 5:Servo_SetDeg(&Servo_Pad,SERVO_PAD_GREEN);break;
    case 6:Servo_SetDeg(&Servo_Pad,SERVO_PAD_BLUE);break;
  }
}

void OG_Action(int Phase)
{
    PAW_OPEN;
   Motor_Lift_GoPos(MOTOR_LIFT_UPOG,MOTOR_LIFT_DELAYUS);
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      PAW_OPEN;
      HAL_Delay(250);
      Pad_SwitchInt(i);
      switch(QRCode[i])
      {
        case '1'://Pad_Switch(QRCode[i]);
        while(!OpenMVGN_Cor(&OpenMV1,1));		//识别红色
		    break;
        case '2'://Pad_Switch(QRCode[i]);
		    while(!OpenMVGN_Cor(&OpenMV1,2));//识别绿色
		    break;
        case '3'://Pad_Switch(QRCode[i]);
		    while(!OpenMVGN_Cor(&OpenMV1,3));//识别蓝色
		    break;
        default:break;
      }
      Motor_Lift_GoPos(MOTOR_LIFT_OG,MOTOR_LIFT_DELAYUS);
      PAW_CLOSE;
      HAL_Delay(250);
      Motor_Lift_GoPos(MOTOR_LIFT_UPOG,MOTOR_LIFT_DELAYUS);
      Pad_Put();
      Motor_Lift_GoPos(MOTOR_LIFT_UPOG,MOTOR_LIFT_DELAYUS);
    }
}

void RM_Action(int Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_SwitchInt(i);
      // Pad_Switch(QRCode[i]);
      HAL_Delay(600);
      Pad_Pick();
      Put_Action(1);
    }
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_SwitchInt(i);
      // Pad_Switch(QRCode[i]);
      Pick_Action();
      Pad_Put();
    }
}

void SM_Action(uint8_t Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_SwitchInt(i);
      // Pad_Switch(QRCode[i]);
      HAL_Delay(600);
      Pad_Pick();
      Put_Action(Phase);
    }
}

void Rout1op(uint8_t round)
{
    Motortot_Left(2000, 200);
    Motortot_Forward(9400, 200);
    // 扫码
    if (round == 1)
    {
      Code_Scan();
    }
    lobotRunActionGroup(0, 1000);
    // 去转盘
    Motortot_Forward(8600, 200);
    if (round == 1)
    {
      Motortot_Right(1000, 200);
    }
    else
    {
      Motortot_Right(800, 200);
    }
    // HAL_Delay(2000);
    // 识别任务
    OG_Action(round);
    // 舵机动作组
    // 路口
    Motortot_Left(1400, 200);
    if (round == 1)
    {
      Motortot_Forward(6200, 200);
    }
    else
    {
      Motortot_Forward(5700, 200);
    }
    Motortot_RotLeft(3900, 200);
    Motortot_Forward(9780, 200);
    // Motortot_Right(800,200);
    // HAL_Delay(2000);
    // 粗加工
    //  HAL_Delay(2000);
    // OpenMVGN_Adj(&OpenMV1);//矫正
    // OPENMV
    // 舵机动作组
    RM_Action(round);
    // 路口
    //  HAL_Delay(2000);
    // 半成品
    Motortot_Forward(9950, 200);
    Motortot_RotLeft(3900, 200);
    Motortot_Forward(9670, 200);
    SM_Action(round);

    // HAL_Delay(2000);
    // 矫正
    // OPENMV
    // 舵机动作组

    Motortot_Forward(13930, 200);
    Motortot_RotLeft(4000, 200);
    Motortot_Forward(22000, 200);
    if (round == 1)
    {
      Motortot_RotLeft(3900, 200);
    }

    // 回路口
    //  OPSIT_Start();
    // while(1);
    // 	HAL_Delay(2000);
    //   if(round==1)
    //   {
    // 	  HAL_Delay(2000);
    //   }
}

void Full_Step()
{
  // while(1);
	Step_Init();
	//去扫码区

	//---------------------------------r1
	Rout1op(1);
  while(1);
	//---------------------------------r2
	Rout1op(2);
  while(1);
	//结束
	HAL_Delay(2000);
	while(1);
}
