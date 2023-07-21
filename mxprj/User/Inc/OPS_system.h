#ifndef __OPS_SYSTEM_H
#define __OPS_SYSTEM_H
#include "GeneralDef.h"
#define OPS_auart_handle			huart1	

#define opsRxbuff_LENGTH 		50	
#define opsOrder_LENGTH 		28	

typedef struct 
{
	uint8_t* pucRxbuff;
	
	float pos_x;		//x坐标
	float pos_y;		//y坐标
	float zangle;		//z角度
	float xangle;		//x角度
	float yangle;		//y角度
	float w_z;			
	
	void (*Update_all)(void);
	void (*Update_X)(float New_X);
	void (*Update_Y)(float New_Y);
	void (*Update_A)(float New_A);

	void (*OPS_Init)(void);
	void (*Protocol_Analysis)(void);
}OPS_t;

extern OPS_t OPS;


#endif
