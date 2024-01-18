/*
 * LEDsetup.c
 *
 *  Created on: 18. jan. 2024
 *      Author: signe
 */


#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdio.h>
#include "joystick.h"


#define LED_R GPIOB, 4
#define LED_G GPIOC, 7
#define LED_B GPIOA, 9

void setPinOut(GPIO_TypeDef *port, unsigned char pin){
	port -> OSPEEDR &= ~(0x3 << (pin * 2)); // Clear speed register
	port -> OSPEEDR |= (0x2 << (pin * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2MHz, 0x03 - 50MHz)

	port -> OTYPER &= ~(0x1 << (pin * 1)); // Clear output type register
	//port -> OTYPER |= (0x0000 << (pin)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)

	port -> MODER &= ~(0x00000003 << (pin * 2)); // Clear mode register
	port -> MODER |= (0x00000001 << (pin * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
}

void setupLEDPins(){
	RCC-> AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC-> AHBENR |= RCC_AHBPeriph_GPIOB;
	RCC-> AHBENR |= RCC_AHBPeriph_GPIOC;

	setPinOut(LED_R);
	setPinOut(LED_G);
	setPinOut(LED_B);


	setPin(LED_R, 1);
	setPin(LED_G, 0);
	setPin(LED_B, 0);

}

void setLED(uint8_t color){  //..0RGB
	color = ~color; //we tell MCU what LEDs not to light up

	setPin(LED_R, (color & (1 << 2)));
	setPin(LED_G, (color & (1 << 1)));
	setPin(LED_B, (color & 1));

	if (readJoy() == (1 << 3)){ //cyan
		setPin(LED_G, (color & (1 << 3)));
		setPin(LED_B, (color & (1 << 3)));
	}
	if (readJoy() == (1 << 4)){ //magenta
		setPin(LED_R, (color & (1 << 4)));
		setPin(LED_B, (color & (1 << 4)));
	}

	//printf("LED: (%d, %d, %d)", readSinglePin(LED_R), readSinglePin(LED_G), readSinglePin(LED_B));
}



