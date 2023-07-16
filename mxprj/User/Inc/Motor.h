#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "GeneralDef.h"


//MOTOR IO CONNECTION
//MOTORFL
#define MOTORFL_EN_GPIOX GPIOE
#define MOTORFL_EN_GPIO_PIN GPIO_PIN_4
#define MOTORFL_STP_GPIOX GPIOE
#define MOTORFL_STP_GPIO_PIN GPIO_PIN_5
#define MOTORFL_DIR_GPIOX GPIOE
#define MOTORFL_DIR_GPIO_PIN GPIO_PIN_6
//MOTORFR
#define MOTORFR_EN_GPIOX GPIOE
#define MOTORFR_EN_GPIO_PIN GPIO_PIN_7
#define MOTORFR_STP_GPIOX GPIOE
#define MOTORFR_STP_GPIO_PIN GPIO_PIN_8
#define MOTORFR_DIR_GPIOX GPIOE
#define MOTORFR_DIR_GPIO_PIN GPIO_PIN_9
//MOTORBL
#define MOTORBL_EN_GPIOX GPIOE
#define MOTORBL_EN_GPIO_PIN GPIO_PIN_10
#define MOTORBL_STP_GPIOX GPIOE
#define MOTORBL_STP_GPIO_PIN GPIO_PIN_11
#define MOTORBL_DIR_GPIOX GPIOE
#define MOTORBL_DIR_GPIO_PIN GPIO_PIN_12
//MOTORBR
#define MOTORBR_EN_GPIOX GPIOE
#define MOTORBR_EN_GPIO_PIN GPIO_PIN_13
#define MOTORBR_STP_GPIOX GPIOE
#define MOTORBR_STP_GPIO_PIN GPIO_PIN_14
#define MOTORBR_DIR_GPIOX GPIOE
#define MOTORBR_DIR_GPIO_PIN GPIO_PIN_15
#include "Motor.h"

void Motortot_SetEn_On();
void Motortot_SetEn_Off();
void Motortot_SetDir(GPIO_PinState FL_DIR,GPIO_PinState FR_DIR, GPIO_PinState BL_DIR, GPIO_PinState BR_DIR);
void Motortot_SetDir_Forward();
void Motortot_SetDir_Backward();
void Motortot_SetDir_Left();
void Motortot_SetDir_Right();
void Motortot_SetDir_RotLeft();
void Motortot_SetDir_RotRight();
void Motortot_SetDir_ForLeft();
void Motortot_SetDir_ForRight();
void Motortot_StepRun_ForLeft(uint8_t time);
void Motortot_StepRun_ForRight(uint8_t time);
void Motortot_Init();
void Motortot_StpRun(uint8_t time);
void Motortot_StpRunWR(uint8_t time);

#endif // !_MOTOR_H_
#define _MOTOR_H_