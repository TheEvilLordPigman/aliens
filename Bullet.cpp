/*
 * Bullet.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 */

#include "Bullet.h"

Bullet::Bullet(int x, int y) {
	texID = T_PLAYERBULLET;
	collisionBox.w = BULLET_WIDTH;
	collisionBox.h = BULLET_HEIGHT;
	setPos(x,y);

	clips[0].x = 0;
	clips[0].y = 0;
	clips[0].w = BULLET_WIDTH;
	clips[0].h = BULLET_HEIGHT;

	clips[1].x = BULLET_WIDTH;
	clips[1].y = 0;
	clips[1].w = BULLET_WIDTH;
	clips[1].h = BULLET_HEIGHT;

	currentClip = 0;
}

void Bullet::changeClip() {
	currentClip += 1;
	if(currentClip == TOTAL_CLIPS) {
		currentClip = 0;
	}
}

SDL_Rect Bullet::getClip() {
	return clips[currentClip];
}
