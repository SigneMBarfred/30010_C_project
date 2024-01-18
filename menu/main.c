#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "joystick.h"
#include "getKeyPress.h"

int main()
{
	uart_init(115200);
	uint8_t choice;
	setupJoystickPins();

	char playerName[25]; //string
	int difficulty;


	clrscrn();
	printf("\x1b[33m");
	window(50, 20, 100, 30, "simple", "Main Menu");
	resetFormat();

	gotoxy(58,21);
	printf("Please select option with joystick: \n");
	gotoxy(62,23);
	printf("UP - Input player name \n");
	gotoxy(62,24);
	printf("RIGHT - Select difficulty\n");
	gotoxy(62,25);
	printf("DOWN - View high scores\n");
	gotoxy(62,26);
	printf("CENTER - Start game\n");
	gotoxy(62,27);
	printf("LEFT - Quit programme\n");

	while(1){

		choice = readJoy();

		//up = 2^0, down = 2^1, left = 2^2, right= 2^3, center = 2^4
		switch (choice){

			case 1: //input player name

				clrscrn();
				gotoxy(0,0);
				printf("Type in player name:\n");
				char str1;
				str1 = getKeyboardInput();
			    printf("Your choosen name is : %s\n", str1);





				break;

			case 8: //right - difficulty
				clrscrn();
				gotoxy(0,0);
				printf("Choose your difficulty\n");

				difficulty = readJoy();
				break;

			case 2:
				clrscrn();
				//display high scores
				break;

			case 16:
				clrscrn();
				//run game logic
				break;

			case 4:
				clrscrn();
				exit(0);
		}





		}
}
