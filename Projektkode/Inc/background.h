/*
 * background.h
 *
 *  Created on: 17. jan. 2024
 *      Author: signe
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

void createMoon(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fg_colorindex, uint8_t bg_colorindex);
void createStars(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fg_colorindex);
void createSurface(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fg_colorindex);

#endif /* BACKGROUND_H_ */
