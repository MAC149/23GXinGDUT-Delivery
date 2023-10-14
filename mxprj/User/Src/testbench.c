#include "testbench.h"
#define MOTOR_DELAYUS 300



extern const double Pos_Target[10][2];
extern Servo_t Servo_Pad;
extern Servo_t Servo_Paw;
extern Servo_t Servo_Rot;

void Motortot_Test()
{
    HAL_Delay(2500);
    Motortot_Forward(6400,MOTOR_DELAYUS);
    HAL_Delay(2500);
    Motortot_Backward(6400,MOTOR_DELAYUS);
    HAL_Delay(2500);
    Motortot_RotLeft(8000,MOTOR_DELAYUS);
    HAL_Delay(2500);
    Motortot_RotRight(8000,MOTOR_DELAYUS);
    HAL_Delay(2500);
    Motortot_Left(6400,MOTOR_DELAYUS);
    HAL_Delay(2500);
    Motortot_Right(6400,MOTOR_DELAYUS);
    HAL_Delay(2500);
}

void Scan_Test()
{
    uint8_t *temp;
    while(1)
    {
        temp=Scan_GetCode();
        HAL_UART_Transmit(&DEBUG_UART,temp,(uint16_t)Scan_Data_Length,1000);
        HAL_Delay(5000);
    }
}

void OLED_Test()
{
    OLED_Init();
    uint16_t temp=0;
    //OLED_ShowChar(1,1,'A',164);
    for(;;temp++)
    {
    HAL_UART_Transmit(&DEBUG_UART,(uint8_t *)"OLED",4,1000);
    OLED_ShowNum(1,1,temp,3,16);
    HAL_Delay(1000);
    //     OLED_Clear();
    }
}

void Scan_OLED()
{
    uint8_t *temp;
    OLED_Init();
    OLED_ShowString(1,1,"nihao",164);
    while(1)
    {
        temp=Scan_GetCode();
        HAL_UART_Transmit(&DEBUG_UART,temp,(uint16_t)Scan_Data_Length,1000);
        OLED_ShowString(1,1,temp,164);
        HAL_Delay(5000);
    }
}

//void OPS_Rec_Test()
//{
//    OLED_Init();
//        OLED_ShowString(1,1,"INIT...",16);
//    OPS.OPS_Init();
//    OLED_Clear();
//    OLED_ShowString(1,1,"PRESS SW1",16);
//    while(!Key_Scan(&KEY1));
//    OLED_ShowString(1,1,"OPSx:",16);
//    OLED_ShowString(2,1,"OPSy:",16);
//    OLED_ShowString(3,1,"OPSyaw:",16);
//    while(1)
//    {
//        OLED_ShowFNum(1,6,OPS.pos_x,7,16);
//        OLED_ShowFNum(2,6,OPS.pos_y,7,16);
//        OLED_ShowFNum(3,8,OPS.zangle,7,16);
//        HAL_Delay(400);
//    }
//}


Servo_t Servo1;
Servo_t Servo2;
Servo_t Servo3;

void Servo_Test()
{
    // HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
    // while(1)
    // {
    //    __HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,150);
    //     HAL_Delay(3000);
    //     __HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,50);
    //     HAL_Delay(3000);
    //     __HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,250);
    //     HAL_Delay(3000);
    //     __HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,200);
    //     HAL_Delay(4000);
    // }
    Servo_Set(&Servo1,&htim3,TIM_CHANNEL_3);
    Servo_Set(&Servo2,&htim3,TIM_CHANNEL_4);
    Servo_Init(&Servo1);
    Servo_Init(&Servo2);
    while(1)
    {
        Servo_SetDeg(&Servo2,90);
        Servo_SetDeg(&Servo1,90);
        // HAL_Delay(2000);
        // Servo_SetDeg(&Servo2,4);
        // HAL_Delay(2000);
        // Servo_SetDeg(&Servo2,180);
        // HAL_Delay(2000);
        // Servo_SetDeg(&Servo2,135);
        // HAL_Delay(2000);
    }
}

void Servo_Adj()
{
    HAL_Delay(1300);
    Servo_Set(&Servo1,&htim4,TIM_CHANNEL_2);//PD13PAW
    Servo_Set(&Servo2,&htim4,TIM_CHANNEL_3);//PD14ROT
    Servo_Set(&Servo3,&htim4,TIM_CHANNEL_4);//PD15PAD
    Servo_Init(&Servo1);
    Servo_Init(&Servo2);
    Servo_Init(&Servo3);
    Servo_SetDeg(&Servo1,90);
    Servo_SetDeg(&Servo2,25);                                       
    // Servo_SetDeg270(&Servo3,20);
    while(1);
}

void Servo_AdjFree()
{
    HAL_Delay(1300);
    Servo_Set(&Servo1,&htim4,TIM_CHANNEL_2);//PD13PAW
    Servo_Set(&Servo2,&htim4,TIM_CHANNEL_3);//PD14ROT
    Servo_Set(&Servo3,&htim4,TIM_CHANNEL_4);//PD15PAD
    Servo_Init(&Servo1);
    Servo_Init(&Servo2);
    Servo_Init(&Servo3);
    Servo_SetDeg(&Servo2,160);
    HAL_Delay(600);
    Motor_Lift_Reset(100);
    Motor_Lift_GoPos(5000,100);
    Servo_SetDeg(&Servo1,102);
    Servo_SetDeg(&Servo2,160);
    Servo_SetDeg270(&Servo3,27);
    Servo_SetDeg(&Servo2,25);
    while(1);
}

void MotorGoDis_Test()
{
    HAL_Delay(1500);
    Motortot_Forward(1940,200);
    while(1);
}


void Motor_Lift_Adj()
{
    HAL_Delay(1300);
    Servo_Set(&Servo1,&htim4,TIM_CHANNEL_2);//PD13PAW
    Servo_Set(&Servo2,&htim4,TIM_CHANNEL_3);//PD14ROT
    Servo_Init(&Servo1);
    Servo_Init(&Servo2);
    Servo_SetDeg(&Servo1,130);
    Servo_SetDeg(&Servo2,160);
    HAL_Delay(600);
    Motor_Lift_Reset(100);
    Motor_Lift_GoPos(2770,100);
    // Motor_Lift_GoPos(3600,100);
    // Motor_Lift_Reset(100);
    // Servo_SetDeg(&Servo2,25);
    // HAL_Delay(600);
    // Motor_LiftDown(550,100);
    // Servo_SetDeg(&Servo1,95);
    while(1);
}

void MotorLT_Test()
{
    Motor_LiftEn_On();
    while(1)
    {
        Motor_LiftUp(3000,200);
        HAL_Delay(2000);
        Motor_LiftDown(3000,200);
        HAL_Delay(2000);
    }
}

uint8_t * OPSx=0;
uint8_t * OPSy=0;

void FloatToUint8(uint8_t * char_array,float_t* data,uint16_t size)
{
    uint16_t i;
    for(i=0;i<size;i++)  
    {
        char_array[i] = round(data[i]) ;
    }
}

void RotPID_Test()
{
    Rotate_PID(90);
	HAL_Delay(1500);
	Rotate_PID(350);
	HAL_Delay(1500);
	Rotate_PID(360);
	HAL_Delay(1500);
	Rotate_PID(10);
	HAL_Delay(1500);
	Rotate_PID(350);
	HAL_Delay(1500);
    Rotate_PID(0);
	HAL_Delay(1500);
}

void RotLog_Test()
{
    Motortot_RotTo(90.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(350.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(360.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(10.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(350.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(0.0,MOTOR_DELAYUS);
    HAL_Delay(3000);
}

void PC_Uart_Test()
{
    // for(;;)
    // {
    //     HAL_Delay(1500);
    //     HAL_UART_Transmit(&DEBUG_UART,(uint8_t*)"aaa\n",4,1000);
    //     //OLED_ShowFNum(1,1,F_a,10,16);
    // }
    while(1)
    {
        printf("HelloWorld!\r\n");
        HAL_Delay(1000);
    }
}


extern int OpenMVGN_Data[4];
void Vision_Test()
{
    // OpenMV_Init();
    _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
    uint8_t* temp;
    // while(1)
    // {
    //     printf("inside\r\n");
    //     HAL_Delay(1500);
    //     printf("inside\r\n");
    //     temp=OpenMV1.OpenMV_Receive(&OpenMV1);
    //     printf("%s\r\n",temp);
    //     OpenMVGN_Data_Process(OpenMV1.OpenMV_Rec);
    //     printf("%d  %d  %d  %d\r\n",OpenMVGN_Data[0],OpenMVGN_Data[1],OpenMVGN_Data[2],OpenMVGN_Data[3]);
    // }
    while(1)
    {
        HAL_Delay(1500);
        printf("bbb");
        //OpenMV1.OpenMV_Send(&OpenMV1,(uint8_t*)"bbb",3);
        if(OpenMVGN_Cor(&OpenMV1,1))
        {
            printf("RED\r\n");
        }
    }
}

void Vision_Adj()
{
    //Servo_Set(&Servo1,&htim4,TIM_CHANNEL_2);//PD13PAW
    Servo_Set(&Servo2,&htim4,TIM_CHANNEL_3);//PD14ROT
    //Servo_Init(&Servo1);
    Servo_Init(&Servo2);
    //Servo_SetDeg(&Servo1,130);
    Servo_SetDeg(&Servo2,160);
    // OpenMV_Init();
    _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
    // lobotRunActionGroup(3,1000);
    Motor_Lift_Reset(80);
    Motor_Lift_GoPos(MOTOR_LIFT_VSJD,80);
    uint8_t* temp;
    // while(1)
    // {
    //     HAL_Delay(1500);
    //     printf("bbb");
    //     //OpenMV1.OpenMV_Send(&OpenMV1,(uint8_t*)"bbb",3);
        
    // }
    // OpenMVGN_Adj(&OpenMV1);
    OpenMVGN_AdjPacked(&OpenMV1);
    printf("out\r\n");
    HAL_Delay(500);
    Motor_Lift_Reset(100);
    //while(1);
}

void ServoCon_Test()
{
    LobotServo _servos1[4]={{6,0},{7,0},{8,0},{9,0}};
    HAL_Delay(1000);
    lobotServo_init();
    _servos1[0].Position = 1000;
	_servos1[1].Position = 930;
	_servos1[2].Position = 2000;
	_servos1[3].Position = 1930;
    lobotServos_moveByArray(_servos1,4,1000);
    // lobotServos_runActionGroup(1,1);
    //lobotServos_runActionGroup(2,1);
    while (1);
}

void ServoAction_Test()
{
    HAL_Delay(1300);
    Servo_Set(&Servo1,&htim4,TIM_CHANNEL_2);//PD13PAW
    Servo_Set(&Servo2,&htim4,TIM_CHANNEL_3);//PD14ROT
    Servo_Set(&Servo3,&htim4,TIM_CHANNEL_4);//PD15PAD
    Servo_Init(&Servo1);
    Servo_Init(&Servo2);
    Servo_Init(&Servo3);
    //
    Servo_SetDeg(&Servo1,130);
    Servo_SetDeg(&Servo2,158);
    Servo_SetDeg(&Servo3,90);
    HAL_Delay(600);
    Motor_Lift_Reset(100);
    //
    Motor_Lift_GoPos(5000,100);
    Servo_SetDeg(&Servo2,25);
    HAL_Delay(600);
    Motor_Lift_GoPos(4450,100);
    Servo_SetDeg(&Servo1,95);
    HAL_Delay(600);
    Motor_Lift_GoPos(5000,100);
    Servo_SetDeg(&Servo2,158);
    HAL_Delay(600);
    Motor_Lift_Reset(100);
    Servo_SetDeg(&Servo1,130);
    /* Servo_SetDeg(&Servo1,95);
    HAL_Delay(600);
    Motor_LiftUp(5000,100);
    Servo_SetDeg(&Servo2,25);
    HAL_Delay(600);
    Motor_LiftDown(5000-4450,100);
    Servo_SetDeg(&Servo1,130);
    HAL_Delay(600);
    Motor_LiftUp(5000-4450,100);
    Servo_SetDeg(&Servo2,158);
    HAL_Delay(300);
    Motor_Lift_Reset(100); */
    while(1);
}

void Motor_LiftRes_Test()
{
    while (1)
    {
        Motor_Lift_Reset(200);
        HAL_Delay(2000);
        Motor_LiftUp(3000, 200);
        HAL_Delay(2000);
    }
}

extern Servo_t Servo_Pad;
extern Servo_t Servo_Paw;
extern Servo_t Servo_Rot;
extern uint8_t *QRCode;

void ActionTest()
{
    // uint8_t *temp;
    _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
    HAL_Delay(2000);
    OLED_Init();
    OLED_ShowString(1,1,"nihao",164);
    __HAL_UART_ENABLE_IT(&SCANER_UARTX,UART_IT_IDLE);   
	Servo_Set(&Servo_Pad,&SERVO_PAD_TIM,SERVO_PAD_CH);
    Servo_Set(&Servo_Paw,&SERVO_PAW_TIM,SERVO_PAW_CH);
    Servo_Set(&Servo_Rot,&SERVO_ROT_TIM,SERVO_ROT_CH);
    Servo_Init(&Servo_Pad);
    Servo_Init(&Servo_Paw);
    Servo_Init(&Servo_Rot);
    PreAction();
    // lobotRunActionGroup(0,1000);
    HAL_Delay(1200);
    do
	{
		QRCode=Scan_GetCodeDMA();
        HAL_UART_Transmit(&DEBUG_UART,QRCode,(uint16_t)Scan_Data_Length,1000);
	}
    while(!strcmp(QRCode,"TO"));
	OLED_ShowString(1,1,QRCode,164);
         Motor_Lift_GoPos(MOTOR_LIFT_VSJD,80);
      OpenMVGN_AdjPacked(&OpenMV1);
    RM_Action(1);
    while(1);
}

void fullInit()
{
    OLED_Init();
    OLED_ShowString(1,1,"INIT...",16);
    OPS.OPS_Init();
    imuDMAStart();
    Delay_Init();
    __HAL_UART_ENABLE_IT(&SCANER_UARTX,UART_IT_IDLE);    
  _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
  OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
}


extern bool IMU_Rec_Flag;
extern IMUData_Packet_t IMUData_Packet;
extern AHRSData_Packet_t AHRSData_Packet;
void Imu_Test()
{
    double actRoll,actPitch,actHeading;
    while(1)
    {
        printf("AHRS: The Heading =  %f\r\n",IMU_yawExclusive());
        // HAL_Delay(2000);
    }
    
}

void YawKeep_Test()
{
    while (1)
    {
        YawKeepStart(0,'W');
        Motortot_Forward(6400, 200);
        HAL_Delay(1500);
        YawKeepStart(0,'S');
        Motortot_Backward(6400, 200);
        HAL_Delay(1500);
        YawKeepStop();
    }
}

void OPS_Rec_Test()
{
    OLED_Init();
    OLED_ShowString(1,1,"INIT...",16);
    OPS.OPS_Init();
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_ShowString(1,1,"OPSx:",16);
    OLED_ShowString(2,1,"OPSy:",16);
    OLED_ShowString(3,1,"OPSyaw:",16);
    while(1)
    {
        OLED_ShowFNum(1,6,OPS.pos_x,7,16);
        OLED_ShowFNum(2,6,OPS.pos_y,7,16);
        OLED_ShowFNum(3,8,OPS.zangle,7,16);
        HAL_Delay(400);
    }
}

void Test_Mod()
{
    // Motor_LiftRes_Test();
    //Servo_Test();
    // HAL_Delay(2000);
    // fullInit();
    // ActionTest();
    //Scan_OLED();
    //ServoCon_Test();
    // HAL_Delay(2000);
    //lobotRunActionGroup(10,1000);
    //while(1);
    // ServoAction_Test();
    // Vision_Test();
    // Vision_Adj();
    // Motortot_Test();
    //OLED_Test();
    //PC_Uart_Test();
    // Servo_Adj();
    Motor_Lift_Adj();
    // OPS_Rec_Test();
    // Servo_AdjFree();
    // MotorLT_Test();
    // Servo_Test();
    HAL_Delay(1500);
    printf("nihao\r\n");
    HAL_UART_Transmit(&huart3,(uint8_t *)"init",4,1000);
    // Imu_Test();
    // Servo_Adj();
    OLED_Init();
    Motortot_Init();
    Motortot_SetEn_On();
    // Vision_Adj();
    // MotorGoDis_Test();
    Delay_Init();
    Motortot_SetEn_Off();
    OLED_ShowString(1,1,"INIT...",16);
    HAL_Delay(3500);
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_Clear();
    OLED_ShowString(4,1,"yaw:",16);
    HAL_TIM_Base_Start_IT(&htim13);
    Motortot_SetEn_On();
    imuDMAStart();
    //OPS_Rec_Test();
    // YawKeep_Test();
    // RotPID_Test();
    // RotLog_Test();
    // Scan_OLED();
    // _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
    // while(1)
    // {
    //     OpenMVGN_Adj(&OpenMV1);
    // }
    while(1)
    {
        HAL_Delay(2000);
        // Vision_Test();
        //Motortot_Test();
    // Motortot_Test();
    }
    //Scan_Test();
}

