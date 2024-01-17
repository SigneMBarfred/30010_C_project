/*
 * getKeyPress.c
 *
 *  Created on: 16. jan. 2024
 *      Author: signe
 */


#include <stdio.h>
#include "ansi.h"

// -- takes keyboard input and appends to array
char getKeyboardInput(){
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


    // creating character buffer of n(here 20) characters
    char buf[20];

    // character pointer for the address of the first character
    char *ptr;

    // variable to take input of single character
    char ch;

    // assigning the address of the first character to ptr
    ptr = buf;
    printf("Enter player name: ");

    // Logic to take input of n characters using a while loop
    while ((ch = uart_get_char()) != '\r' && ch != EOF) {
        // *ptr++ = (char)ch;
        *ptr++ = ch;
    }
    *ptr++ = 0;
    if (ch == EOF) {
        printf("EOF encountered\n");
    }
    gotoxy(4,5);

	return buf[3];

}
