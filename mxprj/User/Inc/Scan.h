#ifndef _SCAN_H_
#define _SCAN_H_
#include"GeneralDef.h"

#define SCANER_RES_BUF_LENGTH 8

//SCANER IO CONNECTION
#define SCANER_UARTX huart2



typedef struct
{
    uint8_t Scan_Char_Buf;
    void (* Scan_Rec_Process)(uint8_t);
}Scan_t;


uint8_t*  Scan_GetCode();

extern Scan_t Scan;


#endif // !_SCAN_H_
