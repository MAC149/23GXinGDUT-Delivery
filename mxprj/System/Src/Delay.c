#include "Delay.h"

void for_delay_us(uint32_t us)
{
    uint32_t Delay = us * 84/4;
    do
    {
        __NOP();
    }
    while (Delay --);
}

void HAL_Delay_us(uint16_t us)
{
    uint16_t differ=0xffff-us-5;                    //设定定时器计数器起始值​
    __HAL_TIM_SET_COUNTER(&htim6,differ);
    HAL_TIM_Base_Start(&htim6);                     //启动定时器
 while(differ<0xffff-6)                             //补偿，判断
 {
  differ=__HAL_TIM_GET_COUNTER(&htim6);             //查询计数器的计数值
 }
 HAL_TIM_Base_Stop(&htim6);
}


//Counter Mode设为Down
//Counter Period设为0,其他保持不变
volatile bool elapsed = false; //用于判断设置的计数值是否耗尽（向下计数模式），耗尽时，在中断回调中会设置为true

void setState(bool state)
{
    elapsed = state;
}

bool getState()
{
    return elapsed;
}

void usDelay(uint32_t time)
{
    __HAL_TIM_SetCounter(&htim6,time); //设置计数值
     setState(false);                  
     HAL_TIM_Base_Start_IT(&htim6);     //开启定时器
     while(!getState());                //判断计数值是否耗尽
     HAL_TIM_Base_Stop_IT(&htim6);      //关闭定时器
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6) {
        setState(true);
    }
    
}