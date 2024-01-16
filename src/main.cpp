#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
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

    // Initialize ImGui
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    SDL_Event event;
    bool renderSprite = false;
    bool running = true;
    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            // ImGui SDL input
            ImGui_ImplSDL2_ProcessEvent(&event);
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
                    renderSprite = !renderSprite;
                break;
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw everything on a dark blue background
        SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);

        if (renderSprite)
            RenderSprite(sprite, renderer, 30, 30);

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        if (ImGui::Begin("Spawn enemies"))
        {
            ImGui::Text("Press X to spawn a sprite");
            if (ImGui::Button("Or press this button"))
                renderSprite = !renderSprite;
            ImGui::Text("Press START to exit");
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

        // Present changes
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
