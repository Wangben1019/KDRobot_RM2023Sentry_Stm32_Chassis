#include "Communication_About.h"

uint32_t ID_User;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint32_t ID = CAN_Receive_DataFrame(&hcan1, CAN1_buff);
    ID_User = ID;
    if (hcan->Instance == CAN1)
    {
        switch(ID)
        {
            case 0x147:
                memcpy(&Rx_Chassis_Speed, CAN1_buff, sizeof(Rx_Chassis_Exp_));
                SUp_Down_Communication_Last = SUp_Down_Communication;
                Feed_Dog(&WUp_Down_Communication);
                break;
        }
    }
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint32_t ID = CAN_Receive_DataFrame(&hcan2, CAN2_buff);
    if (hcan->Instance == CAN2)
    {
        switch(ID)
        {
            case 0x201:
                RM3508_Receive(&Chassis_1_Motor, CAN2_buff);
                Feed_Dog(&WChassis_1_Motor);
                break;
            case 0x202:
                RM3508_Receive(&Chassis_2_Motor, CAN2_buff);
                Feed_Dog(&WChassis_2_Motor);
                break;
            case 0x203:
                RM3508_Receive(&Chassis_3_Motor, CAN2_buff);
                Feed_Dog(&WChassis_3_Motor);
                break;
            case 0x204:
                RM3508_Receive(&Chassis_4_Motor, CAN2_buff);
                Feed_Dog(&WChassis_4_Motor);
                break;
        }
    }
}
