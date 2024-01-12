/*
 * trig.c
 *
 *  Created on: 5. jan. 2024
 *      Author: signe
 */


// define macros
#define ESC 0x1B
#define FIX14_SHIFT 14

#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b)  ( ((a) << FIX14_SHIFT) / b )


// include

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "sineLUT.h"
#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#include "math.h"

typedef struct {
	int32_t x,y;
}vector_t;


// -----------------create your functions below:------


//clear screen
void clrscrn() {

	 printf("%c[H", ESC);
	 printf("%c[2J", ESC); //moves cursor to home and clears

}





//convert from 2.14 format to 16.16
int32_t expand(int32_t i) {
   // Converts an 18.14 fixed point number to 16.16
	return i << 2;
}




//print fixed point format numbers correctly
void printFix(int32_t i) {
    // Prints a signed 16.16 fixed point number
        if ((i & 0x80000000) != 0) { // Handle negative numbers
            printf("-");
            i = ~i + 1;
        }
        printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
        // Print a maximum of 4 decimal digits to avoid overflow
    }



//gets user input for angle in deg
int userInput(){
	char input[100];
	fgets(input, sizeof(input), stdin);
	int value = atoi(input); //convert to int

	return value;
}

// -----------    SINE VALUE FUNCTION   --------------------
int sine(int angle){ //takes an angle in degrees and outputs the sine value of this as 2.14 format

	/*sine is repetitive in nature - meaning sin(x)=sin(360+x);
	 * so modulo 360 of input is taken to account for this
	 */
	angle = fmod(angle,360);
	//printf("fmod 360 to angle is %d \n",angle); //check to see if we get expected
	/*apparently it can be an issue that the "remainder" of the modulo is negative,
	 * so therefore we check and ammend when necessary */
	if (angle < 0.0) { //if angle is negative, add 360 to ensure it is between 0 and 360 deg
	       angle += 360.0;
	}

	//-----------------now to the look up portion!------------
	//convert from degrees to our 512/(2Pi) increments:
	int index;
	index = (angle*512)/ 360;
	int sineResult = SIN[index];

	return sineResult;

}


// -----------    COSINE VALUE FUNCTION   --------------------
int cosine(int angle){ //takes an angle in degrees and outputs the sine value of this as 2.14 format
	/*cosine is repetitive in nature - meaning cosin(x)=cosin(360+x);
	so modulo 360 of input is taken to account for this */
	angle = fmod(angle,360);
	//printf("fmod 360 to angle is %d \n",angle);
	/*apparently it can be an issue that the "remainder" of the modulo is negative,
	so therefore we check and ammend when necessary */
	if (angle < 0.0) { //if angle is negative, add 360 to ensure it is between 0 and 360 deg
	       angle += 360.0;
	}

	//-----------------now to the look up portion!------------
	//convert from degrees to our 512/(2Pi) increments:
	int coIndex;
	coIndex = ((angle+90) * 512)/360;
	coIndex = fmod(coIndex,512);
	if (angle < 0.0) { //if index is negative, add 512 to ensure it is between 0 and 360 deg
		       angle += 512.0;
	}

	//printf("index for LUT to your angle is %d \n",coIndex);

	int cosineResult = SIN[coIndex];

	return cosineResult;
}


// we rotate the vectors
void rotateVector(vector_t *rotVector, int angle){
	int32_t rotX, rotY; // we declare type for the rotated composants
	rotX = FIX14_MULT(rotVector->x, cosine(angle)) - FIX14_MULT(rotVector->y, sine(angle));
	rotY = FIX14_MULT(rotVector->x, sine(angle)) + FIX14_MULT(rotVector->y, cosine(angle));

	//store the rotated values in the vector
	rotVector -> x = rotX;
	rotVector -> y = rotY;
	}

