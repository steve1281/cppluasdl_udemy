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
                if (position.x + width >= WINDOW_WIDTH) {
                    position.x = WINDOW_WIDTH - width;
                }
                if (position.x <= 0) {
                    position.x = 0;
                }
                if (position.y + height >= WINDOW_HEIGHT) {
                    position.y = WINDOW_HEIGHT - height;
                }
                if (position.y <= 0) {
                    position.y = 0;
                }
            }
        }

        void Render() override {
        }
};

#endif
