#include "Task_Init.h"

The_TX_Buffer_1_ The_TX_Buffer_1;
The_TX_Buffer_2_ The_TX_Buffer_2;

#define OutPostStatus_Pos 10U
#define OutPostStatus_Msk (0x1UL << OutPostStatus_Pos)

void Task_Start()
{
    IMU_Rx_Finish_Semaphore = xSemaphoreCreateBinary();
    
    CanFilter_Init(&hcan1);
    CanFilter_Init(&hcan2);
    
    HAL_CAN_Start(&hcan1);
    HAL_CAN_Start(&hcan2);
    
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING);
    
//    HAL_NVIC_DisableIRQ(DMA1_Stream5_IRQn);
    
    RMQueueInit(&Referee_queue, USART6_BUFLEN, 10);     
    HAL_UART_Receive_DMA(&huart2, RMQueueGetEndPtr(&Referee_queue), USART6_BUFLEN);

#if DEBUG
    Remote_Debug_Init();
#endif
    PID_Param_Init_Chassis();
    WatchDog_Init_Gather();
    Rotate_Speed = 0;
    
    User_Referee_Init();
    
    xTaskCreate(WatchDog_Task, "WatchDog_Task", 128, NULL, osPriorityNormal, &WatchDog_Task_Handle);
    xTaskCreate(Monitor_Device_Status_Task, "Monitor_Device_Status_Task", 128, NULL, osPriorityNormal, &Monitor_Device_Status_Task_Handle);
    xTaskCreate(Chassis_Sport_Task, "Chassis_Sport_Task", 128, NULL, osPriorityNormal, &Chassis_Task_Handle);
    xTaskCreate(Remote_Debug_Task, "Remote_Debug_Task", 128, NULL, osPriorityNormal, &Remote_Debug_Task_Handle);
    xTaskCreate(Transmit_CAN_Data_Task, "Transmit_CAN_Data_Task", 128, NULL, osPriorityNormal, &Transmit_CAN_Data_Task_Handle);
}

TaskHandle_t Transmit_CAN_Data_Task_Handle;
void Transmit_CAN_Data_Task(void *pvParameters)
{
    for(;;)
    {
        The_TX_Buffer_1.TX_Buffer_1.Outpost_status = ext_event_data.outposts;
        The_TX_Buffer_1.TX_Buffer_1.chassis_power = ext_power_heat_data.chassis_power;
        The_TX_Buffer_1.TX_Buffer_1.game_progress = ext_game_state.game_progress;
        
        The_TX_Buffer_2.TX_Buffer_2.bullet_speed = ext_shoot_data.bullet_speed;
        The_TX_Buffer_2.TX_Buffer_2.shooter_id1_17mm_cooling_heat = ext_power_heat_data.shooter_id1_17mm_cooling_heat;
        The_TX_Buffer_2.TX_Buffer_2.shooter_id2_17mm_cooling_heat = ext_power_heat_data.shooter_id2_17mm_cooling_heat;
        CAN_Send_StdDataFrame(&hcan1, 0x111, (uint8_t *)&The_TX_Buffer_1);
        osDelay(3);
        CAN_Send_StdDataFrame(&hcan1, 0x222, (uint8_t *)&The_TX_Buffer_2);
        osDelay(3);
    }
}


