/*
 * Entity.h
 *
 *  Created on: 24 May 2015
 *      Author: Jack
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Utils.h"

//Generic entity: a superclass to all objects on the screen
class Entity {
protected:
	int xPos;
	int yPos;
	SDL_Rect collisionBox;
	TextureID texID;

public:
	int getXPos();
	int getYPos();
	SDL_Rect getCollisionBox();
	TextureID getTextureID();

	void move(int dx, int dy);
	void setPos(int x, int y);

	bool collidesWith(Entity other);
};


#endif /* ENTITY_H_ */
