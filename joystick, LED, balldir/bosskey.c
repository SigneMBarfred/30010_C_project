/*
 * bosskey.c
 *
 *  Created on: Jan 16, 2024
 *      Author: mikke
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "project.h"
#include <time.h>
#define ESC 0x1B


void bosskey(){

	gotoxy(50, 20);
	char *key[] = {"W", "O", "R", "K", " ", "I", "N", " ", "P", "R", "O", "G", "R", "E", "S", "S", "!"};

	for (int i = 0; i < 17; i++){
		printf("%s", key[i]);
	}
}

