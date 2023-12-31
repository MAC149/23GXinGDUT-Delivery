#ifndef _OPENMV_H_
#define _OPENMV_H_
#include "GeneralDef.h"

#define OPENMV_REC_BUF_LEN 128

#define OPENMV1_UART huart6


typedef struct OpenMV_t
{
    UART_HandleTypeDef* OpenMV_huart;
    uint8_t Openmv_RxBuf[OPENMV_REC_BUF_LEN];
    uint8_t Buf_pointer;
    uint8_t Data_pointer;
    bool Data_flag;
    bool Rec_Flag;
    uint8_t OpenMV_Rec[OPENMV_REC_BUF_LEN];
    uint8_t Rec_temp;
    void (* OpenMV_Send)(struct OpenMV_t *,uint8_t* CMD,uint8_t len);
    void (* OpenMV_Receive_Start)(struct OpenMV_t *);
    uint8_t* (* OpenMV_Receive)(struct OpenMV_t *);
    void (* OpenMV_Receive_Process)(struct OpenMV_t *);
}OpenMV_tt;



OpenMV_tt* _OpenMV_tt_Init(OpenMV_tt *that,UART_HandleTypeDef *MVhuart);

void OpenMV_Receive_Start(OpenMV_tt* that);
void OpenMVGN_Data_Process(uint8_t *str);
void OpenMVGN_StUpd(OpenMV_tt *that);
void OpenMVGN_Adj(OpenMV_tt *OpenMV);
bool OpenMVGN_Cor(OpenMV_tt *OpenMV,uint8_t Tar_cor);
void OpenMVGN_AdjPacked(OpenMV_tt *OpenMV);

extern OpenMV_tt OpenMV1;

#endif // 