#include "stm32f4xx.h"
#include "cmsis_os2.h"

osMessageQueueId_t msgQueue;

void Task1(void *argument) {
    uint32_t data = 0;
    while (1) {
        data++;
        osMessageQueuePut(msgQueue, &data, 0, osWaitForever);
        osDelay(1000);
    }
}

void Task2(void *argument) {
    uint32_t receivedData;
    while (1) {
        osMessageQueueGet(msgQueue, &receivedData, NULL, osWaitForever);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        osDelay(500);
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    osKernelInitialize();
    
    msgQueue = osMessageQueueNew(10, sizeof(uint32_t), NULL);
    
    osThreadNew(Task1, NULL, NULL);
    osThreadNew(Task2, NULL, NULL);
    osKernelStart();

    while (1) {
    }
}
