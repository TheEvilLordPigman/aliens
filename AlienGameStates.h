/*
 * AlienGameStates.h
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 *
 *  GameState subclasses for the Aliens game
 */

#ifndef ALIENGAMESTATES_H_
#define ALIENGAMESTATES_H_

#include "GameState.h"
#include "Ship.h"
#include "Bullet.h"
#include "Alien.h"
#include "Star.h"
#include <list>
#include <cstdlib>
#include <ctime>

enum AlienGameState {
	AGS_NONE,
	AGS_TITLE,
	AGS_MAIN,
	AGS_TOTAL
};

class TitleState : public GameState {
private:
	Mix_Music* music;

	std::list<Alien> activeAliens;
	int ticksUntilNextAlien;
public:
	static const int ALIEN_TICK_INTERVAL = 50;

	TitleState(Renderer*);
	~TitleState();

	void handleEvent(SDL_Event e);
	void logic();
	void render();
};

//The main game screen
class MainState : public GameState {
private:
	Ship ship;

	//Contains data for all bullets on the screen
	std::list<Bullet> activeBullets;

	//Contains data for all aliens on the screen
	std::list<Alien> activeAliens;
	int ticksUntilNextAlien;

	std::list<Star> activeStars;
	int ticksUntilNextStar;

	Mix_Chunk* shootSound;
	Mix_Music* music;
public:
	static const int ALIEN_TICK_INTERVAL = 100;
	static const int STAR_TICK_INTERVAL = 10;

	MainState(Renderer*);
	~MainState();

	void handleEvent(SDL_Event e);
	void logic();
	void render();
};



#endif /* ALIENGAMESTATES_H_ */
