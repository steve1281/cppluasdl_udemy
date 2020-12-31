#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Game {
    private:
        bool isRunning;
        SDL_Window *window;
    public:
        Game();
        ~Game();
        int ticksLastFrame;
        bool IsRunning() const;
        static SDL_Renderer *renderer; // changed to class wide static cause its used everywhere.
        void LoadLevel(int levelNumber);
        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

};



#endif
