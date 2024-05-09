#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Task_102", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void CircleDrawing(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initializeSDL(&window, &renderer)) {
        return 1;
    }

    SDL_Event event;
    bool running = true;
    int circleRadius = 5; 
    int circleX = SCREEN_WIDTH / 2;
    int circleY = SCREEN_HEIGHT / 2;
    int IncreasingRadius = 5; 

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        
        SDL_SetRenderDrawColor(renderer, 0, 10, 78, 255);
        SDL_RenderClear(renderer);

        
        SDL_SetRenderDrawColor(renderer, 200, 0, 65, 255);
        CircleDrawing(renderer, circleX, circleY, circleRadius);

        
        SDL_RenderPresent(renderer);

       
        circleRadius += IncreasingRadius;

        
        if (circleX + circleRadius >= SCREEN_WIDTH || circleY + circleRadius >= SCREEN_HEIGHT) {
            circleRadius = 5;
            circleX = SCREEN_WIDTH / 2;
            circleY = SCREEN_HEIGHT / 2;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}