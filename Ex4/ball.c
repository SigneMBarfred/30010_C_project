/*
 * ball.c
 * a file that contains relevant functions for movement of ball for ex4
 *  Created on: Jan 9, 2024
 *      Author: signe
 */
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#include "math.h"
#include "ansi.h"

//first: define the structure for ball
typedef struct {
	int32_t pos_x,pos_y; //position
	int32_t v_x,v_y; //velocity
}vector_t;

int ballUpdate(vector_t *ball){ //scale factor is mentioned in exc desc; meaning?
	static int count;
    if (ball->pos_x>>14 <= 2+1 || ball->pos_x>>14 >= 140-2) {
        ball->v_x *= -1;
        count ++;

    }

    if (ball->pos_y>>14 <= 2+1  || ball->pos_y>>14 >= 40-1) {
       ball->v_y *= -1;
       count++;
    }

	ball->pos_x += ball->v_x; //It adds the right operand to the left operand and assign the result to the left operand
	ball->pos_y += ball->v_y;

	return count;


}


void drawBall(vector_t *ball){
	gotoxy(ball->pos_x>>14,ball->pos_y>>14);
	printf("%c",111);

}
