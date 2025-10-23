#include <SDL3/SDL.h>
#include <iostream>

const int WINDOW_W = 800;
const int WINDOW_H = 600;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr
            << "SDL init failed: "
            << SDL_GetError()
            << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Structura Engine",
        WINDOW_H,
        WINDOW_H,
        SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        std::cerr
            << "Window creation failed: "
            << SDL_GetError()
            << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr
            << "Renderer creation failed: "
            << SDL_GetError()
            << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
