#include "Motor.h"
#define PUL_DIS_1MM 25
#include <math.h>

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

void Motortot_RotTo(float target_yaw,uint16_t delay_us)
{
    float temp[4];
    if(target_yaw==180.0)
    {
        temp[0]=-target_yaw;
    }
    else
    {
         temp[0]=target_yaw;
    }
    if(target_yaw==-180.0)
    {
        temp[1]=-target_yaw;
    }
    else
    {
        temp[1]=target_yaw;
    }
    if(target_yaw == 180.0 || target_yaw == -180.0)
    {
        while(1)
        {
			temp[2]=OPS.zangle;
			if(temp[3]==temp[2] || temp[2]==0.00)
			{
				continue;
			}
			else
			{
				temp[3]=temp[2];
			}
            if((temp[2] > temp[0] + 0.5)&& (temp[2] < 0))
            {
                Motortot_SetDir_RotRight();
                Motortot_StpRun(8,delay_us);
            }
            else if((temp[2] < temp[1] - 0.5)&&(temp[2] >= 0))
            {
                Motortot_SetDir_RotLeft();
                Motortot_StpRun(8,delay_us);
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        while(1)
        {
			temp[2]=OPS.zangle;
			if(temp[3]==temp[2] || temp[2]==0.00)
			{
				continue;
			}
			else
			{
				temp[3]=temp[2];
			}
            if(temp[2] > temp[0]+0.2)
            {
                Motortot_SetDir_RotRight();
                Motortot_StpRun(8,delay_us);
            }
            else if(temp[2]<temp[0]	- 0.2)
            {
                Motortot_SetDir_RotLeft();
                Motortot_StpRun(8,delay_us);
            }
            else
            {
                break;
            }
         }
    } 
}

//--------selfDesign PID
#define PID_KP 0.4
#define PID_KI 0.01
#define PID_KD 0.0
#define PID_SPEED_KP 0.1


bool Car_Run_Flag=0;
bool Car_GoDis_Flag=0;
typedef struct
{
	float current_x;
	float current_y;
	float current_yaw;
	float target_x;
	float target_y;
	float target_yaw;
	float error_x;
	float error_y;
	float errortot_x;
	float errortot_y;
	float erroradd_x;
	float erroradd_y;
	float errorlast_x;
	float errorlast_y;
	uint16_t speed_output;
	uint16_t speed_max;
}Car_PID_t;

Car_PID_t PID={0};

/*
Speed ->Delay Convert Idea
define SPEED from 0 -> 300
refering DELAY_US from 300 -> 0
*/
#define SPEED_MAX_OVERALL 300
#define DELAY_MAX_OVERALL 300
#define DELAY_MIN_OVERALL 10
uint16_t Delay_Convert(uint16_t speed)
{
    if(speed>SPEED_MAX_OVERALL)
    {
        return DELAY_MIN_OVERALL;
    }
    return 300-speed;
}

void PID_Interatct(bool targetDir,float target,float yawkeep)
{
    Car_GoDis_Flag=targetDir;
    PID.target_yaw=yawkeep;
    if(targetDir)
    {
        PID.target_x=target;
    }
    else
    {
        PID.target_y=target;
    }
    Car_Run_Flag=1;
    while(Car_Run_Flag)
    {
        PIDSpeedControl();
    }
}

void PID_ARR_Dec()
{
    if(!Car_Run_Flag)
	{
		return;
	}
    if(Car_GoDis_Flag)
    {
        if(PID.current_x<PID.target_x+0.5 && PID.current_x>PID.target_x-0.5)
        {
            Car_Run_Flag=0;
        }
    }
    else
    {
         if(PID.current_y<PID.target_y+0.5 && PID.current_y>PID.target_y-0.5)
        {
            Car_Run_Flag=0;
        }
    }
}

#define PID_YAWKEEP_DELAY 100

void PID_yaw_Keep()
{
    Motortot_RotTo(PID.target_yaw,PID_YAWKEEP_DELAY);
    Motortot_RotTo(PID.target_yaw,PID_YAWKEEP_DELAY);
}

void PIDSpeedControl()
{
	if(!Car_Run_Flag)
	{
		return;
	}
	//PID.current_yaw=OPS.zangle;
	//yaw keeping
	if(Car_GoDis_Flag)
	{
		PID.current_x=OPS.pos_x;
		PID.error_x=PID.target_x-PID.current_x;
		PID.errortot_x+=PID.error_x;
		PID.erroradd_x=PID.error_x-PID.errorlast_x;
		PID.errorlast_x=PID.current_x;
		PID.speed_output=(uint16_t)(PID_SPEED_KP*(PID_KP*PID.error_x+PID_KI*PID.errortot_x+PID_KD*PID.erroradd_x));
        if(PID.current_x>PID.target_x)
        {
            Motortot_SetDir_Left();
        }
        else
        {
            Motortot_SetDir_Right();
        }
	}
	else
	{
		PID.current_y=OPS.pos_y;
		PID.error_y=PID.target_y-PID.current_y;
		PID.errortot_y+=PID.error_y;
		PID.erroradd_y=PID.error_y-PID.errorlast_y;
		PID.errorlast_y=PID.current_y;
		PID.speed_output=(uint16_t)(PID_SPEED_KP*(PID_KP*PID.error_y+PID_KI*PID.errortot_y+PID_KD*PID.erroradd_y));
        if(PID.current_y>PID.target_y)
        {
            Motortot_SetDir_Backward();
        }
        else
        {
            Motortot_SetDir_Forward();
        }
	}
	if(PID.speed_output>PID.speed_max)
	{
		PID.speed_output=PID.speed_max;
	}
    Motortot_StpRun(25,Delay_Convert(PID.speed_output));
}
