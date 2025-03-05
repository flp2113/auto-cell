#pragma once

#include <SDL3/SDL.h>

#include <stdexcept>

#include "../defs.h"

namespace grz 
{

	class Screen
	{
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;

		Screen();
		~Screen();

		SDL_AppResult setup(const char*, int, int, SDL_WindowFlags);
	};

}



