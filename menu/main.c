#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "ansi.h"
#include "joystick.h"
#include "getKeyPress.h"
#include "menuOptions.h"

int main()
{
	uart_init(250000);
	clrscrn();
	uint8_t choice;
	setupJoystickPins(1);
	int difficulty;



	int exitProgramme = 1;

	while (exitProgramme == 1){ //as long as use has not quit program, we default to main menu after having accessed a sub menu
		//title is here
		clrscrn();
		printTitle();
		//main menu is here:
		printMainMenu();




		int exitMenu = 1;
		while(exitMenu == 1){ // as long as an option has not been choosen
			choice = readJoy();

			//up = 2^0, down = 2^1, left = 2^2, right= 2^3, center = 2^4
			switch (choice){

				case 1: //HELP

					//clear menu text
					gotoxy(58,21);
					printf("                                        \n");

					gotoxy(58,23);
					printf("                             \n");

					gotoxy(58,24);
					printf("                             \n");

					gotoxy(58,25);
					printf("                             \n");

					gotoxy(58,26);
					printf("                             \n");

					gotoxy(58,27);
					printf("                             \n");

					printHelp();
					break;

				case 8: //right - difficulty
					clrscrn();
					printTitle();
					printf("\x1b[33m");
					window(50, 20, 100, 30, "simple", "DIFFICULTY");
					resetFormat();
					gotoxy(62,24);
					printf("Choose your difficulty\n");
					gotoxy(65,25);
					printf("UP - Easy\n");
					gotoxy(65,26);
					printf("RIGHT - Medium\n");
					gotoxy(65,27);
					printf("DOWN - Hard\n");


					difficulty = readJoy();

					if(difficulty==1){ //set speed to low
					//clear menu text

					gotoxy(58,21);
					printf("                                        \n");

					gotoxy(58,23);
					printf("                             \n");

					gotoxy(58,24);
					printf("                             \n");

					gotoxy(58,25);
					printf("                             \n");

					gotoxy(58,26);
					printf("                             \n");

					gotoxy(58,27);
					printf("                             \n");

					gotoxy(62,23);
					printf("Easy mode set");

					//do something in the gamemanager/update a variable that sets speed
					//difficultyModifier = ? ;

					}

					else if(difficulty == (1<<1)){ //set speed to medium

						gotoxy(58,21);
						printf("                                        \n");
						gotoxy(58,23);
						printf("                             \n");
						gotoxy(58,24);
						printf("                             \n");
						gotoxy(58,25);
						printf("                             \n");
						gotoxy(58,26);
						printf("                             \n");
						gotoxy(58,27);
						printf("                             \n");

						gotoxy(62,23);
						printf("Medium difficulty set");

					//do something
					// difficultyModifier = ? ;
					}

					else if(difficulty == (1<<3)){ //set speed to high
						gotoxy(58,21);
						printf("                                        \n");
						gotoxy(58,23);
						printf("                             \n");
						gotoxy(58,24);
						printf("                             \n");
						gotoxy(58,25);
						printf("                             \n");
						gotoxy(58,26);
						printf("                             \n");
						gotoxy(58,27);
						printf("                             \n");

						gotoxy(62,23);
						printf("Hard mode set");

					//do something
					// difficultyModifier = ? ;
					}

					//exitMenu = 0; //go back to main menu
					break;

				case 2:

					printf("\x1b[33m");
					window(50, 20, 100, 30, "simple", "HIGH SCORES");
					resetFormat();
					gotoxy(62,25);
					printf("These are your high scores");

					//display high scores
					//for example store a high score if it is higher than one of 3 scores already in a high score array - and then delete the minimum value
					//exitMenu = 0;
					break;

				case 16: //center push
					clrscrn();
					//run game logic

					exitMenu = 0;
					break;

				case 4: //left push
					//quit
					exitMenu = 0;
					exitProgramme = 0;
					break;

				default:
					break;

			}
		}
	}
clrscrn();
gotoxy(60,20);
printf("Goodbye!");


}
