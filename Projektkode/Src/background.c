/*
 * background.c
 *
 *  Created on: 17. jan. 2024
 *      Author: signe
 */
#include "ansi.h"
#define ESC 0x1B

/*
 * function that makes a moon background for game.
 * with inspiration from: https://www.asciiart.eu/space/planets
 */

void createMoon(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fg_colorindex, uint8_t bg_colorindex){

	resetFormat();
	printf("%c[38;5;%dm",ESC,fg_colorindex); 	//print ascii characters in specific color
	gotoxy(x1+32,y2-5); //start moon from 5 lines above bottom of window
    puts("____^/\\___^--____/\\____O______________/\\/\\---/\\___________---______________");


    printf("%c[38;5;%dm%c[48;5;%dm",ESC,fg_colorindex,ESC,bg_colorindex); 	//print ascii characters in specific color
    gotoxy(x1+22,y2-4);
    puts("  __    ..    ^^\          /\\^   ^   --   ^    ^                  ^^ ^  '\\ ^          ^       ---");
    gotoxy(x1+10,y2-3);
    puts("    ---- ^ ^        ^^ ^        ____     ________/\\     --        -  _______         --  -      -        ---  __       ^");
    gotoxy(x1+1,y2-2);
    puts(" ____ ____    ... -      -  --- ^ ^  __           --  __            ____/\\        ___--  ^  ^     __--        ---....             --  __" );
    gotoxy(x1+1,y2-1);
    puts("---        ,,   ___      ____---^ ^^-_-^-___        __^--__      ~~^--     ...     ^^--__  ____.._      _.._____-___         _____    ^ " );

	resetFormat();

}

void createStars(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fg_colorindex){
	resetFormat();
	printf("\x1b[38;5;%dm",fg_colorindex); 	//print ascii characters in specific color

    gotoxy(x1+3,y1+1);
    puts("  .     o           ,             .  ");
/*
	gotoxy(x1+100,y1+2);
    puts(" |              *     .          *" );
    gotoxy(x1+100,y1+3);
    puts("-O-");
    gotoxy(x1+100,y1+4);
    puts(" | ");
*/
    gotoxy(x1+20,y1+7);
    puts("             ,            *     .                       *  ");

	gotoxy(x1+10,y1+15);
    puts(" |                            .        .   *               " );
    gotoxy(x1+10,y1+16);
    puts("-O-");
    gotoxy(x1+10,y1+17);
    puts(" | ");
	gotoxy(x1+10,y1+25);
    puts("         ,                   .    ,   *      .   *     .  " );
    //   "..  /                                                         \  "


    resetFormat();
}
/*
 * function to specifically print surface as the spaceship overwrites it when passing
 */
void createSurface(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fg_colorindex){
	resetFormat();
	printf("%c[38;5;%dm",ESC,fg_colorindex); 	//print ascii characters in specific color
	gotoxy(x1+32,y2-5); //start moon from 5 lines above bottom of window
    puts("____^/\\___^--____/\\____O______________/\\/\\---/\\___________---______________");
    resetFormat();
}

