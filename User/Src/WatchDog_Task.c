#include "WatchDog_Task.h"

uint8_t Start_Flag = 0;

WatchDog_TypeDef WChassis_1_Motor;
WatchDog_TypeDef WChassis_2_Motor;
WatchDog_TypeDef WChassis_3_Motor;
WatchDog_TypeDef WChassis_4_Motor;

WatchDog_TypeDef WUp_Down_Communication;
WatchDog_TypeDef WRemote_Communication;
WatchDog_TypeDef WReferee_Communication;

Device_Status SChassis_1_Motor = Device_Error;
Device_Status SChassis_2_Motor = Device_Error;
Device_Status SChassis_3_Motor = Device_Error;
Device_Status SChassis_4_Motor = Device_Error;
              
Device_Status SUp_Down_Communication = Device_Error;
Device_Status SRemote_Communication = Device_Error;
Device_Status SReferee_Communication = Device_Error;

Device_Status SUp_Down_Communication_Last = Device_Error;

TaskHandle_t WatchDog_Task_Handle;
void WatchDog_Task(void *pvParameters)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        WatchDog_Polling();
        vTaskDelayUntil(&xLastWakeTime,2);
    }
}

TaskHandle_t Monitor_Device_Status_Task_Handle;
void Monitor_Device_Status_Task(void *pvParameters)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        if(SReferee_Communication == Device_Right)
        {
            if(ext_power_heat_data.chassis_power < 140)
            {
                Rotate_Speed += 10;
            }
            if(ext_power_heat_data.chassis_power > 150)
            {
                Rotate_Speed -= 10;
            }
        }
        else
        {
            Rotate_Speed = 3000;
        }
        vTaskDelayUntil(&xLastWakeTime,2);
    }
}

void WatchDog_Init_Gather()
{
    WatchDog_Init(&WChassis_1_Motor, 20);
    WatchDog_Init(&WChassis_2_Motor, 20);
    WatchDog_Init(&WChassis_3_Motor, 20);
    WatchDog_Init(&WChassis_4_Motor, 20);
    
    WatchDog_Init(&WUp_Down_Communication, 20);
    WatchDog_Init(&WRemote_Communication, 20);
    WatchDog_Init(&WReferee_Communication, 20);
}

void FeedDog_CallBack(WatchDogp handle)
{
    if(IS_Dog(handle, WChassis_1_Motor))
    {
        SChassis_1_Motor = Device_Right;
    }
    else if(IS_Dog(handle, WChassis_2_Motor))
    {
        SChassis_2_Motor = Device_Right;
    }
    else if(IS_Dog(handle, WChassis_3_Motor))
    {
        SChassis_3_Motor = Device_Right;
    }
    else if(IS_Dog(handle, WChassis_4_Motor))
    {
        SChassis_4_Motor = Device_Right;
    }
    else if(IS_Dog(handle, WUp_Down_Communication))
    {
        SUp_Down_Communication = Device_Right;
    }
    else if(IS_Dog(handle, WRemote_Communication))
    {
        SRemote_Communication = Device_Right;
    }
    else if(IS_Dog(handle, WReferee_Communication))
    {
        SReferee_Communication = Device_Right;
    }
}

void WatchDog_CallBack(WatchDogp handle)
{
    if(IS_Dog(handle, WChassis_1_Motor))
    {
        SChassis_1_Motor = Device_Error;
    }
    else if(IS_Dog(handle, WChassis_2_Motor))
    {
        SChassis_2_Motor = Device_Error;
    }
    else if(IS_Dog(handle, WChassis_3_Motor))
    {
        SChassis_3_Motor = Device_Error;
    }
    else if(IS_Dog(handle, WChassis_4_Motor))
    {
        SChassis_4_Motor = Device_Error;
    }
    else if(IS_Dog(handle, WUp_Down_Communication))
    {
        SUp_Down_Communication = Device_Error;
    }
    else if(IS_Dog(handle, WRemote_Communication))
    {
        SRemote_Communication = Device_Error;
    }
    else if(IS_Dog(handle, WReferee_Communication))
    {
        SReferee_Communication = Device_Error;
    }
}

