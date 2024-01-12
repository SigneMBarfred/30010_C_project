
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "sineLUT.h"
#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#include "trig.h"
#include "math.h"

#define FIX14_SHIFT 14

#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b)  ( ((a) << FIX14_SHIFT) / b )



//input an angle and get corresponding sine value
int main(){
	uart_init(9600); //initialise receiver at baud 9600
	clrscrn();
	int angle = 0;


	// ---- get a sine value to an angle
	int sine18_14 = sine(angle); //first get a 2.14 format fixed integer
	int32_t sine16_16 = expand(sine18_14); // expand to 16.16 format
	printf("\nThe corresponding sine value to angle %d deg is approx.:\n ", angle);
	printFix(sine16_16); //use printfix to make sure it prints properly


	int angle1 = 45;


	// ---- get a sine value to an angle
	int sine18_14_1 = sine(angle1); //first get a 2.14 format fixed integer
	int32_t sine16_16_1 = expand(sine18_14_1); // expand to 16.16 format
	printf("\nThe corresponding sine value to angle %d deg is approx.:\n ", angle1);
	printFix(sine16_16_1); //use printfix to make sure it prints properly

	int angle2 = -78;


	// ---- get a sine value to an angle
	int sine18_14_2 = sine(angle2); //first get a 2.14 format fixed integer
	int32_t sine16_16_2 = expand(sine18_14_2); // expand to 16.16 format
	printf("\nThe corresponding sine value to angle %d deg is approx.:\n ", angle2);
	printFix(sine16_16_2); //use printfix to make sure it prints properly

	int angle3 = 649;


	// ---- get a sine value to an angle
	int sine18_14_3 = sine(angle3); //first get a 2.14 format fixed integer
	int32_t sine16_16_3 = expand(sine18_14_3); // expand to 16.16 format
	printf("\nThe corresponding sine value to angle %d deg is approx.:\n ", angle3);
	printFix(sine16_16_3); //use printfix to make sure it prints properly


	// ---- get a cosine value to an angle
	int cosine18_14 = cosine(angle); //first get a 2.14 format fixed integer
	int32_t cosine16_16 = expand(cosine18_14); // expand to 16.16 format
	printf("\nThe corresponding cosine value to angle %d deg is approx.:\n ", angle);
	printFix(cosine16_16); //use printfix to make sure it prints properly

	int cosine18_14_1 = cosine(angle1); //first get a 2.14 format fixed integer
	int32_t cosine16_16_1 = expand(cosine18_14_1); // expand to 16.16 format
	printf("\nThe corresponding cosine value to angle %d deg is approx.:\n ", angle1);
	printFix(cosine16_16_1); //use printfix to make sure it prints properly

	int cosine18_14_2 = cosine(angle2); //first get a 2.14 format fixed integer
	int32_t cosine16_16_2 = expand(cosine18_14_2); // expand to 16.16 format
	printf("\nThe corresponding cosine value to angle %d deg is approx.:\n ", angle2);
	printFix(cosine16_16_2); //use printfix to make sure it prints properly

	int cosine18_14_3 = cosine(angle3); //first get a 2.14 format fixed integer
	int32_t cosine16_16_3 = expand(cosine18_14_3); // expand to 16.16 format
	printf("\nThe corresponding cosine value to angle %d deg is approx.:\n ", angle3);
	printFix(cosine16_16_3); //use printfix to make sure it prints properly



	// ----------------- exc. 3.3 ----------------
	//now to rotate vectors:
	angle = 900;
	//we define a structure
	typedef struct {
		int32_t x,y;
	}vector_t;

	// we put in values for each composant
	void initVector(vector_t *v){
		v->x = -4 << 14; // need to bitshift as it is initialy stored as a 32.0 number not 2.14
		v->y = -4 << 14;
	}

	vector_t aVector; //create vector that is a structure
	initVector(&aVector); //assign values for x and y

	rotateVector(&aVector,angle); //rotate vector

	//change to 16.16 format
	int32_t rotVector_x = expand(aVector.x);
	int32_t rotVector_y = expand(aVector.y);


	//output in terminal
	printf("\n\nRotated Vector:\n");
	printf("x-composant:\n");
	printFix(rotVector_x);

	printf("\ny-composant:\n");
	printFix(rotVector_y);

	return 0;

}
