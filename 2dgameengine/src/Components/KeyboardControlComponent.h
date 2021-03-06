#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ColliderBoxComponent.h"


class KeyboardControlComponent: public Component {
    private:

    public:
        std::string upKey;
        std::string downKey;
        std::string rightKey;
        std::string leftKey;
        std::string shootKey;
        std::string toggleCol;

        TransformComponent *transform;
        SpriteComponent *sprite;
        ColliderBoxComponent *box;

        void GlobalKeys() {
            this->toggleCol= GetSDLKeyStringCode("c");
        }

        KeyboardControlComponent(){
            GlobalKeys();
        }

        KeyboardControlComponent(
                std::string upKey,
                std::string rightKey,
                std::string downKey,
                std::string leftKey,
                std::string shootKey
                ){

            // Local Keys
            this->upKey    = GetSDLKeyStringCode(upKey); 
            this->rightKey = GetSDLKeyStringCode(rightKey); 
            this->leftKey  = GetSDLKeyStringCode(leftKey); 
            this->downKey  = GetSDLKeyStringCode(downKey); 
            this->shootKey = GetSDLKeyStringCode(shootKey); 

            GlobalKeys();
        }

    std::string GetSDLKeyStringCode(std::string key) {
            if (key.compare("up")    == 0) return "1073741906";
            if (key.compare("down")  == 0) return "1073741905";
            if (key.compare("left")  == 0) return "1073741904";
            if (key.compare("right") == 0) return "1073741903";
            if (key.compare("space") == 0) return "32";

            return std::to_string(static_cast<int>(key[0]));  //convert character to its ASCII.
    }

    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        sprite = owner->GetComponent<SpriteComponent>();
        box = owner->GetComponent<ColliderBoxComponent>();
    }

    void Update(float deltaTime) override {
        if (Game::event.type == SDL_KEYDOWN) {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);
            //std::cout << keyCode << std::endl;
            if (keyCode.compare(upKey)    == 0) {
                transform->velocity.y = -40;
                transform->velocity.x = 0;
                sprite->Play("UpAnimation");
            }
            if (keyCode.compare(rightKey) == 0) {
                transform->velocity.y = 0;
                transform->velocity.x = 40;
                sprite->Play("RightAnimation");
            }
            if (keyCode.compare(downKey)  == 0) {
                transform->velocity.y = 40;
                transform->velocity.x = 0;
                sprite->Play("DownAnimation");
            }
            if (keyCode.compare(leftKey)  == 0) {
                transform->velocity.y = 0;
                transform->velocity.x = -40;
                sprite->Play("LeftAnimation");
            }
            if (keyCode.compare(shootKey) == 0) {
                // todo: need to code in projectiles.
            }
            if (keyCode.compare(toggleCol) == 0) {
                if (box) box->Toggle();
            }

        }
        if (Game::event.type == SDL_KEYUP) {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);
            if (keyCode.compare(upKey) == 0) {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(rightKey) == 0) {
                transform->velocity.x = 0;
            }
            if (keyCode.compare(downKey)  == 0) {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(leftKey)  == 0) {
                transform->velocity.x = 0;
            }
        }
    }


};


#endif

