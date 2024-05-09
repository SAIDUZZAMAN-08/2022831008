#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define CIRCLE_RADIUS 100
#define CIRCLE_SPEED 5
#define CONTROLLED_CIRCLE_RADIUS 50

bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("Task_103", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            }
        }
    }
}

void ControlledCircleDrawing(SDL_Renderer* renderer, int x, int y) {
    CircleDrawing(renderer, x, y, CONTROLLED_CIRCLE_RADIUS);
}

bool checkCollision(int x1, int y1, int x2, int y2, int radius1, int radius2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int distanceSquared = dx * dx + dy * dy;
    int radiusSumSquared = (radius1 + radius2) * (radius1 + radius2);
    return distanceSquared <= radiusSumSquared;
}

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initializeSDL(&window, &renderer)) {
        return 1;
    }

    int circleX = -CIRCLE_RADIUS;
    int circleY = SCREEN_HEIGHT / 2;
    int controlledCircleX = SCREEN_WIDTH / 2;
    int controlledCircleY = 0;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        controlledCircleY -= 5;
                        break;
                    case SDLK_DOWN:
                        controlledCircleY += 5;
                        break;
                    case SDLK_LEFT:
                        controlledCircleX -= 5;
                        break;
                    case SDLK_RIGHT:
                        controlledCircleX += 5;
                        break;
                }
            }
        }

        
        circleX += CIRCLE_SPEED;
        if (circleX > SCREEN_WIDTH + CIRCLE_RADIUS) {
            circleX = -CIRCLE_RADIUS;
        }

        SDL_SetRenderDrawColor(renderer, 0, 10, 78, 255);
        SDL_RenderClear(renderer);

        
        SDL_SetRenderDrawColor(renderer, 200, 0, 65, 255);
        CircleDrawing(renderer, circleX, circleY, CIRCLE_RADIUS);

        
        SDL_SetRenderDrawColor(renderer, 255 , 255, 255, 255);
        ControlledCircleDrawing(renderer, controlledCircleX, controlledCircleY);

        
        if (checkCollision(circleX, circleY, controlledCircleX, controlledCircleY, CIRCLE_RADIUS, CONTROLLED_CIRCLE_RADIUS)) {
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawLine(renderer, circleX - CIRCLE_RADIUS, circleY, circleX + CIRCLE_RADIUS, circleY);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}