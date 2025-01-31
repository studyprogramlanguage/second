#include "stm32f4xx.h"
#include "cmsis_os2.h"

void Task1(void *argument) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        osDelay(1000);
    }
}

void Task2(void *argument) {
    while (1) {
        osDelay(5000);
        osThreadSuspend(NULL);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
        osThreadResume(osThreadGetId());
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    osKernelInitialize();

    osThreadNew(Task1, NULL, NULL);
    osThreadNew(Task2, NULL, NULL);
    osKernelStart();

    while (1) {
    }
}
