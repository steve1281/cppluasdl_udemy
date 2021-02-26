#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "./Game.h"

class FontManager {
    public:
        static TTF_Font* LoadFont(const char* fileName, int fontSize) ;
        static void Draw(SDL_Texture* texture, SDL_Rect position);
};


#endif //FONTMANAGER_H
