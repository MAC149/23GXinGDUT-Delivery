#ifndef _SERVO_H_
#define _SERVO_H_

#include "GeneralDef.h"

#define SERVO_DEGREE_0 50
#define SERVO_DEGREE_45 100
#define SERVO_DEGREE_90 150
#define SERVO_DEGREE_135 200
#define SERVO_DEGREE_180 250

typedef struct
{
    TIM_HandleTypeDef* Servo_TIMx;
   uint32_t Servo_Channel;
   uint16_t Servo_NowDeg;
}Servo_t;

void Servo_Set(Servo_t* Servo,TIM_HandleTypeDef* Servo_TIMx,uint32_t Servo_Channel);
void Servo_Init(Servo_t* Servo);
uint16_t Servo_Deg(uint8_t Deg);
void Servo_SetDeg(Servo_t* Servo,uint8_t Deg);
void Servo_SetDeg270(Servo_t* Servo,uint16_t Deg);
void Servo_SetDegSlow(Servo_t* Servo,uint16_t Deg);
void Servo_SetDegSlow270(Servo_t* Servo,uint16_t Deg);


#endif // !_SERVO_H_