#include <iostream>
#include "SDL.h"
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include <array>
#include "Sprite.h"

const float PI = 3.141;

using namespace std;
using namespace std::chrono;

static void BuildWindow();
void Render();
static void ProcessInput(int&, int&, int&, int&);
static void Update(int&, int&, int&, int&, int&, int&, int&);
void Spoopy();
void bouncer();
void Gemstone();

array<Sprite, 42> sprites;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool up = false;
bool Left = false;
bool Right = false;
high_resolution_clock::time_point t1 = high_resolution_clock::now();

int main(int argc, char* argv[])
{
	BuildWindow();
	int x = 0, k = 0, j = 0, i = 1, s = 90, c = 90, z = 650, g = 480;
	Gemstone();
	while (x == 0)
	{
		ProcessInput(x, i, z, g);
		Update(j, k, s, c, z, g, x);
		Render();
	}

	return 0;
}

static void BuildWindow()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Render()
{
	SDL_Delay(30);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, sprites[0].tex, &sprites[0].SrcR, &sprites[0].DestR);
	SDL_RenderPresent(renderer);
}

static void ProcessInput(int& x, int& d, int& z, int& g)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				sprites[0].SrcR.y = 0;
				break;
			case SDLK_2:
				sprites[0].SrcR.y = 17;
				break;
			case SDLK_3:
				sprites[0].SrcR.y = 34;
				break;
			case SDLK_ESCAPE:
				x = 1;
				break;
			case SDLK_UP:
				up=true;
				break;
			case SDLK_LEFT:
				Left = true;
				break;
			case SDLK_RIGHT:
				Right = true;
				break;
			case SDLK_f:
				if (d == 0)
				{
					SDL_SetWindowFullscreen(window, 0);
					SDL_SetWindowSize(window, 650, 480);
					z = 650;
					g = 480;
					d = 1;
				}
				else
				{
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
					SDL_GetWindowSize(window, &z, &g);
					d = 0;
				}
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				up = false;
				break;
			case SDLK_LEFT:
				Left = false;
				break;
			case SDLK_RIGHT:
				Right = false;
				break;
			}
			break;
		case SDL_QUIT:
			x = 1;
			break;
		default:
			break;
		}
	}
}

static void Update(int& j, int& k, int& s, int& c, int& z, int& g, int& x)
{
	if (sprites[0].DestR.y >= 480 - 64)
	{
		if (up)
		{
			sprites[0].force[1] += sprites[0].mass * 200;
		}
	}
	else
	{
		sprites[0].force[1] += sprites[0].mass*-9.81;
	}
	sprites[0].move[1] = sprites[0].force[1] / sprites[0].mass / 10;
	if (sprites[0].DestR.y - sprites[0].move[1] >= 480-64)
	{
		sprites[0].DestR.y = 480 - 64;
		sprites[0].force[1] = 0;
	}
	else
	{
		sprites[0].DestR.y -= sprites[0].move[1];
	}
	if (Left)
	{
		if (sprites[0].SrcR.x == 42)
		{
			sprites[0].SrcR.x = 0;
		}
		else
		{
			sprites[0].SrcR.x += 14;
		}
	}
	if (Right)
	{
		if (sprites[0].SrcR.x == 0)
		{
			sprites[0].SrcR.x = 42;
		}
		else
		{
			sprites[0].SrcR.x -= 14;
		}
	}
}

void bouncer()
{
	SDL_Surface *bmp;
	bmp = SDL_LoadBMP("images.bmp");
	sprites[0].tex = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	bmp = NULL;

	sprites[0].SrcR.x = 0;
	sprites[0].SrcR.y = 0;
	sprites[0].SrcR.w = 64;
	sprites[0].SrcR.h = 64;
	sprites[0].DestR.x = (640 - 64) / 2;
	sprites[0].DestR.y = (480 - 64) / 2;
	sprites[0].DestR.w = 64;
	sprites[0].DestR.h = 64;

	sprites[0].pos[0] = (640 - 64) / 2;
	sprites[0].pos[1] = 480 - 64;
	sprites[0].move[0] = 0;
	sprites[0].move[1] = 25;
	sprites[0].mass = 3;
	sprites[0].force[1] = 100;

}

void Spoopy()
{
	for (int i = 0;i<sprites.size();i++)
	{
		SDL_Surface *bmp;
		bmp = SDL_LoadBMP("images.bmp");
		sprites[i].tex = SDL_CreateTextureFromSurface(renderer, bmp);
		SDL_FreeSurface(bmp);
		bmp = NULL;

		sprites[i].SrcR.x = 0;
		sprites[i].SrcR.y = 0;
		sprites[i].SrcR.w = 64;
		sprites[i].SrcR.h = 64;
		sprites[i].DestR.x = rand() % 577;
		sprites[i].DestR.y = rand() % 417;
		sprites[i].DestR.w = 64;
		sprites[i].DestR.h = 64;
	}
}

void Gemstone()
{
	SDL_Surface *bmp;
	bmp = SDL_LoadBMP("SuperTexture.bmp");
	SDL_SetColorKey(bmp,SDL_TRUE,SDL_MapRGB(bmp->format,255,255,255));
	sprites[0].tex = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	bmp = NULL;

	

	sprites[0].SrcR.x = 14;
	sprites[0].SrcR.y = 0;
	sprites[0].SrcR.w = 13;
	sprites[0].SrcR.h = 16;
	sprites[0].DestR.x = (640 - 52) / 2;
	sprites[0].DestR.y = (480 - 64) / 2;
	sprites[0].DestR.w = 52;
	sprites[0].DestR.h = 64;

	sprites[0].mass = 3;
	sprites[0].force[1] = 0;
	sprites[0].move[1] = 0;
}