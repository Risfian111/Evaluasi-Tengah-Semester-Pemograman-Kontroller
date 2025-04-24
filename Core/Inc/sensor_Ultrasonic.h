// hcsr04.h
#ifndef HCSR04_H
#define HCSR04_H

#include <stdint.h>
#include "stm32f446xx.h"
#include "stm32f4xx.h"

// Tipe dummy untuk simulasi HAL

// Struktur sensor ultrasonic
typedef struct {
    TIM_HandleTypeDef *htim;
    GPIO_TypeDef *trigPort;
    uint16_t trigPin;
    GPIO_TypeDef *echoPort;
    uint16_t echoPin;
} ultrasonic_t;

// Fungsi inisialisasi sensor
void HCSR04_Init(TIM_HandleTypeDef *htim, GPIO_TypeDef *trigPort, uint16_t trigPin,
                 GPIO_TypeDef *echoPort, uint16_t echoPin);

// Fungsi baca jarak berdasarkan waktu pantulan
float HCSR04_ReadDistance();

#endif // HCSR04_H
