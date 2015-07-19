/*
 * Entity.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 */

#include "Entity.h"

int Entity::getXPos() {
	return xPos;
}

int Entity::getYPos() {
	return yPos;
}

SDL_Rect Entity::getCollisionBox() {
	return collisionBox;
}

TextureID Entity::getTextureID() {
	return texID;
}

void Entity::move(int dx, int dy) {
	xPos += dx;
	yPos += dy;
	collisionBox.x += dx;
	collisionBox.y += dy;
}

void Entity::setPos(int x, int y) {
	xPos = x;
	yPos = y;
	collisionBox.x = x - (collisionBox.w / 2);
	collisionBox.y = y - (collisionBox.h / 2);
}

bool Entity::collidesWith(Entity other) {
	if(collisionBox.y + collisionBox.h <= other.getCollisionBox().y) {
		return false;
	}
	if(collisionBox.y >= other.getCollisionBox().y + other.getCollisionBox().h) {
		return false;
	}
	if(collisionBox.x + collisionBox.w <= other.getCollisionBox().x) {
		return false;
	}
	if(collisionBox.x >= other.getCollisionBox().x + other.getCollisionBox().w) {
		return false;
	}
	return true;
}
