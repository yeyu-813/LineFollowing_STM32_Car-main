#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"
#include "Infrared.h"
#include "Car1.h"

static GPIO_TypeDef * const Sensor_Ports[8] = {
    IR_SENSOR_L4_PORT, IR_SENSOR_L3_PORT, IR_SENSOR_L2_PORT, IR_SENSOR_L1_PORT,
    IR_SENSOR_R1_PORT, IR_SENSOR_R2_PORT, IR_SENSOR_R3_PORT, IR_SENSOR_R4_PORT
};

static const uint16_t Sensor_Pins[8] = {
    IR_SENSOR_L4_PIN, IR_SENSOR_L3_PIN, IR_SENSOR_L2_PIN, IR_SENSOR_L1_PIN,
    IR_SENSOR_R1_PIN, IR_SENSOR_R2_PIN, IR_SENSOR_R3_PIN, IR_SENSOR_R4_PIN
};

static const int8_t Sensor_Weights[8] = {-7, -5, -3, -1, 1, 3, 5, 7};

void Infrared_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                             RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_13 |
                                  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Infrared_Track(void){
	static uint8_t Last_Direction = 0;
    uint8_t sensor_state = 0;
    uint8_t active_count = 0;
    uint8_t i;
    int16_t position = 0;
    int16_t magnitude;

    for (i = 0; i < 8; i++)
    {
        if (GPIO_ReadInputDataBit(Sensor_Ports[i], Sensor_Pins[i]) != RESET)
        {
            sensor_state |= (uint8_t)(1u << (7u - i));
            position += Sensor_Weights[i];
            active_count++;
        }
    }

    if (sensor_state == 0x00)
    {
        if (Last_Direction == 1)      { Self_Left(); }
        else if (Last_Direction == 2) { Self_Right(); }
        else                          { Go_Ahead(); }
        return;
    }

    if (sensor_state == 0xFF)
    {
        Car_Stop();
        Last_Direction = 0;
        return;
    }

    magnitude = (position < 0) ? -position : position;
    if (magnitude <= active_count)
    {
        Go_Ahead();
        Last_Direction = 0;
    }
    else if (magnitude <= (int16_t)(3 * active_count))
    {
        if (position < 0)
        {
            Turn_Left();
            Last_Direction = 1;
        }
        else
        {
            Turn_Right();
            Last_Direction = 2;
        }
    }
    else if (position < 0)
    {
        Self_Left();
        Last_Direction = 1;
    }
    else
    {
        Self_Right();
        Last_Direction = 2;
    }
}
