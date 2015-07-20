/*
 * Star.cpp
 *
 *  Created on: 18 Jul 2015
 *      Author: Jack
 */

#include "Star.h"

Star::Star() {
	collisionBox.w = 20;
	collisionBox.h = 20;
	setPos(rand() % SCREEN_WIDTH, 0);
	texID = T_STARS;
	int clipNum = 0;
	clip.x = clipNum * 20;
	clip.y = 0;
	clip.w = 20;
	clip.h = 20;
}

SDL_Rect Star::getClip() {
	return clip;
}
