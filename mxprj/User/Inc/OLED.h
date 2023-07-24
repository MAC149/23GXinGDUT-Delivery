#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char,uint8_t fonts);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String,uint8_t fonts);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t fonts);
void OLED_ShowFNum(u8 x,u8 y,float num,u8 len,u8 size);

#endif
