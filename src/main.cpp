#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <psp2/kernel/processmgr.h>

// Screen dimension constants
enum
{
    SCREEN_WIDTH = 960,
    SCREEN_HEIGHT = 544
};

SDL_Texture* LoadSprite(const char* file, SDL_Renderer* renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
    if (texture == nullptr)
    {
        return nullptr;
    }
    return texture;
}

void RenderSprite(SDL_Texture* sprite, SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(sprite, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, sprite, NULL, &dest);
}

auto main() -> int
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER))
        return -1;

    SDL_Window* window =
        SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* sprite = LoadSprite("sprites/sprite.png", renderer);

    SDL_Event event;
    bool renderSprite = false;
    bool running = true;
    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_CONTROLLERDEVICEADDED:
                SDL_GameControllerOpen(event.cdevice.which);
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
                    running = false;
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
                    renderSprite = true;
                break;
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw everything on a dark blue background
        SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);

        // Draw sprite
        if (renderSprite && sprite != nullptr)
        {
            RenderSprite(sprite, renderer, 100, 100); // Render at position 100, 100
        }

        // Present changes
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
