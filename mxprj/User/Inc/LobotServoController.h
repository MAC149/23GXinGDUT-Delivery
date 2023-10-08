/*******************************************************************************
* 文件名: LobotServoController.h
* 作者: 深圳乐幻索尔科技
* 日期：20160806
* LSC系列舵机控制板二次开发示例
*******************************************************************************/

#ifndef LOBOTSERVOCONTROLLER_H_
#define LOBOTSERVOCONTROLLER_H_
#include "GeneralDef.h"

#define g_servoControl_uart_handle huart5

#define FRAME_HEADER 0x55             //帧头
#define CMD_SERVO_MOVE 0x03           //舵机移动指令
#define CMD_ACTION_GROUP_RUN 0x06     //运行动作组指令
#define CMD_ACTION_GROUP_STOP 0x07    //停止动作组指令
#define CMD_ACTION_GROUP_SPEED 0x0B   //设置动作组运行速度
#define CMD_GET_BATTERY_VOLTAGE 0x0F  //获取电池电压指令



typedef enum 
{
	get_material = (uint8_t)0,
	place_material = (uint8_t)1
}lobotGrapOrPlace_t;

typedef struct _lobot_servo_ {  //舵机ID,舵机目标位置
	uint8_t ID;
	uint16_t Position;

} LobotServo;
typedef struct {  //舵机控制板串口通信缓存
	
	uint16_t batteryVolt;	//电池电压

	uint8_t ucDatabuf;
	uint8_t ucRec_count;
	uint8_t ucRec_flag;
	bool isUartRxCompleted;
	uint8_t *pucRecbuf;
} LobotServoUart_typedef;

void lobotServo_init(void);
void lobotServo_move(uint8_t servoID, uint16_t Position, uint16_t Time);
void lobotServos_moveByArray(LobotServo servos[], uint8_t Num, uint16_t Time);
void lobotServos_move(uint8_t Num, uint16_t Time, ...);
void lobotServos_runActionGroup(uint8_t numOfAction, uint16_t Times);
void lobotServos_stopActionGroup(void);
void lobotServos_setActionGroupSpeed(uint8_t numOfAction, uint16_t Speed);
void lobotServos_setAllActionGroupSpeed(uint16_t Speed);
void getBatteryVoltage(void);
void lobotServos_receiveHandle(void);
void lobotServos_ControlProcessing(uint8_t Res);

void lobotRunActionGroup(uint8_t AcGp,uint16_t speed);

extern bool isUartRxCompleted;
extern uint8_t LobotRxBuf[16];
extern uint16_t batteryVolt;

extern LobotServoUart_typedef LobotServoUart;
#endif
