//aim is to make a window with a moving ball and a hit counter
#define ESC 0x1B
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdint.h> // standard lib specifying int types
#include "ansi.h" //include ANSI escape codes and function
#include "stdio.h"
#include "stdlib.h"
#include "ball.h"
#include <string.h> //for the draw window function



int main(void){

	uart_init(115200); //initialise receiver at baud 9600


	//define a ball
	vector_t Ball;
	Ball.pos_x = 80 << 14; //bitshift so we get 2.14 not 32.0
	Ball.pos_y = 20 << 14; //bitshift

	Ball.v_x = 1 << 14;
	Ball.v_y = 1 << 14;


	clrscrn();
	resetFormat(); //undoes whatever formatting was activated so that next run is "normal"

	//make window that fits terminal
	window(2, 2, 140, 40, "double", "|IO DEFENDER|");



	//printf("Start position of ball: (%d, %d)\n", Ball.pos_x >> 14, Ball.pos_y >> 14);
	//printf("velocity: (%d, %d)\n", Ball.v_x >> 14, Ball.v_y >> 14);


	// Update the ball using the function
	ballUpdate(&Ball);
	//printf("updated position of ball: (%d, %d)\n", Ball.pos_x >> 14, Ball.pos_y >> 14);

	//draw ball
	drawBall(&Ball);
	static int count = 0;
	//now, we will delete the ball each time we wish to print it in a new position. this is accomplished in below while loop
    while (1) {
    	teleport(&Ball);
        drawBall(&Ball);
        ballUpdate(&Ball); //updates ball, velocity and count

        for (int i = 0; i < 100000; ++i) { //delay so the ball moves at slower speed
            asm("nop"); //no operation instruction on assembly level
        }


        deleteBall(&Ball);
        printf("%c[H", ESC); //home cursor

    	box(60, 18, 80, 23, "simple","Hit Count:\n");
        gotoxy(70,21);
    	printf("%d",ballUpdate(&Ball)); //ballupdate outputs a hit count
    	drawWormhole();
    }


	//make box inside window
	box(60, 18, 80, 23, "simple","Hit Count");
	//update counter



	while(1){}
}