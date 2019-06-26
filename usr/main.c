#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "portable.h"
#include "FreeRTOSConfig.h"
#include "stm32f10x.h"
#include "uart.h"
TaskHandle_t test_Task_Handle;

void Task_Function(void *param)
{
    for(;;)
    {
        vTaskDelay(500/portTICK_RATE_MS);
        UART5_SendString("Welcome to FreeRTOS!\r\n");
    }
}

int main(void)
{
    UART5_Init(119200);
    UART5_Send(0xaa);
    
    xTaskCreate(Task_Function,
            "1213",
            1024,
            NULL,
            1,
            &test_Task_Handle);

    vTaskStartScheduler();
//while(1)
//{
//    u16 i,j;
//    for(i=0;i<1000;i++)
//        for(j=0;j<1000;j++);
//    static u8 cnt = 0;
//    UART5_Send(cnt);
//    cnt ++;
//}
}
