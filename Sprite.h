#pragma once
#include "SDL.h"
#include "array"

class Sprite
{
public:
	SDL_Texture *tex;
	SDL_Rect SrcR, DestR;
	float pos[2];
	float move[2];
	float mass;
	float force[2] = {0,0};
};
