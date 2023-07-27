#ifndef _TASK_INIT_H_
#define _TASK_INIT_H_

#include "stm32f4xx_hal.h"
#include "can.h"
#include "usart.h"
#include "gpio.h"
#include "dma.h"	

#include "FreeRTOS.h"
#include "semphr.h"
#include "cmsis_os.h"
#include "task.h"
#include "queue.h"

#include "CANDrive.h"
#include "Chassis.h"
#include "motor.h"
#include "PID.h"
#include "ramp.h"
#include "remote.h"
#include "WatchDog.h"
#include "IMU.h"
#include "RMQueue.h"
#include "Referee_offcial.h"

#include "Chassis_Task.h"
#include "Communication_About.h"
#include "Remote_Debug.h"
#include "IMU_Data_Process_Task.h"
#include "WatchDog_Task.h"

#include "arm_math.h"

#include "Task_Referee.h"

typedef __packed struct {
    uint8_t game_progress;
    uint8_t Outpost_status;
    float chassis_power;
} TX_Buffer_1_Typedef;

typedef union
{
    uint8_t can_buff[8];
    TX_Buffer_1_Typedef TX_Buffer_1;
} The_TX_Buffer_1_;
extern The_TX_Buffer_1_ The_TX_Buffer_1;

typedef __packed struct {
    uint16_t shooter_id1_17mm_cooling_heat;
    uint16_t shooter_id2_17mm_cooling_heat;
    float bullet_speed;
} TX_Buffer_2_Typedef;

typedef union
{
    uint8_t can_buff[8];
    TX_Buffer_2_Typedef TX_Buffer_2;
} The_TX_Buffer_2_;
extern The_TX_Buffer_2_ The_TX_Buffer_2;

void Task_Start(void);

extern TaskHandle_t Transmit_CAN_Data_Task_Handle;
void Transmit_CAN_Data_Task(void *pvParameters);

#endif 
