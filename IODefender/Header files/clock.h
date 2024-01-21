#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <unistd.h>

#ifndef CLOCK_H_
#define CLOCK_H_

void configureTimer15();
volatile uint32_t counter;

void configureTimer16();

void initialiseTimer2();
void setBuzzerPin();
void buzzerOff();
void buzzerOn();
void setFreq(uint16_t freq);

#endif /* CLOCK_H_ */
