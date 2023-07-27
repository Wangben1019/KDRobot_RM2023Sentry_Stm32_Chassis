#include "Remote_Debug.h"

#if DEBUG

uint8_t rx_dbus[DBUS_LEN];

SemaphoreHandle_t Dbus_Rx_Finish_Semaphore;

TaskHandle_t Remote_Debug_Task_Handle;
void Remote_Debug_Task(void *pvParameters)
{
    BaseType_t Dbus_return_data = pdFALSE;
    for(;;)
    {
        Dbus_return_data = xSemaphoreTake(Dbus_Rx_Finish_Semaphore, portMAX_DELAY);
        if(Dbus_return_data == pdTRUE)
        {
            Remote_Rx(rx_dbus);
        }
        else if(Dbus_return_data == pdFALSE)
        {
            vTaskDelay(10);
        }  
    }
}

void Remote_Debug_Init()
{
    Dbus_Rx_Finish_Semaphore = xSemaphoreCreateBinary();
    HAL_NVIC_DisableIRQ(DMA2_Stream2_IRQn);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart1, rx_dbus, DBUS_LEN);
    
    xTaskCreate(Remote_Debug_Task, "Remote_Debug_Task", 128, NULL, osPriorityNormal, &Remote_Debug_Task_Handle);
}


#endif
