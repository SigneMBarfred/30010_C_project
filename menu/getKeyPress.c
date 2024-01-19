/*
 * getKeyPress.c
 *
 *  Created on: 16. jan. 2024
 *      Author: signe
 */


#include <stdio.h>
#include "ansi.h"
#include "joystick.h"

// -- takes keyboard input and appends to array
char getKeyboardInput(){
	setupJoystickPins(0); //disable joystick while this runs
    char playerName[25]; // max size of name

    int index = 0;
    char playerLetter;

    do {
        playerLetter = uart_get_char();

        if (playerLetter != '\r') { //so dont collect any more chars if carriage return is pressed
            if (index < (sizeof(playerName) - 1)) { //or if 24 chars are already in string
                playerName[index] = playerLetter;
                index++;
                printf("%d\n", index);
            } else {
                printf("Name too long. Only 25 characters permitted\n");
            }
        }
    } while (playerLetter != '\r');

    playerName[index] = '\0'; // add terminator

    printf("\nYour chosen name is: %s\n", playerName);

    setupJoystickPins(1); //enable joystick again

    return playerName[0]; // Return the first character if needed
}

//	char playerName[25]; //set max size of name
//
//	int index = 0;
//	char playerLetter;
//	uart_clear(); //clear buffer
//
//	do {
//
//		playerLetter = uart_get_char();
//
//		if (index < (strlen(playerName)-1)){
//			//remember we start at 0, so -1
//
//			playerName[index] = playerLetter;
//			index++;
//			printf("%d\n", index);
//		}
//
//		else{
//			printf("Name too long. Only 25 characters permitted\n");
//
//		}
//	}
//	while(playerLetter != '\r');
//
//	playerName[index] = '\0';
//
//	printf("\nYour choosen name is: %s", playerName);
//

    // creating character buffer 25 chars
//    char * buf[25];
//
//    // character pointer for the address of the first character
//    char *ptr;
//
//    // variable to take input of single character
//    char ch;
//
//    // assigning the address of the first character to ptr
//    ptr = buf;
//
//    // Logic to take input of n characters using a while loop
//    while ((ch = uart_get_char()) != '\r' && ch != EOF) {
//        *ptr++ = ch;
//    }
//    *ptr++ = 0;
//    if (ch == EOF) {
//        printf("EOF encountered\n");
//    }
//    gotoxy(4,5);
//	return buf[3];
