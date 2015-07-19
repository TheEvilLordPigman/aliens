/*
 * Alien.h
 *
 *  Created on: 26 May 2015
 *      Author: Jack
 */

#ifndef ALIEN_H_
#define ALIEN_H_

#include "Utils.h"
#include "Entity.h"

class Alien : public Entity {
private:
	int currentHP;
	int maxHP;
public:
	static const int ALIEN_WIDTH = 40;
	static const int ALIEN_HEIGHT = 40;

	static const int BASIC_ALIEN_MAX_HP = 30;

	Alien(int x, int y);

	int getCurrentHP();
	int getMaxHP();
	void takeDamage(int damage);
};

#endif /* ALIEN_H_ */
