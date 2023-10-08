#include "Servo.h"

void Servo_Set(Servo_t* Servo,TIM_HandleTypeDef* Servo_TIMx,uint32_t Servo_Channel)
{
    Servo->Servo_TIMx=Servo_TIMx;
    Servo->Servo_Channel=Servo_Channel;
}

void Servo_Init(Servo_t* Servo)
{
    HAL_TIM_PWM_Start(Servo->Servo_TIMx,Servo->Servo_Channel);
}

uint16_t Servo_Deg(uint8_t Deg)
{
    return (uint16_t)((((double)Deg)*10.0f/9.0f)+50.0f);
}

void Servo_SetDeg(Servo_t* Servo,uint8_t Deg)
{
    __HAL_TIM_SET_COMPARE(Servo->Servo_TIMx,Servo->Servo_Channel,Servo_Deg(Deg));
}

