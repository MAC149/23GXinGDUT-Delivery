#include "Motor.h"
#define PUL_DIS_1MM 15
#include <math.h>
#include "stdio.h"

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

//---------OPS


void Motortot_GoXdis(float disx,uint16_t delay_us)
{
    long desx=OPS.pos_x+disx;
    if(disx<0)
    {
        Motortot_SetDir_Left();
        while(!(OPS.pos_x<desx+5 && OPS.pos_x>desx-5))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
    else
    {
        Motortot_SetDir_Right();
        while(!(OPS.pos_x<desx+5 && OPS.pos_x>desx-5))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
}

void Motortot_GoYdis(float disy,uint16_t delay_us)
{
    long desy=OPS.pos_y+disy;
    if(disy<0.0)
    {
        Motortot_SetDir_Backward();
        while(!(OPS.pos_y<desy+5.0 && OPS.pos_y>desy-5.0))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
    else
    {
        Motortot_SetDir_Forward();
        while(!(OPS.pos_y<desy+5.0 && OPS.pos_y>desy-5.0))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
}

void Motortot_GoX(float targetx,uint16_t delay_us)
{
    if(targetx<OPS.pos_x)
    {
        Motortot_SetDir_Left();
        while(!(OPS.pos_x<targetx+5 && OPS.pos_x>targetx-5))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
    else
    {
        Motortot_SetDir_Right();
        while(!(OPS.pos_x<targetx+5 && OPS.pos_x>targetx-5))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
}

void Motortot_GoY(float targety,uint16_t delay_us)
{
    if(targety<OPS.pos_y)
    {
        Motortot_SetDir_Backward();
        while(!(OPS.pos_y<targety+5.0 && OPS.pos_y>targety-5.0))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
    else
    {
        Motortot_SetDir_Forward();
        while(!(OPS.pos_y<targety+5.0 && OPS.pos_y>targety-5.0))
        {
            Motortot_StpRun(2*PUL_DIS_1MM,delay_us);
        }
    }
}



void RotYaw_ParamUpdate(float target_yaw,float *RotYaw_Param)
{
    RotYaw_Param[0] = (target_yaw == 180.0) ? -target_yaw : target_yaw;
    RotYaw_Param[1] = (target_yaw == -180.0) ? -target_yaw : target_yaw;
}

int8_t RotYaw_Status(float* RotYaw_Param)
{
    RotYaw_Param[2]=OPS.zangle;
    if(RotYaw_Param[0] == 180.0 || RotYaw_Param[0] == -180.0)
    {
        if((RotYaw_Param[2] > RotYaw_Param[0] + 0.24)&& (RotYaw_Param[2] < 0.0))
        {return 2;}
        else if((RotYaw_Param[2] < RotYaw_Param[1] - 0.24)&&(RotYaw_Param[2] >= 0.0))
        {return 1;}
        else
        {return 0;}
    }
    else
    {
        if(RotYaw_Param[2] > RotYaw_Param[0]+0.2)
        {return 2;}
        else if(RotYaw_Param[2]<RotYaw_Param[0]- 0.2)
        {return 1;}
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

//-------coopPID
float delay_FL;
float delay_FR;
float delay_BL;
float delay_BR;

float target_y = 0;
float target_x = 0;
float target_yaw = 0;

int car_speed_max_now = 1;
float pi_control_out;

u8 speed_gx_bit = 0;
u8 move_mode = 0;

u16 car_speed_max = 100;
u16 car_speed_yaw_max = 50;

u8 Car_Loc_Flag = 0; // 0--start 1--approach 2--arrive

union
{
    float yaw;
    u8 usart_data[4];
} my_yaw;

void speed_control() // 每10ms执行一次
{
    if (pi_control_out > car_speed_max_now)
    {
        if (car_speed_max_now < car_speed_max)
        {
                car_speed_max_now++;
        }
    }
    else if (pi_control_out < car_speed_max_now)
    {
        car_speed_max_now = pi_control_out;
    }
}

void move_motor_control()			//每5us运行一次
{
	static u16 Aa=0;
	static u16 Bb=0;
	static u16 Cc=0;
	static u16 Dd=0;
	
	if(delay_FL!=0){if(++Aa>=(u16)delay_FL){MOTORFL_PLU_TOG;Aa=0;}}else {Aa=0;}		//x50 delay_fl=18
	if(delay_FR!=0){if(++Bb>=(u16)delay_FR){MOTORFR_PLU_TOG;Bb=0;}}else {Bb=0;}
	if(delay_BL!=0){if(++Cc>=(u16)delay_BL){MOTORBL_PLU_TOG;Cc=0;}}else {Cc=0;}
	if(delay_BR!=0){if(++Dd>=(u16)delay_BR){MOTORBR_PLU_TOG;Dd=0;}}else {Dd=0;}
}//切换引脚状态产生脉冲

void velocity_analysis(float x,float y,float yaw)  //逆运动学模型  x方向右正左负  y方向前为正 后为负  yaw 逆时针为正
{
	float RF_sudu,LF_sudu,LB_sudu,RB_sudu;
		
	if(yaw > 30) yaw = 30;
	else if(yaw < -30) yaw = -30;
		
	RF_sudu=y-x+yaw;
	LF_sudu=y+x-yaw;
	LB_sudu=y-x-yaw;
	RB_sudu=y+x+yaw;

	if(LF_sudu<0){LF_sudu=-LF_sudu;MOTORFL_DIR(CW);}else MOTORFL_DIR(CCW);
	if(RF_sudu<0){RF_sudu=-RF_sudu;MOTORFR_DIR(CCW);}else MOTORFR_DIR(CW);
	if(LB_sudu<0){LB_sudu=-LB_sudu;MOTORBL_DIR(CW);}else MOTORBL_DIR(CCW);
	if(RB_sudu<0){RB_sudu=-RB_sudu;MOTORBR_DIR(CCW);}else MOTORBR_DIR(CW);
	
	if(RF_sudu!=0)delay_FR=100000/((RF_sudu*6400)/60.0);else delay_FR=0;			//输出的是半个脉冲的时间
	if(LF_sudu!=0)delay_FL=100000/((LF_sudu*6400)/60.0);else delay_FL=0;
	if(LB_sudu!=0)delay_BL=100000/((LB_sudu*6400)/60.0);else delay_BL=0;
	if(RB_sudu!=0)delay_BR=100000/((RB_sudu*6400)/60.0);else delay_BR=0;

}//得到速度和方向

float actual_rotation_angle(float now_angle,float tag_angle)
{
	float dis1,dis2;
	dis1 = tag_angle - now_angle;
	if (now_angle > 0)
	{
			dis2 = 180 - now_angle + tag_angle + 180;		//逆时针转
	}
	else
	{
			dis2 = -180 - now_angle + tag_angle - 180;		//顺时针转
	}
	if (abs_ff(dis1) < abs_ff(dis2))return dis1;
	else return dis2;
}

// 位置PID控制参数
#define POSITION_KP 2.0
#define POSITION_KI 0.02
#define POSITION_MAX_INTEGRAL 80

// 位置PID控制函数
void position_control()
{
    static float x_integral = 0;
    static float y_integral = 0;
    static u8 last_mode = 1;

    float x_err = target_x - OPS.pos_x;
    float y_err = target_y - OPS.pos_y;

    // 判断是否已经接近目标
    if (x_err < 200 && y_err < 200)
    {
        Car_Loc_Flag = 1;
    }

    if (move_mode == 1)
    {
        // 积分项分离
        if (x_err < 5 && x_err > -5)
        {
                x_integral += x_err * POSITION_KI;
        }
        else
        {
                x_integral = 0;
        }

        if (y_err < 5 && y_err > -5)
        {
                y_integral += y_err * POSITION_KI;
        }
        else
        {
                y_integral = 0;
        }

        // 位置式PI
        float pi_x_out = x_err * POSITION_KP + x_integral;
        float pi_y_out = y_err * POSITION_KP + y_integral;

        // 限制积分项
        if (pi_x_out > POSITION_MAX_INTEGRAL)
        {
                pi_x_out = POSITION_MAX_INTEGRAL;
        }
        else if (pi_x_out < -POSITION_MAX_INTEGRAL)
        {
                pi_x_out = -POSITION_MAX_INTEGRAL;
        }

        if (pi_y_out > POSITION_MAX_INTEGRAL)
        {
                pi_y_out = POSITION_MAX_INTEGRAL;
        }
        else if (pi_y_out < -POSITION_MAX_INTEGRAL)
        {
                pi_y_out = -POSITION_MAX_INTEGRAL;
        }

        // 控制输出限制
        pi_control_out = abs_ff(pi_x_out) + abs_ff(pi_y_out);
        if (pi_control_out > car_speed_max_now)
        {
                // 限制控制输出
                float factor = car_speed_max_now / pi_control_out;
                pi_x_out *= factor;
                pi_y_out *= factor;
        }

        // 转换为全局坐标系
        float pi_x_out1 = pi_x_out * cosf(OPS.zangle * 0.0174528f) + pi_y_out * sinf(OPS.zangle * 0.0174528f);
        float pi_y_out1 = pi_y_out * cosf(OPS.zangle * 0.0174528f) - pi_x_out * sinf(OPS.zangle * 0.0174528f);

        // 速度分析
        velocity_analysis(pi_x_out1, pi_y_out1, actual_rotation_angle(OPS.zangle, target_yaw) * 3);

        // 判断是否到达目标
        if (OPS.pos_y > target_y - 2 && OPS.pos_y < target_y + 2 &&
            OPS.pos_x > target_x - 2 && OPS.pos_x < target_x + 2 &&
            target_yaw < OPS.zangle + 1 && target_yaw > OPS.zangle - 1)
        {
                Car_Loc_Flag = 2;
                last_mode = 0;
        }
    }
    else
    {
        x_integral = 0;
        y_integral = 0;
        if (last_mode == 0)
        {
                last_mode = 1;
                velocity_analysis(0, 0, 0);
        }
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

void rotatePIDrealize(int sud) // 速度给10作用
{
    //	HAL_Delay(100);
    while (1)
    {
        if (OPS.zangle > -1 && OPS.zangle < 1)
        {
                break;
        }
        Rotate_PID(0);
        HAL_Delay(10);
    }
}

//----------
float Yaw_Angle_Dis(float yaw_target)
{
    float now_angle=OPS.zangle;
    float error1=fabs(yaw_target-now_angle);
    float error2=360.0-error1;
    float error=(error1<error2) ? error1 : error2;
    if(now_angle>=0.0)
    {
        if((yaw_target>=now_angle) || (yaw_target<=(now_angle-180.0))){return error;}
        else{return -error;}
    }
    else
    {
        if((yaw_target<=now_angle) || (yaw_target>=180.0+now_angle)){return -error;}
        else{return error;}
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

void car_go(uint8_t mode, float fDistance_x, float fDistance_y, float target_yaw)
{
    const float tolerance = 2.0;   // 定义每个轴的容差范围
    const float tolerance2 = 20.0; // 定义每个轴的容差范围
    Car_Loc_Flag = 0;
    target_x = fDistance_x;
    target_y = fDistance_y;
    target_yaw = target_yaw;
    move_mode = 1;
    Delay_Init();
    if (mode)
    {
        while (1)
        {
            float x_err = target_x - OPS.pos_x;
            float y_err = target_y - OPS.pos_y;
            float yaw_err = actual_rotation_angle(OPS.zangle, target_yaw);

            if (abs_(x_err) <= tolerance && abs_(y_err) <= tolerance && abs_(yaw_err) <= 1)
            {
                velocity_analysis(0, 0, 0);
                mode = 0;
                HAL_Delay(1000);
                PIDT_Stop(); // Rotate_PID(target_yaw,80); // 将移动模式设置回0（停止）
                break;
            }
            //                position_control(); //得数值，给方向
            //                move_motor_control(); //给脉冲
        }
    }
}
