#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "io.h"
#include <stdint.h>

uint8_t updateFlag = 0;

// TODO: Tilføj interrupt til flag
// TODO: Omskriv spawner-funktion ud fra level

struct player{
	uint8_t hp;
	uint8_t x;
	uint8_t y;
};

struct asteroid{
	uint8_t hp;
	uint8_t y;
};

struct bullet{
	uint8_t x;
	uint8_t y;
	uint8_t speed;
	uint8_t dir;
	uint8_t anim;
	uint8_t dist;
	uint8_t active;
};

struct alien{
	int8_t x;
	uint8_t y;
	uint8_t speed;
	uint8_t nxtdir;
};

struct border{
	uint8_t xMax;
	uint8_t yMax;
	uint8_t xMin;
	uint8_t yMin;
};

void clrscrn(){
	printf("\x1b[0m");
	printf("\x1b[2J\x1b[H");
}

// Initialize level on first load
void init_level(uint8_t lvl, uint32_t points, uint8_t HP){
	// Setup level grid
	uint8_t border;

	// Start the game!
	gameManager(lvl, points, HP);

}

void gameManager(uint8_t lvl, uint32_t startPoints, uint8_t startHP, uint8_t pPosX, uint8_t pPosY){
	struct border borders;
	borders.xMax = 58;
	borders.yMax = 16;
	borders.xMin = 6;
	borders.yMin = 3;
	struct player pPos;
	pPos.x = pPosx;
	pPos.y = pPosY;
	struct bullet bullets[50];
	struct bullet asteroids[16];
	struct bullet aliens[16];
	// TODO: Tilføj difficulty modifier til entities

	uint8_t i;

	uint8_t asteroidCount = 0;
	uint8_t alienCount = 0;
	uint8_t bulletCount = 0;

	while(1){

		if (updateFlag == 0){
			continue;
		}

		/*** Player Movemnet Input ***/
		uint8_t pInput = readJoy(); // PLACEHOLDER!
		uint8_t pMoveX, pMoveY; // MoveRequest variables
		switch (pInput){
			case 1:
				pMoveX = 1;
				pMoveY = 0;
				break;
			case 2:
				pMoveX = -1;
				pMoveY = 0;
				break;
			case 4:
				pMoveX = 0;
				pMoveY = 1;
				break;
			case 8:
				pMoveX = 0;
				pMoveY = -1;
				break;
			default:
				pMoveX = 0;
				pMoveY = 0;
		}

		// Player attempting "Out-of-bounds" movement handler
		if (pMoveX + pPos.x >= borders.xMax || pMoveX + pPos.x <= borders.xMin){
			pMoveX = 0;}
		if (pMoveY + pPos.y >= borders.yMax || pMoveX + pPos.x <= borders.yMin){
			pMoveY = 0;}

		// Opdater spillerens logiske lokation
		if (pMoveY != 0 && pMoveX != 0){
			pPos.x += pMoveX;
			pPos.y += pMoveY;}

		for (i = 0 ; i < bulletCount ; i++){
			if (bullets[i].active == 0){continue;}
			if (dir){
				switch (bullets[i].dist){
					case 0: bullets[i].y += 3;
					break;
					case 3: bullets[i].y += 3;
					break;
					case 6: bullets[i].y += 2;
					break;
					case 8: bullets[i].y += 1;
							bullet[i].dir = 0;
					break;
					default: bullets[i].y += 1;}}
			else {
				switch (bullets[i].dist){
					case 5: bullets[i].y += 3;
					break;
					case 3: bullets[i].y += 2;
					break;
					default: bullets[i].y += 1;}}

			// TODO: Add collision detection!
			}

		for (i = 0 ; i < asteroidCount ; i++){
			if (asteroid[i].active == 0){continue;} // Add search algorithm?
			asteroid[i].y += 3;
			// TODO: Add collision detection!
		}

		for (i = 0 ; i < alienCount ; i++){
			if (aliens[i].active == 0){continue;}
			aliens[i].y -= 1;
			aliens[i].x += ((-2 * dir) + 1 * 2); // (-2 * 0) + 1 * 2 = 2 eller (-2 * 1) + 1 * 2 = -2
			aliens[i].dir ^= 1;
			}

		// Win-condition reached?
		if (points >= nxtLvlCon){
			// Next level code...
		}

		// Player shooting?
		if (pInput == 16){
			for (i = 0 ; i < 50 ; i++){
				if (bullets[i].active){continue;}
				else {bulletCount++;
					bullets[i].active = 1;
					bullets[i].x = pPos.x;
					bullets[i].y = (pPos.y + 2);}
			}
		}

	}


}


int main(void)
{
	uart_init(128000);
	clrscrn();
	setupJoystickPins();

	uint32_t points = 0;
	uint8_t HP = 3;
	uint8_t ng = 1;
	uint8_t lvl = 1;

	if (ng == 1) {
		ng = 0;
		init_level(lvl, points, HP);
	}







	while(1){}
}
