/*
 * Renderer.h
 *
 *  Created on: 22 May 2015
 *      Author: Jack
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include "Utils.h"

struct TextureBox {
	SDL_Texture* texture;
	int w;
	int h;
};

//A class that bundles together the window and the renderer to separate rendering textures from
//the rest of the program logic. Requires an SDL context to work.
class Renderer {
private:
	//An array storing all of the textures in the game
	TextureBox textures[T_TOTAL];

	SDL_Renderer* theRenderer;
	SDL_Window* window;

	TextureBox loadTextureFromFile(std::string path);
	TextureBox loadTextureFromText(std::string text, TTF_Font* , SDL_Color);

	//Loads the required textures into the textures array
	void generateTextures();

	TTF_Font* titleFont;
	TTF_Font* buttonFont;

public:
	Renderer();
	~Renderer();

	//Renders the texture of the specified ID with the paramters given
	void render(TextureID id, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Loads and renders an image of our lord and saviour Heropon Riki at (100, 100)
	void renderDebug();

	//Calls SDL_RenderClear on theRenderer
	void renderClear();

	//Calls SDL_RenderPresent on theRenderer
	void renderPresent();

	void renderRect(SDL_Rect rect, SDL_Color color, bool fill);
};

#endif /* RENDERER_H_ */
