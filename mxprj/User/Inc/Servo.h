#ifndef _SERVO_H_
#define _SERVO_H_

#include "GeneralDef.h"

#define SERVO_DEGREE_0 500
#define SERVO_DEGREE_45 1000
#define SERVO_DEGREE_90 1500
#define SERVO_DEGREE_135 2000
#define SERVO_DEGREE_180 2500

typedef struct
{
    TIM_HandleTypeDef* Servo_TIMx;
   uint32_t Servo_Channel;
}Servo_t;

void Servo_Set(Servo_t Servo,TIM_HandleTypeDef* Servo_TIMx,uint32_t Servo_Channel);
void Servo_Init(Servo_t Servo);
void Servo_SetDeg(Servo_t Servo,uint16_t Deg);
uint16_t Servo_Deg(uint8_t Deg);


#endif // !_SERVO_H_