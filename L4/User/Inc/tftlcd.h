#ifndef __LCD_H
#define __LCD_H
#include "main.h"
#include "GeneralDef.h"

extern u16	POINT_COLOR;	//默认画笔颜色
extern u16	BACK_COLOR;		//默认背景颜色

#define LCD_RS_Pin GPIO_PIN_10
#define LCD_RS_GPIO_Port GPIOB
#define LCD_PWR_Pin GPIO_PIN_11
#define LCD_PWR_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOB

//LCD的宽和高定义
#define USE_HORIZONTAL 2 //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_Width 172
#define LCD_Height 320

#else
#define LCD_Width 320
#define LCD_Height 172
#endif

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)



/*
    	LCD_PWR:	PA3
    	LCD_RST:	PA4
    	LCD_DC:		PA5
    	LCD_CS:		PC4
*/
//#define	LCD_PWR(X) if(X) \
//				HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_SET); \
//				else \
//				HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_RESET)
//				
//#define	LCD_RST(X) if(X) \
//				HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET); \
//				else \
//				HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET)		
//				
//				
//#define	LCD_DC(X) if(X) \
//				HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET); \
//				else \
//				HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)				
//#define	LCD_CS		PCout(4)

#define	LCD_PWR(n)		(n?HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_PWR_GPIO_Port,LCD_PWR_Pin,GPIO_PIN_RESET))
#define	LCD_CS(n)		(n?HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET))
#define	LCD_RS(n)			(n?HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,GPIO_PIN_RESET))


void LCD_Init(void);																	//初始化
void LCD_DisplayOn(void);																//开显示
void LCD_DisplayOff(void);																//关显示
void LCD_Write_HalfWord(const u16 da);													//写半个字节数据到LCD
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);									//设置数据显示区域
void LCD_Clear(u16 color);																//清屏
void LCD_Fill(u16 x_start, u16 y_start, u16 x_end, u16 y_end, u16 color);				//填充单色
void LCD_Draw_Point(u16 x, u16 y);														//画点
void LCD_Draw_ColorPoint(u16 x, u16 y,u16 color);										//画带颜色点
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);										//画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);									//画矩形
void LCD_Draw_Circle(u16 x0, u16 y0, u8 r);												//画圆
void LCD_ShowChar(u16 x, u16 y, char chr, u8 size);										//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);									//显示一个数字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);							//显示数字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);					//显示字符串
void LCD_Show_Image(u16 x, u16 y, u16 width, u16 height, const u8 *p);					//显示图片
void Display_ALIENTEK_LOGO(u16 x,u16 y);												//显示ALIENTEK LOGO
void LCD_Draw_Point1(u16 x, u16 y,u8 t);



#endif


