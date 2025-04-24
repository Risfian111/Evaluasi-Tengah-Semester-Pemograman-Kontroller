#include "sensor_Ultrasonic.h"
#include "stm32f4xx_hal.h"

static TIM_HandleTypeDef *ultra_htim;
static GPIO_TypeDef *ultra_trig_port, *ultra_echo_port;
static uint16_t ultra_trig_pin, ultra_echo_pin;

void HCSR04_Init(TIM_HandleTypeDef *htim, GPIO_TypeDef *trigPort, uint16_t trigPin, GPIO_TypeDef *echoPort, uint16_t echoPin) {
    ultra_htim = htim;
    ultra_trig_port = trigPort;
    ultra_trig_pin = trigPin;
    ultra_echo_port = echoPort;
    ultra_echo_pin = echoPin;
}

float HCSR04_ReadDistance(int32_t echo_time_us) {
    uint32_t stop_time = 0;

    // Trigger pulse
    HAL_GPIO_WritePin(ultra_trig_port, ultra_trig_pin, GPIO_PIN_RESET);
    for (volatile int i = 0; i < 100; i++); // Short ~2us delay
    HAL_GPIO_WritePin(ultra_trig_port, ultra_trig_pin, GPIO_PIN_SET);
    for (volatile int i = 0; i < 1000; i++); // ~10us delay
    HAL_GPIO_WritePin(ultra_trig_port, ultra_trig_pin, GPIO_PIN_RESET);

    // Wait for echo start
    while (HAL_GPIO_ReadPin(ultra_echo_port, ultra_echo_pin) == GPIO_PIN_RESET);
    __HAL_TIM_SET_COUNTER(ultra_htim, 0);

    // Wait for echo end
    while (HAL_GPIO_ReadPin(ultra_echo_port, ultra_echo_pin) == GPIO_PIN_SET);
    stop_time = __HAL_TIM_GET_COUNTER(ultra_htim);

    // Distance in cm
    float distance = (stop_time * 0.0343f) / 2.0f;
    return distance;
}
