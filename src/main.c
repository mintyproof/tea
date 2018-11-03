#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "assets.h"

typedef struct Engine {
    SDL_Window* window;
} Engine;

Engine engine_init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow("Test Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Error initializing creating SDL window: %s\n", SDL_GetError());
        exit(1);
    }

    // Draw to fill the framebuffer, just once
    SDL_Surface* surf = SDL_GetWindowSurface(window);
    SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 255, 0, 0));

    return (Engine) {
        .window = window
    };
}

void engine_loop(Engine* engine) {
    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_UpdateWindowSurface(engine->window);
    }
}

void engine_quit(Engine *engine) {
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
}

int main() {
    AssetManager* am = new_asset_manager();
    if (!load_asset(am, "test.txt")) exit(2);
    
    const char* data;
    uint32_t length;
    if (find_asset(am, "test.txt", &length, &data)) {
        char* buf = malloc(length+1);
        memcpy(buf, data, length);
        buf[length] = '\0';

        printf("Test file says: %s\n", buf);
    }


    Engine engine = engine_init();
    engine_loop(&engine);
    engine_quit(&engine);
    return 0;
}