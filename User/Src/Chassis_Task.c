#include "Chassis_Task.h"

RM3508_TypeDef Chassis_1_Motor;
RM3508_TypeDef Chassis_2_Motor;
RM3508_TypeDef Chassis_3_Motor;
RM3508_TypeDef Chassis_4_Motor;

PID Chassis_1_Speed_PID;
PID Chassis_2_Speed_PID;
PID Chassis_3_Speed_PID;
PID Chassis_4_Speed_PID;

Rx_Chassis_Exp_ Rx_Chassis_Speed;
Chassis_Motor_Speed Chassis_Motor_Expect;
Chassis_Motor_Speed Temp_Exp_Speed;
int16_t Rotate_Speed;

int16_t can2_tx[4];

TaskHandle_t Chassis_Task_Handle;
void Chassis_Sport_Task(void *pvParameters)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
//        Temp_Exp_Speed.speed_1 = Rx_Chassis_Speed.Chassis_Speed_Exp.speed_1 - Rotate_Speed;
//        Temp_Exp_Speed.speed_2 = Rx_Chassis_Speed.Chassis_Speed_Exp.speed_2 - Rotate_Speed;
//        Temp_Exp_Speed.speed_3 = Rx_Chassis_Speed.Chassis_Speed_Exp.speed_3 - Rotate_Speed;
//        Temp_Exp_Speed.speed_4 = Rx_Chassis_Speed.Chassis_Speed_Exp.speed_4 - Rotate_Speed;
        
        Chassis_Motor_Expect.speed_1 = RAMP_Chassis(Rx_Chassis_Speed.Chassis_Speed_Exp.speed_1, Chassis_Motor_Expect.speed_1, 10);
        Chassis_Motor_Expect.speed_2 = RAMP_Chassis(Rx_Chassis_Speed.Chassis_Speed_Exp.speed_2, Chassis_Motor_Expect.speed_2, 10);
        Chassis_Motor_Expect.speed_3 = RAMP_Chassis(Rx_Chassis_Speed.Chassis_Speed_Exp.speed_3, Chassis_Motor_Expect.speed_3, 10);
        Chassis_Motor_Expect.speed_4 = RAMP_Chassis(Rx_Chassis_Speed.Chassis_Speed_Exp.speed_4, Chassis_Motor_Expect.speed_4, 10);
        
        PID_Control(Chassis_1_Motor.Speed, Chassis_Motor_Expect.speed_1, &Chassis_1_Speed_PID);
        PID_Control(Chassis_2_Motor.Speed, Chassis_Motor_Expect.speed_2, &Chassis_2_Speed_PID);
        PID_Control(Chassis_3_Motor.Speed, Chassis_Motor_Expect.speed_3, &Chassis_3_Speed_PID);
        PID_Control(Chassis_4_Motor.Speed, Chassis_Motor_Expect.speed_4, &Chassis_4_Speed_PID);
        
        limit(Chassis_1_Speed_PID.pid_out, RM3508_LIMIT, -RM3508_LIMIT);
        limit(Chassis_2_Speed_PID.pid_out, RM3508_LIMIT, -RM3508_LIMIT);
        limit(Chassis_3_Speed_PID.pid_out, RM3508_LIMIT, -RM3508_LIMIT);
        limit(Chassis_4_Speed_PID.pid_out, RM3508_LIMIT, -RM3508_LIMIT);
        
        can2_tx[0] = Chassis_1_Speed_PID.pid_out;
        can2_tx[1] = Chassis_2_Speed_PID.pid_out;
        can2_tx[2] = Chassis_3_Speed_PID.pid_out;
        can2_tx[3] = Chassis_4_Speed_PID.pid_out;
        
        MotorSend(&hcan2, 0x200, can2_tx);
        
        vTaskDelayUntil(&xLastWakeTime,2);
    }
}

int16_t RAMP_Chassis(int16_t final, int16_t now, int16_t ramp)
{
    int16_t buffer = final - now;
	if (buffer > 0)
	{
		if (buffer > ramp)  
			now += ramp;  
		else
			now += buffer;
	}		
	else
	{
		if (buffer < -ramp)
			now += -ramp;
		else
			now += buffer;
	}
	return now;
}

void PID_Param_Init_Chassis()
{
    Chassis_1_Speed_PID.Kp = 5;
    Chassis_1_Speed_PID.Ki = 0;
    Chassis_1_Speed_PID.Kd = 0;
    Chassis_1_Speed_PID.limit = 5000;
    Chassis_1_Speed_PID.error_inter = 0;
    Chassis_1_Speed_PID.error_last = 0;
    Chassis_1_Speed_PID.error_now = 0;
    Chassis_1_Speed_PID.pid_out = 0;
    
    Chassis_2_Speed_PID.Kp = 5;
    Chassis_2_Speed_PID.Ki = 0;
    Chassis_2_Speed_PID.Kd = 0;
    Chassis_2_Speed_PID.limit = 5000;
    Chassis_2_Speed_PID.error_inter = 0;
    Chassis_2_Speed_PID.error_last = 0;
    Chassis_2_Speed_PID.error_now = 0;
    Chassis_2_Speed_PID.pid_out = 0;
    
    Chassis_3_Speed_PID.Kp = 5;
    Chassis_3_Speed_PID.Ki = 0;
    Chassis_3_Speed_PID.Kd = 0;
    Chassis_3_Speed_PID.limit = 5000;
    Chassis_3_Speed_PID.error_inter = 0;
    Chassis_3_Speed_PID.error_last = 0;
    Chassis_3_Speed_PID.error_now = 0;
    Chassis_3_Speed_PID.pid_out = 0;
    
    Chassis_4_Speed_PID.Kp = 5;
    Chassis_4_Speed_PID.Ki = 0;
    Chassis_4_Speed_PID.Kd = 0;
    Chassis_4_Speed_PID.limit = 5000;
    Chassis_4_Speed_PID.error_inter = 0;
    Chassis_4_Speed_PID.error_last = 0;
    Chassis_4_Speed_PID.error_now = 0;
    Chassis_4_Speed_PID.pid_out = 0;
}
