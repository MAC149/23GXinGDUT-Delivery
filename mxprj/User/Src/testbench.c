#include "testbench.h"
#define MOTOR_DELAYUS 300


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

void Servo_Test()
{
    // __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,500);
    // HAL_Delay(2000);
    // __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,2500);
    // HAL_Delay(3000);
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

void Usart_Reply()
    {
        uint8_t FFT_SampI[512];
        //FloatToUint8(FFT_SampI,sd.FFT_Samples,512);Usart1_DmaStart((uint8_t*)FFT_SampI,sd.spec_len);
}


void OPS_Rec_Test()
{
    HAL_Delay(3500);
    OPS.OPS_Init();
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
    //Motortot_Test();
    float_t F_a=1.3431;
    //OLED_Test();
    OLED_Init();
    OLED_ShowString(1,1,"PRESS SW1",32);
    while(!Key_Scan(&KEY1));
    OLED_ShowString(1,1,"OPSx:",16);
    OLED_ShowString(2,1,"OPSy:",16);
    OLED_ShowString(3,1,"OPSyaw:",16);
    Motortot_Init();
    Motortot_SetEn_Off();
    OPS.OPS_Init();
    Motortot_SetEn_On();
    // for(;;F_a++)
    // {
    //     HAL_Delay(1500);
    //     HAL_UART_Transmit(&DEBUG_UART,(uint8_t*)"aaa\n",4,1000);
    //     OLED_ShowFNum(1,1,F_a,10,16);
    // }
    //OPS_Rec_Test();
    while(1)
    {
    Motortot_GoY(500,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_GoY(-500,MOTOR_DELAYUS);
    HAL_Delay(2500);
    Motortot_GoY(-500,MOTOR_DELAYUS);
    HAL_Delay(1500);
    Motortot_GoY(500,MOTOR_DELAYUS);
    HAL_Delay(3000);
    // Motortot_Test();
    }
    //Scan_Test();
}