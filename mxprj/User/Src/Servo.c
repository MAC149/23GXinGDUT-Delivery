#include "Servo.h"

void Servo_Set(Servo_t* Servo,TIM_HandleTypeDef* Servo_TIMx,uint32_t Servo_Channel)
{
    Servo->Servo_TIMx=Servo_TIMx;
    Servo->Servo_Channel=Servo_Channel;
    Servo->Servo_NowDeg=0;
}

void Servo_Init(Servo_t* Servo)
{
    HAL_TIM_PWM_Start(Servo->Servo_TIMx,Servo->Servo_Channel);
}

uint16_t Servo_Deg(uint8_t Deg)
{
    return (uint16_t)((((double)Deg)*10.0f/9.0f)+50.0f);
}

uint16_t Servo_Deg270(uint16_t Deg)
{
    return (uint16_t)((((double)Deg)*20.0f/27.0f)+50.0f);
}

void Servo_SetDeg(Servo_t* Servo,uint8_t Deg)
{
    __HAL_TIM_SET_COMPARE(Servo->Servo_TIMx,Servo->Servo_Channel,Servo_Deg(Deg));
    Servo->Servo_NowDeg=Deg;
}

void Servo_SetDeg270(Servo_t* Servo,uint16_t Deg)
{
    __HAL_TIM_SET_COMPARE(Servo->Servo_TIMx,Servo->Servo_Channel,Servo_Deg270(Deg));
    Servo->Servo_NowDeg=Deg;
}

void Servo_SetDegSlow(Servo_t* Servo,uint16_t Deg)
{
    if(Servo->Servo_NowDeg<Deg)
    {
            for(;Servo->Servo_NowDeg<Deg;)
    {
        Servo_SetDeg(Servo,Servo->Servo_NowDeg+5);
        HAL_Delay(20);
    }
    }
    else
    {
         for(;Servo->Servo_NowDeg>Deg;)
    {
        Servo_SetDeg(Servo,Servo->Servo_NowDeg-5);
        HAL_Delay(20);
    }
    }
    Servo_SetDeg(Servo,Deg);
}

void Servo_SetDegSlow270(Servo_t* Servo,uint16_t Deg)
{
    if(Servo->Servo_NowDeg<Deg)
    {
            for(;Servo->Servo_NowDeg<Deg;)
    {
        Servo_SetDeg270(Servo,Servo->Servo_NowDeg+5);
        HAL_Delay(20);
    }
    }
    else
    {
         for(;Servo->Servo_NowDeg>Deg;)
    {
        Servo_SetDeg270(Servo,Servo->Servo_NowDeg-5);
        HAL_Delay(20);
    }
    }
    Servo_SetDeg270(Servo,Deg);
}

