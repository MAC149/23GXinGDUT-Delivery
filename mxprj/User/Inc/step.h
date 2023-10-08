#ifndef _STEP_H_
#define _STEP_H_

#include "Motor.h"
#include "Delay.h"
#include "OLED.h"
#include "Scan.h"
#include "misc.h"
#include <math.h>
#include <stdio.h>
#include "vision.h"
#include "Servo.h"
#include <string.h>
#include "LobotServoController.h"
#include "imu.h"

#define SERVO_PAD_TIM htim4
#define SERVO_PAD_CH TIM_CHANNEL_4  //PD15
#define SERVO_PAW_TIM htim4
#define SERVO_PAW_CH TIM_CHANNEL_2  //PD13
#define SERVO_ROT_TIM htim4
#define SERVO_ROT_CH TIM_CHANNEL_3 //PD14

#define SERVO_PAW_CLOSE 95
#define SERVO_PAW_OPEN 130
#define SERVO_PAD_RED 0
#define SERVO_PAD_GREEN 90
#define SERVO_PAD_BLUE 180

#define SERVO_ROT_GND 158
#define SERVO_ROT_PAD 25

#define MOTOR_LIFT_UPGROUD 800
#define MOTOR_LIFT_PAD 4450
#define MOTOR_LIFT_UPPAD 5000
#define MOTOR_LIFT_2XGND 2300
#define MOTOR_LIFT_UPOG 5000
#define MOTOR_LIFT_OG 4450
#define MOTOR_LIFT_TOP 5500
#define MOTOR_LIFT_NRTOP 5200

#define PAW_OPEN Servo_SetDeg(&Servo_Paw,SERVO_PAW_OPEN)
#define PAW_CLOSE Servo_SetDeg(&Servo_Paw,SERVO_PAW_CLOSE)
#define PAD_R Servo_SetDeg(&Servo_Pad,SERVO_PAD_RED)
#define PAD_G Servo_SetDeg(&Servo_Pad,SERVO_PAD_GREEN)
#define PAD_B Servo_SetDeg(&Servo_Pad,SERVO_PAD_BLUE)
#define ROT_GND Servo_SetDeg(&Servo_Rot,SERVO_ROT_GND)
#define ROT_PAD Servo_SetDeg(&Servo_Rot,SERVO_ROT_PAD)


void Full_Step();


void Pad_Put();
void Pad_Pick();
void Pick_Action();
void Put_Action(uint8_t phase);
void Pad_Switch(char target);
void OG_Action(int Phase);
void RM_Action(int Phase);
void SM_Action(uint8_t Phase);
void PreAction();



#endif // !_STEP_H_
