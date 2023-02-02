#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t t1, t2, t3, t4, t5;
QueueHandle_t msg_q;
static int taskcore = 1;


const TickType_t t_delay = 10000/portTICK_PERIOD_MS;

void task1(void *data)
{
    printf("Task 1 started\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    printf("Task 1 End\n");
    vTaskDelete(t1);
}

void task2(void *data)
{
    printf("Task 2 started\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    printf("Task 2 End\n");
    vTaskDelete(t2);
}

void task3(void *data)
{
    printf("Task 3 started\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    printf("Task 3 End\n");
    vTaskDelete(t3);
}

void task4(void *data)
{
    int num = 0;
    printf("Task 4 started\n");
    while(1)
	{
        num++;
        printf("Sending messsage\n");
        xQueueSend(msg_q,&num,pdMS_TO_TICKS(5000));
        
        if(num > 10)
        {
            num = 0;
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
	}
    printf("Task 4 End\n");
    vTaskDelete(t4);;
}

void task5(void *data)
{
    printf("Task 5 started\n");
    int buffer = 0, num1 = 0;
	while(1)
	{
        xQueueReceive(msg_q,&buffer,portMAX_DELAY);
        printf("Message received from task is: %d\n",buffer);
        if(num1 > 10)
        {
            num1 = 0;
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
	    // vTaskDelay(pdMS_TO_TICKS(1000));
	}
    printf("Task 5 end\n");
    vTaskDelete(t5);
}

void app_main()
{
    printf("\tEntered main\n");
	msg_q = xQueueCreate(100,64);

    xTaskCreatePinnedToCore(task1,"task 1",2048,NULL,5,&t1,taskcore);
    xTaskCreatePinnedToCore(task2,"task 2",2048,NULL,6,&t2,taskcore);
    xTaskCreatePinnedToCore(task3,"task 3",2048,NULL,7,&t3,taskcore);
    xTaskCreatePinnedToCore(task4,"task 4",2048,NULL,8,&t4,taskcore);
    xTaskCreatePinnedToCore(task5,"task 5",2048,NULL,9,&t5,taskcore);
}
