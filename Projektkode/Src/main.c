#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "clock.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"
#include "ansi.h"
#include "renderengine.h"
#include "charset.h"
#include "joystick.h"
#include "jukebox.h"
#include "menuOptions.h"

// Main gameManager code by Dimitri, menu-code by Signe

uint8_t updateFlag = 0;


struct player{
	uint8_t hp;
	uint8_t x;
	uint8_t y;
};

struct asteroid{
	uint8_t hp;
	uint8_t y;
	uint8_t x;
	uint8_t active;
};

struct bullet{
	uint8_t x;
	uint8_t y;
	uint8_t dir;
	uint8_t anim;
	uint8_t dist;
	uint8_t active;
};

struct alien{
	uint8_t x;
	uint8_t y;
	uint8_t dir;
	uint8_t step;
	uint8_t active;
};

struct powerup1{
	uint8_t x;
	uint8_t y;
	uint8_t dir1;
	uint8_t dir2;
	uint8_t step;
	uint8_t active;
};

struct border{
	uint8_t xMax;
	uint8_t yMax;
	uint8_t xMin;
	uint8_t yMin;
};


void TIM1_BRK_TIM15_IRQHandler(void) {
	updateFlag = 1;
	TIM15->SR &= ~(0x0001);
}

void wincon(uint32_t points, uint8_t hp, uint8_t lvl, uint8_t diff, uint32_t hiScore){
	clrscrn();
	successSong();
	if (points > hiScore){
			hiScore = points;
			printf("\x1b[13;17HNy High-Score: %d !", hiScore);
	}

	printf("\x1b[15;17HGodt klaret, Pilot!");
	printf("\x1b[16;17HLevel %d besejret", lvl);
	printf("\x1b[17;17HLiv Tilbage: %d | Score: %ld", hp, points);
	printf("\x1b[19;17HDin naeste mission begynder om lidt...");

	int a = 0;
	while (1){
		if (a > 35){
			break;
		} else if (updateFlag == 1){
			a++;
			updateFlag = 0;
		}
	}

	gameManager(lvl+1, points, diff, hiScore);
}

void losecon(uint32_t points, uint8_t hp, uint8_t lvl, uint8_t diff, uint32_t hiScore){
	clrscrn();
	loseSong();
	if (points > hiScore){
		hiScore = points;
		printf("\x1b[13;17HNy High-Score: %d !", hiScore);
	}

	printf("\x1b[15;17HBedre held naeste gang, Pilot!");
	printf("\x1b[16;17HBesejret paa level %d", lvl);
	printf("\x1b[17;17HLiv Tilbage: %d | Score: %ld", hp, points);
	printf("\x1b[19;17HDu bliver sent til level om lidt...");

	int a = 0;
	while (1){
		if (a > 35){break;}
		else if (updateFlag == 1){
			a++;
			updateFlag = 0;
		}
	}
	clrscrn();
	gameManager(1, 0, diff, hiScore);
}


void lcd_write_string(char strIn[25]){
	char buffer[512];
	int i, j, n;
	n = (strlen(strIn));
	memset(buffer, 0x00,512);
	for (i = 0; i < n ; i++){
		for (j = 0 ; j < 5 ; j++){
				buffer[j+(i*5)] = character_data[strIn[i]-0x20][j];
			}
	}
	lcd_push_buffer(buffer);
}


void gameManager(uint8_t lvl, uint32_t startPoints, uint8_t diff, uint32_t hiScore){
	printf("Starting GameManager init\n");

	/*** Standard Variables ***/
	uint8_t i, k;
	uint32_t j;
	time_t tid;
	uint32_t points = startPoints;
	uint32_t nxtLvlCon = (lvl * 2048 + (diff * 512));
	//uint8_t asteroidCount = 0;
	uint8_t ledStep = 0;
	uint8_t doublePoints = 0;
	uint8_t doublePointsC = 0;
	uint8_t bulletCooldown = 3;
	uint8_t alienCooldown = 4;
	uint8_t txpCooldown = 65;
	uint8_t renderQueue[160];
	char lcdoutput[25];

	j = (300 - (lvl * 8 + diff * 2));
	if (j < 120){j = 120;}
	TIM15->ARR = j;  // Load reload value based on lvl and difficulty

	// Seed random-functions from time.h
	srand((unsigned) time(&tid));

	/*** Game Entities (Defined as structures) ***/
	struct border borders;
	borders = ((struct border) {58, 27, 6, 16}); // X-Max, Y-Max, X-Min, Y-Min

	struct player pPos;
	pPos = ((struct player) {3-diff, 32, 20}); // HP, X-Start, Y-Start

	struct bullet bullets[16];
	struct alien aliens[16];
	struct powerup1 txP[16]; // 2x Points

	for (i = 0 ; i < 16 ; i++){
		bullets[i] = ((struct bullet) {64, 0, 1, 0, 0, 0});
		aliens[i] = ((struct alien) {0, 0, 0, 0, 0});
		txP[i] = ((struct powerup1) {0, 0, 0, 0, 0, 0}); // X, Y, dir1, dir2, step, active

	}

	memset(renderQueue, 14, 160); // renderQueue variable insurance (Stopcode: 14))

	printf("GameManager: starting first cycle\n"); // Debug message
	while(1){
		/*** Update cycle Handler ***/
		if (updateFlag == 0){
			continue;
		} else {updateFlag = 0;}

		if (ledStep != 0){ledStep--;}
		else {setLED(0);}


		/*** Player Movement Input ***/
		uint8_t pInput = readJoy(); // Hvis board joystick ikke er i brug, lyt efter ekstern joystick
		if (pInput == 0){pInput = potf();}

		switch (pInput){
			case 2:
				pPos.y += 1;
				if (pPos.y > borders.yMax || pPos.y < borders.yMin){pPos.y -= 1;}
				break;

			case 1:
				pPos.y -= 1;
				if (pPos.y > borders.yMax || pPos.y < borders.yMin){pPos.y += 1;}
				break;

			case 8:
				pPos.x += 1;
				if (pPos.x > borders.xMax || pPos.x < borders.xMin){pPos.x -= 1;}
				break;

			case 4:
				pPos.x -= 1;
				if (pPos.x > borders.xMax || pPos.x < borders.xMin){pPos.x += 1;}
				break;

			default:
				break;
		}

		/*** Bullet Movement and Collision Detection ***/
		for (i = 0 ; i < 8 ; i++){
			if (bullets[i].active == 0){continue;}
			bullets[i].anim ^=1; // Animation toggle
			// Initial direction and inertia handling
			if (bullets[i].dir){
				switch (bullets[i].dist){
					case 0: bullets[i].y -= 3;
							bullets[i].dist += 3;
					break;

					case 3: bullets[i].y -= 3;
					bullets[i].dist += 3;
					break;

					case 6: bullets[i].y -= 2;
					bullets[i].dist += 2;
					break;

					case 8: bullets[i].y -= 2;
					bullets[i].dist += 2;
					break;

					case 10: bullets[i].y -= 1;
					bullets[i].dist += 1;
					break;

					case 11: bullets[i].y -= 1;
						bullets[i].dist += 1;
						bullets[i].dir = 0;
					break;

					default: bullets[i].y -= 1;
					bullets[i].dist += 1;
					break;
				}
			}

			// Flip direction
			else {
				switch (bullets[i].dist){
					case 12: bullets[i].y += 1;
					bullets[i].dist += 1;
					break;

					default: bullets[i].y += 2;
					bullets[i].dist += 2;
					break;}

				// Bullet out of bounds detection
				if (bullets[i].y > 26){
					bullets[i] = ((struct bullet) {64, 0, 1, 0, 0, 0});
				}
			}

			// Bullet hit target?
			for (k = 0 ; k < 8 ; k++){
					if (bullets[i].y > aliens[k].y-2 && bullets[i].y < aliens[k].y+2){
						if ((bullets[i].x < aliens[k].x+2) && (bullets[i].x > aliens[k].x-2)){
							aliens[k] = ((struct alien) {0, 0, 0, 0, 0});
							bullets[i] = ((struct bullet) {64, 0, 1, 0, 0, 0});
							points += (250 + (250 * doublePoints));
							setLED(2); // Set to Green
							ledStep = 3;
						}
					}

					if (bullets[i].y > pPos.y-2 && bullets[i].y < pPos.y+2 && !(bullets[i].dir)){
						if ((bullets[i].x < pPos.x+2) && (bullets[i].x > pPos.x-2)){
							pPos.hp -= 1;
							setLED(4); // Set to Red
							ledStep = 3;
							if (pPos.hp <= 0){
								losecon(points, 0, lvl, diff, hiScore);
							}
							bullets[i] = ((struct bullet) {64, 0, 1, 0, 0, 0});
						}
					}
				}
			}


		/*** Player Combat and Fire-rate handler ***/
		if (bulletCooldown != 0){bulletCooldown--;}
		if (pInput == 16 && bulletCooldown == 0){
			bulletCooldown = 5; // Reset cooldown on successful execution
			// Find inactive bullet entity to reuse
			for (i = 0 ; i < 8 ; i++){
				if (bullets[i].active){continue;}
				else {
					bullets[i] = ((struct bullet) {pPos.x, (pPos.y - 3), 1, 0, 0, 1});
					break;
				}
			}
		}

		// Move Alien
		for (i = 0 ; i < 8 ; i++){
			if (aliens[i].active == 0){continue;}
			if (aliens[i].step < 3){
				aliens[i].step += 1;
				continue;}
			aliens[i].step = 0;
			aliens[i].y += 1;
			if (aliens[i].y > 24){
				aliens[i] = ((struct alien) {0, 0, 0, 0, 0});
				pPos.hp -= 1;
				if (pPos.hp <= 0){losecon(points, 0, lvl, diff, hiScore);}
			}
			aliens[i].x += ((4 * aliens[i].dir) - 2); // (4 * 0) - 2 = -2 eller (4 * 1) - 2 = 2
			aliens[i].dir ^= 1;
			j = (rand() % 10);
			if (j == 5){
				// Find inactive bullet entity to reuse
				for (j = 0 ; j < 8 ; j++){
					if (bullets[j].active){continue;}
					else {
					bullets[j] = ((struct bullet) {aliens[i].x, (aliens[i].y + 4), 0, 0, 13, 1});
					break;
					}
				}
			}

			//bullets[i] = ((struct bullet) {pPos.x, (pPos.y - 3), 1, 0, 0, 1});
			if (aliens[i].y > pPos.y-2 && aliens[i].y < pPos.y+2){
				if ((aliens[i].x < pPos.x+2) && (aliens[i].x > pPos.x-2)){
					pPos.hp -= 1;
					if (pPos.hp <= 0){losecon(points, 0, lvl, diff, hiScore);}
					aliens[i] = ((struct alien) {0, 0, 0, 0, 0});
				}
			}
		}

		// Move 2xP
		for (i = 0 ; i < 3 ; i++){
			if (txP[i].active == 0){continue;}
			if (txP[i].step < 2){
				txP[i].step += 1;
				continue;
			}
			txP[i].step = 0;
			txP[i].y += 1;
			if (txP[i].y > 24){txP[i] = ((struct powerup1) {0, 0, 0, 0, 0});}
			txP[i].x += ((4 * txP[i].dir1) - 2); // (4 * 0) - 2 = -2 eller (4 * 1) - 2 = 2
			txP[i].dir1 ^= 1;
		}

		// Win-condition reached?
		if (points >= nxtLvlCon){
			wincon(points, pPos.hp, lvl, diff, hiScore);
		}

		// Spawner funktion
		j = rand() % 10;
		//printf("\x1b[7;2H %d", j);
		if (alienCooldown != 0){alienCooldown--;}
		if (txpCooldown != 0){txpCooldown--;}
		if (j < 2){
			if (alienCooldown == 0){
				alienCooldown = 22;
				for (i = 0 ; i < 8 ; i++){
					if (aliens[i].active){continue;}
					else {
						aliens[i].active = 1;
						j = ((rand() % 10) + (rand() % 10) + (rand() % 10) + (rand() % 10) + (rand() % 10) + 1);
						if (j < 8){j = 8;}
						aliens[i].x = j;
						aliens[i].y = 4;
						aliens[i].dir = 0;
						break;}}}

		} else if (j == 4){
			if (txpCooldown == 0){
				txpCooldown = 110;
				for (i = 0 ; i < 8 ; i++){
					if (txP[i].active){continue;}
					else {
						txP[i].active = 1;
						j = ((rand() % 10) + (rand() % 10) + (rand() % 10) + (rand() % 10) + (rand() % 10) + 1);
						if (j < 8){j = 8;}
						else if (j > 50){j = 50;}
						txP[i].x = j;
						txP[i].y = 4;
						txP[i].dir1 = 0;
						break;}}}
		}

		// Hit double points?
		for (i = 0 ; i < 3 ; i++){
			if (txP[i].active){
				if (txP[i].y > pPos.y-2 && txP[i].y < pPos.y+2){
					if ((txP[i].x < pPos.x+2) && (txP[i].x > pPos.x-2)){
						doublePoints = 1;
						doublePointsC += 60;
						txP[i] = ((struct powerup1) {64, 0, 0, 0, 0, 0});
					}
				}
			}
		}

		// Double Points Counter
		if (doublePointsC == 0 && doublePoints == 1){doublePoints = 0;}
		else if (doublePointsC > 0){doublePointsC--;}



		// Add player, bullets, aliens, asteroids to list
		// Code: 10.x.y, 11.x.y.anim, 12.x.y, 13.x.y | EXIT-CODE: 14

		memset(renderQueue, 14, 160); // renderQueue variable insurance (Stopcode: 14))
		renderQueue[0] = 10;
		renderQueue[1] = pPos.y;
		renderQueue[2] = pPos.x;
		j = 3;

		for (i = 0 ; i < 25 ; i++){
			if (i < 8){
				//printf("RenderEngine: i = %d, bullet...");
				if (!(bullets[i].active)){continue;}
				else {
					renderQueue[j++] = 11; // Declare 'bullet'
					renderQueue[j++] = bullets[i].y;
					renderQueue[j++] = bullets[i].x;
					renderQueue[j++] = bullets[i].anim;
				}
			}
			if (i > 7 && i < 24){
				if (!(aliens[i-8].active)){continue;}
				else {
					renderQueue[j++] = 12; // Declare 'alien'
					renderQueue[j++] = aliens[i-8].y;
					renderQueue[j++] = aliens[i-8].x;
				}
			}
			if (i > 23){
				if (!(txP[i-8].active)){continue;}
				else {
					renderQueue[j++] = 13; // Declare '2xP'
					renderQueue[j++] = txP[i-24].y;
					renderQueue[j++] = txP[i-24].x;
				}
			}
		}


		// API-call to renderengine.c, draw the level graphics from queue
		drawLevel(renderQueue);
		printf("\x1b[1;1H\x1b[0mPoints: %ld", points);
		printf("\x1b[2;1H\x1b[0mLiv: %d", pPos.hp);

		sprintf(lcdoutput, "Liv: %d | Points: %ld", pPos.hp, points);
		lcd_write_string(lcdoutput);

		/** Debug info **/
		//printf("\x1b[%d;%dHG", pPos.y,pPos.x);
		//printf("GameManager: drawLevel() complete. \n");

		//printf("\x1b[2J\x1bH\x1b[2;2HbulletCount: %d\nBulletID: 0, bulletActive: %d, bulletDistance: %d", bulletCount, bullets[0].active, bullets[0].dist);
		//printf("\x1b[%d;%dHB", bullets[0].y, bullets[0].x);
		//printf("\x1b[2;2H X: %d, Y: %d, Active: %d, Dir: %d", aliens[0].x,aliens[0].y,aliens[0].active,aliens[0].dir);

		//uint32_t potv = potf();
		//printf("\x1b[6;2H potf: %ld", potv);

		// Prepare next cycle...
		updateFlag = 0;


	}
}


int main(void)
{
	uart_init(921600);
	clrscrn();
	lcd_init();
	lcd_reset();
	setupJoystickPins();
	setupLEDPins();
	setLED(0);
	configureTimer15();
	configureADC();

	printf("Config setup correctly\n");

	int difficulty = 0;
	int localDiff = 0;
	int choice = 0;

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
						localDiff = 0;
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
						localDiff = 1;
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

							localDiff = 2;
						}

						//exitMenu = 0; //go back to main menu
						break;
					case 2:
						printBossKey();
						break;

					case 16: //center push
						clrscrn();
						gameManager(1, 0, localDiff, 0); // Level, Start-Points, Difficulty, High-Score

						exitMenu = 0;
						break;

					case 4: //left push
						//quit
						exitMenu = 0;
						exitProgramme = 1;
						break;

					default:
						break;

				}
			}
		}
	clrscrn();
	gotoxy(60,20);
	printf("Goodbye!");


	while(1){}
}
