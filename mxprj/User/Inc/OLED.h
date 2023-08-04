#ifndef __OLED_H
#define __OLED_H

#define _OLED_INCH_13
//#define _OLED_INCH_096

/*引脚配置*/
#define OLED_W_SCL(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState)(x))
#define OLED_W_SDA(x)		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (GPIO_PinState)(x))


void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char,uint8_t fonts);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String,uint8_t fonts);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowFNum(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t size);

#endif
