#ifndef HEATER_H
#define HEATER_H

#include <stdint.h>
#include "stm32f4xx_hal.h"  // Include STM32 HAL header for GPIO functions

// Structure for Heater
typedef struct {
    GPIO_TypeDef *port;  // GPIO Port for controlling the heater
    uint16_t pin;        // GPIO Pin for controlling the heater
    uint8_t state;       // Heater state: 0 = OFF, 1 = ON
} heater_t;

// Function to initialize the heater (setting port and pin)
void Heater_Init(heater_t *heater, GPIO_TypeDef *port, uint16_t pin);

// Function to turn on the heater
void Heater_On();

// Function to turn off the heater
void Heater_Off();

// Function to toggle the heater state
void Heater_Toggle(heater_t *heater);

// Function to simulate GPIO pin write (optional for your own implementation)
void HAL_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState PinState);

#endif // HEATER_H
