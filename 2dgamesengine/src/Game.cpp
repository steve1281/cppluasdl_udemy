#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"

#include "./EntityManager.h"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}


void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) !=0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL Window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL Renderer." << std::endl;
        return;
    }
    isRunning = true;
    return;
}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        }
        default: {
            break;
        }
    }
    
}

void Game::Update() {

    // Wait until 16ms (for 60fps) has elapsed since the last frame
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) /1000.0f;
    
    //clamp deltatime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    ticksLastFrame = SDL_GetTicks();

    //todo: call update all entities.
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);    // set color gray and opaque
    SDL_RenderClear(renderer);   // clear back buffer

    // todo: 
    // yah, need to call the entities.
    
    SDL_RenderPresent(renderer);   // buffer swap

}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


