#include "step.h"

#define MOTOR_LIFT_DELAYUS 70
 
Servo_t Servo_Pad;
Servo_t Servo_Paw;
Servo_t Servo_Rot;
static uint8_t GPhase=0;

const double Pos_Target[10][3]=
{
-190,530,0,                           //扫码
-85,1455,0,                        //转盘
-956,1920,90,                        //粗加工
-1705,1100,180,                     //半成品
-1580,1870,180,                      //左上路口
-130,1870,0,                        //右上路口
-1550,85,180,                         //左下路口
-120,85,0,                               //右下路口
-956,1870,90,                        //粗加工过渡
-1580,1100,180,                    //半成品过渡
};

const double Pos_Targetog[10][3]=
{
-190,530,0,                           //扫码
-95,1455,0,                        //转盘
-956,1910,90,                        //粗加工
-1695,1100,180,                     //半成品
-1580,1870,180,                      //左上路口
-130,1870,0,                        //右上路口
-1550,85,180,                         //左下路口
-120,85,0,                               //右下路口
-956,1870,90,                        //粗加工过渡
-1580,1100,180,                    //半成品过渡
};

#define POSX(i) Pos_Target[i][0]
#define POSY(i) Pos_Target[i][1]
#define POSYaw(i) Pos_Target[i][2]


void car_goA(uint8_t place)
{
  car_go(1,Pos_Target[place][0],Pos_Target[place][1],Pos_Target[place][2]);
}

void car_goYAW(uint8_t place,double yawtar)
{
  car_go(1,Pos_Target[place][0],Pos_Target[place][1],yawtar);
}



void VisionAdjPack()
{
  Motor_Lift_GoPos(MOTOR_LIFT_VSJD,MOTOR_LIFT_DELAYUS);
  OpenMVGN_AdjPacked(&OpenMV1);
}

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
    Delay_Init();
    // HAL_TIM_Base_Start_IT(&htim13);
    OLED_ShowString(1,1,"INIT...",16);
    OPS.OPS_Init();
    // imuDMAStart();
    Motortot_SetEn_Off();
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_Clear();
	Motortot_SetEn_On();
  __HAL_UART_ENABLE_IT(&SCANER_UARTX,UART_IT_IDLE);    
  _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
	HAL_Delay(500);//----------------DELETE WHEN ON STAGE
}

uint8_t *QRCode;

void Code_Scan()
{
  do
	{
		QRCode=Scan_GetCodeDMA();
    //HAL_UART_Transmit(&DEBUG_UART,QRCode,(uint16_t)Scan_Data_Length,1000);
  }
  while(!strcmp(QRCode,"TO"));
  // printf("%s",QRCode);
  // QRCode="123+321";
	OLED_ShowString(1,1,QRCode,164);
	// for (uint8_t i = 0; i < 3; i++)
	// {
	// 	Act_Order1[i]=Scan_ResRet(i);
	// 	Act_Order2[i]=QRCode[i+4];
	// }
	
}

void StartAction()
{
  PAW_CLOSE;
  Motor_LiftUp(1800,MOTOR_LIFT_DELAYUS);
  ROT_GND;
  HAL_Delay(600);
  Motor_Lift_Reset(MOTOR_LIFT_DELAYUS);
}

void EndAction()
{
  PAW_CLOSE;
  Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  Servo_SetDeg(&Servo_Rot,160);
  HAL_Delay(600);
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
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
  ROT_PAD;
  HAL_Delay(1000);
  Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  HAL_Delay(500);
  Motor_Lift_GoPos(MOTOR_LIFT_PAD,MOTOR_LIFT_DELAYUS);
  PAW_OPENX;
  HAL_Delay(500);
  //Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
  PAW_OPEN;
  ROT_GND;
  HAL_Delay(600);
}

void Pad_Pick()
{
  PAW_OPEN;
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
  ROT_PAD;
  HAL_Delay(600);
  PAW_OPENX;
  HAL_Delay(500);
  Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  HAL_Delay(500);
  Motor_Lift_GoPos(MOTOR_LIFT_PAD,MOTOR_LIFT_DELAYUS);
  PAW_CLOSE;
  HAL_Delay(600);
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
  ROT_GND;
  HAL_Delay(600);
}

void Pick_Action()
{
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
  PAW_OPEN;
  ROT_GND;
  HAL_Delay(200);
  Motor_Lift_GoPos(MOTOR_LIFT_UPGROUD,MOTOR_LIFT_DELAYUS);
  Motor_Lift_GoPos(MOTOR_LIFT_GND,MOTOR_LIFT_DELAYUS);
  PAW_CLOSE;
  HAL_Delay(800);
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
}

void Put_Action(int phase)
{
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
  PAW_CLOSE;
  ROT_GND;
  HAL_Delay(200);
  if(phase==1)
  {
    Motor_Lift_GoPos(MOTOR_LIFT_GND,MOTOR_LIFT_DELAYUS);
  }
  else if(phase==2)
  {
    Motor_Lift_GoPos(MOTOR_LIFT_2XGND,MOTOR_LIFT_DELAYUS);
  }
  HAL_Delay(500);
  PAW_OPEN;
  HAL_Delay(500);
  Motor_Lift_GoPos(MOTOR_LIFT_NRTOP,MOTOR_LIFT_DELAYUS);
}

void Pad_Switch(char target)
{
  switch(target)
  {
    case '1':PAD_R;break;
    case '2':PAD_G;break;
    case '3':PAD_B;break;
  }
}

void Pad_SwitchInt(int target)
{
  switch(target)
  {
    case 0:
    case 4:PAD_SR;break;
    case 1:
    case 5:PAD_SG;break;
    case 2:
    case 6:PAD_SB;break;
  }
}

void ActionPos_Go(char pos);
__inline void ActionPos_Go(char pos)
{
  switch(pos)
  {
    case '3':Motortot_Forward(MOTOR_POS_DISTANCE,200);break;
    case '2':break;
    case '1':Motortot_Backward(MOTOR_POS_DISTANCE,200);break;
  }
}

 void ActionPos_Return(char pos);
__inline void ActionPos_Return(char pos)
{
  switch(pos)
  {
    case '3':Motortot_Backward(MOTOR_POS_DISTANCE,200);break;
    case '2':break;
    case '1':Motortot_Forward(MOTOR_POS_DISTANCE,200);break;
  }
}

void OG_Action()
{
    PAW_OPEN;
    // printf("a,%s\r\n",QRCode);
   Motor_Lift_GoPos(MOTOR_LIFT_UPOG,MOTOR_LIFT_DELAYUS);
    for(int i=(GPhase-1)*4;i<((GPhase-1)*4)+3;i++)
    {
      PAW_OPEN;
      HAL_Delay(250);
      Pad_SwitchInt(i);
      switch(Scan_ResRet(i))
      {
        case '1':printf("r\r\n");//Pad_Switch(Scan_ResRet(i));
        while(!OpenMVGN_Cor(&OpenMV1,1));		//识别红色
		    break;
        case '2':printf("g\r\n");//Pad_Switch(Scan_ResRet(i));
		    while(!OpenMVGN_Cor(&OpenMV1,2));//识别绿色
		    break;
        case '3':printf("b\r\n");//Pad_Switch(Scan_ResRet(i));
		    while(!OpenMVGN_Cor(&OpenMV1,3));//识别蓝色
		    break;
        default:printf("err\r\n");break;
      }
      Motor_Lift_GoPos(MOTOR_LIFT_OG,MOTOR_LIFT_DELAYUS);
      PAW_CLOSE;
      HAL_Delay(600);
      Motor_Lift_GoPos(MOTOR_LIFT_UPOG,MOTOR_LIFT_DELAYUS);
      Pad_Put();
      Motor_Lift_GoPos(MOTOR_LIFT_UPOG,MOTOR_LIFT_DELAYUS);
    }
}

__inline void RM_Action()
{
  int temp=(GPhase - 1) * 4;
    for (temp=(GPhase - 1) * 4; temp < ((GPhase - 1) * 4) + 3; temp++)
    {
      Pad_SwitchInt(temp);
      // ActionPos_Go(Scan_ResRet(i));
      switch (SCANRESRET(temp))
      {
      case '3':
        Motortot_Forward(MOTOR_POS_DISTANCE, 200);
        break;
      case '2':
        break;
      case '1':
        Motortot_Backward(MOTOR_POS_DISTANCE, 200);
        break;
      }
      // Pad_Switch(Scan_ResRet(i));
      // HAL_Delay(600);
      PAW_OPEN;
      Motor_Lift_GoPos(MOTOR_LIFT_VSJD,MOTOR_LIFT_DELAYUS);
      OpenMVGN_AdjPacked(&OpenMV1);
      HAL_Delay(200);
      // OpenMVGN_AdjPacked(&OpenMV1);
      Pad_Pick();
      Put_Action(1);
      // ActionPos_Return(Scan_ResRet(i));
      switch (SCANRESRET(temp))
      {
      case '3':
        Motortot_Backward(MOTOR_POS_DISTANCE, 200);
        break;
      case '2':OPS.Update_X(POSX(2));OPS.Update_Y(POSY(2));
        break;
      case '1':
        Motortot_Forward(MOTOR_POS_DISTANCE, 200);
        break;
      }
    }
    Rotate_PIDOPS(POSYaw(2));
   for (temp=(GPhase - 1) * 4;temp < ((GPhase - 1) * 4) + 3; temp++)
    {
      // ActionPos_Go(Scan_ResRet(i));
      switch (SCANRESRET(temp))
      {
      case '3':
        Motortot_Forward(MOTOR_POS_DISTANCE, 200);
        break;
      case '2':
        break;
      case '1':
        Motortot_Backward(MOTOR_POS_DISTANCE, 200);
        break;
      }
      Pad_SwitchInt(temp);
      //HAL_Delay(800);
      // Pad_Switch(Scan_ResRet(i));
      // Motortot_RotToOPS(POSYaw(2),300);
      Pick_Action();
      Pad_Put();
      // ActionPos_Return(Scan_ResRet(i));
      switch (SCANRESRET(temp))
      {
      case '3':
        Motortot_Backward(MOTOR_POS_DISTANCE, 200);
        break;
      case '2':
        break;
      case '1':
        Motortot_Forward(MOTOR_POS_DISTANCE, 200);
        break;
      }
    }
}

__inline void SM_Action()
{
  int temp;
    for (temp =(GPhase - 1) * 4; temp < ((GPhase - 1) * 4) + 3; temp++)
    {
      // ActionPos_Go(SCANRESRET(i));
      switch (SCANRESRET(temp))
      {
      case '3':
        Motortot_Forward(MOTOR_POS_DISTANCE, 200);
        break;
      case '2':
        break;
      case '1':
        Motortot_Backward(MOTOR_POS_DISTANCE, 200);
        break;
      }
      Pad_SwitchInt(temp);
      // Pad_Switch(Scan_ResRet(i));
      //HAL_Delay(800);
      Motor_Lift_GoPos(MOTOR_LIFT_VSJD, MOTOR_LIFT_DELAYUS);
      OpenMVGN_AdjPacked(&OpenMV1);
      // Motortot_RotToOPS(POSYaw(3),300);
      // OpenMVGN_AdjPacked(&OpenMV1);
      Pad_Pick();
      Put_Action(GPhase);
      // ActionPos_Return(SCANRESRET(i));
      switch (SCANRESRET(temp))
      {
      case '3':
        Motortot_Backward(MOTOR_POS_DISTANCE, 200);
        break;
      case '2':OPS.Update_X(POSX(3));OPS.Update_Y(POSY(3));
        break;
      case '1':
        Motortot_Forward(MOTOR_POS_DISTANCE, 200);
        break;
      }
    }
}

void PosTest()
{
    PreAction();
    car_goA(0);
    Code_Scan();
    // 去转盘
    car_goA(1);
    HAL_Delay(3000);
    car_goA(5);
    HAL_Delay(3000);
    car_goA(8);
    HAL_Delay(3000);
    // 粗加工
    car_goA(2);
    HAL_Delay(3000);
    // 路口
    car_goA(4);
    HAL_Delay(3000);
    car_goA(9);
    HAL_Delay(3000);
    // 半成品
    car_goA(3);
    HAL_Delay(3000);
    car_goA(4);
    HAL_Delay(3000);
    car_goA(5);
    HAL_Delay(3000);
    //转盘
    car_goA(1);
    HAL_Delay(3000);
    car_goA(5);
    HAL_Delay(3000);
    car_goA(8);
    HAL_Delay(3000);
    // 粗加工
    car_goA(2);
    HAL_Delay(3000);
    // 路口
    car_goA(4);
    HAL_Delay(3000);
    car_goA(9);
    HAL_Delay(3000);
    car_goA(3);
    HAL_Delay(3000);
    car_goA(6);
    HAL_Delay(3000);
    car_goYAW(7, 180);
    HAL_Delay(700);
    car_go(1, 0, 0, 180);
    EndAction();
    while (1)
      ;
}

void Rout1op(uint8_t round)
{
    Motortot_Left(2200, 200);
    YawKeepStart(0,'W');
    Motortot_Forward(7500, 200);
    YawKeepStop();
    // 扫码
    if (round == 1)
    {
      Code_Scan();
    }
    PreAction();
    // 去转盘
    Motortot_Forward(10700, 200);
    if (round == 1)
    {
      Motortot_Right(1600, 200);
    }
    else
    {
      Motortot_Right(800, 200);
    }
    // HAL_Delay(2000);
    // 识别任务
    OG_Action();
    
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
    RM_Action();
    while(1);
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

void Rout1()
{
    // 扫码
    if (GPhase == 1)
    {
        
      car_goA(0);
      StartAction();
      PreAction();
      Code_Scan();
      HAL_UART_DMAStop(&SCANER_UARTX);
    }
    // 去转盘
    car_goA(1);
    // HAL_Delay(2000);
    // 识别任务
    OG_Action();
    // 舵机动作组
    // 路口
  car_goA(5);

    car_goA(8);
    
    // Motortot_Right(800,200);
    // HAL_Delay(2000);
    // 粗加工
      car_goA(2);
    //  HAL_Delay(2000);
    // OpenMVGN_Adj(&OpenMV1);//矫正
    // OPENMV
      // Motor_Lift_GoPos(MOTOR_LIFT_VSJD,MOTOR_LIFT_DELAYUS);
      // OpenMVGN_AdjPacked(&OpenMV1);
    // 舵机动作组
    RM_Action();
    // 路口
      car_goA(4);
    //  HAL_Delay(2000);
    car_goA(9);
    // 半成品
    car_goA(3);
    // if(GPhase==1)
    // {
    //   Motor_Lift_GoPos(MOTOR_LIFT_VSJD,MOTOR_LIFT_DELAYUS);
    //   OpenMVGN_AdjPacked(&OpenMV1);
    // }
    SM_Action();

    // HAL_Delay(2000);
    // 矫正
    // OPENMV
    // 舵机动作组

    
    if (GPhase == 1)
    {
      car_goA(4);
      car_goA(5);
      car_goA(1);
    }
  else
  {
  //    PAW_CLOSE;
  // Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  // Servo_SetDeg(&Servo_Rot,165);
    car_goA(6);
    car_goYAW(7,180);
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


__inline void Full_Step()
{
  // while(1);
	Step_Init();
	//去扫码区
//StartAction();
// PosTest();
GPhase=1;
	//---------------------------------r1
	// Rout1op(1);
  Rout1();
	//---------------------------------r2
  GPhase=2;
	Rout1();
  //car_go(1,0,0,180);
  Motortot_Left(6000,200);
  Motortot_Forward(3000,200);
  // EndAction();
  // PAW_CLOSE;
  // Motor_Lift_GoPos(MOTOR_LIFT_UPPAD,MOTOR_LIFT_DELAYUS);
  // Servo_SetDeg(&Servo_Rot,165);
	//结束
	while(1);
}
