#include<math.h>
#include "imu.h"
#include <string.h>
#include "OLED.h"

IMUData_Packet_t IMUData_Packet;
AHRSData_Packet_t AHRSData_Packet;
u8 ttl_receive;
u8 Fd_data[64];
u8 Fd_rsimu[64];
u8 Fd_rsahrs[56];
int rs_imutype =0;
int rs_ahrstype =0;
extern int Time_count;
u8 Usart_Receive;
bool IMU_Rec_Flag=0;

void imuRecStart()
{
	IMU_Rec_Flag=0;
	ttl_receive = 1;
	HAL_UART_Receive_IT(&IMU_UART, &Usart_Receive, 1);
}


static u8 Count = 0;
static u8 rs_count = 0;
static u8 last_rsnum = 0;
static u8 rsimu_flag = 0;
static u8 rsacc_flag = 0;
void imuRec(void)
{
	{

		// RS485_RX_RE=0;
		// RS485_RX_DE=0;
		
		Fd_data[Count] = Usart_Receive; // 串口数据填入数组

		if (((last_rsnum == FRAME_END) && (Usart_Receive == FRAME_HEAD)) || Count > 0)
		{
			rs_count = 1;
			Count++;
			if ((Fd_data[1] == TYPE_IMU) && (Fd_data[2] == IMU_LEN))
				rsimu_flag = 1;
			if ((Fd_data[1] == TYPE_AHRS) && (Fd_data[2] == AHRS_LEN))
				rsacc_flag = 1;
		}
		else
			Count = 0;
		last_rsnum = Usart_Receive;

		if (rsimu_flag == 1 && Count == IMU_RS) // 将本帧数据保存至Fd_rsimu数组中
		{
			Count = 0;
			rsimu_flag = 0;
			rs_imutype = 1;
			if (Fd_data[IMU_RS - 1] == FRAME_END) // 帧尾校验
				memcpy(Fd_rsimu, Fd_data, sizeof(Fd_data));
		}
		if (rsacc_flag == 1 && Count == AHRS_RS) //
		{
			Count = 0;
			rsacc_flag = 0;
			rs_ahrstype = 1;
			if (Fd_data[AHRS_RS - 1] == FRAME_END)
				{memcpy(Fd_rsahrs, Fd_data, sizeof(Fd_data));}
			for (int i = 0; i < sizeof(Fd_data); i++)
				{Fd_data[i] = 0;}
			IMU_Rec_Flag=1;
			return;
		}
		if(!IMU_Rec_Flag)
		{
			HAL_UART_Receive_IT(&IMU_UART, &Usart_Receive, 1);
		}	
	}
}


/*******************************
16进制转浮点型数据
*******************************/
u8 TTL_Hex2Dec(void)  
{
	u8 i;
	 if(rs_ahrstype==1)
	{
		if(Fd_rsahrs[1]==TYPE_AHRS&&Fd_rsahrs[2]==AHRS_LEN)
		{	
		AHRSData_Packet.RollSpeed=DATA_Trans(Fd_rsahrs[7],Fd_rsahrs[8],Fd_rsahrs[9],Fd_rsahrs[10]);       //横滚角速度
		AHRSData_Packet.PitchSpeed=DATA_Trans(Fd_rsahrs[11],Fd_rsahrs[12],Fd_rsahrs[13],Fd_rsahrs[14]);   //俯仰角速度
		AHRSData_Packet.HeadingSpeed=DATA_Trans(Fd_rsahrs[15],Fd_rsahrs[16],Fd_rsahrs[17],Fd_rsahrs[18]); //偏航角速度
			
    AHRSData_Packet.Roll=DATA_Trans(Fd_rsahrs[19],Fd_rsahrs[20],Fd_rsahrs[21],Fd_rsahrs[22]);      //横滚角
		AHRSData_Packet.Pitch=DATA_Trans(Fd_rsahrs[23],Fd_rsahrs[24],Fd_rsahrs[25],Fd_rsahrs[26]);     //俯仰角
		AHRSData_Packet.Heading=DATA_Trans(Fd_rsahrs[27],Fd_rsahrs[28],Fd_rsahrs[29],Fd_rsahrs[30]);	 //偏航角
			
		AHRSData_Packet.Qw=DATA_Trans(Fd_rsahrs[31],Fd_rsahrs[32],Fd_rsahrs[33],Fd_rsahrs[34]);  //四元数
		AHRSData_Packet.Qx=DATA_Trans(Fd_rsahrs[35],Fd_rsahrs[36],Fd_rsahrs[37],Fd_rsahrs[38]);
		AHRSData_Packet.Qy=DATA_Trans(Fd_rsahrs[39],Fd_rsahrs[40],Fd_rsahrs[41],Fd_rsahrs[42]);
		AHRSData_Packet.Qz=DATA_Trans(Fd_rsahrs[43],Fd_rsahrs[44],Fd_rsahrs[45],Fd_rsahrs[46]);
		AHRSData_Packet.Timestamp=timestamp(Fd_rsahrs[47],Fd_rsahrs[48],Fd_rsahrs[49],Fd_rsahrs[50]);   //时间戳
    // AHRSData2PC();
		}
	rs_ahrstype=0;
 }
	if(rs_imutype==1)
	{
		if(Fd_rsimu[1]==TYPE_IMU&&Fd_rsimu[2]==IMU_LEN)
		{
		IMUData_Packet.gyroscope_x=DATA_Trans(Fd_rsimu[7],Fd_rsimu[8],Fd_rsimu[9],Fd_rsimu[10]);  //角速度
		IMUData_Packet.gyroscope_y=DATA_Trans(Fd_rsimu[11],Fd_rsimu[12],Fd_rsimu[13],Fd_rsimu[14]);
		IMUData_Packet.gyroscope_z=DATA_Trans(Fd_rsimu[15],Fd_rsimu[16],Fd_rsimu[17],Fd_rsimu[18]);
			
		IMUData_Packet.accelerometer_x=DATA_Trans(Fd_rsimu[19],Fd_rsimu[20],Fd_rsimu[21],Fd_rsimu[22]);  //线加速度
		IMUData_Packet.accelerometer_y=DATA_Trans(Fd_rsimu[23],Fd_rsimu[24],Fd_rsimu[25],Fd_rsimu[26]);
		IMUData_Packet.accelerometer_z=DATA_Trans(Fd_rsimu[27],Fd_rsimu[28],Fd_rsimu[29],Fd_rsimu[30]);

		IMUData_Packet.magnetometer_x=DATA_Trans(Fd_rsimu[31],Fd_rsimu[32],Fd_rsimu[33],Fd_rsimu[34]);  //磁力计数据
		IMUData_Packet.magnetometer_y=DATA_Trans(Fd_rsimu[35],Fd_rsimu[36],Fd_rsimu[37],Fd_rsimu[38]);
		IMUData_Packet.magnetometer_z=DATA_Trans(Fd_rsimu[39],Fd_rsimu[40],Fd_rsimu[41],Fd_rsimu[42]);
			
		IMUData_Packet.Timestamp=timestamp(Fd_rsimu[55],Fd_rsimu[56],Fd_rsimu[57],Fd_rsimu[58]);   //时间戳
    // IMUData2PC();
		}
		rs_imutype=0;
 }
return 0;
}
/*************
实现16进制的can数据转换成浮点型数据
****************/
float DATA_Trans(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4)
{
  long long transition_32;
	float tmp=0;
	int sign=0;
	int exponent=0;
	float mantissa=0;
  transition_32 = 0;
  transition_32 |=  Data_4<<24;   
  transition_32 |=  Data_3<<16; 
	transition_32 |=  Data_2<<8;
	transition_32 |=  Data_1;
  sign = (transition_32 & 0x80000000) ? -1 : 1;//符号位
	//先右移操作，再按位与计算，出来结果是30到23位对应的e
	exponent = ((transition_32 >> 23) & 0xff) - 127;
	//将22~0转化为10进制，得到对应的x系数 
	mantissa = 1 + ((float)(transition_32 & 0x7fffff) / 0x7fffff);
	tmp=sign * mantissa * pow(2, exponent);
	return tmp;
}
long long timestamp(u8 Data_1,u8 Data_2,u8 Data_3,u8 Data_4)
{
  u32 transition_32;
  transition_32 = 0;
  transition_32 |=  Data_4<<24;   
  transition_32 |=  Data_3<<16; 
	transition_32 |=  Data_2<<8;
	transition_32 |=  Data_1;
	return transition_32;
}
void AHRSData2PC(void)
{
 	 printf("AHRS: The RollSpeed =  %f\r\n",AHRSData_Packet.RollSpeed);
	 printf("AHRS: The PitchSpeed =  %f\r\n",AHRSData_Packet.PitchSpeed);
   printf("AHRS: The HeadingSpeed =  %f\r\n",AHRSData_Packet.HeadingSpeed);
   printf("AHRS: The Roll =  %f\r\n",AHRSData_Packet.Roll);
   printf("AHRS: The Pitch =  %f\r\n",AHRSData_Packet.Pitch);
   printf("AHRS: The Heading =  %f\r\n",AHRSData_Packet.Heading);
   printf("AHRS: The Quaternion.Qw =  %f\r\n",AHRSData_Packet.Qw);
   printf("AHRS: The Quaternion.Qx =  %f\r\n",AHRSData_Packet.Qx);
   printf("AHRS: The Quaternion.Qy =  %f\r\n",AHRSData_Packet.Qy);
   printf("AHRS: The Quaternion.Qz =  %f\r\n",AHRSData_Packet.Qz);
   printf("AHRS: The Timestamp =  %d\r\n",AHRSData_Packet.Timestamp);
}
void IMUData2PC(void)
{
   //printf("Now start sending IMU data.\r\n");
	printf("IMU: The gyroscope_x =  %f\r\n",IMUData_Packet.gyroscope_x);
	 printf("IMU:The gyroscope_y =  %f\r\n",IMUData_Packet.gyroscope_y);
   printf("IMU:The gyroscope_z =  %f\r\n",IMUData_Packet.gyroscope_z);
   printf("IMU:The accelerometer_x =  %f\r\n",IMUData_Packet.accelerometer_x);
   printf("IMU:The accelerometer_y =  %f\r\n",IMUData_Packet.accelerometer_y);
   printf("IMU:The accelerometer_z =  %f\r\n",IMUData_Packet.accelerometer_z);
   printf("IMU:The magnetometer_x =  %f\r\n",IMUData_Packet.magnetometer_x);
   printf("IMU:The magnetometer_y =  %f\r\n",IMUData_Packet.magnetometer_y);
   printf("IMU:The magnetometer_z =  %f\r\n",IMUData_Packet.magnetometer_z);
   printf("IMU:The Timestamp =  %d\r\n",IMUData_Packet.Timestamp);
	 //printf("Now the data of IMU has been sent.\r\n");

}

double IMU_yawData=0;

double IMU_yawExclusive()
{
	imuRecStart();
   u8 i;
   while(!IMU_Rec_Flag);
   if (rs_ahrstype == 1)
   {
		if (Fd_rsahrs[1] == TYPE_AHRS && Fd_rsahrs[2] == AHRS_LEN)
		{
		AHRSData_Packet.Heading = DATA_Trans(Fd_rsahrs[27], Fd_rsahrs[28], Fd_rsahrs[29], Fd_rsahrs[30]);  // 偏航角
		AHRSData_Packet.Timestamp = timestamp(Fd_rsahrs[47], Fd_rsahrs[48], Fd_rsahrs[49], Fd_rsahrs[50]); // 时间戳
		// AHRSData2PC();
		}
		rs_ahrstype = 0;
   }
   return AHRSData_Packet.Heading*180.0f/pai;
}

double IMU_yawDataUpdate()
{
	IMU_yawData=IMU_yawExclusive();
	return IMU_yawData;
}

void OLED_ShowYaw()
{
	// IMU_yawDataUpdate();
	OLED_ShowFNum(1,5,IMU_yawData,7,16);
}