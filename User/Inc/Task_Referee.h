#ifndef _TASK_REFEREE_H_
#define _TASK_REFEREE_H_

#include "Task_Init.h"
#include "RMQueue.h"

extern const EventBits_t Event_1_Game_Status;   //!<@brief 接收比赛状态信息事件
extern const EventBits_t Event_1_Robot_HP;      //!<@brief 接收机器人血量事件
extern const EventBits_t Event_1_All;           //!<@brief 发送缓冲区1全部事件

extern const EventBits_t Event_2_Sentry_Pose;   //!<@brief 接收哨兵位置事件
extern const EventBits_t Event_2_Robot_Pose;    //!<@brief 接收其他机器人位置事件
extern const EventBits_t Event_2_All;           //!<@brief 发送缓冲区2全部事件

extern EventGroupHandle_t EventGroup_Receive_Finish_1;  //!<@brief 发送缓冲区1事件组
extern EventGroupHandle_t EventGroup_Receive_Finish_2;  //!<@brief 发送缓冲区2事件组

extern EventBits_t Event_Wait_Result_1;     //!<@brief 发送缓冲区1事件等待结果
extern EventBits_t Event_Wait_Result_2;     //!<@brief 发送缓冲区2事件等待结果

extern RMQueue_Handle Referee_queue;    //!<@brief 裁判系统接收队列

typedef struct {
	float shoot_rate; //射频限制
	int16_t shoot_level;//射速上限
}Referee_data;
extern Referee_data referee_data;

/**
 * @brief 发送缓冲区更新完成标志位
 */
typedef struct {
    uint8_t Transmit_Data_1_Update_Flag;
    uint8_t Transmit_Data_2_Update_Flag;
} Update_Finish_Flag_t;
extern Update_Finish_Flag_t Update_Finish_Flag;

/**
 * @brief 机器人阵容枚举体
 */
typedef enum {
    Unknown = 0,
    Red,
    Blue
} Robot_Lineup_;
extern Robot_Lineup_ Robot_Lineup;

/**
 * @brief 比赛状态信息结构体
 */
typedef struct {
    uint8_t game_progress;
    uint16_t stage_remain_time;
} Game_Status_t;

/**
 * @brief 比赛结果信息结构体
 */
typedef struct {
    uint8_t winner;
} Game_Result_t;

/**
 * @brief 机器人血量信息结构体
 */
typedef struct {
    uint16_t Hero_HP;
    uint16_t Engineer_HP;
    uint16_t Infantry_3_HP;
    uint16_t Infantry_4_HP;
    uint16_t Sentry_HP;
    uint16_t Outpost_HP;
    uint16_t Base_HP;
} Robot_HP_Data_t;

/**
 * @brief 发送缓冲区1
 */
typedef struct {
    Game_Status_t Game_Status;
    Robot_HP_Data_t Robot_HP_Data;
    uint16_t Allow_Shoot_Num;
    uint8_t Aim_Status;
    uint8_t Robot_Lineup;
} Transmit_Data_1_t;
extern Transmit_Data_1_t Transmit_Data_1;

/**
 * @brief 机器人位置信息结构体
 */
typedef struct {
    float Hero_X;
    float Hero_Y;
    float Engineer_X;
    float Engineer_Y;
    float Infantry_3_X;
    float Infantry_3_Y;
    float Infantry_4_X;
    float Infantry_4_Y;
    float Sentry_X;     
    float Sentry_Y;
} Robot_Pose_t;

/**
 * @brief 发送缓冲区2
 */
typedef struct {
    Robot_Pose_t Robot_Pose;    
} Transmit_Data_2_t;
extern Transmit_Data_2_t Transmit_Data_2;

extern TaskHandle_t Referee_Update_1_Task_Handle;   //!<@brief 发送缓冲区1更新任务句柄
/**
 * @brief 发送缓冲区1更新任务
 */
void Referee_Update_1_Task(void *pvParameters);

extern TaskHandle_t Referee_Update_2_Task_Handle;   //!<@brief 发送缓冲区2更新任务句柄
/**
 * @brief 发送缓冲区2更新任务
 */
void Referee_Update_2_Task(void *pvParameters);

extern TaskHandle_t Get_Robot_Lineup_Task_Handle;   //!<@brief 获取机器人阵容信息任务句柄
/**
 * @brief 获取机器人阵容信息任务
 */
void Get_Robot_Lineup_Task(void *pvParameters);

extern TaskHandle_t Updata_Referee_Task_Handle;
void Updata_Referee_Task(void *pvParameters);

/**
* @brief 初始化任务打包函数，注意如果不在临界区内调用函数，需要手写进出临界区
 */
void User_Referee_Init(void);

#endif 
