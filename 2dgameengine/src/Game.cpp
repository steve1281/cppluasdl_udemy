#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/ColliderBoxComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0,WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
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
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {

    // load assets
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
    assetManager->AddTexture("collision-texture", std::string("./assets/images/collision-texture.png").c_str());

    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

    // start including entities and their components
    // tank - enemy
    Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
    tankEntity.AddComponent<TransformComponent>(150, 495, 5, 0, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image",1,0,false, false); 
    tankEntity.AddComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);
    tankEntity.AddComponent<ColliderBoxComponent>("collision-texture");
    tankEntity.AddComponent<KeyboardControlComponent>();

    // chopper - player
    player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1, true);
    player.AddComponent<SpriteComponent>("chopper-image",2,90,true,false); // id,numFrames,animSpeed,hasDirections,isFixed   
    player.AddComponent<ColliderBoxComponent>("collision-texture");
    player.AddComponent<KeyboardControlComponent>("up","right","down","left","space");
    player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

    // radar
    Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image",8,150,false,true);

    // END LEVEL marker
    Entity& heliport(manager.AddEntity("Heliport", OBSTACLE_LAYER));
    heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    heliport.AddComponent<SpriteComponent>("heliport-image", 1, 0, false, false);
    heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);
    
    //manager.ListOutEntities();
    //manager.AnyTransforms();
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

void Game::Update() {
    // Wait until 16ms has ellapsed since the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    
    // Delta time is the difference in ticks from last frame converted to secomds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);

    HandleCameraMovement();

    CheckCollisions();

}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render(); 

    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
    TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH /2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT/2);

    // clamp
    camera.x = camera.x < 0 ? 0:camera.x;
    camera.y = camera.y < 0 ? 0:camera.y;
    camera.x = camera.x > camera.w ? camera.w :camera.x;
    camera.h = camera.y > camera.h ? camera.h :camera.y;

}

void Game::CheckCollisions() {
    CollisionType collisionType =  manager.CheckCollisions();
    if (collisionType == PLAYER_ENEMY_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
        ProcessNextLevel(1);
    }

}

void Game::ProcessGameOver() {
    std::cout<<"Game Over"<<std::endl;
    isRunning = false;
}

void Game::ProcessNextLevel(int level)
{
    std::cout<<"Next Level"<<std::endl;
    isRunning = false;
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
