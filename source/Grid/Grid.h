#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "../defs.h"
#include "../Screen/Screen.h"
#include "../Particle/Particle.h"

namespace grz
{
	
	class Grid
	{
	public:
		int particleCounter;
		Screen* screen;
		std::vector<std::vector<Particle_Type>> grid;

		Grid(Screen* screen);

		void render();
		void update();

		void handleInput(SDL_Event* event);

	private:
		void updateParticle(int x, int y);
		void renderParticle(int x, int y, Particle_Type type);
	};

}

