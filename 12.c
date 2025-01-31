#include "stm32f4xx.h"
#include "cmsis_os2.h"

osTimerId_t timerId;

void TimerCallback(void *argument) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    osKernelInitialize();

    osTimerDef(timerId, TimerCallback);
    timerId = osTimerNew(TimerCallback, osTimerPeriodic, NULL, NULL);
    osTimerStart(timerId, 500);

    osKernelStart();

    while (1) {
    }
}
