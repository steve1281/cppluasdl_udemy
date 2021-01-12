#ifndef COLLIDERBOXCOMPONENT_H
#define COLLIDERBOXCOMPONENT_H


class ColliderBoxComponent: public Component  {
    private:
        SDL_Texture* texture;
        TransformComponent* transform;
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;

    public:
        ColliderBoxComponent(std::string id) {
            SetTexture(id); 
        }
        void Initialize() override { 
              transform = owner->GetComponent<TransformComponent>();
              sourceRectangle.x = 0;
              sourceRectangle.y = 0;
              sourceRectangle.w = transform->width;
              sourceRectangle.h = transform->height;
        }

        void Update(float deltaTime) override { 
              //sourceRectangle.y = transform->height ;

              destinationRectangle.x = static_cast<int>(transform->position.x) -  Game::camera.x;
              destinationRectangle.y = static_cast<int>(transform->position.y) -  Game::camera.y;
              destinationRectangle.w = static_cast<int>(transform->width * transform->scale) ;
              destinationRectangle.h = static_cast<int>(transform->height * transform->scale) ;
        }

        void Render() override { 
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
        }

        void SetTexture(std::string id) {
            texture = Game::assetManager->GetTexture(id);
        }
};


#endif

