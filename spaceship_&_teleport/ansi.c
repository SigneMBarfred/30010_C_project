/*
 * ansi.c
 *
 *  Created on: Jan 9, 2024
 *      Author: signe
 */


#define ESC 0x1B

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include <string.h>

//a function that clears screen
void clrscrn() {

	printf("%c[2J", ESC); //clear
	printf("%c[H", ESC); //home
}


//a function that clears current line
void clreol() {
	printf("%c[K", ESC);
}

// a function that moves cursor to specified position
void gotoxy(int x, int y){
	printf("%c[%d;%dH",ESC,y,x);
}

// a function that can turn on/off underline when parameter 1 or not 1 is taken
void underline(uint8_t on){
	int p = (on == 1) ? 4 : 24 ; //? is an if else statement - if on is true, then parameter is 4 - otherwise 24 (turn of underline)
	printf("%c[%dm", ESC, p);
}

// a function that can turn on/off blink when parameter 1 or not 1 is taken
void blink(uint8_t on){
	int p = (on == 1) ? 5 : 25 ; //? is an if else statement - if on is true, then parameter is 5 - otherwise 25 (turn of blink)
	printf("%c[%dm", ESC, p);
}

void setRed(uint8_t on){
	int p = (on == 1) ? 31 : 0 ; //? is an if else statement - if on is true, then parameter is 5 - otherwise 25 (turn of blink)
	printf("%c[%dm", ESC, p);
}


// a function that reverses text colour
void inverse(uint8_t on){
	int p = (on == 1) ? 7 : 27 ; //? is an if else statement - if on is true, then parameter is 7 - otherwise 27 (turn of reversal)
	printf("%c[%dm", ESC, p);
}




// a function to clear format when parameter is given
void resetFormat(){
	printf("%c[0m", ESC);
}


// ------------------------------------------ DRAW WINDOW -------------------------------
//a function that takes two sets of coo and style as well as title input and then writes out a boxed area in terminal
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *style, const char *title){

	clrscrn(); //start from fresh
	gotoxy(x1,y1); //move cursor to starting position
	// we can take a number of different styles. each has a set of vertical/horistonal ascii chars
	// therefore: define these vertical and horistonal variables so we can assign them an ascii char for each style

	char horisontalCharacter,
		verticalCharacter,
		upperLeftCorner,
		upperRightCorner,
		lowerLeftCorner,
		lowerRightCorner;

	// assign ASCII chars based on the style parameter. for this, compare string input for style. strcmp returns 0 if strings are equal and 1 if not equal
	if (strcmp(style,"simple") == 0){
		horisontalCharacter = 196; //single thin lines
		verticalCharacter = 179;
		upperLeftCorner = 218;
		upperRightCorner = 191;
		lowerLeftCorner = 192;
		lowerRightCorner = 217;

	} else if(strcmp(style, "double") == 0){
		horisontalCharacter = 205; //double thin lines
		verticalCharacter = 186;
		upperLeftCorner = 201;
		upperRightCorner = 187;
		lowerLeftCorner = 200;
		lowerRightCorner = 188;

	} else {
		horisontalCharacter = 42; // asterix if no recognized style is given
		verticalCharacter = 42;
		upperLeftCorner = 42;
		upperRightCorner = 42;
		lowerLeftCorner = 42;
		lowerRightCorner = 42;
	}

	//figure out characteristics of the title and give it position central to horisontal span
	int titleLen = strlen(title);
	int titlePos = (x2-x1 - titleLen) /2; //so we get first the length of horisontal border and then we figure out what length is left when we have made space for the title. that is then divided by 2


	// --------- construct the box ----------

	// upper edge spans upper LeftCorner to upper RightCorner
	printf("%c", upperLeftCorner);
	for (int i = 0; i < x2 - x1 - 2; i++){  //now for the line where we loop over the distance in increments. notice we subtract 2 from the length bc those spaces are filled by the corners
		if (i== titlePos){
			printf("%s",title);
			i += strlen(title) - 1;
		} else{
			printf("%c", horisontalCharacter);
		}
	}
	printf("%c\n", upperRightCorner);


	//vertical lengths are now printed line by line
    for (int i = y1 + 1; i < y2; i++) {
        printf("%c[%dC%c", ESC, x1-1, verticalCharacter);
        for (int j = 0; j < x2 - x1 - 2; j++) {
            printf(" ");
        }
        printf("%c\n", verticalCharacter);
    }

	//bottom line is drawn:
		printf("%c[%dC%c", ESC, x1-1, lowerLeftCorner);
		for (int i = 0; i < x2 - x1 - 2; i++){  //now for the line where we loop over the distance in increments. notice we subtract 2 from the length bc those spaces are filled by the corners
				printf("%c", horisontalCharacter);
		}
		printf("%c\n", lowerRightCorner);
}

// ---------- ex.4 box w text --------
//box with text
void box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *style, const char *text){

	//clrscrn(); //start from fresh
	gotoxy(x1,y1); //move cursor to starting position
	// we can take a number of different styles. each has a set of vertical/horistonal ascii chars
	// therefore: define these vertical and horistonal variables so we can assign them an ascii char for each style

	char horisontalCharacter,
		verticalCharacter,
		upperLeftCorner,
		upperRightCorner,
		lowerLeftCorner,
		lowerRightCorner;

	// assign ASCII chars based on the style parameter. for this, compare string input for style. strcmp returns 0 if strings are equal and 1 if not equal
	if (strcmp(style,"simple") == 0){
		horisontalCharacter = 196; //single thin lines
		verticalCharacter = 179;
		upperLeftCorner = 218;
		upperRightCorner = 191;
		lowerLeftCorner = 192;
		lowerRightCorner = 217;

	} else if(strcmp(style, "double") == 0){
		horisontalCharacter = 205; //double thin lines
		verticalCharacter = 186;
		upperLeftCorner = 201;
		upperRightCorner = 187;
		lowerLeftCorner = 200;
		lowerRightCorner = 188;

	} else {
		horisontalCharacter = 42; // asterix if no recognized style is given
		verticalCharacter = 42;
		upperLeftCorner = 42;
		upperRightCorner = 42;
		lowerLeftCorner = 42;
		lowerRightCorner = 42;
	}


	// --------- construct the box ----------

	// upper edge spans upper LeftCorner to upper RightCorner
	printf("%c", upperLeftCorner);
	for (int i = 0; i < x2 - x1 - 2; i++){  //now for the line where we loop over the distance in increments. notice we subtract 2 from the length bc those spaces are filled by the corners
		printf("%c", horisontalCharacter);
	}
	printf("%c\n", upperRightCorner);


	//vertical lengths are now printed line by line
    for (int i = y1 + 1; i < y2; i++) {
        printf("%c[%dC%c", ESC, x1-1, verticalCharacter);
        for (int j = 0; j < x2 - x1 - 2; j++) {
            printf(" ");
        }
        printf("%c\n", verticalCharacter);
    }

	//bottom line is drawn:
		printf("%c[%dC%c", ESC, x1-1, lowerLeftCorner);
		for (int i = 0; i < x2 - x1 - 2; i++){  //now for the line where we loop over the distance in increments. notice we subtract 2 from the length bc those spaces are filled by the corners
				printf("%c", horisontalCharacter);
		}
		printf("%c\n", lowerRightCorner);

	//write text inside box
	int textLen = strlen(text);

	int textPosx = (((x2-x1) - textLen) /2)+x1;
	int textPosy = ((y2-y1) /2)+y1;

	gotoxy(textPosx,textPosy);

	printf("%s\n", text);
}



