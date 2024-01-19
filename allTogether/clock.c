/*
 * clock.c
 *
 *  Created on: 12. jan. 2024
 *      Author: signe
 */



#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "stm32f30x.h"





void configureTimer16() {
    // Enable clock line to timer 16
    RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;

    // Configure timer 16 (CR1 settings)
    TIM16->CR1 &= 0xF400;  // Reset CR1 to default settings

    // Configure CR1 with the specified settings
    TIM16->CR1 |= 0 << 11;  // No UIFREMAP remapping
    TIM16->CR1 |= 0 << 8;  // No clock division (CKD)
    TIM16->CR1 |= 0 << 7;  // Non-buffered auto-reload preload (ARPE)
    TIM16->CR1 |= 0 << 3;  // One-pulse mode disabled (OPM)
    TIM16->CR1 |= 0 << 2;  // Any update request source (URS)
    TIM16->CR1 |= 0 << 1;  // Update events enabled (UDIS)


	/*to get interrupt signal at every milisec
	 * when interrupt is every 999th count
	 * and internal clock is at 64MHz
	 * prescale the clock freq with 64
	 */
    TIM16->PSC = 64;  // Set prescale value
    TIM16->ARR = 999;  // Set reload value

    TIM16->DIER |= 1;
    NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 2);
    NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

    // Enable the timer
    TIM16->CR1 |= TIM_CR1_CEN;  // Set the counter enable bit
}


void initialiseTimer2(){
	// Enable clock line to timer 2
	    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	    // Configure timer 2 (CR1 settings)
	    TIM2->CR1 &= 0xF400;  // Reset CR1 to default settings

	    TIM2->PSC = 64;  // Set prescale value
	    TIM2->ARR = 999;  // Set reload value

	    // Enable the timer
	    TIM2->CR1 |= TIM_CR1_CEN;  // Set the counter enable bit

	    TIM2->CCER &= ~TIM_CCER_CC3P;  // Clear CCER register
	    TIM2->CCER |= 0x00000001 << 8; // Enable OC3 output

	    //configure as in exc tutorial
		TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
		TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
		TIM2->CCMR2 |= TIM_OCMode_PWM1; // Set output mode to PWM1
		TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
		TIM2->CCMR2 |=  TIM_OCPreload_Enable;
		TIM2->CCR3 = 99 / 2; // Set duty cycle to 50 %

}



void setBuzzerPin(){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
	GPIOB->MODER &= ~(0x00000003 << (10 * 2)); // Clear mode register
	GPIOB->MODER |=  (0x00000002 << (10 * 2)); // Set mode register (0x00 –
	   //Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);

}



void setFreq(uint16_t freq) {
    uint32_t reload = 64e6 / freq;

    TIM2->ARR  = reload;   // Set reload value
    TIM2->CCR3 = reload/2; // Set compare register

    TIM2->EGR |= 0x01;
}

