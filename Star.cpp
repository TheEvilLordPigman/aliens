/*
 * Star.cpp
 *
 *  Created on: 18 Jul 2015
 *      Author: Jack
 */

#include "Star.h"

Star::Star() {
	setPos(rand() % (SCREEN_WIDTH + 1), 0);
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
