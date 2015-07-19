/*
 * Bullet.h
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Utils.h"
#include "Entity.h"

class Bullet : public Entity {
private:
	static const int TOTAL_CLIPS = 2;
	SDL_Rect clips[TOTAL_CLIPS];
	short currentClip;
public:
	static const int BULLET_WIDTH = 20;
	static const int BULLET_HEIGHT = 20;
	static const int BULLET_VEL = 20;
	static const int BULLET_DMG = 10;

	void changeClip();
	SDL_Rect getClip();
	Bullet(int x, int y);
};


#endif /* BULLET_H_ */
