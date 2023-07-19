#include "CallBack.h"

static uint8_t Scan_Rec_RX;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart==&SCANER_UARTX)
    {
        Scan_Rec_RX=Scan.Scan_Char_Buf;
        Scan.Scan_Rec_Process(Scan_Rec_RX);
    }
}