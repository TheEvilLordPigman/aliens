/*
 * Star.h
 *
 *  Created on: 18 Jul 2015
 *      Author: Jack
 */

#ifndef STAR_H_
#define STAR_H_

#include "Utils.h"
#include "Entity.h"

class Star : public Entity {
private:
	static const int TOTAL_CLIPS = 1;
	SDL_Rect clip;
public:
	Star();
	SDL_Rect getClip();
};



#endif /* STAR_H_ */
