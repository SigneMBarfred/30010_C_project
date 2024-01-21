/*
 * menuOptions.c
 * a source file containing the different sub-screens that can be printed when somethin in the menu is accessed
 *  Created on: 19. jan. 2024
 *      Author: signe
 */

#include "ansi.h"



//the title
void printTitle(){ //generated via https://patorjk.com/software/taag/#p=display&f=Epic&t=IO%20%20%20%20%20Defender
	printf("\x1b[33m");

	gotoxy(25,5);
	puts("_________ _______            ______   _______  _______  _______  _        ______   _______  _______ ");
	gotoxy(25,6);
	puts("\\__   __/(  ___  )          (  __  \\ (  ____ \\(  ____ \\(  ____ \\( (    /|(  __  \\ (  ____ \\(  ____ )");
	gotoxy(25,7);
	puts("   ) (   | (   ) |          | (  \\  )| (    \\/| (    \\/| (    \\/|  \\  ( || (  \\  )| (    \\/| (    )|");
	gotoxy(25,8);
	puts("   | |   | |   | |          | |   ) || (__    | (__    | (__    |   \\ | || |   ) || (__    | (____)|");
	gotoxy(25,9);
	puts("   | |   | |   | |          | |   | ||  __)   |  __)   |  __)   | (\\ \\) || |   | ||  __)   |     __)");
	gotoxy(25,10);
	puts("   | |   | |   | |          | |   ) || (      | (      | (      | | \\   || |   ) || (      | (\\ (   ");
	gotoxy(25,11);
	puts("___) (___| (___) |          | (__/  )| (____/\\| )      | (____/\\| )  \\  || (__/  )| (____/\\| ) \\ \\__");
	gotoxy(25,12);
	puts("\\_______/(_______)          (______/ (_______/|/       (_______/|/    )_)(______/ (_______/|/   \\__/");
	resetFormat();
}


//the main menu
void printMainMenu(){
	printf("\x1b[33m");
	window(50, 20, 100, 30, "simple", "Main Menu");
	resetFormat();
	gotoxy(58,21);
	printf("Please select option with joystick: \n");
	gotoxy(62,23);
	printf("UP - Help \n");
	gotoxy(62,24);
	printf("DOWN - Bosskey");
	gotoxy(62,25);
	printf("RIGHT - Select difficulty\n");
	gotoxy(62,26);
	printf("CENTER - Start game\n");
	gotoxy(62,27);
	printf("LEFT - Quit programme\n");
}

void printBossKey(){
	clrscrn();
	resetFormat();
	printf("Microsoft Windows [Version 10.0.22621.3007]\n");
	printf("(c) Microsoft Corporation. All rights reserved.\n\n");
	printf("C:/User/30031Student>");
}


//the help text
void printHelp(){
	clrscrn();
	printTitle();
	printf("\x1b[33m");
	window(50, 20, 100, 40, "simple", "HELP");
	resetFormat();
	gotoxy(52,21);
	printf("Your mission is to defend Jupiters' moon, IO");
	gotoxy(52,22);
	printf("from hostile attackers!");
	gotoxy(52,23);
	printf("You have a set amount of lives - if an enemy");
	gotoxy(52,24);
	printf("reaches the moons' surface, you lose a life. ");
	gotoxy(52,25);
	printf("Shoot enemies before this happens by ");
	gotoxy(52,26);
	printf("pressing down on the grey button.");
	gotoxy(52,27);
	printf("But be careful! Io's gravity means your bullets");
	gotoxy(52,28);
	printf(" might fall down and hit you.");
	gotoxy(52,28);
	printf("Avoid getting hit by an enemy ship - this kills!");
	gotoxy(52,30);
	printf("Direct your spaceship with the joystick. ");

	gotoxy(62,35);
	printf("LEFT - Go back to menu");

}

//the gameover text


// the quit text

