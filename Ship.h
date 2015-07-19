/*
 * Ship.h
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Utils.h"
#include "Entity.h"
#include <cstdio>

class Ship : public Entity {
private:
	int velocity;
	int acceleration;
public:
	//Collision box dimensions
	static const int SHIP_WIDTH = 40;
	static const int SHIP_HEIGHT = 40;

	static const int MAX_ACCEL = 1;
	static const int MAX_VEL = 10;
	static const int FRICTION = 1;

	Ship();

	void setAcceleration(int acc);
	void incAcceleration(int inc);

	//Update the values of xPos and yPos based on velocity
	void updatePosition();

	int getAcceleration();
};


#endif /* SHIP_H_ */
