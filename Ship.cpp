/*
 * Ship.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 */

#include "Ship.h"

Ship::Ship() {
	texID = T_SHIP;

	collisionBox.w = SHIP_WIDTH;
	collisionBox.h = SHIP_HEIGHT;

	setPos(0,0);

	acceleration = 0;
	velocity = 0;
}

void Ship::updatePosition() {
	velocity += acceleration;
	if(velocity > MAX_VEL) {
		velocity = MAX_VEL;
	}
	if(velocity < -MAX_VEL) {
		velocity = -MAX_VEL;
	}

	move(velocity, 0);
	if(xPos - (SHIP_WIDTH / 2) <= 0 || xPos + (SHIP_WIDTH / 2) >= SCREEN_WIDTH) {
		move(-velocity, 0);
	}

	//printf("Acceleration: %i\tVelocity: %i\n", acceleration,velocity);

	if(velocity > 0 && acceleration == 0) {
		velocity -= FRICTION;
	}
	if(velocity < 0 && acceleration == 0) {
		velocity += FRICTION;
	}
}

void Ship::setAcceleration(int acc) {
	acceleration = acc;
}

void Ship::incAcceleration(int inc) {
	acceleration += inc;
}

int Ship::getAcceleration() {
	return acceleration;
}
