#include "./TextureManager.h"

#include <iostream>
#include <fstream>

SDL_Texture* TextureManager::LoadTexture(const char * fileName){
    std::ifstream f(fileName);
    if (!f.good()) {
        std::cout << "Asset file " << fileName << " missing."<< std::endl;
        exit(-1);
    }

    SDL_Surface* surface = IMG_Load(fileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(
        SDL_Texture* texture, 
        SDL_Rect sourceRectangle, 
        SDL_Rect destinationRectangle, 
        SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);
}
