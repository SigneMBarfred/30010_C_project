/*
 * ball.h
 *
 *  Created on: Jan 9, 2024
 *      Author: signe
 */

#ifndef BALL_H_
#define BALL_H_
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#include "math.h"
#include "joystick.h"
#include "ansi.h"

typedef struct {
	int32_t pos_x,pos_y; //position
	int32_t v_x,v_y; //velocity
}vector_t;

int ballUpdate(vector_t *ball);
void drawBall(vector_t *ball);
void deleteBall(vector_t *ball);
void teleport(vector_t *ball);
void drawWormhole();
void setdir(vector_t *ball);


#endif /* BALL_H_ */
