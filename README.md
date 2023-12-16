# 23GXinGDUT-Delivery

An STM32 embedded program for the auto-delivery car project completing a specific contest's task. It features a limited area positioning system and coordinate-base navigation.  

The project contains drivers for or offers solutions to(in the STM32HAL environment):  

+ QRCode Scan
+ Basic car movement control
+ OLED Display
+ Servos control
+ Visual: simple color & ring recognition + vision-based position adjustment
+ Communication Driver for MCUs(UART)  

PCB design in the project contains solutions to:

+ General STM32 Extended Board
+ Multi-MCUs connection & communication
+ Single 12V power source to 5V,3V3,7V4
+ Power moniter & alarm system
+ Built-in USB-C port support 5V power supply & data tranfer with PC
+ Built-in buttons & press detection  

**--CHECK IF ERROR--**  
**You need to add CMSIS & HAL driver to Drivers folder manually to build the project.**  
Check .ioc file for project's specific MCU & firmware package version.  
For Keil5 users: Make sure files in *"./User*" & "*./System*" are added to the project, and paths "*./User/Inc*" & "*./System/Inc*" are added to the Include Path.  
**Builder Options:**
|AC6(ARM C Compiler Version 6)|C/C++ Compiler Options|
|:-:|:-:|
|Use MicroLIB|Optimization -- Level 0(-O0)|

mxprj

+ MCU: STM32F407VGT6
+ BoardProvider: DevEBox

L4

+ MCU: STM32L431RCT6
+ BoardProvider: WEIyi/139SR

### Software Side Module List

|Module|Model/Provider|
|:-:|:-:|
|IMU|N100 by wheeltec|
|Rader|N10 by wheeltec|
|Scaner|GM65 by GROW|
|ServoController|LSC-16 by Hiwonder|
|MotorController|Emm42_V4.2 by ZHANGDATOU|
|OPS|OPS-9 by Action|
|OLED & Controller|1.3'/0.9' IIC SSD1306|
|Vision Solotion|OpenMV4 H7|

**Not all modules were in use in the actual program meaning unused modules' functional were not guaranteed*

### Electronic Side Module List

|Module|Model/Provider|
|:-:|:-:|
|12V to 5V DCDC|Missing Info / Keyword: Mini 3A|
|12V to 3.3V DCDC|Same as above|
|12V to 7.4V DCDC|TPS54560Module by Mindesigner|
|TTL to RS232|SP3232 from touglesy|

**STM32L4 was not mounted in the actual situation meaning the system with L4 was not guaranteed or validated*

**As the contest ended, I was no longer working on the project. I do only support the project very limited meaning no more updates are expected. But I do recommend you could do more than this as there are so many windows for further development.**

//////////////////////////////////////////////////////////  
## 2023年广东省大学生工程实践与创新能力大赛 暨2023年中国大学生工程实践与创新能力大赛选拔赛 

### 智能搬运赛项  

星之卡车  
电控源码+OpenMV视觉+PCB

PCB:  
导入至立创EDA标准版  

|版本|说明|
|:-:|:-:|
|1.0|初版(存在问题不建议使用)|
|1.8| 4电机机械臂终版|
|2.1| 5电机升降比赛版|  

对于L4的说明:L4设计为ADC电压检测及外部模块实时状态检测作用,但因时间关系未能完成,实际比赛中并未实装.  
