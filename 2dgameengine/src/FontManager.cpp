#include "FontManager.h"
#include <iostream>

TTF_Font*  FontManager::LoadFont(const char* fileName, int fontSize) {
    TTF_Font* x =  TTF_OpenFont(fileName, fontSize);
    if (x == NULL) {
        std::cout << "FontManager::LoadFont got a null-check assets folder for font." << std::endl;
        std::cout << "Expected: " << fileName << " " << fontSize << std::endl;
    } 
    return x;
}

void FontManager::Draw(SDL_Texture *texture, SDL_Rect position) {
    SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}

