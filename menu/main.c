#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "joystick.h"
#include "getKeyPress.h"

int main()
{
	uart_init(9600);
	uint8_t choice;
	setupJoystickPins();

	char playerName[25]; //string
	int difficulty;


	clrscrn();
	printf("Main menu\n");

	printf("Please select option with joystick \n");

	printf("UP - Input player name \n");
	printf("RIGHT - Select difficulty\n");
	printf("DOWN - View high scores\n");
	printf("CENTER - Start game\n");
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