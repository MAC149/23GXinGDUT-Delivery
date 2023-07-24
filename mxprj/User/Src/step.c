#include "step.h"

void Full_Step()
{
    OLED_Init();
    OPS.OPS_Init();
    OLED_ShowString(1,1,"OPSx:",16);
    OLED_ShowString(2,1,"OPSy:",16);
    OLED_ShowString(3,1,"OPSyaw:",16);
// 	while(1)
// 	{
// 		if(Key_Scan(&KEY1) == KEY_ON)
// 		{
// 			GUI_ShowCHinese(16,16,16,(uint8_t*)"按下键一启动",1);
// 			break;
// 		}
		
// 	}
// 	LED_TogglePin;
// //	HAL_Delay(1500);
// 	OLED_Clear(0);

// 	HAL_TIM_Base_Start_IT(&htim6);
// 	HAL_TIM_Base_Start_IT(&htim7);
// 	move_mode = 1;
// 	target_x = -400;
// 	target_y = 600; 
// 	HAL_Delay(500);
// 	target_yaw = 0;

// 	car_go(ModeOps,target_x,target_y,target_yaw);
// //	
// 	/*先关，会影响扫码，因为用的模拟IIC*/	
// 	HAL_TIM_Base_Stop_IT(&htim6);
// 	HAL_TIM_Base_Stop_IT(&htim7);

// 	/*扫码*/
// 	Scan.scan_getsituation();

// 	/*开启PID闭环的定时器*/
// 	HAL_TIM_Base_Start_IT(&htim6);
// 	HAL_TIM_Base_Start_IT(&htim7);

// 	/*移动到物料区*/
// 	move_mode = 1;
// 	target_x = -650;target_y = 1600;  
// 	HAL_Delay(1000);
// 	target_yaw = 0;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
// 	HAL_TIM_Base_Stop_IT(&htim6);
// 	HAL_TIM_Base_Stop_IT(&htim7);
// 	/*openmv识别*/
// 	Openmv.MV_Recdata();
// 	HAL_TIM_Base_Start_IT(&htim6);
// 	HAL_TIM_Base_Start_IT(&htim7);
	
// 	/*移动到原料区工区*/
// //	move_mode = 1;
// //	target_x = -300;
// //	target_y = 1635;
// //	target_yaw = -90;
// //	car_go(ModeOps,target_x,target_y,target_yaw);
// 	move_mode = 1;
// 	target_x = -780;target_y = 1630;  
// 	HAL_Delay(1000);
// 	target_yaw = -90;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
// //	while(1);
// //	yaw_Spin_90(-1);
// //	Y_fast_move(-70);
// 	car_go(ModeHui,0,0,-90);
// 	Y_fast_move(265);
// 	lobotGetMaterial(0,0);

// 	/*移动到粗加工区*/
// 	move_mode = 1;
// 	target_x = -1100;
// 	target_y = 1650;
// 	target_yaw = 0;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
// 	car_go(ModeHui,0,0,target_yaw);
// 	OPS.Update_A(0);
// 	Y_fast_move(28);
// 	lobotPlaceMaterial(0,1);
	
// 	/*移动到精加工区*/

// 	move_mode = 1;
// 	target_x = -1680;
// 	target_y = 1060;
// 	HAL_Delay(1000);
// 	target_yaw = 90;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
// 	car_go(ModeHui,target_x-50,0,target_yaw);
// 	OPS.Update_A(90);
// 	Y_fast_move(-96);

// 	lobotPlaceMaterial(0,0);

// 	/*回到物料区*/	
// 	move_mode = 1;
// 	target_yaw = -90;
// 	target_y = 1630;  
// 	HAL_Delay(500);
// 	target_x = -780;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
// 	car_go(ModeHui,0,0,target_yaw);
// 	lobotGetMaterial(0,4);

// 	/*移动到粗加工区*/
// //	OPS.Update_A(-5);
// 	move_mode = 1;
// 	target_x = -1100;
// 	target_y = 1670;
// 	target_yaw = 0;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
// 	car_go(ModeHui,0,0,target_yaw);
// 	OPS.Update_A(0);
// 	Y_fast_move(28);
// 	lobotPlaceMaterial(4,1);

// 	/*移动到精加工区*/
// 	move_mode = 1;
// 	target_y = 1060;
// 	target_x = -1680;
// 	HAL_Delay(1000);
// 	target_yaw = 90;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
// 	car_go(ModeHui,target_x-50,0,target_yaw);
// 	OPS.Update_A(90);
// 	Y_fast_move(-115);
// 	lobotPlaceMaterial(4,0);
// 	/*到终点*/
// 	OPS.Update_all();		//将全部坐标清0
// 	move_mode = 1; 
	
// 	target_y = 440;
// 	target_yaw = 90;
// 	lobotControl(95,95,45,130,5,400,5);			//上来
// 	HAL_Delay(500);
// 	target_x = -1060;
// 	car_go(ModeOps,target_x,target_y,target_yaw);
}
