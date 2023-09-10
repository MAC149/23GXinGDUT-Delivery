#include "Servo.h"

void Servo_Set(Servo_t Servo,TIM_HandleTypeDef* Servo_TIMx,uint32_t Servo_Channel)
{
    Servo.Servo_TIMx=Servo_TIMx;
    Servo.Servo_Channel=Servo_Channel;
}

void Servo_Init(Servo_t Servo)
{
    HAL_TIM_PWM_Start(Servo.Servo_TIMx,Servo.Servo_Channel);
}

void Servo_SetDeg(Servo_t Servo,uint16_t Deg)
{
    __HAL_TIM_SET_COMPARE(Servo.Servo_TIMx,Servo.Servo_Channel,Deg);
}

uint16_t Servo_Deg(uint8_t Deg)
{
    return (int)(2000*(1-((0.5+Deg/90.0)/20.0))) -5;
}