#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h" 
using namespace std;

const int WIDTH = 650;
const int HEIGHT = 700;

const int SOLID = 100;
const int SHADED = 101;
const int BLENDED = 102;

#define M 33
#define N 30

SDL_RendererFlip no = SDL_FLIP_NONE;
SDL_RendererFlip ho = SDL_FLIP_HORIZONTAL;
SDL_RendererFlip ve = SDL_FLIP_VERTICAL;
SDL_RendererFlip hove = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

Mix_Music* beginning = NULL;    //00 : 00 : 04 : 06
Mix_Music* death = NULL;        //00 : 00 : 01 : 16
Mix_Music* intermission = NULL; //00 : 00 : 05 : 06
Mix_Music* woooo = NULL;
Mix_Music* woooo2 = NULL;
Mix_Music* woooo3 = NULL;
Mix_Music* woooo4 = NULL;
Mix_Music* woooo5 = NULL;
Mix_Music* frighten = NULL;
Mix_Music* backtocenter = NULL;
Mix_Chunk* chomp = NULL;
Mix_Chunk* eatghost = NULL;

struct ImageData
{
	SDL_Texture* texture;
	int width;
	int height;
	int num;
	int wn;
	int hn;
};

struct TextData
{
	SDL_Texture* texture;
	int width;
	int height;
};

struct color
{
	int r;
	int g;
	int b;
	int alpha;
};

struct Rank
{
	char name[20];
	int score;
};

struct vec3d
{
	double x = 0;
	double y = 0;
	double z = 0;
	double w = 1;
};

enum MouseState
{
	NONE = 0,
	OUT = 1, // Mouse out
	LB_SC = 2,  // Inside, Left Button, Single Click
	RB_SC = 3,  // Inside, RIGHT Button, Single Click
	LB_DC = 4,  // Inside, Left Button, Double Click
	RB_DC = 5,  // Inside, RIGHT Button, Double Click
	LB_PR = 6,  // Inside, Left Button, Press
	RB_PR = 7,  // Inside, Left Button, Press
	WU = 8,  // Inside, Wheel UP
	WD = 9,  // Inside, Wheel DOWN
	HOVER = 10, // Mouse hover
	IN_LB_PR_HOVER = 11 // Inside, Left Button, Press, Hover
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("OOP SDL Tutorial", 50, 50, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 2;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed: %s\n", IMG_GetError());
		return 3;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 4;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 5;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 5;
	}
	return 0;
}

void closeSDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

ImageData loadImgTexture(char* path, int num, int hn, int wn, bool ckEnable, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* loadedSurface = IMG_Load(path);

	if (loadedSurface == NULL)
	{
		printf("IMG_Load failed: %s\n", IMG_GetError());
		return { NULL };
	}
	else
	{
		ImageData img;

		SDL_SetColorKey(loadedSurface, ckEnable, SDL_MapRGB(loadedSurface->format, r, g, b));

		img.texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (img.texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}
		img.width = loadedSurface->w;
		img.height = loadedSurface->h;
		img.num = num;
		img.wn = wn;
		img.hn = hn;

		SDL_FreeSurface(loadedSurface);

		return img;
	}
}

int imgRender(SDL_Renderer* renderer, ImageData img, int posX, int posY, int frame, int cx, int cy, double angle, SDL_RendererFlip flip, int alpha, double stretchX, double stretchY)
{
	int wc = frame % img.wn;
	int hc = frame / img.wn;

	SDL_Rect src, dst;
	src.x = img.width / img.wn * wc;
	src.y = img.height / img.hn * hc;
	src.w = img.width / img.wn;
	src.h = img.height / img.hn;
	dst.x = posX;
	dst.y = posY;
	dst.w = src.w * stretchX;
	dst.h = src.h * stretchY;

	if (SDL_SetTextureBlendMode(img.texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return -1;
	}

	if (SDL_SetTextureAlphaMod(img.texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Point center = { cx, cy };

	SDL_RenderCopyEx(renderer, img.texture, &src, &dst, angle, &center, flip);

	return 1;
}

TextData loadTextTexture(const char* str, const char* fontPath, int fontSize, Uint8 fr, Uint8 fg, Uint8 fb, int textType, Uint8 br, Uint8 bg, Uint8 bb)
{
	TTF_Font* ttfFont = NULL;

	ttfFont = TTF_OpenFont(fontPath, fontSize);

	if (ttfFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	SDL_Color textFgColor = { fr, fg, fb }, textBgColor = { br, bg, bb };

	SDL_Surface* textSurface = NULL;

	if (textType == SOLID)
	{
		textSurface = TTF_RenderText_Solid(ttfFont, str, textFgColor);
	}
	else if (textType == SHADED)
	{
		textSurface = TTF_RenderText_Shaded(ttfFont, str, textFgColor, textBgColor);
	}
	else if (textType == BLENDED)
	{
		textSurface = TTF_RenderText_Blended(ttfFont, str, textFgColor);
	}

	TTF_CloseFont(ttfFont);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return { NULL };
	}
	else
	{
		TextData text;

		text.texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (text.texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		text.width = textSurface->w;
		text.height = textSurface->h;

		SDL_FreeSurface(textSurface);

		return text;
	}
}

int textRender(SDL_Renderer* renderer, TextData text, int posX, int posY, int cx, int cy, double angle, SDL_RendererFlip flip, int alpha)
{
	SDL_Rect r;
	r.x = posX;
	r.y = posY;
	r.w = text.width;
	r.h = text.height;

	if (SDL_SetTextureBlendMode(text.texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return -1;
	}

	if (SDL_SetTextureAlphaMod(text.texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Point center = { cx, cy };

	SDL_RenderCopyEx(renderer, text.texture, NULL, &r, angle, &center, flip);
	return 1;
}

void mouseHandleEvent(SDL_Event* e, MouseState* mouseState, int* x, int* y)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEWHEEL)
	{
		SDL_GetMouseState(x, y);
		static int lasttime = SDL_GetTicks();
		static int curtime = SDL_GetTicks();
		int timediv;

		lasttime = curtime;
		curtime = SDL_GetTicks();
		timediv = curtime - lasttime;

		switch (e->type)
		{
		case SDL_MOUSEBUTTONUP:
			if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 2 && timediv < 150)
			{
				*mouseState = LB_DC;
			}
			else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 2 && timediv < 150)
			{
				*mouseState = RB_DC;
			}
			else if (e->button.button == SDL_BUTTON_LEFT && e->button.clicks == 1 && timediv < 800 && timediv > 10)
			{
				*mouseState = LB_SC;
			}
			else if (e->button.button == SDL_BUTTON_RIGHT && e->button.clicks == 1 && timediv < 800 && timediv > 10)
			{
				*mouseState = RB_SC;
			}
			break;
		case SDL_MOUSEWHEEL:
			if (e->wheel.y > 0) // scroll up
			{
				*mouseState = WU;
			}
			else if (e->wheel.y < 0) // scroll down
			{
				*mouseState = WD;
			}
			break;
		}
	}
}

bool loadAudio()
{
	/*
	beginning = Mix_LoadMUS("../audio/pacman_beginning.wav");
	if (beginning == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	chomp = Mix_LoadMUS("../audio/pacman_chomp.wav");
	if (chomp == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	death = Mix_LoadMUS("../audio/pacman_death.wav");
	if (death == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}


	eatghost = Mix_LoadMUS("../audio/pacman_eatghost.wav");
	if (eatghost == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	intermission = Mix_LoadMUS("../audio/pacman_intermission.wav");
	if (intermission == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	*/
	beginning = Mix_LoadMUS("../audio/pacman_beginning.wav");
	if (beginning == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	death = Mix_LoadMUS("../audio/pacman_death.wav");
	if (death == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}


	intermission = Mix_LoadMUS("../audio/pacman_intermission.wav");
	if (intermission == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	woooo = Mix_LoadMUS("../audio/pacman_woooo.wav");
	if (woooo == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	woooo2 = Mix_LoadMUS("../audio/pacman_woooo2.wav");
	if (woooo2 == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	woooo3 = Mix_LoadMUS("../audio/pacman_woooo3.wav");
	if (woooo3 == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	woooo4 = Mix_LoadMUS("../audio/pacman_woooo4.wav");
	if (woooo4 == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	woooo5 = Mix_LoadMUS("../audio/pacman_woooo5.wav");
	if (woooo5 == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	frighten = Mix_LoadMUS("../audio/pacman_frighten.wav");
	if (frighten == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	backtocenter = Mix_LoadMUS("../audio/pacman_backtocenter.wav");
	if (backtocenter == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	chomp = Mix_LoadWAV("../audio/pacman_chomp.wav");
	if (chomp == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	eatghost = Mix_LoadWAV("../audio/pacman_eatghost.wav");
	if (eatghost == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	/*
	Mix_Music* beginning = NULL;    //00 : 00 : 04 : 06
	Mix_Music* death = NULL;        //00 : 00 : 01 : 16
	Mix_Music* intermission = NULL; //00 : 00 : 05 : 06
	Mix_Music* woooo = NULL;
	Mix_Music* woooo2 = NULL;
	Mix_Music* woooo3 = NULL;
	Mix_Music* woooo4 = NULL;
	Mix_Music* woooo5 = NULL;
	Mix_Music* frighten = NULL;
	Mix_Music* backtocenter = NULL;
	Mix_Chunk* chomp = NULL;
	Mix_Chunk* eatghost = NULL;
	*/
}
