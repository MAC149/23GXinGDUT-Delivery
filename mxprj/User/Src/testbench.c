#include "testbench.h"
#define MOTOR_DELAYUS 200

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
    //HAL_UART_Transmit(&DEBUG_UART,(uint8_t *)"OLED",4,1000);
    OLED_ShowNum(1,1,temp,3,164);
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



void Test_Mod()
{
    Motortot_Test();
}