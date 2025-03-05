#include "Grid.h"
#include <iostream>

grz::Grid::Grid(Screen* screen) : particleCounter(0), screen(screen)
{
	int gridWidth = WINDOW_WIDTH / PARTICLE_SCALE;
	int gridHeight = WINDOW_HEIGHT / PARTICLE_SCALE;

	grid.resize(gridHeight, std::vector<Particle_Type>(gridWidth, EMPTY));
	std::cout << "GRID WIDTH: " << gridWidth << " GRID HEIGHT: " << gridHeight << '\n';

	for (int y = 0; y < gridHeight; y++)
		for (int x = 0; x < gridWidth; x++)
			grid.at(y).at(x) = EMPTY;

	for (int x = gridWidth / 2; x < gridWidth; x++)
		for(int y = 20; y < gridHeight; y++)
			grid.at(y).at(x) = ROCK;

	
	for (int x = 0; x < gridWidth / 2; x++)
		grid.at(100).at(x) = ROCK;

	for (int x = 0; x < gridWidth; x++)
		grid.at(140).at(x) = ROCK;
	
}

void grz::Grid::render() 
{
	int gridWidth = WINDOW_WIDTH / PARTICLE_SCALE;
	int gridHeight = WINDOW_HEIGHT / PARTICLE_SCALE;
	for (int y = 0; y < gridHeight; y++) {
		for (int x = 0; x < gridWidth; x++) {
			renderParticle(x * PARTICLE_SCALE, y * PARTICLE_SCALE, grid.at(y).at(x));
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
	if (y - 1 > 0 && grid.at(y - 1).at(x) == SAND) {
		// IF THE LOWER PARTICLE IS EMPTY
		if (grid.at(y).at(x) == EMPTY) {
			std::swap(grid.at(y - 1).at(x), grid.at(y).at(x));
			return;
		}

		if (grid.at(y).at(x) == ROCK)
			return;
		//std::swap(grid.at(y - 1).at(x), grid.at(y).at(x));
	}

	// IF THE LOWER PARTICLE IS NOT EMPTY
	if (x - 1 > 0 && y - 1 > 0 && grid.at(y - 1).at(x) == SAND) {
		if (grid.at(y).at(x - 1) == EMPTY)
			std::swap(grid.at(y - 1).at(x), grid.at(y).at(x - 1));

		if (grid.at(y).at(x + 1) == EMPTY)
			std::swap(grid.at(y - 1).at(x), grid.at(y).at(x + 1));
	}

}

void grz::Grid::renderParticle(int x, int y, Particle_Type type)
{
	SDL_FRect particle = { x, y, PARTICLE_SCALE, PARTICLE_SCALE };
	switch (type) {
	case SAND:
		SDL_SetRenderDrawColorFloat(screen->renderer, 1.0f, 1.0f, 0.0f, SDL_ALPHA_OPAQUE);
		break;
	case ROCK:
		SDL_SetRenderDrawColorFloat(screen->renderer, 0.5f, 0.5f, 0.5f, SDL_ALPHA_OPAQUE);
		break;
	case EMPTY:
		SDL_SetRenderDrawColorFloat(screen->renderer, 0.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE);
		break;
	}
	SDL_RenderFillRect(screen->renderer, &particle);
}


void grz::Grid::handleInput(SDL_Event* event)
{
	float mouseX, mouseY;
	switch (event->type) {
	case SDL_EVENT_KEY_DOWN:
		SDL_GetMouseState(&mouseX, &mouseY);
		if (grid.at(mouseY / PARTICLE_SCALE).at(mouseX / PARTICLE_SCALE) == EMPTY) {
			grid.at(mouseY / PARTICLE_SCALE).at(mouseX / PARTICLE_SCALE) = SAND;
			particleCounter++;
			std::cout << "Particle Counter: " << particleCounter << '\n';
		}
		break;


	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		SDL_GetMouseState(&mouseX, &mouseY);
		grid.at(mouseY / PARTICLE_SCALE).at(mouseX / PARTICLE_SCALE) = EMPTY;
		break;
	}

}



