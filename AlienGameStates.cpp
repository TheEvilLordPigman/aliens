/*
 * AlienGameStates.cpp
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 */

#include "AlienGameStates.h"

//TitleState

TitleState::TitleState(Renderer* r) {
	mainRenderer = r;
	nextState = AGS_NONE;
	music = Mix_LoadMUS("titlemusic.mp3");
	Mix_PlayMusic(music, -1);
	ticksUntilNextAlien = 1;
}

TitleState::~TitleState() {
	Mix_HaltMusic();
	Mix_FreeMusic(music);
}

void TitleState::handleEvent(SDL_Event e) {
	if(e.type == SDL_KEYDOWN) {
		if(e.key.keysym.sym == SDLK_RETURN) {
			nextState = AGS_MAIN;
		}
	}
}

void TitleState::logic() {
	//Move or remove aliens
	for(std::list<Alien>::iterator itAlien = activeAliens.begin(); itAlien != activeAliens.end(); ++itAlien) {
		if(itAlien->getXPos() < 0 || itAlien->getXPos() > SCREEN_WIDTH || itAlien->getYPos() < 0 || itAlien->getYPos() > SCREEN_HEIGHT) {
			itAlien = activeAliens.erase(itAlien);
			--itAlien;
		}
		else {
			itAlien->move(0, 2);
		}
	}

	ticksUntilNextAlien--;
	if(ticksUntilNextAlien == 0) {
		activeAliens.push_back(Alien(20, 0));
		activeAliens.push_back(Alien(60, 0));
		activeAliens.push_back(Alien(SCREEN_WIDTH - 20, 0));
		activeAliens.push_back(Alien(SCREEN_WIDTH - 60, 0));
		ticksUntilNextAlien = ALIEN_TICK_INTERVAL;
	}
}

void TitleState::render() {
	mainRenderer->render(T_TITLE, 140, 100);
	mainRenderer->render(T_STARTBUT, 140, 300);
	for(std::list<Alien>::iterator it = activeAliens.begin(); it != activeAliens.end(); ++it) {
		mainRenderer->render(T_ALIEN, it->getCollisionBox().x, it->getCollisionBox().y);
	}
}


//MainState

MainState::MainState(Renderer* r) {
	mainRenderer = r;
	nextState = AGS_NONE;
	ship.setPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 30);

	shootSound = Mix_LoadWAV("shot.wav");
	if(shootSound == NULL) {
		printf("Failed to load shot.wav: %s\n", Mix_GetError());
	}
	else {
		Mix_VolumeChunk(shootSound, MIX_MAX_VOLUME/4);
	}

	music = Mix_LoadMUS("gamemusic.mp3");
	Mix_PlayMusic(music, -1);

	ticksUntilNextAlien = ALIEN_TICK_INTERVAL;
	ticksUntilNextStar = STAR_TICK_INTERVAL;
	srand(time(NULL));
}

MainState::~MainState() {
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_FreeChunk(shootSound);
}

void MainState::logic() {
	ship.updatePosition();

	//Erase any bullet that is not on screen, or move them is they are on screen
	for(std::list<Bullet>::iterator itBullet = activeBullets.begin(); itBullet != activeBullets.end(); ++itBullet) {
		if(itBullet->getXPos() < 0 || itBullet->getXPos() > SCREEN_WIDTH || itBullet->getYPos() < 0 || itBullet->getYPos() > SCREEN_HEIGHT) {
			itBullet = activeBullets.erase(itBullet);
			--itBullet;
		}
		else {
			itBullet->move(0, -20);
		}
	}

	//Move or remove aliens
	for(std::list<Alien>::iterator itAlien = activeAliens.begin(); itAlien != activeAliens.end(); ++itAlien) {
		if(itAlien->getXPos() < 0 || itAlien->getXPos() > SCREEN_WIDTH || itAlien->getYPos() < 0 || itAlien->getYPos() > SCREEN_HEIGHT) {
			itAlien = activeAliens.erase(itAlien);
			--itAlien;
		}
		else {
			itAlien->move(0, 2);
			for(std::list<Bullet>::iterator itBullet = activeBullets.begin(); itBullet != activeBullets.end(); ++itBullet) {
				if(itAlien->collidesWith(*itBullet)) {
					itAlien->takeDamage(10);
					itBullet = activeBullets.erase(itBullet);
					--itBullet;
				}
			}
			if(itAlien->getCurrentHP() <= 0) {
				itAlien = activeAliens.erase(itAlien);
				--itAlien;
			}
		}
	}

	for(std::list<Star>::iterator it = activeStars.begin(); it != activeStars.end(); ++it) {
		if(it->getYPos() > SCREEN_HEIGHT) {
			it = activeStars.erase(it);
			--it;
		}
		else {
			it->move(0, 1);
		}
	}

	//Spawn new aliens if the time is right
	ticksUntilNextAlien--;
	if(ticksUntilNextAlien == 0) {
		int numAliens = rand() % 4;
		for(int i = 0; i < numAliens; i++) {
			activeAliens.push_back(Alien((rand() % (SCREEN_WIDTH - 20) + 20), 30));
		}
		ticksUntilNextAlien = ALIEN_TICK_INTERVAL;
	}

	ticksUntilNextStar--;
	if(ticksUntilNextStar == 0) {
		activeStars.push_back(Star());
		ticksUntilNextStar = STAR_TICK_INTERVAL;
	}
}

void MainState::handleEvent(SDL_Event e) {
	if(e.type == SDL_KEYDOWN) {
		switch(e.key.keysym.sym) {
			case SDLK_LEFT:
				if(ship.getAcceleration() > -ship.MAX_ACCEL) {
					ship.setAcceleration(-ship.MAX_ACCEL);
					//printf("Pressed left, now accelerating left\n");
				}
				else {
					//printf("Pressed left, but acceleration is maxed\n");
				}
				break;
			case SDLK_RIGHT:
				if(ship.getAcceleration() < ship.MAX_ACCEL) {
					ship.setAcceleration(ship.MAX_ACCEL);
					//printf("Pressed right, now accelerating right\n");
				}
				else {
					//printf("Pressed right, but acceleration is maxed\n");
				}
				break;
			case SDLK_UP:
				activeBullets.push_back(Bullet(ship.getXPos(),ship.getYPos() - 20));
				Mix_PlayChannel(-1, shootSound, 0);
				break;
			case SDLK_ESCAPE:
				nextState = AGS_TITLE;
				break;
		}
	}
	else if(e.type == SDL_KEYUP) {
		switch(e.key.keysym.sym) {
			case SDLK_LEFT:
				if(ship.getAcceleration() < 0) {
					ship.setAcceleration(0);
					//printf("Released left, decelerating\n");
				}
				break;
			case SDLK_RIGHT:
				if(ship.getAcceleration() > 0) {
					ship.setAcceleration(0);
					//printf("Released right, decelerating\n");
				}
				break;
		}
	}
}

void MainState::render() {
	mainRenderer->render(ship.getTextureID(), ship.getCollisionBox().x, ship.getCollisionBox().y);
	for(std::list<Bullet>::iterator it = activeBullets.begin(); it != activeBullets.end(); ++it) {
		SDL_Rect clip = it->getClip();
		mainRenderer->render(it->getTextureID(), it->getCollisionBox().x, it->getCollisionBox().y, &clip);
		it->changeClip();
	}
	for(std::list<Alien>::iterator it = activeAliens.begin(); it != activeAliens.end(); ++it) {
		mainRenderer->render(T_ALIEN, it->getCollisionBox().x, it->getCollisionBox().y);
		SDL_Rect healthBar = {it->getCollisionBox().x, it->getCollisionBox().y - 5, (int)(((double)it->getCurrentHP() / (double)it->getMaxHP()) * 40), 5};
		SDL_Rect healthBarFrame = healthBar;
		healthBarFrame.w = 40;
		SDL_Color green = {0, 0xFF, 0, 0};
		SDL_Color grey = {0x10, 0x10, 0x10, 0};
		mainRenderer->renderRect(healthBar, green, true);
		mainRenderer->renderRect(healthBarFrame, grey, false);
	}

	for(std::list<Star>::iterator it = activeStars.begin(); it != activeStars.end(); ++it) {
		SDL_Rect clip = it->getClip();
		mainRenderer->render(it->getTextureID(), it->getCollisionBox().x, it->getCollisionBox().y, &clip);
	}
}


