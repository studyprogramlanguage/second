#include "stm32f4xx.h"
#include "cmsis_os2.h"

osMutexId_t mutex;

void Task1(void *argument) {
    while (1) {
        osMutexAcquire(mutex, osWaitForever);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        osDelay(500);
        osMutexRelease(mutex);
    }
}

void Task2(void *argument) {
    while (1) {
        osMutexAcquire(mutex, osWaitForever);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
        osDelay(1000);
        osMutexRelease(mutex);
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    osKernelInitialize();
    
    mutex = osMutexNew(NULL);
    
    osThreadNew(Task1, NULL, NULL);
    osThreadNew(Task2, NULL, NULL);
    osKernelStart();

    while (1) {
    }
}
