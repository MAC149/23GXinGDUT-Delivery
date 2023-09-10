/*
Scaner module setups:
Using GM65
Default Bitrate:9600
Data preflex:DA(44 41)
*/
#ifndef _SCAN_H_
#define _SCAN_H_
#include"GeneralDef.h"

#define SCAN_RES_BUF_LENGTH 16


//SCANER IO CONNECTION
#define SCANER_UARTX huart6

typedef struct
{
    uint8_t Scan_Char_Buf;
    void (* Scan_Rec_Process)(uint8_t);
}Scan_t;


uint8_t*  Scan_GetCode();

extern Scan_t Scan;
extern uint8_t Scan_Data_Length;

#endif // !_SCAN_H_
