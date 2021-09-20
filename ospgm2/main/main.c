//rtos lab exam qsn 2
//MANJUNATH V 210550154008
//Demonstration of oneshot timer implementation


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TimerHandle_t t_handle;
void *const t_timerid;

void t_timer_handler(TimerHandle_t xTimer)
{
    printf("Task3 called this function.....oneshot timer is fired!\n");
}



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
    vTaskDelay(2000/ portTICK_PERIOD_MS);   // periodicity = 2000 ms
    long end = xTaskGetTickCount()-start;
    printf("Periodicity of ptask2 = %lu\n",end);
    }
    
}

void ptask3(void *data)
{
    // oneshot software timer creation
    t_handle = xTimerCreate("pt_timer",pdMS_TO_TICKS(10000),pdFALSE,&t_timerid,t_timer_handler);
    xTimerStart(t_handle,0);    // call back after 10000 ms
    while(1)
    {
    long start = xTaskGetTickCount();    
    vTaskDelay(5000/ portTICK_PERIOD_MS);   // periodicity = 5000 ms
    long end = xTaskGetTickCount()-start;
    printf("Periodicity of ptask5 = %lu\n",end);
    }
    
}


void app_main(void)
{
    int i = 0;
    // Task creation 
    xTaskCreate(ptask1,"p_tk1",2048,NULL,1,NULL);
    xTaskCreate(ptask2,"p_tk1",2048,NULL,1,NULL);
    xTaskCreate(ptask3,"p_tk1",2048,NULL,1,NULL);
    while (1) 
    {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
