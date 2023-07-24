#include "Motor.h"
#define PUL_DIS_1MM 25

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
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_RESET);
}

void Motortot_SetDir_Backward()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_SET);
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
    HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_SET);
}

void Motortot_SetDir_ForRight()
{
    HAL_GPIO_WritePin(MOTORFL_DIR_GPIOX,MOTORFL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(MOTORFR_DIR_GPIOX,MOTORFR_DIR_GPIO_PIN,GPIO_PIN_SET);
    // HAL_GPIO_WritePin(MOTORBL_DIR_GPIOX,MOTORBL_DIR_GPIO_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTORBR_DIR_GPIOX,MOTORBR_DIR_GPIO_PIN,GPIO_PIN_SET);
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

void Motortot_StpRun(uint16_t time,uint16_t delay_us)//may less efficiency
{
    for(uint16_t i=0;i<time;i++)
    {
        HAL_GPIO_TogglePin(MOTORFL_STP_GPIOX,MOTORFL_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORFR_STP_GPIOX,MOTORFR_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORBL_STP_GPIOX,MOTORBL_STP_GPIO_PIN);
        HAL_GPIO_TogglePin(MOTORBR_STP_GPIOX,MOTORBR_STP_GPIO_PIN);
        HAL_Delay_us(delay_us);
    }
}

void Motortot_StpRunWR(uint16_t time,uint16_t delay_us)
{
    for(uint16_t i=0;i<time/2;i++)
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
    float temp[2];
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
        temp[1]=target_yaw;
    }
    else
    {
        temp[1]=-target_yaw;
    }
    if(target_yaw == 180.0 || target_yaw == -180.0)
    {
        while(1)
        {
            if((OPS.zangle > temp[0] + 0.5)&& (OPS.zangle < 0))
            {
                Motortot_SetDir_RotLeft();
                Motortot_StpRun(50,delay_us);
            }
            else if((OPS.zangle < temp[1] - 0.5)&&(OPS.zangle >= 0))
            {
                Motortot_SetDir_RotRight();
                Motortot_StpRun(50,delay_us);
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
            if(OPS.zangle > temp[0] + 0.5)
            {
                Motortot_SetDir_RotLeft();
                Motortot_StpRun(50,delay_us);
            }
            else if(OPS.zangle< temp[1] - 0.5)
            {
                Motortot_SetDir_RotRight();
                Motortot_StpRun(50,delay_us);
            }
            else
            {
                break;
            }
         }
    } 
}



void Motortot_GoDis(float disx,float disy,float pointyaw)
{
}