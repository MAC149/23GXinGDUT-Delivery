/*
Scaner module setups:
Using GM65
Default Bitrate:9600
Data preflex:DA(44 41)
*/
#ifndef _SCAN_H_
#define _SCAN_H_
#include"GeneralDef.h"

#define SCAN_RES_BUF_LENGTH 64
#define SCAN_DMA_MAX_LENGTH 128
extern uint8_t scan_dmabuf[SCAN_DMA_MAX_LENGTH];
extern uint8_t c_count;


//SCANER IO CONNECTION
#define SCANER_UARTX huart4
#define SCANER_UARTDMA hdma_uart4_rx

#define SCANRESRET(i) scan_dmabuf[c_count+1+i]

typedef struct
{
    uint8_t Scan_Char_Buf;
    void (* Scan_Rec_Process)(uint8_t);
}Scan_t;


uint8_t*  Scan_GetCode();
void Scan_DMA_RecProcess();
uint8_t* Scan_GetCodeDMA();
char Scan_ResRet(int i);
void Scan_IDInit();
char* Scan_ResRetA(uint8_t i);


extern Scan_t Scan;
extern uint8_t Scan_Data_Length;

#endif // !_SCAN_H_
