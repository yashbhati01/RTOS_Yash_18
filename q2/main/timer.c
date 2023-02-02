#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t t1, t2, t3;
TimerHandle_t Time_handler;
static int taskcore = 1;
const TickType_t delay = 10000/portTICK_PERIOD_MS;

void timer_function(TimerHandle_t timer)
{
    printf("Timer function fired from Task-3\n");
}

void Time1(void *data)
{
    printf("Task 1 started\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    printf("Task 1 end\n");
    vTaskDelete(t1);
}

void Time2(void *data)
{
    printf("Task 2 started\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    printf("Task 2 end\n");
    vTaskDelete(t2);
}

void Time3(void *asd)
{
    printf("Task 3 started\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    Time_handler = xTimerCreate("one_shot_timer",delay,pdTRUE,NULL,timer_function);
    printf("Timer Created\n");
    xTimerStart(Time_handler,0);
    vTaskDelete(t3);
}

void app_main()
{
    printf("\tEntered main\n");
    printf("Creating Timer\n");
    xTaskCreatePinnedToCore(Time1,"Timer creation",2048,NULL,5,&t1,taskcore);
    xTaskCreatePinnedToCore(Time2,"Timer creation",2048,NULL,6,&t2,taskcore);
    xTaskCreatePinnedToCore(Time3,"Timer creation",2048,NULL,7,&t3,taskcore);
}