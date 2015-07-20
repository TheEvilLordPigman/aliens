/*
 * main.cpp
 *
 *  Created on: 22 May 2015
 *      Author: Jack
 *
 *  Aliens: A game in which you must shoot aliens.
 */

#include "Utils.h"
#include "Renderer.h"
#include "AlienGameStates.h"

//Loads an SDL context, SDL_image, SDL_ttf and SDL_mixer
bool initSDL() {
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialise! SDL_Error: %s\n",SDL_GetError());
        success = false;
    }
    else {
    	int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags)) {
        	printf("SDL_image could not initialise! SDL_image error: %s\n",IMG_GetError());
        	success = false;
        }

        if(TTF_Init() == -1) {
        	printf("SDL_ttf could not initialise! SDL_ttf Error: %s\n", TTF_GetError());
        	success = false;
        }

        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0) {
        	printf("SDL_mixer could not initialise! SDL_mixer Error: %s\n",Mix_GetError());
        	success = false;
        }
    }
    return success;
}

//Closes down SDL and its add-ons
void closeSDL() {
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
	if(initSDL()) {
		Renderer renderer;

		GameState* currentState = new TitleState(&renderer);

		bool quit = false;
		SDL_Event e;

		while(!quit) {
			while(SDL_PollEvent(&e)) {
				if(e.type == SDL_QUIT) {
					quit = true;
				}
				else {
					currentState->handleEvent(e);
				}
			}

			currentState->logic();

			renderer.renderClear();
			currentState->render();
			renderer.renderPresent();

			if(currentState->getNextState() != AGS_NONE) {
				switch(currentState->getNextState()) {
					case AGS_TITLE:
						currentState = new TitleState(&renderer);
						break;
					case AGS_MAIN:
						currentState = new MainState(&renderer);
						break;
				}
			}
		}

		delete currentState;
	}
	closeSDL();
	return 0;
}


