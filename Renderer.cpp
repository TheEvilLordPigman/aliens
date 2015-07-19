/*
 * Renderer.cpp
 *
 *  Created on: 22 May 2015
 *      Author: Jack
 */

#include "Renderer.h"

TextureBox Renderer::loadTextureFromFile(std::string path) {
	TextureBox newTexture;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image error: %s\n",path.c_str(),IMG_GetError());
    }
    else {
    	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF,0,0xFF));
    	newTexture.texture = SDL_CreateTextureFromSurface(theRenderer,loadedSurface);
    	if(newTexture.texture == NULL) {
    		printf("Failed to create texture from %s! SDL_Error: %s\n",path.c_str(),SDL_GetError());
    	}
    	else {
    		newTexture.w = loadedSurface->w;
    		newTexture.h = loadedSurface->h;
    	}
    	SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

TextureBox Renderer::loadTextureFromText(std::string text, TTF_Font* font, SDL_Color color) {
	TextureBox newTexture;
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if(textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
	}
	else {
		newTexture.texture = SDL_CreateTextureFromSurface(theRenderer, textSurface);
		if(newTexture.texture == NULL) {
			printf("Unable to create texture from rendered text! SDL_Error: %s\n",SDL_GetError());
		}
		else {
			newTexture.w = textSurface->w;
			newTexture.h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return newTexture;
}

Renderer::Renderer() {
	window = SDL_CreateWindow("Aliens",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if(window == NULL) {
		printf("Failed to create window: %s", SDL_GetError());
	}
	theRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(theRenderer == NULL) {
		printf("Failed to create renderer: %s", SDL_GetError());
	}
	SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0x00, 0x00);
	titleFont = TTF_OpenFont("Airstream.ttf", 100);
	buttonFont = TTF_OpenFont("Airstream.ttf", 32);
	generateTextures();
}

Renderer::~Renderer() {
	for(int i=0; i<T_TOTAL; i++) {
		SDL_DestroyTexture(textures[i].texture);
		textures[i].texture = NULL;
	}

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(window);
}

void Renderer::generateTextures() {
	SDL_Color white = {0xFF, 0xFF, 0xFF};
	textures[T_TITLE] = loadTextureFromText("ALIENS", titleFont, white);
	textures[T_STARTBUT] = loadTextureFromText("Press enter to begin...", buttonFont, white);
	textures[T_SHIP] = loadTextureFromFile("ship.png");
	textures[T_PLAYERBULLET] = loadTextureFromFile("bullet.png");
	textures[T_ALIEN] = loadTextureFromFile("alien.png");
	textures[T_STARS] = loadTextureFromFile("stars.png");
}

void Renderer::render(TextureID id, int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = {x, y, textures[id].w, textures[id].h};

	if(clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(theRenderer, textures[id].texture, clip, &renderQuad, angle, centre, flip);
}

void Renderer::renderDebug() {
	TextureBox riki = loadTextureFromFile("Riki.png");
	SDL_Rect renderQuad = {100, 100, riki.w, riki.h};
	SDL_RenderCopy(theRenderer, riki.texture, NULL, &renderQuad);
}

void Renderer::renderClear() {
	SDL_RenderClear(theRenderer);
}

void Renderer::renderPresent() {
	SDL_RenderPresent(theRenderer);
}

void Renderer::renderRect(SDL_Rect rect, SDL_Color color, bool fill) {
	SDL_SetRenderDrawColor(theRenderer, color.r, color.g, color.b, color.a);
	if(fill) {
		SDL_RenderFillRect(theRenderer, &rect);
	}
	else {
		SDL_RenderDrawRect(theRenderer, &rect);
	}
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 0);
}
