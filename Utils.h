/*
 * Utils.h
 *
 *  Created on: 22 May 2015
 *      Author: Jack
 *
 *  General utilities for every file: SDL includes, screen dimension
 *  constants and texture ID enum.
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdio>
#include <cstdlib>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum TextureID {
	T_TITLE,
	T_STARTBUT,
	T_SHIP,
	T_PLAYERBULLET,
	T_ALIEN,
	T_STARS,
	T_TOTAL
};

#endif /* UTILS_H_ */

