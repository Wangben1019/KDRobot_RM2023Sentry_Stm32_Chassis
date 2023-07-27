#include "Task_Referee.h"

const EventBits_t Event_1_Game_Status = 0x01;
const EventBits_t Event_1_Robot_HP = 0x02;
const EventBits_t Event_1_All = 0x03;

const EventBits_t Event_2_Sentry_Pose = 0x01;
const EventBits_t Event_2_Robot_Pose = 0x02;
const EventBits_t Event_2_All = 0x03;

RMQueue_Handle Referee_queue;
Referee_data referee_data;

Update_Finish_Flag_t Update_Finish_Flag;

Robot_Lineup_ Robot_Lineup = Unknown;

EventGroupHandle_t EventGroup_Receive_Finish_1;
EventGroupHandle_t EventGroup_Receive_Finish_2;

EventBits_t Event_Wait_Result_1;
EventBits_t Event_Wait_Result_2;

Transmit_Data_1_t Transmit_Data_1;
Transmit_Data_2_t Transmit_Data_2;

TaskHandle_t Referee_Update_1_Task_Handle;
void Referee_Update_1_Task(void *pvParameters)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        Event_Wait_Result_1 = xEventGroupWaitBits(EventGroup_Receive_Finish_1, Event_1_All, pdFALSE, pdTRUE, portMAX_DELAY);
        if(Event_Wait_Result_1 == Event_1_All && Robot_Lineup != Unknown)
        {
            Transmit_Data_1.Allow_Shoot_Num = ext_bullet_remaining.bullet_remaining_num_17mm;
            Transmit_Data_1.Game_Status.game_progress = ext_game_state.game_progress;
            Transmit_Data_1.Game_Status.stage_remain_time = ext_game_state.stage_remain_time;
            if(Robot_Lineup == Red)
            {
                Transmit_Data_1.Robot_Lineup = 1;
                Transmit_Data_1.Robot_HP_Data.Hero_HP = ext_game_robot_HP.red_1_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Engineer_HP = ext_game_robot_HP.red_2_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Infantry_3_HP = ext_game_robot_HP.red_3_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Infantry_4_HP = ext_game_robot_HP.red_4_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Sentry_HP = ext_game_robot_HP.red_7_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Outpost_HP = ext_game_robot_HP.red_outpost_HP;
                Transmit_Data_1.Robot_HP_Data.Base_HP = ext_game_robot_HP.red_base_HP;
            }
            else if(Robot_Lineup == Blue)
            {
                Transmit_Data_1.Robot_Lineup = 2;
                Transmit_Data_1.Robot_HP_Data.Hero_HP = ext_game_robot_HP.blue_1_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Engineer_HP = ext_game_robot_HP.blue_2_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Infantry_3_HP = ext_game_robot_HP.blue_3_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Infantry_4_HP = ext_game_robot_HP.blue_4_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Sentry_HP = ext_game_robot_HP.blue_7_robot_HP;
                Transmit_Data_1.Robot_HP_Data.Outpost_HP = ext_game_robot_HP.blue_outpost_HP;
                Transmit_Data_1.Robot_HP_Data.Base_HP = ext_game_robot_HP.blue_base_HP;
            }
            
            Update_Finish_Flag.Transmit_Data_1_Update_Flag = 1;
            
            xEventGroupClearBits(EventGroup_Receive_Finish_1, Event_1_All);
        }
        vTaskDelayUntil(&xLastWakeTime,2);
    }
}

TaskHandle_t Referee_Update_2_Task_Handle;
void Referee_Update_2_Task(void *pvParameters)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        Event_Wait_Result_2 = xEventGroupWaitBits(EventGroup_Receive_Finish_2, Event_2_All, pdFALSE, pdTRUE, portMAX_DELAY);
        if(Event_Wait_Result_2 == Event_2_All && Robot_Lineup != Unknown)
        {
            Transmit_Data_2.Robot_Pose.Hero_X = ground_robot_position.hero_x;
            Transmit_Data_2.Robot_Pose.Hero_Y = ground_robot_position.hero_y;
            Transmit_Data_2.Robot_Pose.Engineer_X = ground_robot_position.engineer_x;
            Transmit_Data_2.Robot_Pose.Engineer_Y = ground_robot_position.engineer_y;
            Transmit_Data_2.Robot_Pose.Infantry_3_X = ground_robot_position.standard_3_x;
            Transmit_Data_2.Robot_Pose.Infantry_3_Y = ground_robot_position.standard_3_y;
            Transmit_Data_2.Robot_Pose.Infantry_4_X = ground_robot_position.standard_4_x;
            Transmit_Data_2.Robot_Pose.Infantry_4_Y = ground_robot_position.standard_4_y;
            Transmit_Data_2.Robot_Pose.Sentry_X = ext_game_robot_pos.x;
            Transmit_Data_2.Robot_Pose.Sentry_Y = ext_game_robot_pos.y;
            
            Update_Finish_Flag.Transmit_Data_2_Update_Flag = 1;
            
            xEventGroupClearBits(EventGroup_Receive_Finish_2, Event_2_All);
        }
        vTaskDelayUntil(&xLastWakeTime,2);
    }
}

TaskHandle_t Get_Robot_Lineup_Task_Handle;
void Get_Robot_Lineup_Task(void *pvParameters)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        Event_Wait_Result_1 = xEventGroupWaitBits(EventGroup_Receive_Finish_1, Event_1_Robot_HP, pdFALSE, pdTRUE, portMAX_DELAY);
        if(Robot_Lineup == Unknown)
        {
            if(ext_game_robot_state.robot_id == 107)
            {
                Robot_Lineup = Blue;
                xEventGroupClearBits(EventGroup_Receive_Finish_1, Event_1_Robot_HP);
                vTaskSuspend(NULL);
            }
            else if(ext_game_robot_state.robot_id == 7)
            {
                Robot_Lineup = Red;
                xEventGroupClearBits(EventGroup_Receive_Finish_1, Event_1_Robot_HP);
                vTaskSuspend(NULL);
            }
            else
            {
                Robot_Lineup = Unknown;
            }
        }
        vTaskDelayUntil(&xLastWakeTime,2);
    }
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{		
	if(huart->Instance == USART2)			
	{	
		RMQueuePushEndPtr(&Referee_queue);
		HAL_UART_Receive_DMA(&huart2, RMQueueGetEndPtr(&Referee_queue), USART6_BUFLEN);
	}	
}

TaskHandle_t Updata_Referee_Task_Handle;
void Updata_Referee_Task(void *pvParameters)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        unpack_refree_system_data(&Referee_queue);
        vTaskDelayUntil(&xLastWakeTime,2);
    }
}

void User_Referee_Init()
{
    EventGroup_Receive_Finish_1 = xEventGroupCreate();
    EventGroup_Receive_Finish_2 = xEventGroupCreate();
//    xTaskCreate(Referee_Update_1_Task, "Referee_Update_1_Task", 128, NULL, osPriorityNormal, &Referee_Update_1_Task_Handle);
//    xTaskCreate(Referee_Update_2_Task, "Referee_Update_2_Task", 128, NULL, osPriorityNormal, &Referee_Update_2_Task_Handle);
//    xTaskCreate(Get_Robot_Lineup_Task, "Get_Robot_Lineup_Task", 128, NULL, osPriorityNormal, &Get_Robot_Lineup_Task_Handle);
    xTaskCreate(Updata_Referee_Task, "Updata_Referee_Task", 256 * 4, NULL, osPriorityNormal, &Updata_Referee_Task_Handle);
}

