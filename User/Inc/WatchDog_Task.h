#ifndef _WATCHDOG_TASK_H_
#define _WATCHDOG_TASK_H_

#include "Task_Init.h"

extern WatchDog_TypeDef WChassis_1_Motor;
extern WatchDog_TypeDef WChassis_2_Motor;
extern WatchDog_TypeDef WChassis_3_Motor;
extern WatchDog_TypeDef WChassis_4_Motor;

extern WatchDog_TypeDef WUp_Down_Communication;
extern WatchDog_TypeDef WRemote_Communication;
extern WatchDog_TypeDef WReferee_Communication;

extern TaskHandle_t WatchDog_Task_Handle;
void WatchDog_Task(void *pvParameters);

extern TaskHandle_t Monitor_Device_Status_Task_Handle;
void Monitor_Device_Status_Task(void *pvParameters);

void WatchDog_Init_Gather(void);

typedef enum
{
    Device_Error = 0,
    Device_Right = 1
} Device_Status;
extern Device_Status SChassis_1_Motor;
extern Device_Status SChassis_2_Motor;
extern Device_Status SChassis_3_Motor;
extern Device_Status SChassis_4_Motor;
              
extern Device_Status SUp_Down_Communication;
extern Device_Status SRemote_Communication;

extern Device_Status SUp_Down_Communication_Last;

#endif
