#ifndef PROJECTILEEMITTERCOMPONENT
#define PROJECTILEEMITTERCOMPONENT

#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"


class ProjectileEmitterComponent : public Component {


private:
    TransformComponent *transform;
    glm::vec2 origin;
    int speed;
    int range;
    float angleRad; // needs to be radians
    bool shouldLoop; 
public:
    ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop) {
        this->speed = speed;
        this->angleRad = glm::radians(static_cast<float>(angleDeg));
        this->range = range;
        this->shouldLoop = shouldLoop;
    }
    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        origin = glm::vec2(transform->position.x, transform->position.y);
        transform->velocity = glm::vec2(glm::cos(angleRad)*speed, glm::sin(angleRad)*speed); // speed in a direction.
        
    }
    void Update(float deltaTime) override {
        if (glm::distance(transform->position, origin) > range) {
            if (shouldLoop) {
                transform->position.x = origin.x;
                transform->position.y = origin.y;
            } else {
                owner->Destroy();
            }
        }
    }
};




#endif // PROJECTILEEMITTERCOMPONENT

