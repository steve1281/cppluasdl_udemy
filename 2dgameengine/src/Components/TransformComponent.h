#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include "../Game.h"
#include "../Constants.h"

class TransformComponent: public Component {
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;
        bool bounded; 

        void init( int posX, int posY, int velX, int velY, int w, int h, int s, bool bounded) {
            this->bounded = bounded;
            position = glm::vec2(posX, posY);
            velocity = glm::vec2(velX, velY);
            width = w;
            height = h;
            scale = s;
        }

        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
            init(posX, posY, velX, velY, w, h, s, false);
        }

        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s, bool bounded) {
            init(posX, posY, velX, velY, w, h, s, bounded);
        }

        void Initialize() override { 
        }

        void Update(float deltaTime) override {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
            if (bounded) {
                 // todo: need to be bounded
            }
        }

        void Render() override {
        }
};

#endif
