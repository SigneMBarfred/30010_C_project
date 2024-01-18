/*
 * LEDsetup.h
 *
 *  Created on: 18. jan. 2024
 *      Author: signe
 */

#ifndef LEDSETUP_H_
#define LEDSETUP_H_


#include <stdint.h>
#include <stdio.h>

void setPinOut(GPIO_TypeDef *port, unsigned char pin);

void setupLEDPins();

void setLED(uint8_t color);  //..0RGB


#endif /* LEDSETUP_H_ */
