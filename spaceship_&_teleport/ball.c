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
#include "joystick.h"


//first: define the structure for ball
typedef struct {
	int32_t pos_x,pos_y; //position
	int32_t v_x,v_y; //velocity
}vector_t;
//

void setdir(vector_t *ball){ 		//up = 2^0, down = 2^1, left = 2^2, right= 2^3, center = 2^4
	uint8_t readball = readJoy();
	if(readball == 1){
		ball->v_x = 0;
		ball->v_y = -1 <<14 ;
	}
	else if(readball == (1 << 1)){
		ball->v_x = 0;
		ball->v_y = 1 << 14;
	}
	else if(readball == (1 << 2)){
		ball->v_x = -1 << 14;
		ball->v_y = 0;
	}
	else if(readball == (1 << 3)){
		ball->v_x = 1 << 14;
		ball->v_y = 0;
	}
	else if(readball == (1 << 4)){
		ball->v_x = 0;
		ball->v_y = 0;
	}
}



int ballUpdate(vector_t *ball){ //scale factor is mentioned in exc desc; meaning?
	static int count;

	int32_t xcoo = (ball->pos_x) >>14;
	int32_t ycoo = (ball->pos_y) >>14;

	if (xcoo <= 2+1 || xcoo >= 140-13) {
        ball->v_x *= -1;
        count ++;
    }

    if (ycoo <= 2+2  || ycoo >= 40-9) {
       ball->v_y *= -1;
       count++;
    }


	ball->pos_x += ball->v_x; //It adds the right operand to the left operand and assign the result to the left operand
	ball->pos_y += ball->v_y;
	return count;


}


void drawBall(vector_t *ball){//based on ascii art from http://www.ascii-art.de/ascii/pqr/rockets.txt
	int32_t xcoo = ball->pos_x>>14;
	int32_t ycoo = ball->pos_y>>14;

	gotoxy(xcoo,ycoo);

    puts("   /\\   ");
    gotoxy(xcoo,ycoo+1);
    puts("  /  \\  ");
    gotoxy(xcoo,ycoo+2);
    puts(" /|{}|\\ ");
    gotoxy(xcoo,ycoo+3);
    puts("/_|__|_\\" );
}

void deleteBall(vector_t *ball){
	int32_t xcoo = (ball->pos_x - ball->v_x) >>14;
	int32_t ycoo = (ball->pos_y - ball->v_y) >>14;

	gotoxy(xcoo,ycoo-1);
	printf("         ");
	gotoxy(xcoo,ycoo);
	printf("         ");
	gotoxy(xcoo,ycoo+1);
	printf("         ");
	gotoxy(xcoo,ycoo+2);
	printf("         ");
	gotoxy(xcoo,ycoo+3);
	printf("         ");
	gotoxy(xcoo,ycoo+4);
	printf("         ");


}

void drawWormhole(){
	int32_t worm1x = 13;
	int32_t worm1y = 10;
	uint8_t on = 1;
	uint8_t off = 0;
	blink(on);
	gotoxy(worm1x-1,worm1y-1);
	printf("  %c ",196);
	gotoxy(worm1x-1,worm1y);
	printf("( O )");
	gotoxy(worm1x-1,worm1y+1);
	printf("  %c ",196);
	blink(off);


}

void teleport(vector_t *ball){
	int32_t worm1x = 13;
	int32_t worm1y = 10;

	int32_t worm2x = 100;
	int32_t worm2y = 20;

	int32_t xcoo = (ball->pos_x) >>14;
	int32_t ycoo = (ball->pos_y) >>14;
	static int teleportations;

	if (worm1x-3< xcoo && xcoo < worm1x+3 && worm1y-3 < ycoo && ycoo < worm1y+3 ){

		ball->pos_x = worm2x<<14; //update ball pos
		ball->pos_y = worm2y<<14;

		//set red and mark wormhole
		setRed(1);
		gotoxy(worm1x-1,worm1y-1);
		printf("  %c ",196);
		gotoxy(worm1x-1,worm1y);
		printf("( @ )");
		gotoxy(worm1x-1,worm1y+1);
		printf("  %c ",196);

		//print the wormhole we exit from
		gotoxy(worm2x-1,worm2y-1);
		printf("  %c ",196);
		gotoxy(worm2x-1,worm2y);
		printf("( O )");
		gotoxy(worm2x-1,worm2y+1);
		printf("  %c ",196);
		setRed(0);

        for (int i = 0; i < 300000; ++i) { //delay before deleting wormhole
            asm("nop"); //no operation instruction on assembly level
        }

		//delete the wormhole we exit from
		gotoxy(worm2x-1,worm2y-1);
		printf("     ");
		gotoxy(worm2x-1,worm2y);
		printf("     ");
		gotoxy(worm2x-1,worm2y+1);
		printf("     ");


		teleportations++; //check why ship doesnt teleport after hitting wormhole twice
		gotoxy(145,10);
		printf("t: %d", teleportations);

	}
}
