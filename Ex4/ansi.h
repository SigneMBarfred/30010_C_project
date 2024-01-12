/*
 * ansi.h
 *
 *  Created on: Jan 9, 2024
 *      Author: signe
 */

#ifndef ANSI_H_
#define ANSI_H_


/* Includes -------------------------------------------------------------*/
#include <stdio.h>// Whatever needs to be included
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/* Exported types -------------------------------------------------------*/
/* Exported constants ---------------------------------------------------*/
/* Exported macro -------------------------------------------------------*/

/* #define // Whatever needs to be defined */

//prototype the functions from ansi.c
void clrscrn();
void clreol();
void gotoxy(int x, int y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
int setCursorPos(); //this function still doesnt accept user input
void resetFormat();
void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *style, const char *title);
void box(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *style, const char *text);

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);

/* Exported functions -------------------------------------------------- */



#endif /* ANSI_H_ */
