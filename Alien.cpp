/*
 * Alien.cpp
 *
 *  Created on: 26 May 2015
 *      Author: Jack
 */

#include "Alien.h"

Alien::Alien(int x, int y) {
	collisionBox.w = ALIEN_WIDTH;
	collisionBox.h = ALIEN_HEIGHT;
	setPos(x, y);
	texID = T_ALIEN;
	maxHP = BASIC_ALIEN_MAX_HP;
	currentHP = maxHP;
}

int Alien::getCurrentHP() {
	return currentHP;
}

int Alien::getMaxHP() {
	return maxHP;
}

void Alien::takeDamage(int damage) {
	currentHP = currentHP - damage;
}

