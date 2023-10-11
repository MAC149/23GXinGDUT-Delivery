#include "testbench.h"
#define MOTOR_DELAYUS 200



extern const double Pos_Target[8][2];

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

extern uint8_t Scan_Res[SCAN_RES_BUF_LENGTH];
void Scan_Test()
{
    uint8_t *temp;
    while(1)
    {
//        temp=Scan_GetCode();
        HAL_UART_Transmit(&DEBUG_UART,Scan_Res,(uint16_t)Scan_Data_Length,1000);
        HAL_Delay(5000);
    }
}

void Scan_TestDMA()
{
    uint8_t *temp;
    while(1)
    {
//        temp=Scan_GetCode();
        	__HAL_UART_ENABLE_IT(&SCANER_UARTX,UART_IT_IDLE);    
        Scan_GetCodeDMA();
        // HAL_UART_Transmit(&DEBUG_UART,temp,(uint16_t)Scan_Data_Length,1000);
        printf("res:%s\r\n",Scan_Res);
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
//        temp=Scan_GetCode();
        HAL_UART_Transmit(&DEBUG_UART,temp,(uint16_t)Scan_Data_Length,1000);
        OLED_ShowString(1,1,temp,164);
        HAL_Delay(5000);
    }
}

Servo_t Servo1;
Servo_t Servo2;

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
    Servo_Set(&Servo1,&htim3,TIM_CHANNEL_3);
    Servo_Set(&Servo2,&htim3,TIM_CHANNEL_4);
    Servo_Init(&Servo1);
    Servo_Init(&Servo2);
    Servo_SetDeg(&Servo2,100);
    while(1);
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

void RotPID_Test()
{
    Rotate_PID(90);
	HAL_Delay(1500);
	Rotate_PID(-170);
	HAL_Delay(1500);
	Rotate_PID(180);
	HAL_Delay(1500);
	Rotate_PID(10);
	HAL_Delay(1500);
	Rotate_PID(-10);
	HAL_Delay(1500);
    Rotate_PID(0);
	HAL_Delay(1500);
}

void RotLog_Test()
{
    Motortot_RotTo(90.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(-170.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(180.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(10.0,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_RotTo(-10.0,MOTOR_DELAYUS);
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
    while(1)
    {
        printf("inside\r\n");
        HAL_Delay(1500);
        printf("inside\r\n");
        temp=OpenMV1.OpenMV_Receive(&OpenMV1);
        printf("%s\r\n",temp);
        OpenMVGN_Data_Process(OpenMV1.OpenMV_Rec);
        printf("%d  %d  %d  %d\r\n",OpenMVGN_Data[0],OpenMVGN_Data[1],OpenMVGN_Data[2],OpenMVGN_Data[3]);
    }
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
    // OpenMV_Init();
    _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
    lobotRunActionGroup(3,1000);
    uint8_t* temp;
    // while(1)
    // {
    //     HAL_Delay(1500);
    //     printf("bbb");
    //     //OpenMV1.OpenMV_Send(&OpenMV1,(uint8_t*)"bbb",3);
        
    // }
    OpenMVGN_Adj(&OpenMV1);
    while(1);
}

void PickSpot(uint8_t place)
{
    car_go(1,Pos_Target[place][0],Pos_Target[place][1],Pos_Target[place][2]);
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
    HAL_Delay(2000);
    lobotServo_init();
    Servo_Set(&Servo1,&htim3,TIM_CHANNEL_3);
    Servo_Init(&Servo1);
    Servo_SetDeg(&Servo1,130);
    lobotServos_runActionGroup(1,1);
    HAL_Delay(1000);
    lobotServos_runActionGroup(2,1);
    HAL_Delay(1000);
    Servo_SetDeg(&Servo1,80);
    HAL_Delay(1000);
    lobotServos_runActionGroup(1,1);
    HAL_Delay(1000);
    lobotServos_runActionGroup(0,1);
    HAL_Delay(1000);
    lobotServos_runActionGroup(3,1);
    HAL_Delay(1000);
    Servo_SetDeg(&Servo1,130);
    HAL_Delay(1000);
    lobotServos_runActionGroup(0,1);
    HAL_Delay(1000);
    while(1);
}

void ServoAction_Test1()
{
    HAL_Delay(1200);
    lobotServo_init();
    Servo_Set(&Servo1,&htim3,TIM_CHANNEL_3);
    Servo_Init(&Servo1);
    Servo_SetDeg(&Servo1,130);
    lobotRunActionGroup(1,1000);
    HAL_Delay(1200);
    lobotRunActionGroup(2,1000);
    HAL_Delay(1200);
    Servo_SetDeg(&Servo1,80);
    HAL_Delay(1200);
    lobotRunActionGroup(1,1000);
    HAL_Delay(1200);
    lobotRunActionGroup(0,1000);
    HAL_Delay(1200);
    lobotRunActionGroup(6,1000);
    HAL_Delay(1200);
    Servo_SetDeg(&Servo1,130);
    HAL_Delay(1200);
    lobotRunActionGroup(0,1000);
    HAL_Delay(1200);
    while(1);
}


extern Servo_t Servo_Pad;
extern Servo_t Servo_Paw;
extern uint8_t *QRCode;

void ActionTest()
{
    // uint8_t *temp;
    _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
    HAL_Delay(2000);
    OLED_Init();
    OLED_ShowString(1,1,"nihao",164);
    Servo_Set(&Servo_Pad,&SERVO_PAD_TIM,SERVO_PAD_CH);
    Servo_Set(&Servo_Paw,&SERVO_PAW_TIM,SERVO_PAW_CH);
    Servo_Init(&Servo_Pad);
    Servo_Init(&Servo_Paw);
    lobotRunActionGroup(0,1000);
    HAL_Delay(1200);
    do
	{
//		QRCode=Scan_GetCode();
        HAL_UART_Transmit(&DEBUG_UART,QRCode,(uint16_t)Scan_Data_Length,1000);
	}
    while(!strcmp(QRCode,"TO"));
	OLED_ShowString(1,1,QRCode,164);
    OG_Action(1);
    while(1);
}


void Test_Mod()
{
    // OPS_Rec_Test();
    //Servo_Test();
    // HAL_Delay(2000);
    //ActionTest();
    //Scan_OLED();
    //ServoCon_Test();
    //HAL_Delay(2000);
    //lobotRunActionGroup(10,1000);
    //while(1);
    //ServoAction_Test1();
    //Vision_Test();
    //Motortot_Test();
    //OLED_Test();
    //PC_Uart_Test();
    //Servo_Adj();
    // Servo_Test();
    // Scan_TestDMA();
    //HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
    //__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,1500);
    OLED_Init();
    Motortot_Init();
    Motortot_SetEn_On();
    // Vision_Adj();

    Delay_Init();
    Motortot_SetEn_Off();
    OLED_ShowString(1,1,"INIT...",16);
    OPS.OPS_Init();
    OLED_Clear();
    OLED_ShowString(1,1,"PRESS SW1",16);
    while(!Key_Scan(&KEY1));
    OLED_Clear();
    OLED_ShowString(1,1,"OPSx:",16);
    OLED_ShowString(2,1,"OPSy:",16);
    OLED_ShowString(3,1,"OPSyaw:",16);
    HAL_TIM_Base_Start_IT(&htim13);
    Motortot_SetEn_On();
    Vision_Test();
    //car_go(1,-130,1400,0);
    // PickSpot(0);
    // Scan_OLED();
    //OPS_Rec_Test();
    // _OpenMV_tt_Init(&OpenMV1,&OPENMV1_UART);
    // while(1)
    // {
    //     OpenMVGN_Adj(&OpenMV1);
    // }
    while(1)
    {
        HAL_Delay(2000);
        // Vision_Test();
        // while(1)
        // {
        //     printf("%f\r\n",OPS.zangle);
        // }
        //Motortot_Test();

    // Motortot_Test();
    }
    //Scan_Test();
}

