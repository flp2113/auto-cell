#include "Grid.h"
#include <iostream>

grz::Grid::Grid(Screen* screen) : particleCounter(0), screen(screen)
{
	int gridWidth = WINDOW_WIDTH / PARTICLE_SCALE;
	int gridHeight = WINDOW_HEIGHT / PARTICLE_SCALE;

	grid.resize(gridHeight, std::vector<Particle>(gridWidth, Particle{ Vec4{ 0.0f, 0.0f, 0.0f, 1.0f }, EMPTY }));
	std::cout << "GRID WIDTH: " << gridWidth << " GRID HEIGHT: " << gridHeight << '\n';

	for (int y = 0; y < gridHeight; y++)
		for (int x = 0; x < gridWidth; x++)
			grid.at(y).at(x) = Particle{ Vec4{ 0.0f, 0.0f, 0.0f, 1.0f }, EMPTY };

	for (int x = gridWidth / 2; x < gridWidth; x++)
		for(int y = 20; y < gridHeight; y++) 
			grid.at(y).at(x) = Particle{ Vec4{ 0.5f, 0.5f, 0.5f, 1.0f }, ROCK };

	
	for (int x = 0; x < gridWidth / 2; x++)
		grid.at(100).at(x) = Particle{ Vec4{ 0.5f, 0.5f, 0.5f, 1.0f }, ROCK };

	for (int x = 0; x < gridWidth; x++)
		grid.at(140).at(x) = Particle{ Vec4{ 0.5f, 0.5f, 0.5f, 1.0f }, ROCK };
	
}

void grz::Grid::render() 
{
	int gridWidth = WINDOW_WIDTH / PARTICLE_SCALE;
	int gridHeight = WINDOW_HEIGHT / PARTICLE_SCALE;
	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {
			renderParticle(x * PARTICLE_SCALE, y * PARTICLE_SCALE, &grid.at(y).at(x));
		}
	}
}

void grz::Grid::update()
{
	int gridWidth = WINDOW_WIDTH / PARTICLE_SCALE;
	int gridHeight = WINDOW_HEIGHT / PARTICLE_SCALE;
	// IT ITERATES THROUGH THE MATRIX FROM THE BOTTOM TO THE TOP
	for (int y = gridHeight - 1; y >= 0; y--) {
		for (int x = 0; x < gridWidth; x++) {
			updateParticle(x, y);
		}
	}
}

void grz::Grid::updateParticle(int x, int y)
{
	// IF THE TOP PARTICLE IS SAND, IT MUST GO DOWN
	// IF ITS A ROCK STOP
	if (y - 1 > 0 && grid.at(y - 1).at(x).type == SAND) {
		// IF THE LOWER PARTICLE IS EMPTY
		if (grid.at(y).at(x).type == EMPTY) {
			std::swap(grid.at(y - 1).at(x), grid.at(y).at(x));
			return;
		}

		if (grid.at(y).at(x).type == ROCK)
			return;
		//std::swap(grid.at(y - 1).at(x), grid.at(y).at(x));
	}

	// IF THE LOWER PARTICLE IS NOT EMPTY
	if (x - 1 > 0 && y - 1 > 0 && grid.at(y - 1).at(x).type == SAND) {
		if (grid.at(y).at(x - 1).type == EMPTY)
			std::swap(grid.at(y - 1).at(x), grid.at(y).at(x - 1));

		if (grid.at(y).at(x + 1).type == EMPTY)
			std::swap(grid.at(y - 1).at(x), grid.at(y).at(x + 1));
	}

}

void grz::Grid::renderParticle(int x, int y, Particle* particle)
{
	if (!particle->color.x && particle->type == SAND) {
		float r = 0.8f + (rand() % 20) / 100.0f;
		float g = 0.7f + (rand() % 20) / 100.0f;
		float b = 0.2f + (rand() % 20) / 100.0f;
		particle->color = { r, g, b, SDL_ALPHA_OPAQUE };
	}

	if (!particle->color.x && particle->type == ROCK) {
		float r = 0.5f + (rand() % 10) / 100.0f;
		float g = 0.5f + (rand() % 10) / 100.0f;
		float b = 0.5f + (rand() % 10) / 100.0f;
		particle->color = { r, g, b, SDL_ALPHA_OPAQUE };
	}
	
	SDL_FRect particleRect = { x, y, PARTICLE_SCALE, PARTICLE_SCALE };
	switch (particle->type) {
	case SAND: 
		SDL_SetRenderDrawColorFloat(screen->renderer, particle->color.x, particle->color.y, particle->color.w, SDL_ALPHA_OPAQUE);
		break;
	case ROCK:
		SDL_SetRenderDrawColorFloat(screen->renderer, particle->color.x, particle->color.y, particle->color.w, SDL_ALPHA_OPAQUE);
		break;
	case EMPTY:
		SDL_SetRenderDrawColorFloat(screen->renderer, 0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE);
		break;
	}
	SDL_RenderFillRect(screen->renderer, &particleRect);
}


void grz::Grid::handleInput(SDL_Event* event)
{
	float mouseX, mouseY;
	switch (event->type) {
	case SDL_EVENT_KEY_DOWN:

		switch (event->key.key) {
		case SDLK_S:
			SDL_GetMouseState(&mouseX, &mouseY);
			if (grid.at(mouseY / PARTICLE_SCALE).at(mouseX / PARTICLE_SCALE).type == EMPTY)
				grid.at(mouseY / PARTICLE_SCALE).at(mouseX / PARTICLE_SCALE) = Particle{ Vec4{ }, SAND };
			break;

		case SDLK_R:
			SDL_GetMouseState(&mouseX, &mouseY);
			if (grid.at(mouseY / PARTICLE_SCALE).at(mouseX / PARTICLE_SCALE).type == EMPTY)
				grid.at(mouseY / PARTICLE_SCALE).at(mouseX / PARTICLE_SCALE) = Particle{ Vec4{ }, ROCK };
			break;
		}
		break;


	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		SDL_GetMouseState(&mouseX, &mouseY);
		int mouseGridX = mouseX / PARTICLE_SCALE;
		int mouseGridY = mouseY / PARTICLE_SCALE;

		int offsetX, offsetY;

		for (int y = mouseGridY - 5; y < mouseGridY + 5; y++) {
			for (int x = mouseGridX - 5; x < mouseGridX + 5; x++) {
				if (grid.at(y).at(x).type != EMPTY) {
					grid.at(y).at(x) = Particle{ Vec4{ }, EMPTY };
				}
			}
		}
		break;
	}

}



