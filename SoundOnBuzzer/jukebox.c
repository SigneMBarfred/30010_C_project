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



	while(noteIndex < lengthMelody){//inefficient (busy loop)
		uint16_t newFreq = marioMelody[noteIndex];
		setFreq(newFreq);
		for(noteIndex = 0; noteIndex < lengthMelody; noteIndex++ ){ //loop through notes
			while (c < (marioDuration[noteIndex]*10)){}
			newFreq = marioMelody[noteIndex+1]*10;
			setFreq(newFreq);
			c = 0;

		}
	 // Dis-able the timer2 (stop signal to buzzer)
	    TIM2->CR1 &= ~TIM_CR1_CEN;  // Set the counter enable bit
	}


}

int loseSong(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //enable line to buzzer
	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;

	configureTimer15();
	initialiseTimer2();
	setBuzzerPin();

	uint16_t noteIndex = 0;
	c = 0;
	int lengthLoseMelody = sizeof(loseMelody)/sizeof(loseMelody[0]); //amount of bytes of array divided by amount of bytes pr element



	while(noteIndex < lengthLoseMelody){//inefficient (busy loop)
		uint16_t newFreq = loseMelody[noteIndex];
		setFreq(newFreq);
		for(noteIndex = 0; noteIndex < lengthLoseMelody; noteIndex++ ){ //loop through notes
			while (c < (loseDuration[noteIndex]*10)){}
			newFreq = loseMelody[noteIndex+1]*10;
			setFreq(newFreq);
			c = 0;

		}
	 // Dis-able the timer2 (stop signal to buzzer)
		TIM2->CR1 &= ~TIM_CR1_CEN;  // Set the counter enable bit
	}



}

int successSong(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //enable line to buzzer
	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;

	configureTimer15();
	initialiseTimer2();
	setBuzzerPin();

	uint16_t noteIndex = 0;
	c = 0;
	int lengthSuccessMelody = sizeof(successMelody)/sizeof(successMelody[0]); //amount of bytes of array divided by amount of bytes pr element



	while(noteIndex < lengthSuccessMelody){//inefficient (busy loop)
		uint16_t newFreq = successMelody[noteIndex];
		setFreq(newFreq);
		for(noteIndex = 0; noteIndex < lengthSuccessMelody; noteIndex++ ){ //loop through notes
			while (c < (successDuration[noteIndex]*10)){}
			newFreq = successMelody[noteIndex+1]*100;
			setFreq(newFreq);
			c = 0;

		}
	 // Dis-able the timer2 (stop signal to buzzer)
		TIM2->CR1 &= ~TIM_CR1_CEN;  // Set the counter enable bit
	}



}

//
