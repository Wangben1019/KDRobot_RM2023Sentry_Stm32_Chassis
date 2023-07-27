#ifndef _IMU_DATA_PROCESS_TASK_H_
#define _IMU_DATA_PROCESS_TASK_H_

#include "Task_init.h"

#define IMU_LEN 30
extern uint8_t rx_imu[IMU_LEN];

extern SemaphoreHandle_t IMU_Rx_Finish_Semaphore;

extern IMU_Typedef IMU_Data_Chassis;
extern float Euler_Yaw_Start;

extern TaskHandle_t IMU_Data_Process_Task_Handle;
void IMU_Data_Process_Task(void *pvParameters);

#endif
