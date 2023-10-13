#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "GeneralDef.h"
#include "Delay.h"


/*
OPS:
x   <-  -   + ->
y    ↑+  -↓
zangle(yaw) CW- +CCW
*/


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
#define MOTORBL_EN_GPIO_PIN GPIO_PIN_13
#define MOTORBL_STP_GPIOX GPIOE
#define MOTORBL_STP_GPIO_PIN GPIO_PIN_14
#define MOTORBL_DIR_GPIOX GPIOE
#define MOTORBL_DIR_GPIO_PIN GPIO_PIN_15
//MOTORBR
#define MOTORBR_EN_GPIOX GPIOE
#define MOTORBR_EN_GPIO_PIN GPIO_PIN_10
#define MOTORBR_STP_GPIOX GPIOE
#define MOTORBR_STP_GPIO_PIN GPIO_PIN_11
#define MOTORBR_DIR_GPIOX GPIOE
#define MOTORBR_DIR_GPIO_PIN GPIO_PIN_12
//MOTORLIFT
#define MOTORLT_EN_GPIOX GPIOE
#define MOTORLT_EN_GPIO_PIN GPIO_PIN_2
#define MOTORLT_STP_GPIOX GPIOE
#define MOTORLT_STP_GPIO_PIN GPIO_PIN_3
#define MOTORLT_DIR_GPIOX GPIOC
#define MOTORLT_DIR_GPIO_PIN GPIO_PIN_13

//COMPATIBILITY
//控制使能引脚
/* 带参宏，可以像内联函数一样使用 */
#define MOTORFL_EN(x)         HAL_GPIO_WritePin(MOTORFL_EN_GPIOX,MOTORFL_EN_GPIO_PIN,x)
#define MOTORFL_PLU(x)        HAL_GPIO_WritePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN,x)
#define MOTORFL_PLU_TOG       HAL_GPIO_TogglePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN)
#define MOTORFL_DIR(x)        HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,x)
	
#define MOTORFR_EN(x)        HAL_GPIO_WritePin(MOTORFR_EN_GPIOX,MOTORFR_EN_GPIO_PIN,x)
#define MOTORFR_PLU(x)        HAL_GPIO_WritePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN,x)
#define MOTORFR_PLU_TOG       HAL_GPIO_TogglePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN)
#define MOTORFR_DIR(x)        HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,x)

#define MOTORBL_EN(x)         HAL_GPIO_WritePin(MOTORBL_EN_GPIOX,MOTORBL_EN_GPIO_PIN,x)
#define MOTORBL_PLU(x)        HAL_GPIO_WritePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN,x)
#define MOTORBL_PLU_TOG       HAL_GPIO_TogglePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN)
#define MOTORBL_DIR(x)        HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,x)

#define MOTORBR_EN(x)        HAL_GPIO_WritePin(MOTORBR_EN_GPIOX,MOTORBR_EN_GPIO_PIN,x)
#define MOTORBR_PLU(x)        HAL_GPIO_WritePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN,x)
#define MOTORBR_PLU_TOG       HAL_GPIO_TogglePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN)
#define MOTORBR_DIR(x)        HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,x)

#define _0_1_mm_y 1.2739f   //y方向前进0.1mm 需要的脉冲数量
#define _0_1_mm_x 1.2739f   //x方向前进0.1mm 需要的脉冲数量

#define ZTARGET_SPEED_MAX  10
#define MOTOR_STP_1ROUND 3200 

/* typedef struct Motor_t
{
    GPIO_TypeDef* Motor_EN_GPIOX;
    uint16_t Motor_EN_GPIOPin;
    GPIO_TypeDef* Motor_Stp_GPIOX;
    uint16_t Motor_Stp_GPIOPin;
    GPIO_TypeDef* Motor_Dir_GPIOX;
    uint16_t Motor_Dir_GPIOPin;
    void(* Motor_En_Set)(struct Motor_t *, GPIO_PinState);
    void(* Motor_Dir_Set)(struct Motor_t *, GPIO_PinState);
    void(* Motor_Stp_Set)(struct Motor_t *, GPIO_PinState);
}Motor_tt; */

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
void Motortot_StpRun_ForLeft(uint16_t time,uint16_t delay_us);
void Motortot_StpRun_ForRight(uint16_t time,uint16_t delay_us);
void Motortot_Init();
void Motortot_StpRun(uint16_t time,uint16_t delay_us);
void Motortot_StpRunWR(uint16_t time,uint16_t delay_us);

//-----packed
void Motortot_Forward(uint16_t time,uint16_t delay_us);
void Motortot_Backward(uint16_t time,uint16_t delay_us);
void Motortot_Left(uint16_t time,uint16_t delay_us);
void Motortot_Right(uint16_t time,uint16_t delay_us);
void Motortot_RotLeft(uint16_t time,uint16_t delay_us);
void Motortot_RotRight(uint16_t time,uint16_t delay_us);
void Motortot_ForLeft(uint16_t time,uint16_t delay_us);
void Motortot_ForRight(uint16_t time,uint16_t delay_us);

void Motortot_RotTo(float target_yaw,uint16_t delay_us);

void Rotate_PID(float target_z);
void YawKeep();
void YawKeepStart(float yawTarget,char dir);
void YawKeepStop();

void Motor_LiftUp(uint16_t time, uint16_t delay_us);
void Motor_LiftDown(uint16_t time, uint16_t delay_us);
void Motor_LiftEn_On();
void Motor_LiftEn_Off();
void Motor_Lift_Reset(uint16_t delay_us);
void Motor_Lift_GoPos(uint16_t tarpos,uint16_t delayus);

//------ops
void Motortot_GoX(float targetx,uint16_t delay_us);
void Motortot_GoY(float targety,uint16_t delay_us);
void Motortot_GoXdis(float disx,uint16_t delay_us);
void Motortot_GoYdis(float disy,uint16_t delay_us);
void move_motor_control(void);
void velocity_analysis(float x,float y,float yaw);
void X_fast_move(float mm);
void Y_fast_move(float mm);
void position_control(void);
float actual_rotation_angle(float now_angle,float tag_angle);
void speed_control(void);
void rotatePIDrealize(int sud);	
void car_go(uint8_t mode, double fDistance_x, double fDistance_y, float target_z);

#endif // !_MOTOR_H_
#define _MOTOR_H_