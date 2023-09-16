/*******************************************************************************
* 文件名： LobotServoController.c
* 作者： 深圳乐幻索尔科技
* 日期：20160806
* LSC系列舵机控制板二次开发示例
*******************************************************************************/

#include "LobotServoController.h"
#include <stdarg.h>
#include <string.h>


#define GET_LOW_BYTE(A) ((uint8_t)(A))
//宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//宏函数 获得A的高八位

uint8_t LobotTxBuf[128];  //发送缓存
uint8_t LobotRxBuf[16];
static uint8_t UART_RX_BUF[16];

//通信结构体初始化
LobotServoUart_typedef LobotServoUart = {0,0,0,0,false,UART_RX_BUF};

//舵机结构体初始化
LobotServo servos[5] = 
{
	{0,1500},
	{1,1600},		//大于1500是往下
	{2,800},		//大于1500是往外
	{3,2000},		//大于1500是往里
	{4,600}
};

/*********************************************************************************
 * Function:  lobotServo_init
 * Description： 初始化
 * Parameters:   无
 * Return:       无返回
 * Others:
 **********************************************************************************/
void lobotServo_init(void)
{
	HAL_UART_Receive_IT(&g_servoControl_uart_handle,&LobotServoUart.ucDatabuf,1);
	//lobotServos_moveByArray(servos,5,2000);
}
/*********************************************************************************
 * Function:  lobotServo_move
 * Description： 控制单个舵机转动
 * Parameters:   sevoID:舵机ID，Position:目标位置,Time:转动时间
                    舵机ID取值:0<=舵机ID<=31,Time取值: Time > 0
 * Return:       无返回
 * Others:
 **********************************************************************************/
void lobotServo_move(uint8_t servoID, uint16_t Position, uint16_t Time)
{
	if (servoID > 31 || !(Time > 0)) {  //舵机ID不能打于31,可根据对应控制板修改
		return;
	}
	LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;    //填充帧头
	LobotTxBuf[2] = 8;
	LobotTxBuf[3] = CMD_SERVO_MOVE;           //数据长度=要控制舵机数*3+5，此处=1*3+5//填充舵机移动指令
	LobotTxBuf[4] = 1;                        //要控制的舵机个数
	LobotTxBuf[5] = GET_LOW_BYTE(Time);       //取得时间的低八位
	LobotTxBuf[6] = GET_HIGH_BYTE(Time);      //取得时间的高八位
	LobotTxBuf[7] = servoID;                  //舵机ID
	LobotTxBuf[8] = GET_LOW_BYTE(Position);   //取得目标位置的低八位
	LobotTxBuf[9] = GET_HIGH_BYTE(Position);  //取得目标位置的高八位

	HAL_UART_Transmit(&g_servoControl_uart_handle,LobotTxBuf,10,1000);
//	uartWriteBuf(LobotTxBuf, 10);
}

/*********************************************************************************
 * Function:  lobotServos_moveByArray
 * Description： 控制多个舵机转动
 * Parameters:   servos[]:舵机结体数组，Num:舵机个数,Time:转动时间
                    0 < Num <= 32,Time > 0
 * Return:       无返回
 * Others:
 **********************************************************************************/
void lobotServos_moveByArray(LobotServo servos[], uint8_t Num, uint16_t Time)
{
	uint8_t index = 7;
	uint8_t i = 0;

	if (Num < 1 || Num > 32 || !(Time > 0)) {
		return;                                          //舵机数不能为零和大与32，时间不能为零
	}
	LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;      //填充帧头
	LobotTxBuf[2] = Num * 3 + 5;                       //数据长度 = 要控制舵机数*3+5
	LobotTxBuf[3] = CMD_SERVO_MOVE;                    //填充舵机移动指令
	LobotTxBuf[4] = Num;                               //要控制的舵机个数
	LobotTxBuf[5] = GET_LOW_BYTE(Time);                //取得时间的低八位
	LobotTxBuf[6] = GET_HIGH_BYTE(Time);               //取得时间的高八位

	for (i = 0; i < Num; i++) {                        //循环填充舵机ID和对应目标位置
		LobotTxBuf[index++] = servos[i].ID;              //填充舵机ID
		LobotTxBuf[index++] = GET_LOW_BYTE(servos[i].Position); //填充目标位置低八位
		LobotTxBuf[index++] = GET_HIGH_BYTE(servos[i].Position);//填充目标位置高八位
	}
	HAL_UART_Transmit(&g_servoControl_uart_handle,LobotTxBuf,LobotTxBuf[2] + 2,1000);
//	uartWriteBuf(LobotTxBuf, LobotTxBuf[2] + 2);             //发送
}

/*********************************************************************************
 * Function:  lobotServos_move
 * Description： 控制多个舵机转动
 * Parameters:   Num:舵机个数,Time:转动时间,...:舵机ID,转动角，舵机ID,转动角度 如此类推
 * Return:       无返回
 * Others:
 **********************************************************************************/
void lobotServos_move(uint8_t Num, uint16_t Time, ...)
{
	uint8_t index = 7;
	uint8_t i = 0;
	uint16_t temp;
	va_list arg_ptr;  //

	va_start(arg_ptr, Time); //取得可变参数首地址
	if (Num < 1 || Num > 32) {
		return;               //舵机数不能为零和大与32，时间不能小于0
	}
	LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;      //填充帧头
	LobotTxBuf[2] = Num * 3 + 5;                //数据长度 = 要控制舵机数 * 3 + 5
	LobotTxBuf[3] = CMD_SERVO_MOVE;             //舵机移动指令
	LobotTxBuf[4] = Num;                        //要控制舵机数
	LobotTxBuf[5] = GET_LOW_BYTE(Time);         //取得时间的低八位
	LobotTxBuf[6] = GET_HIGH_BYTE(Time);        //取得时间的高八位

	for (i = 0; i < Num; i++) {//从可变参数中取得并循环填充舵机ID和对应目标位置
		temp = va_arg(arg_ptr, int);//可参数中取得舵机ID
		LobotTxBuf[index++] = GET_LOW_BYTE(((uint16_t)temp));
		temp = va_arg(arg_ptr, int);  //可变参数中取得对应目标位置
		LobotTxBuf[index++] = GET_LOW_BYTE(((uint16_t)temp)); //填充目标位置低八位
		LobotTxBuf[index++] = GET_HIGH_BYTE(temp);//填充目标位置高八位
	}

	va_end(arg_ptr);  //置空arg_ptr
	
	HAL_UART_Transmit(&g_servoControl_uart_handle,LobotTxBuf,LobotTxBuf[2] + 2,1000);
//	uartWriteBuf(LobotTxBuf, LobotTxBuf[2] + 2);    //发送
}


/*********************************************************************************
 * Function:  lobotServos_runActionGroup
 * Description： 运行指定动作组
 * Parameters:   NumOfAction:动作组序号, Times:执行次数
 * Return:       无返回
 * Others:       Times = 0 时无限循环
 **********************************************************************************/
void lobotServos_runActionGroup(uint8_t numOfAction, uint16_t Times)
{
	LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;  //填充帧头
	LobotTxBuf[2] = 5;                      //数据长度，数据帧除帧头部分数据字节数，此命令固定为5
	LobotTxBuf[3] = CMD_ACTION_GROUP_RUN;   //填充运行动作组命令
	LobotTxBuf[4] = numOfAction;            //填充要运行的动作组号
	LobotTxBuf[5] = GET_LOW_BYTE(Times);    //取得要运行次数的低八位
	LobotTxBuf[6] = GET_HIGH_BYTE(Times);   //取得要运行次数的高八位
	
	HAL_UART_Transmit(&g_servoControl_uart_handle,LobotTxBuf,7,1000);
//	uartWriteBuf(LobotTxBuf, 7);            //发送
}

/*********************************************************************************
 * Function:  lobotServos_stopActionGroup
 * Description： 停止动作组运行
 * Parameters:   Speed: 目标速度
 * Return:       无返回
 * Others:
 **********************************************************************************/
void lobotServos_stopActionGroup(void)
{
	LobotTxBuf[0] = FRAME_HEADER;     //填充帧头
	LobotTxBuf[1] = FRAME_HEADER;
	LobotTxBuf[2] = 2;                //数据长度，数据帧除帧头部分数据字节数，此命令固定为2
	LobotTxBuf[3] = CMD_ACTION_GROUP_STOP;   //填充停止运行动作组命令

	HAL_UART_Transmit(&g_servoControl_uart_handle,LobotTxBuf,4,1000);
//	uartWriteBuf(LobotTxBuf, 4);      //发送
}
/*********************************************************************************
 * Function:  lobotServos_setActionGroupSpeed
 * Description： 设定指定动作组的运行速度
 * Parameters:   NumOfAction: 动作组序号 , Speed:目标速度
 * Return:       无返回
 * Others:
 **********************************************************************************/
void lobotServos_setActionGroupSpeed(uint8_t numOfAction, uint16_t Speed)
{
	LobotTxBuf[0] = LobotTxBuf[1] = FRAME_HEADER;   //填充帧头
	LobotTxBuf[2] = 5;                       //数据长度，数据帧除帧头部分数据字节数，此命令固定为5
	LobotTxBuf[3] = CMD_ACTION_GROUP_SPEED;  //填充设置动作组速度命令
	LobotTxBuf[4] = numOfAction;             //填充要设置的动作组号
	LobotTxBuf[5] = GET_LOW_BYTE(Speed);     //获得目标速度的低八位
	LobotTxBuf[6] = GET_HIGH_BYTE(Speed);    //获得目标熟读的高八位

	HAL_UART_Transmit(&g_servoControl_uart_handle,LobotTxBuf,7,1000);
//	uartWriteBuf(LobotTxBuf, 7);             //发送
}

/*********************************************************************************
 * Function:  lobotServos_setAllActionGroupSpeed
 * Description： 设置所有动作组的运行速度
 * Parameters:   Speed: 目标速度
 * Return:       无返回
 * Others:
 **********************************************************************************/
void lobotServos_setAllActionGroupSpeed(uint16_t Speed)
{
	lobotServos_setActionGroupSpeed(0xFF, Speed);  //调用动作组速度设定，组号为0xFF时设置所有组的速度
}

/*********************************************************************************
 * Function:  getBatteryVoltage
 * Description： 发送获取电池电压命令
 * Parameters:   Timeout：重试次数
 * Return:       无返回
 * Others:
 **********************************************************************************/
void getBatteryVoltage(void)
{
//	uint16_t Voltage = 0;
	LobotTxBuf[0] = FRAME_HEADER;  //填充帧头
	LobotTxBuf[1] = FRAME_HEADER;
	LobotTxBuf[2] = 2;             //数据长度，数据帧除帧头部分数据字节数，此命令固定为2
	LobotTxBuf[3] = CMD_GET_BATTERY_VOLTAGE;  //填充获取电池电压命令

	HAL_UART_Transmit(&g_servoControl_uart_handle,LobotTxBuf,4,1000);
//	uartWriteBuf(LobotTxBuf, 4);   //发送
}

void lobotServos_receiveHandle(void)
{
	//可以根据二次开发手册添加其他指令
	if (LobotServoUart.isUartRxCompleted) {
		LobotServoUart.isUartRxCompleted = false;
		switch (LobotRxBuf[3]) {
		case CMD_GET_BATTERY_VOLTAGE: //获取电压
			LobotServoUart.batteryVolt = (((uint16_t)(LobotRxBuf[5])) << 8) | (LobotRxBuf[4]);
			break;
		default:
			break;
		}
	}
}
void lobotServos_ControlProcessing(uint8_t Res)
{
	static bool isGotFrameHeader = false;
	static uint8_t frameHeaderCount = 0;
	static uint8_t dataLength = 2;
	static uint8_t dataCount = 0;

	if (!isGotFrameHeader) //判断帧头
	{  
		if (Res == FRAME_HEADER) 
		{
			frameHeaderCount++;
			if (frameHeaderCount == 2) 
			{
				frameHeaderCount = 0;
				isGotFrameHeader = true;
				dataCount = 1;
			}
		} 
		else 
		{
			isGotFrameHeader = false;
			dataCount = 0;
			frameHeaderCount = 0;
		}
	}
	if (isGotFrameHeader) //接收接收数据部分
	{ 
		UART_RX_BUF[dataCount] = Res;
		if (dataCount == 2) 
		{
			dataLength = UART_RX_BUF[dataCount];
			if (dataLength < 2 || dataLength > 8) 
			{
				dataLength = 2;
				isGotFrameHeader = false;
			}
		}
		dataCount++;
		if (dataCount == dataLength + 2) 
		{
			if (LobotServoUart.isUartRxCompleted == false) 
			{
				LobotServoUart.isUartRxCompleted = true;
				memcpy(LobotRxBuf, UART_RX_BUF, dataCount);
			}
			isGotFrameHeader = false;
		}
	}
	
}


void lobotControl(uint16_t duo1_angle,uint16_t duo2_angle,uint16_t duo3_angle,uint16_t duo4_angle,uint16_t speed,uint8_t num)
{
	LobotServo _servos[4] = {{6,duo1_angle},{7,duo2_angle},{8,duo3_angle},{9,duo4_angle}};
	if(num !=4 )
		switch(num)
		{
			case 0:lobotServo_move(0,_servos[0].Position,speed);break;
			case 1:lobotServo_move(1,_servos[1].Position,speed);break;
			case 2:lobotServo_move(2,_servos[2].Position,speed);break;
			case 3:lobotServo_move(3,_servos[3].Position,speed);break;
		}
	else
		lobotServos_moveByArray(_servos,4,speed);
}

const LobotServo ActionGroup[11][4]=
{
	{{6,2000},{7,930},{8,2000},{9,1930}},//0放上过渡
	{{6,1000},{7,930},{8,2000},{9,1930}},//1盘上过渡
	{{6,1000},{7,700},{8,1880},{9,2250}},//2盘中
	{{6,2000},{7,2400},{8,600},{9,1900}},//3中一层
	{{6,2340},{7,2500},{8,750},{9,1570}},//4左一层
	{{6,1700},{7,2500},{8,750},{9,1550}},//5右一层
	{{6,2000},{7,1970},{8,810},{9,2050}},//6中二层
	{{6,2300},{7,2150},{8,920},{9,1750}},//7左二层
	{{6,1700},{7,2180},{8,960},{9,1660}},//8右二层
	{{6,2030},{7,1720},{8,800},{9,2330}},//9转盘拿
	{{6,2030},{7,1550},{8,1020},{9,2250}}//10转盘上
};

LobotServo _servosTemp[4];
void lobotRunActionGroup(uint8_t AcGp,uint16_t speed)
{
	memcpy(&_servosTemp,ActionGroup[AcGp],4*sizeof(LobotServo));
	lobotServos_moveByArray(_servosTemp,4,speed);
}