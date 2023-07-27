#ifndef _REMOTE_DEBUG_H_
#define _REMOTE_DEBUG_H_

#include "Task_Init.h"

#if DEBUG

#define DBUS_LEN 30
extern uint8_t rx_dbus[DBUS_LEN];

extern SemaphoreHandle_t Dbus_Rx_Finish_Semaphore;

extern TaskHandle_t Remote_Debug_Task_Handle;
void Remote_Debug_Task(void *pvParameters);

void Remote_Debug_Init(void);

#endif
#endif
