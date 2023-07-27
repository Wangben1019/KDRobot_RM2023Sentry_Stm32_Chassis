#include "IMU_Data_Process_Task.h"

uint8_t rx_imu[IMU_LEN];

SemaphoreHandle_t IMU_Rx_Finish_Semaphore;

IMU_Typedef IMU_Data_Chassis;
float Euler_Yaw_Start;

TaskHandle_t IMU_Data_Process_Task_Handle;
void IMU_Data_Process_Task(void *pvParameters)
{
    BaseType_t IMU_return_data = pdFALSE;
    for(;;)
    {
        IMU_return_data = xSemaphoreTake(IMU_Rx_Finish_Semaphore, portMAX_DELAY);
        if(IMU_return_data == pdTRUE)
        {
            IMU_Receive(&IMU_Data_Chassis, rx_imu);
        }
        else if(IMU_return_data == pdFALSE)
        {
            vTaskDelay(10);
        }
    }
}

