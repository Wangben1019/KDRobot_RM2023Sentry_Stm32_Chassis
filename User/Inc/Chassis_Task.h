#ifndef _CHASSIS_TASK_H_
#define _CHASSIS_TASK_H_

#include "Task_Init.h"

#define USER_PI 3.141592f
#define USER_SIN(x) arm_sin_f32(x/180*USER_PI)
#define USER_COS(x) arm_cos_f32(x/180*USER_PI)
//#define USER_SIN_COS(x) arm_sin_cos_f32(x,&USER_SIN(x),USER_COS(x))

extern RM3508_TypeDef Chassis_1_Motor;
extern RM3508_TypeDef Chassis_2_Motor;
extern RM3508_TypeDef Chassis_3_Motor;
extern RM3508_TypeDef Chassis_4_Motor;

extern PID Chassis_1_Speed_PID;
extern PID Chassis_2_Speed_PID;
extern PID Chassis_3_Speed_PID;
extern PID Chassis_4_Speed_PID;
extern int16_t Rotate_Speed;

typedef union
{
    uint8_t can_buff[8];
    Chassis_Motor_Speed Chassis_Speed_Exp;
} Rx_Chassis_Exp_;
extern Rx_Chassis_Exp_ Rx_Chassis_Speed;

typedef struct {
    int16_t Speed_1_Differential;    //!<@brief 底盘电机1速度微分
    int16_t Speed_2_Differential;    //!<@brief 底盘电机2速度微分
    int16_t Speed_3_Differential;    //!<@brief 底盘电机3速度微分
    int16_t Speed_4_Differential;    //!<@brief 底盘电机4速度微分
} Chassis_Exp_Differential_Typedef;

extern TaskHandle_t Chassis_Task_Handle;
void Chassis_Sport_Task(void *pvParameters);
int16_t RAMP_Chassis(int16_t final, int16_t now, int16_t ramp);
void PID_Param_Init_Chassis(void);

#endif 
