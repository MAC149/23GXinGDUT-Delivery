#ifndef __RADER_H_
#define __RADER_H_
#include "GeneralDef.h"	  	




#define HEADER_0 0xA5
#define HEADER_1 0x5A
#define Length_ 0x3A

#define POINT_PER_PACK 16

#define RADER_UART huart4


typedef struct PointData
{
	uint8_t distance_h;
	uint8_t distance_l;
	uint8_t Strong;

}LidarPointStructDef;

typedef struct PackData
{
	uint8_t header_0;//
	uint8_t header_1;//
	uint8_t ver_len;
	
	uint8_t speed_h;
	uint8_t speed_l;
	uint8_t start_angle_h;
	uint8_t start_angle_l;	
	LidarPointStructDef point[POINT_PER_PACK];
	uint8_t end_angle_h;
	uint8_t end_angle_l;
	uint8_t crc;
}LiDARFrameTypeDef;

typedef struct PointDataProcess_
{
	u16 distance;
	float angle;
}PointDataProcessDef;



void data_process(void);

extern PointDataProcessDef PointDataProcess[50] ;//更新50个数据
extern LiDARFrameTypeDef Pack_Data;
extern u8 data_cnt;
#endif

