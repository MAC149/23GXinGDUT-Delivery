#ifndef _IMU_H_
#define _IMU_H_

#include "stdio.h"
#include "GeneralDef.h"

#define IMU_UART huart1

#define FRAME_HEADER      0X7B //Frame_header //֡ͷ
#define FRAME_TAIL        0X7D //Frame_tail   //֡β
#define SEND_DATA_SIZE    24
#define RECEIVE_DATA_SIZE 11
#define IMU_RS 64
#define AHRS_RS 56
#define INSGPS_RS 80
//FDlink candata
#define FRAME_HEAD 0xfc
#define FRAME_END 0xfd
#define TYPE_IMU 0x40
#define TYPE_AHRS 0x41
#define TYPE_INSGPS 0x42
#define TYPE_GROUND 0xf0
#define IMU_LEN  0x38   //56+8  8组数据
#define AHRS_LEN 0x30   //48+8  7组数据
#define INSGPS_LEN 0x42 //72+8  10组数据
#define IMU_CAN 9
#define AHRS_CAN 8
#define INSGPS_CAN 11
//#define RS485_RX_DE		PAout(11)	//485模式控制.0,接收;1,发送.
//#define RS485_RX_RE		PAout(12)	//485模式控制.0,接收;1,发送.
typedef struct IMUData_Packet_t{
		float gyroscope_x;          //unit: rad/s
		float gyroscope_y;          //unit: rad/s
		float gyroscope_z;          //unit: rad/s
		float accelerometer_x;      //m/s^2
		float accelerometer_y;      //m/s^2
		float accelerometer_z;      //m/s^2
		float magnetometer_x;       //mG
		float magnetometer_y;       //mG
		float magnetometer_z;       //mG
		float imu_temperature;      //C
		float Pressure;             //Pa
		float pressure_temperature; //C
		u32 Timestamp;          //us
} IMUData_Packet_t;

typedef struct AHRSData_Packet_t
{
	float RollSpeed;   //unit: rad/s
	float PitchSpeed;  //unit: rad/s
	float HeadingSpeed;//unit: rad/s
	float Roll;        //unit: rad
	float Pitch;       //unit: rad
	float Heading;     //unit: rad
	float Qw;//w          //Quaternion
	float Qx;//x
	float Qy;//y
	float Qz;//z
	u32 Timestamp; //unit: us
}AHRSData_Packet_t;

extern u8 ttl_receive;

extern IMUData_Packet_t IMUData_Packet;
extern AHRSData_Packet_t AHRSData_Packet;


long long timestamp(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4);
void AHRSData2PC(void);
void IMUData2PC(void);

void imuRec(void);

u8 TTL_Hex2Dec(void);  
float DATA_Trans(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4);
void imuRecStart();
double IMU_yawExclusive();

#endif // !_IMU_H_
