/*
 * GameState.h
 *
 *  Created on: 25 May 2015
 *      Author: Jack
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Utils.h"
#include "Renderer.h"

//Abstract class for basic game state functionality
class GameState {
protected:
	//A pointer to the renderer object in the main program. This is passed to the constructor.
	Renderer* mainRenderer;

	int nextState;

public:
	virtual ~GameState() = 0;

	//Responds accordingly to event e
	virtual void handleEvent(SDL_Event e) = 0;

	//Alters the game state eg. moving bullets and ship
	virtual void logic() = 0;

	//Uses the mainRenderer pointer to render the scene to the screen
	virtual void render() = 0;

	int getNextState();
};



#endif /* GAMESTATE_H_ */
