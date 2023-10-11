#include "step.h"



Servo_t Servo_Pad;
Servo_t Servo_Paw;




const double Pos_Target[8][3]=
{
-170,730,0,                           //扫码
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
    Servo_Init(&Servo_Pad);
    Servo_Init(&Servo_Paw);
    // Delay_Init();
    Motortot_SetEn_Off();
    OLED_ShowString(1,1,"INIT...",16);
    OPS.OPS_Init();
    // HAL_Delay(14500);
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_Clear();
        OLED_ShowString(1,1,"OPSx:",16);
    OLED_ShowString(2,1,"OPSy:",16);
    OLED_ShowString(3,1,"OPSyaw:",16);
    HAL_TIM_Base_Start_IT(&htim13);
	Motortot_SetEn_On();
  _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
  __HAL_UART_ENABLE_IT(&SCANER_UARTX,UART_IT_IDLE);    
	HAL_Delay(500);//----------------DELETE WHEN ON STAGE
}

uint8_t QRCode[32];
uint8_t Act_Order1[3]={0};
uint8_t Act_Order2[3]={0};
extern uint8_t Scan_Res[16];
extern bool Scan_TO_Flag;

void Code_Scan()
{
  HAL_UART_DMAStop(&huart1);
/*   do
	{
		Scan_GetCodeDMA();
    //HAL_UART_Transmit(&DEBUG_UART,QRCode,(uint16_t)Scan_Data_Length,1000);
  }
  while(!strcmp(Scan_Res,"TO")); */
  Scan_GetCodeDMA();
  // printf("%s",QRCode);
  // QRCode="123+321";
	printf("qcode=%s\r\n",SCANRES);
	//OLED_ShowString(1,1,SCANRES,164);
	// for (uint8_t i = 0; i < 3; i++)
	// {
	// 	Act_Order1[i]=QRCode[i];
	// 	Act_Order2[i]=QRCode[i+4];
	// }
	
}

void Pad_Put()
{
  lobotRunActionGroup(1,1000);
  HAL_Delay(1200);
  lobotRunActionGroup(2,500);
  HAL_Delay(800);
  PAW_OPEN;
  HAL_Delay(250);
  lobotRunActionGroup(1,500);
  HAL_Delay(600);
}

void Pad_Pick()
{
  PAW_OPEN;
  lobotRunActionGroup(1,1000);
  HAL_Delay(1200);
  lobotRunActionGroup(2,1000);
  HAL_Delay(1200);
  PAW_CLOSE;
  HAL_Delay(500);
  lobotRunActionGroup(1,1000);
  HAL_Delay(1200);
}

void Pick_Action(uint8_t pos)
{
  lobotRunActionGroup(0,1000);
  HAL_Delay(1200);
  switch(pos)
  {
    case '3':lobotRunActionGroup(4,1000);break;
    case '2':lobotRunActionGroup(3,1000);break;
    case '1':lobotRunActionGroup(5,1000);break;
  }
  HAL_Delay(1200);
  PAW_CLOSE;
  HAL_Delay(500);
  lobotRunActionGroup(0,1000);
  HAL_Delay(1200);
}

void Put_Action(uint8_t phase,uint8_t pos)
{
  lobotRunActionGroup(0,1000);
  HAL_Delay(1000);
  if(phase==1)
  {
    switch(pos)
    {
      case '3':lobotRunActionGroup(4,1000);break;
      case '2':lobotRunActionGroup(3,1000);break;
      case '1':lobotRunActionGroup(5,1000);break;
    }
  }
  else if(phase==2)
  {
      switch(pos)
    {
      case '3':lobotRunActionGroup(7,1000);break;
      case '2':lobotRunActionGroup(6,1000);break;
      case '1':lobotRunActionGroup(8,1000);break;
    }
  }
  HAL_Delay(1000);
  PAW_OPEN;
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
    PAW_OPEN;
   lobotRunActionGroup(10,1000);
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      PAW_OPEN;
      HAL_Delay(250);
      switch(scan_dmabuf[c_count+i])
      {
        case '1':Pad_Switch(Scan_Res[i]);
        while(!OpenMVGN_Cor(&OpenMV1,1));		//识别红色
		    break;
        case '2':Pad_Switch(Scan_Res[i]);
		    while(!OpenMVGN_Cor(&OpenMV1,2));//识别绿色
		    break;
        case '3':Pad_Switch(Scan_Res[i]);
		    while(!OpenMVGN_Cor(&OpenMV1,3));//识别蓝色
		    break;
        default:break;
      }
      lobotRunActionGroup(9,250);//抓
      HAL_Delay(250);
      PAW_CLOSE;
      HAL_Delay(250);
      lobotRunActionGroup(0,500);
      HAL_Delay(600);
      Pad_Put();
      lobotRunActionGroup(0,500);
      HAL_Delay(600);
      lobotRunActionGroup(10,500);
      HAL_Delay(600);
    }
}

void RM_Action(int Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_Switch(Scan_Res[i]);
      lobotRunActionGroup(0,500);
      HAL_Delay(600);
      Pad_Pick();
      Put_Action(1,Scan_Res[i]);
    }
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_Switch(Scan_Res[i]);
      Pick_Action(Scan_Res[i]);
      Pad_Put();
    }
}

void SM_Action(uint8_t Phase)
{
    for(int i=(Phase-1)*4;i<((Phase-1)*4)+3;i++)
    {
      Pad_Switch(Scan_Res[i]);
      lobotRunActionGroup(0,500);
      HAL_Delay(600);
      Pad_Pick();
      Put_Action(Phase,Scan_Res[i]);
    }
}

void OPSIT_Start()
{
  __HAL_UART_ENABLE_IT(&OPS_auart_handle,UART_IT_IDLE);
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
}

void OPSIT_Stop()
{
  __HAL_UART_DISABLE_IT(&OPS_auart_handle,UART_IT_IDLE);
  HAL_TIM_Base_Stop_IT(&htim6);
  HAL_TIM_Base_Stop_IT(&htim7);
  HAL_NVIC_DisableIRQ(DMA2_Stream2_IRQn);
}


void car_goA(uint8_t place)
{
  car_go(1,Pos_Target[place][0],Pos_Target[place][1],Pos_Target[place][2]);
}

void Rout1op(uint8_t round)
{
  Motortot_Left(2000, 200);
  Motortot_Forward(9400, 200);
  // X_fast_move(-250);
  // Y_fast_move(950);
  // OPSIT_Stop();
  // 扫码
  if (round == 1)
  {
      Code_Scan();
  }
  //OPS.OPS_Init();
  // OPSIT_Start();
  lobotRunActionGroup(0, 1000);
  // 去转盘
  //  car_goA(1);
  //  X_fast_move(180);
  //  Y_fast_move(800);
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
  // OPSIT_Stop();
  OG_Action(round);
  // OPSIT_Start();
  // 舵机动作组
  // 路口
  // car_goA(5);
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
  //  car_goA(2);
  //  HAL_Delay(2000);
  // OpenMVGN_Adj(&OpenMV1);//矫正
  // OPENMV
  // OPSIT_Stop();
  // 舵机动作组
  RM_Action(round);
  // OPSIT_Start();
  // 路口
  // car_goA(4);
  // HAL_Delay(2000);
  // 半成品
  // car_goA(3);
  Motortot_Forward(9950, 200);
  Motortot_RotLeft(3900, 200);
  Motortot_Forward(9670, 200);
  SM_Action(round);

  // HAL_Delay(2000);
  // 矫正
  // OPENMV
  // 舵机动作组
  // OPSIT_Stop();

  Motortot_Forward(13930, 200);
  Motortot_RotLeft(4000, 200);
  Motortot_Forward(22000, 200);
  if (round == 1)
  {
      Motortot_RotLeft(3900, 200);
  }

  // 回路口
  //  OPSIT_Start();
  //  car_goA(6);
  // while(1);
  // 	HAL_Delay(2000);
  //   if(round==1)
  //   {
  //     car_goA(7);
  // 	  HAL_Delay(2000);
  //   }
}

void Rout1(uint8_t round)
{
  // OPSIT_Stop();
  // 扫码
  if (round == 1)
  {
      Code_Scan();
  }
  // OPSIT_Start();
  lobotRunActionGroup(0, 1000);
  // 去转盘
  car_goA(1);
  // HAL_Delay(2000);
  // 识别任务
  // OPSIT_Stop();
  OG_Action(round);
  // OPSIT_Start();
  // 舵机动作组
  // 路口
  car_goA(5);
  // Motortot_Right(800,200);
  // HAL_Delay(2000);
  // 粗加工
  car_goA(2);
  //  HAL_Delay(2000);
  // OpenMVGN_Adj(&OpenMV1);//矫正
  // OPENMV
  // OPSIT_Stop();
  // 舵机动作组
  RM_Action(round);
  // OPSIT_Start();
  // 路口
  car_goA(4);
  // HAL_Delay(2000);
  // 半成品
  car_goA(3);
  SM_Action(round);

  // HAL_Delay(2000);
  // 矫正
  // OPENMV
  // 舵机动作组
  // OPSIT_Stop();

  // 回路口
  //  OPSIT_Start();
  car_goA(6);
  // while(1);
  // 	HAL_Delay(2000);
  if (round == 1)
  {
      car_goA(7);
      // HAL_Delay(2000);
  }
}

void Full_Step()
{
  // while(1);
	Step_Init();
	//去扫码区
	// car_goA(0);

	//---------------------------------r1
	Rout1op(1);
  // Rout1(1);
  
	//---------------------------------r2
	Rout1op(2);
  while(1);
	//结束
	HAL_Delay(2000);
	// car_go(1,0,0,180);
	while(1);
}
