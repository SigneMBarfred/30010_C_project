#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdint.h>
#include <stdlib.h>
#include "ansi.h"
#include "background.h"



void drawLevel(uint8_t rq[160]){

	//printf("RenderEngine: Starting drawLevel()...");

	int i,j;
	char playerS[9]   = {0x2F, 0x41, 0x5C, 0x7C, 0x58, 0x7C, 0x5C, 0x56, 0x2F};
	char bulletS      = 0xDB;
	char alienS[9]    = {0x2F, 0x6F, 0x5C, 0x7C, 0x58, 0x7C, 0x5C, 0x6F, 0x2F};

	printf("\x1b[0m");
	printf("\x1b[2J\x1b[H");
	//printf("RenderEngine: Cleared screen, rendering...");
	createStars(1, 1, 31, 31, 221);
	for (i = 0 ; i < 32 ;){
		switch (rq[i]){
			case 10:
				// Player render
				//printf("\x1b[2;2Hi = %d, rq = %d", i, rq[i]);
				printf("\x1b[%d;%dH\x1b[34m%c%c%c",rq[i+1]-1,rq[i+2]-1,playerS[0],playerS[1],playerS[2]);
				printf("\x1b[%d;%dH\x1b[34m%c%c%c",rq[i+1]  ,rq[i+2]-1,playerS[3],playerS[4],playerS[5]);
				printf("\x1b[%d;%dH\x1b[34m%c%c%c",rq[i+1]+1,rq[i+2]-1,playerS[6],playerS[7],playerS[8]);
				i += 3;
				//printf("\x1b[3;2Hi = %d, rq = %d", i, rq[i]);
				break;
			case 11:
				// Bullet render
				printf("\x1b[%d;%dH\x1b[%dm%c",rq[i+1],rq[i+2],rq[i+3]+32,bulletS);

				i += 4;
				break;
			case 12:
				// Alien render
				printf("\x1b[%d;%dH\x1b[31m%c%c%c",rq[i+1]-1,rq[i+2]-1,alienS[0],alienS[1],alienS[2]);
				printf("\x1b[%d;%dH\x1b[31m%c%c%c",rq[i+1]  ,rq[i+2]-1,alienS[3],alienS[4],alienS[5]);
				printf("\x1b[%d;%dH\x1b[31m%c%c%c",rq[i+1]+1,rq[i+2]-1,alienS[6],alienS[7],alienS[8]);
				printf("\x1b[31;16H d\x1b[2K");

				i += 3;
				continue;

			case 13:
			// Asteroid render
				printf("\x1b[%d;%dH\x1b[37m2xP",rq[i+1],rq[i+2]-1);
				i += 3;
				break;

			case 14:
				i = 160; // Terminate RenderQueue
				printf("\x1b[37m");
				break;
			default:
				i = 160;
				printf("\x1b[38m");
				break;
		}
		printf("\x1b[31;16H d");
	}




	 // Planet texture
		printf("\x1b[0m");
		printf("\x1b[%d;1H     _____________________________________________________", 29);
		printf("\x1b[%d;1H    /                                                     %c", 30, 0x5C);
		printf("\x1b[%d;1H   /                                                       %c", 31, 0x5C);
		printf("\x1b[%d;1H  /                                                         %c", 32, 0x5C);

	return;
}
