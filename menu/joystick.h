/*
 * joystick.h
 *
 *  Created on: 15. jan. 2024
 *      Author: signe
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_


#include <stdint.h>
#include <stdio.h>

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"

//Ports for joystick C0, A4, B5, C1, B0
void setPinIn(GPIO_TypeDef *port, unsigned char pin);

void setPinOut(GPIO_TypeDef *port, unsigned char pin);

void setPin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);

void setPort(GPIO_TypeDef *port, uint8_t pins, uint8_t value);

void setupJoystickPins(uint8_t on);

uint16_t readPort(GPIO_TypeDef *port, uint16_t pins);

char readSinglePin(GPIO_TypeDef *port, uint8_t pin);

uint8_t readJoy();
void deSetPinIn();
void deInitJoystickPins();


#endif /* JOYSTICK_H_ */
