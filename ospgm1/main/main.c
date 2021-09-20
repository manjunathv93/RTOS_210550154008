//rtos lab exam qsn1
//MANJUNATH V 210550154008
//Implementation of message queue to send integer data from task4 to task5



#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t datamq;

void ptask1(void *data)
{
    while(1)
    {
    long start = xTaskGetTickCount();    
    vTaskDelay(1000/ portTICK_PERIOD_MS);   // periodicity = 1000 ms
    long end = xTaskGetTickCount()-start;
    printf("Periodicity of ptask1 = %lu\n",end);
    }  
}

void ptask2(void *data)
{
    while(1)
    {
    long start = xTaskGetTickCount();
    vTaskDelay(2000/ portTICK_PERIOD_MS);     // periodicity = 2000 ms
    long end = xTaskGetTickCount()-start;
    printf("Periodicity of ptask2 = %lu\n",end);
    }  
}

void ptask3(void *data)
{
    while(1)
    {
    long start = xTaskGetTickCount();
    vTaskDelay(5000/ portTICK_PERIOD_MS);     // periodicity = 3000 ms
    long end = xTaskGetTickCount()-start;
    printf("Periodicity of ptask3 = %lu\n",end);
    }  
}


//sending end 
void senderptask4(void *data)
{
    int msg = 0;
    while(1)
    {
    printf("ptask4 is created\n");
    msg++;
    xQueueSend(datamq,&msg,0);
    printf("ptask4 is ended\n");
    vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    
}


//receiving end
void receiverptask5(void *data)
{
    while(1)
    {
    printf("ptask5 is created\n");
    int buff;
    xQueueReceive(datamq,&buff,0);
    printf("Data(ptask5): %d\n",buff);
    printf("ptask5 is ended\n");
    vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    //message queue creation
    datamq = xQueueCreate(5,sizeof(int));   // no of messages = 5 and each with a size of int 

    //Task creation
    xTaskCreate(ptask1,"p_tk1",2048,NULL,6,NULL);
    xTaskCreate(ptask2,"p_tk2",2048,NULL,6,NULL);
    xTaskCreate(ptask3,"p_tk3",2048,NULL,6,NULL);
    xTaskCreate(senderptask4,"p_tk4",2048,NULL,5,NULL);
    xTaskCreate(receiverptask5,"p_tk5",2048,NULL,4,NULL);
    while(1)
    {
        vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
}
