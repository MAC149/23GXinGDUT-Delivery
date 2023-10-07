#include "rader.h"
#include <string.h>

extern u16 receive_cnt;

PointDataProcessDef PointDataProcess[50] ;//更新50个数据
LiDARFrameTypeDef Pack_Data;
 u8 data_cnt = 0;


static u8 state = 0;//状态位	
static u8 crc_sum = 0;//校验和
static u8 cnt = 0;//用于一帧16个点的计数
u8 temp_data;
bool Rader_RecFlag=0;

void Rader_RecStart()
{
    Rader_RecFlag=0;
    HAL_UART_Receive_IT(&RADER_UART,&temp_data,1);
}

void Rader_RecStop()
{
    // Rader_RecFlag=0;
}

void Rader_Rec()
{
    if (state > 6)
    {
        if (state < 55)
        {
            if (state % 3 == 1) // 序号7,10,13....52
            {
                Pack_Data.point[cnt].distance_h = temp_data; // 16个点的距离数据，高字节
                state++;
                crc_sum += temp_data;
            }
            else if (state % 3 == 2) // 序号8,11,14...53
            {
                Pack_Data.point[cnt].distance_l = temp_data; // 16个点的距离数据，低字节
                state++;
                crc_sum += temp_data;
            }
            else // 序号9,12,15...54
            {
                Pack_Data.point[cnt].Strong = temp_data; // 16个点的强度数据
                state++;
                crc_sum += temp_data;
                cnt++; // 开始下一个数据
            }
        }
        else
        {
            switch (state)
            {
            case 55:
                Pack_Data.end_angle_h = temp_data;
                state++;
                crc_sum += temp_data;
                break;
            case 56:
                Pack_Data.end_angle_l = temp_data;
                state++;
                crc_sum += temp_data;
                break;
            case 57: // 校验
                Pack_Data.crc = temp_data;
                state = 0;
                cnt = 0;
                if (crc_sum == Pack_Data.crc) // 这里已完成数据的接收，Pack_Data是接收到的数据
                {
                    // receive_cnt++;//成功接收的次数加1
                    //  data_process();//数据处理，校验正确不断刷新存储的数据
                }
                else
                {
                    memset(&Pack_Data, 0, sizeof(Pack_Data)); // 清零
                }
                crc_sum = 0; // 校验和清零
                Rader_RecFlag = 1;
                break;
            default:
                break;
            }
        }
    }
    else
    {
        switch (state)
        {
        case 0:
            if (temp_data == HEADER_0) // 头固定
            {
                Pack_Data.header_0 = temp_data;
                state++;
                // 校验
                crc_sum += temp_data;
            }
            else
                state = 0, crc_sum = 0;
            break;
        case 1:
            if (temp_data == HEADER_1) // 头固定
            {
                Pack_Data.header_1 = temp_data;
                state++;
                crc_sum += temp_data;
            }
            else
                state = 0, crc_sum = 0;
            break;
        case 2:
            if (temp_data == Length_) // 字长固定
            {
                Pack_Data.ver_len = temp_data;
                state++;
                crc_sum += temp_data;
            }
            else
                state = 0, crc_sum = 0;
            break;
        case 3:
            Pack_Data.speed_h = temp_data;
            state++;
            crc_sum += temp_data;
            break;
        case 4:
            Pack_Data.speed_l = temp_data;
            state++;
            crc_sum += temp_data;
            break;
        case 5:
            Pack_Data.start_angle_h = temp_data;
            state++;
            crc_sum += temp_data;
            break;
        case 6:
            Pack_Data.start_angle_l = temp_data;
            state++;
            crc_sum += temp_data;
            break;
        default:
            break;
        }
    }
    if (!Rader_RecFlag)
    {
        HAL_UART_Receive_IT(&RADER_UART, &temp_data, 1);
    }
}

//这里做一定的简化处理，只要前方100度范围的点（可自行更改），避障算法可使用PointDataProcess这个变量进行判断
void data_process(void)//数据处理函数，小车前进时避障，只需前方的点的数据
{
	
	u8 i;
	u32 distance_sum = 0;//16个点距离和
	u16 average_distance = 0;//16个点的平均距离
	float start_angle = (((u16)Pack_Data.start_angle_h<<8)+Pack_Data.start_angle_l)/100.0;//计算一帧16个点的开始角度
	float end_angel = (((u16)Pack_Data.end_angle_h<<8)+Pack_Data.end_angle_l)/100.0;//结束角度
	float area_angel;//定义一帧数据平均角度
	if(start_angle>end_angel) end_angel +=360;
	area_angel = start_angle+(end_angel - start_angle)/2;
	if(area_angel>=360) area_angel -= 360;//359度到0度边缘需做处理
	if(area_angel>310||area_angel<50)//只提取前方范围内的点,一共100度范围
	{
		for(i = 0;i<16;i++)
		{
			distance_sum += ((u16)Pack_Data.point[i].distance_h<<8)+Pack_Data.point[i].distance_l;
		}
		average_distance = distance_sum/16;//平均的距离
		
		PointDataProcess[data_cnt].angle = area_angel;//合成一个数据
		PointDataProcess[data_cnt].distance = average_distance;//50个数据作为避障的判断
		data_cnt++;
		if(data_cnt == 50)
			data_cnt = 0;

	}
//	distance_area[(u8)(area_angel/10)] = average_distance;
	

}





