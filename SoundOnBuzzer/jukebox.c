/*
 * melody.c
 *
 *  Created on: 17. jan. 2024
 *      Author: signe
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include "clock.h"
#include "melody.h"

volatile uint32_t c = 0; //flag, global variable

void TIM1_BRK_TIM15_IRQHandler(void) { //interrupt handler
	c++; //increment c when interrupt
	TIM15->SR &= ~(0x0001); //reset
}

int melody1(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;

	configureTimer15();
	initialiseTimer2();
	setBuzzerPin();

	uint16_t noteIndex = 0;
	c = 0;
	int lengthMelody = sizeof(marioMelody)/sizeof(marioMelody[0]); //amount of bytes of array divided by amount of bytes pr element



	while(1){//inefficient (busy loop)
		uint16_t newFreq = marioMelody[noteIndex];
		setFreq(newFreq);
		for(noteIndex = 0; noteIndex < lengthMelody; noteIndex++ ){ //loop through notes
			while (c < (marioDuration[noteIndex]*10)){}
			newFreq = marioMelody[noteIndex+1];
			setFreq(newFreq);
			c = 0;

		}

	}


}


//
