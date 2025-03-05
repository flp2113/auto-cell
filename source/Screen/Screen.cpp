#include "Screen.h"

grz::Screen::Screen() : window(nullptr), renderer(nullptr) { }

grz::Screen::~Screen() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_AppResult grz::Screen::setup(const char* title, int width, int height, SDL_WindowFlags flags)
{
    if (width < MIN_WINDOW_WIDTH || height < MIN_WINDOW_HEIGHT)
        throw std::runtime_error("BAD WINDOW WIDTH/HEIGHT");

    if (!SDL_CreateWindowAndRenderer(title, width, height, flags, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_SUCCESS;

}