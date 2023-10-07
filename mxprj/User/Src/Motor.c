#include "Motor.h"
#define PUL_DIS_1MM 15
#include <math.h>
#include "stdio.h"
#include "imu.h"

void Motortot_SetEn_On()
{
    HAL_GPIO_WritePin(MOTORFL_EN_GPIOX,MOTORFL_EN_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORFR_EN_GPIOX,MOTORFR_EN_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBL_EN_GPIOX,MOTORBL_EN_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBR_EN_GPIOX,MOTORBR_EN_GPIO_PIN,GPIO_PIN_SET);
}

void Motortot_SetEn_Off()
{
    HAL_GPIO_WritePin(MOTORFL_EN_GPIOX,MOTORFL_EN_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORFR_EN_GPIOX,MOTORFR_EN_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBL_EN_GPIOX,MOTORBL_EN_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBR_EN_GPIOX,MOTORBR_EN_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_SetDir(GPIO_PinState FL_DIR,GPIO_PinState FR_DIR, GPIO_PinState BL_DIR, GPIO_PinState BR_DIR)
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,FL_DIR);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,FR_DIR);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,BL_DIR);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,BR_DIR);
} 

void Motortot_SetDir_Forward()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_SET);
}

void Motortot_SetDir_Backward()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_SetDir_Left()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_SetDir_Right()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_SET);
}

void Motortot_SetDir_RotLeft()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_SET);
}

void Motortot_SetDir_RotRight()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_SetDir_ForLeft()
{
    // HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_SET);
    // HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_SetDir_ForRight()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_SET);
    // HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_StpRun_ForLeft(uint16_t time,uint16_t delay_us)
{
    for(uint16_t i=0;i<time;i++)
    {
        // HAL_GPIO_TogglePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN);
        // HAL_GPIO_TogglePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN);
        HAL_Delay_us(delay_us);
    }
}

void Motortot_StpRun_ForRight(uint16_t time,uint16_t delay_us)
{
    for(uint16_t i=0;i<time;i++)
    {
        HAL_GPIO_TogglePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN);
        // HAL_GPIO_TogglePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN);
        // HAL_GPIO_TogglePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN);
        HAL_Delay_us(delay_us);
    }
}

void Motortot_Init()
{
    Motortot_SetEn_Off();
    Motortot_SetDir_RotRight();
    HAL_GPIO_WritePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_StpRunWR(uint16_t time,uint16_t delay_us)//may less efficiency
{
    for(uint16_t i=0;i<time*2;i++)
    {
        HAL_GPIO_TogglePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN);
        HAL_Delay_us(delay_us);
    }
}

void Motortot_StpRun(uint16_t time,uint16_t delay_us)
{
    for(uint16_t i=0;i<time;i++)
    {
        HAL_GPIO_WritePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN,GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN,GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN,GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN,GPIO_PIN_SET);
        HAL_Delay_us(delay_us);
        HAL_GPIO_WritePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN,GPIO_PIN_RESET);
        HAL_Delay_us(delay_us);
    }
}

//-----packed
void Motortot_Forward(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_Forward();
    Motortot_StpRun(time,delay_us);
}

void Motortot_Backward(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_Backward();
    Motortot_StpRun(time,delay_us);
}

void Motortot_Left(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_Left();
    Motortot_StpRun(time,delay_us);
}

void Motortot_Right(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_Right();
    Motortot_StpRun(time,delay_us);
}

void Motortot_RotLeft(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_RotLeft();
    Motortot_StpRun(time,delay_us);
}

void Motortot_RotRight(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_RotRight();
    Motortot_StpRun(time,delay_us);
}

void Motortot_ForLeft(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_ForLeft();
    Motortot_StpRun_ForLeft(time,delay_us);
}

void Motortot_ForRight(uint16_t time,uint16_t delay_us)
{
    Motortot_SetDir_ForRight();
    Motortot_StpRun_ForRight(time,delay_us);
}



void RotYaw_ParamUpdate(float target_yaw,float *RotYaw_Param)
{
    RotYaw_Param[0] = (target_yaw == 360.0) ? 0.0 : target_yaw;
    RotYaw_Param[1] = (target_yaw == 0.0) ? 360.0 : target_yaw;
}

int8_t RotYaw_Status(float* RotYaw_Param)
{
    RotYaw_Param[2]=IMU_yawDataUpdate();
    if(RotYaw_Param[0] == 360.0 || RotYaw_Param[0] == 0.0)
    {
        if((RotYaw_Param[2] > RotYaw_Param[0] + 0.24)&& (RotYaw_Param[2] < 180.0))
        {return 1;}
        else if((RotYaw_Param[2] < RotYaw_Param[1] - 0.24)&&(RotYaw_Param[2] >= 180.0))
        {return 2;}
        else
        {return 0;}
    }
    else
    {
        if(RotYaw_Param[2] > RotYaw_Param[0]+0.2)
        {return 1;}
        else if(RotYaw_Param[2]<RotYaw_Param[0]- 0.2)
        {return 2;}
        else
        {return 0;}
    } 
}

void Motortot_RotTo(float target_yaw,uint16_t delay_us)
{
    float ftmp[4];
    RotYaw_ParamUpdate(target_yaw,ftmp);
    uint8_t temp=RotYaw_Status(ftmp);
    while(temp)
    {
        switch(temp)
        {
            case 1:Motortot_SetDir_RotLeft();
                Motortot_StpRun(8,delay_us);
                break;
            case 2: Motortot_SetDir_RotRight();
                Motortot_StpRun(8,delay_us);
                break;
            case 0:break;
            default:break;
        }
        temp=RotYaw_Status(ftmp);
    }
}


void x_move(int move_mmx10, long speed) // x方向移动 参数 移动距离 mm*10，速度
{
    u16 i, delay;
    if (move_mmx10 > 0) // 右移
    {
        Motortot_SetDir_Right();
    }
    else // 左移
    {
        Motortot_SetDir_Left();
        move_mmx10 = -move_mmx10;
    }
    move_mmx10 *= _0_1_mm_x;
    delay = 500000 / ((speed * 6400) / 60.0);
    Motortot_StpRun(move_mmx10, delay);
}

void X_fast_move(float mm) // x快速移动 参数 移动距离
{
    float speed = 5, j, num;
    int i;

    if (mm != 0)
    {
        if (abs_(mm) > 1)
        {
                num = abs_(mm) * 10; // 总数 0.1mm
                j = 80 / (num / 3);
                if (j > 0.15f)
                    j = 0.15f;
                for (i = 0; i < (num / 3); i++)
                {
                    if (mm < 0)
                        x_move(-1, (long)speed);
                    if (mm > 0)
                        x_move(1, (long)speed);
                    speed += j;
                }
                for (i = 0; i < (num / 3); i++)
                {
                    if (mm < 0)
                        x_move(-1, (long)speed);
                    if (mm > 0)
                        x_move(1, (long)speed);
                }
                for (i = 0; i < (num / 3); i++)
                {
                    if (mm < 0)
                        x_move(-1, (long)speed);
                    if (mm > 0)
                        x_move(1, (long)speed);
                    speed -= j;
                }
        }
        else
        {
                x_move(mm * 10, 2);
        }
    }
}

void y_move(int move_mmx10, long speed)
{
    u16 i, delay;
    if (move_mmx10 > 0) // 前进
    {
        Motortot_SetDir_Forward();
    }
    else // 后退
    {
        move_mmx10 = -move_mmx10;
        Motortot_SetDir_Backward();
    }

    move_mmx10 *= _0_1_mm_y;
    delay = 500000 / ((speed * 6400) / 60.0);
    Motortot_StpRun(move_mmx10, delay);
}

void Y_fast_move(float mm)
{
    float speed = 10, j, num;
    int i;

    if (mm != 0)
    {
        if (abs_(mm) > 1)
        {
                num = abs_(mm) * 10; // 总数 0.1mm
                j = 80 / (num / 3);
                if (j > 0.15f)
                    j = 0.15f;
                for (i = 0; i < (num / 3); i++)
                {
                    if (mm < 0)
                        y_move(-1, (long)speed);
                    if (mm > 0)
                        y_move(1, (long)speed);
                    speed += j;
                }
                for (i = 0; i < (num / 3); i++)
                {
                    if (mm < 0)
                        y_move(-1, (long)speed);
                    if (mm > 0)
                        y_move(1, (long)speed);
                }
                for (i = 0; i < (num / 3); i++)
                {
                    if (mm < 0)
                        y_move(-1, (long)speed);
                    if (mm > 0)
                        y_move(1, (long)speed);
                    speed -= j;
                }
        }
        else
        {
                y_move(mm * 10, 2);
        }
    }
}


//----------
float Yaw_Angle_Dis(float yaw_target)
{
    float now_angle=IMU_yawExclusive();
    float error1=fabs(yaw_target-now_angle);
    float error2=360.0-error1;
    float error=(error1<error2) ? error1 : error2;
    if(now_angle>=180.0)
    {
        if((yaw_target>=now_angle) || (yaw_target<=(now_angle-180.0))){return error;}
        else{return error;}
    }
    else
    {
        if((yaw_target<=now_angle) || (yaw_target>=180.0+now_angle)){return -error;}
        else{return -error;}
    }
}

//--coop

void Rotate_PID(float target_z)
{
    static float Integral_error = 0, Last_error = 0;
    const float P = 0.4, I = 0.01, D = 0.0;
    int Integral_errormax = 2;
    int angle1;  // 数据缓存区
    float error; // 偏差值
    float ftmp[4];
    RotYaw_ParamUpdate(target_z,ftmp);
    int8_t temp=RotYaw_Status(ftmp);
    while (temp)
    {
        error=Yaw_Angle_Dis(target_z);
        printf("%f\r\n",error);
        int pwm = fabs(error) * P * 2 + fabs(Integral_error * I * 2) + (error - Last_error) * D;
        angle1 = fabs(error * P) + fabs(Integral_error * I) + (error - Last_error) * D;
        if (error > 0)
        {
            Motortot_RotLeft(2+angle1,160- pwm);
        }
        if (error < 0)
        {
            Motortot_RotRight(2+angle1, 160-pwm);
        }
        Last_error = error;
        temp=RotYaw_Status(ftmp);
    }
}

bool YawKeepFlag=0;
double YawKeepTar=0;
void YawKeepStart(double yawTarget)
{
    YawKeepTar=yawTarget;
    YawKeepFlag=1;
}

void YawKeepStop()
{
    YawKeepFlag=0;
}

void YawKeep()
{
    if(YawKeepFlag)
    {
        Motortot_RotTo(YawKeepTar,50);
    }
}

void Motor_LiftEn_On()
{
    HAL_GPIO_WritePin(MOTORLT_DIR_GPIOX, MOTORLT_EN_GPIO_PIN, GPIO_PIN_SET);
}

void Motor_LiftEn_Off()
{
    HAL_GPIO_WritePin(MOTORLT_DIR_GPIOX, MOTORLT_EN_GPIO_PIN, GPIO_PIN_RESET);
}

void Motor_LiftUp(uint16_t time, uint16_t delay_us)
{
    HAL_GPIO_WritePin(MOTORLT_DIR_GPIOX, MOTORLT_DIR_GPIO_PIN, GPIO_PIN_RESET);
    for (uint16_t i = 0; i < time; i++)
    {
        HAL_GPIO_WritePin(MOTORLT_STP_GPIOX, MOTORLT_STP_GPIO_PIN, GPIO_PIN_SET);
        HAL_Delay_us(delay_us);
        HAL_GPIO_WritePin(MOTORLT_STP_GPIOX, MOTORLT_STP_GPIO_PIN, GPIO_PIN_RESET);
        HAL_Delay_us(delay_us);
    }
}

void Motor_LiftDown(uint16_t time, uint16_t delay_us)
{
    HAL_GPIO_WritePin(MOTORLT_DIR_GPIOX, MOTORLT_DIR_GPIO_PIN, GPIO_PIN_SET);
    for (uint16_t i = 0; i < time; i++)
    {
        HAL_GPIO_WritePin(MOTORLT_STP_GPIOX, MOTORLT_STP_GPIO_PIN, GPIO_PIN_SET);
        HAL_Delay_us(delay_us);
        HAL_GPIO_WritePin(MOTORLT_STP_GPIOX, MOTORLT_STP_GPIO_PIN, GPIO_PIN_RESET);
        HAL_Delay_us(delay_us);
    }
}