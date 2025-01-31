#include "stm32f4xx.h"
#include "cmsis_os2.h"

void TimerInterrupt(void) {
    osThreadYield();
}

void Task1(void *argument) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        osDelay(500);
    }
}

void Task2(void *argument) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
        osDelay(1000);
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    osKernelInitialize();

    osThreadNew(Task1, NULL, NULL);
    osThreadNew(Task2, NULL, NULL);
    
    HAL_NVIC_EnableIRQ(TIM2_IRQn);  // 타이머 인터럽트 활성화
    
    osKernelStart();

    while (1) {
    }
}
