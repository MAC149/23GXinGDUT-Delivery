#include "Delay.h"

void for_delay_us(uint32_t us)
{
    uint32_t Delay = us * 168/4;
    do
    {
        __NOP();
    }
    while (Delay --);
}

void Delay_Init()
{
    HAL_TIM_Base_Start_IT(&htim6);
    //HAL_TIM_Base_Start_IT(&htim7);
}

void PIDT_Stop()
{
    HAL_TIM_Base_Stop_IT(&htim6);
    HAL_TIM_Base_Stop_IT(&htim7);
}

void TIM6_Delay_us(uint32_t us) 
{
    uint16_t startCnt = __HAL_TIM_GET_COUNTER(&htim6);
    while ((__HAL_TIM_GET_COUNTER(&htim6) - startCnt) <= us);
}


void HAL_Delay_usST(uint16_t us)
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

void HAL_Delay_us(uint32_t us)
{
    uint32_t ticks;
    uint32_t told;
    uint32_t tnow;
    uint32_t tcnt = 0;
    uint32_t reload;
       
	reload = SysTick->LOAD;                
    ticks = us * (SystemCoreClock / 1000000);	 /* 需要的节拍数 */  
    
    tcnt = 0;
    told = SysTick->VAL;             /* 刚进入时的计数器值 */
 
    while (1)
    {
        tnow = SysTick->VAL;    
        if (tnow != told)
        {    
            /* SYSTICK是一个递减的计数器 */    
            if (tnow < told)
            {
                tcnt += told - tnow;    
            }
            /* 重新装载递减 */
            else
            {
                tcnt += reload - tnow + told;    
            }        
            told = tnow;
 
            /* 时间超过/等于要延迟的时间,则退出 */
            if (tcnt >= ticks)
            {
            	break;
            }
        }  
    }
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
