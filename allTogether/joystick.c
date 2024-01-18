/*
 * joystick.c
 *
 *  Created on: 15. jan. 2024
 *      Author: signe + mikkel
 */


#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdio.h>



#define RIGHT_JOY GPIOC, 0
#define UP_JOY GPIOA, 4
#define CENTER_JOY GPIOB, 5
#define LEFT_JOY GPIOC, 1
#define DOWN_JOY GPIOB, 0



//Ports for joystick C0, A4, B5, C1, B0

void setPinIn(GPIO_TypeDef *port, unsigned char pin){
	port-> MODER &= ~(0x00000003 << (pin * 2)); // Clear mode register
	//port-> MODER |= (0x00000000 << (pin * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

	port->PUPDR &= ~(0x00000003 << (pin * 2)); // Clear push/pull register
	port->PUPDR |= (0x00000002 << (pin * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

}

void setPin(GPIO_TypeDef *port, uint8_t pin, uint8_t value){
	if(value)
		port -> ODR |= (0x0001 << pin);
	else
		port -> ODR &= ~(0x0001 << pin);
}
void setPort(GPIO_TypeDef *port, uint8_t pins, uint8_t value){
	port -> ODR &= ~pins; 	//Setting selected pins in register to zero
	value &= pins; 			//Masking value with selected pins
	port -> ODR &= value;	//Setting the pins in the array
}

void setupJoystickPins(){
	RCC-> AHBENR |= RCC_AHBPeriph_GPIOA;
	RCC-> AHBENR |= RCC_AHBPeriph_GPIOB;
	RCC-> AHBENR |= RCC_AHBPeriph_GPIOC;

	setPinIn(UP_JOY);
	setPinIn(GPIOB, 0);
	setPinIn(GPIOB, 5);
	setPinIn(GPIOC, 0);
	setPinIn(GPIOC, 1);
}


	uint16_t readPort(GPIO_TypeDef *port, uint16_t pins){
		return port -> IDR & pins;
	}

char readSinglePin(GPIO_TypeDef *port, uint8_t pin){
	uint16_t reading = port -> IDR & (1 << pin);
	return (char) (reading >> pin);
}

uint8_t readJoy(){
	uint8_t joy = 0;
	joy |= readSinglePin(UP_JOY) << 0;
	joy |= readSinglePin(DOWN_JOY) << 1;
	joy |= readSinglePin(LEFT_JOY) << 2;
	joy |= readSinglePin(RIGHT_JOY) << 3;
	joy |= readSinglePin(CENTER_JOY) << 4;

	return joy;
}


// Function to configure ADC
void configureADC() {
    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12; // Clear ADC12 prescaler bits
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6; // Set ADC12 prescaler to 6
    RCC->AHBENR |= RCC_AHBPeriph_ADC12; // Enable clock for ADC12

    ADC1->CR = 0x00000000; // Clear CR register
    ADC1->CFGR &= 0xFDFFC007; // Clear ADC1 config register
    ADC1->SQR1 &= ~ADC_SQR1_L; // Clear regular sequence register 1

    ADC1->CR |= 0x10000000; // Enable internal ADC voltage regulator
    for (int i = 0; i < 1000; i++) {} // Wait for about 16 microseconds

    ADC1->CR |= 0x80000000; // Start ADC1 calibration
    while (!(ADC1->CR & 0x80000000)); // Wait for calibration to finish
    for (int i = 0; i < 100; i++) {} // Wait for a little while

    ADC1->CR |= 0x00000001; // Enable ADC1 (0x01 - Enable, 0x02 - Disable)
    while (!(ADC1->ISR & 0x00000001)); // Wait until ready
}

// Function to perform ADC measurement on a specific channel
uint16_t measureADC(uint8_t channel) {
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0);
    return ADC_GetConversionValue(ADC1);
}


