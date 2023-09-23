#ifndef _STEP_H_
#define _STEP_H_

#include "Motor.h"
#include "Delay.h"
#include "OLED.h"
#include "Scan.h"
#include "OPS_system.h"
#include "misc.h"
#include <math.h>
#include <stdio.h>
#include "vision.h"
#include "Servo.h"
#include <string.h>
#include "LobotServoController.h"
#include "imu.h"

#define PAW_OPEN Servo_SetDeg(&Servo_Paw,SERVO_PAW_OPEN)
#define PAW_CLOSE Servo_SetDeg(&Servo_Paw,SERVO_PAW_CLOSE)
#define PAD_R Servo_SetDeg(&Servo_Pad,SERVO_PAD_RED)
#define PAD_G Servo_SetDeg(&Servo_Pad,SERVO_PAD_GREEN)
#define PAD_B Servo_SetDeg(&Servo_Pad,SERVO_PAD_BLUE)

#define SERVO_PAD_TIM htim3
#define SERVO_PAD_CH TIM_CHANNEL_4
#define SERVO_PAW_TIM htim3
#define SERVO_PAW_CH TIM_CHANNEL_3

#define SERVO_PAW_CLOSE 75
#define SERVO_PAW_OPEN 130
#define SERVO_PAD_RED 4
#define SERVO_PAD_GREEN 93
#define SERVO_PAD_BLUE 180

void Full_Step();


void Pad_Put();
void Pad_Pick();
void Pick_Action(uint8_t pos);
void Put_Action(uint8_t phase,uint8_t pos);
void Pad_Switch(char target);
void OG_Action(int Phase);
void RM_Action(int Phase);
void SM_Action(uint8_t Phase);




#endif // !_STEP_H_
