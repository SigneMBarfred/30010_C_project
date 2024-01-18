/*
 * clock.h
 *
 *  Created on: 12. jan. 2024
 *      Author: signe
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course

#ifndef CLOCK_H_
#define CLOCK_H_

volatile uint32_t counter;

void TIM1_BRK_TIM15_IRQHandler(void);
void configureTimer15();

void initialiseTimer2();
void setBuzzerPin();
void buzzerOff();
void buzzerOn();
void setFreq(uint16_t freq);

#endif /* CLOCK_H_ */

