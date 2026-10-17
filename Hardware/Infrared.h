#ifndef __INFRARED_H
#define __INFRARED_H

#include "stm32f10x_gpio.h"

#define IR_SENSOR_L4_PORT GPIOA
#define IR_SENSOR_L4_PIN  GPIO_Pin_3
#define IR_SENSOR_L3_PORT GPIOB
#define IR_SENSOR_L3_PIN  GPIO_Pin_2
#define IR_SENSOR_L2_PORT GPIOA
#define IR_SENSOR_L2_PIN  GPIO_Pin_8
#define IR_SENSOR_L1_PORT GPIOB
#define IR_SENSOR_L1_PIN  GPIO_Pin_13
#define IR_SENSOR_R1_PORT GPIOB
#define IR_SENSOR_R1_PIN  GPIO_Pin_14
#define IR_SENSOR_R2_PORT GPIOB
#define IR_SENSOR_R2_PIN  GPIO_Pin_15
#define IR_SENSOR_R3_PORT GPIOB
#define IR_SENSOR_R3_PIN  GPIO_Pin_10
#define IR_SENSOR_R4_PORT GPIOC
#define IR_SENSOR_R4_PIN  GPIO_Pin_13

void Infrared_Init(void);
void Infrared_Track(void);
#endif



