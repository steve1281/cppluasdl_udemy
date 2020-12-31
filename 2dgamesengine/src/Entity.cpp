#include "./Entity.h"
#include <string>

Entity::Entity(EntityManager& manager): manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name): manager(manager),name(name) {
    // note to self, he is short cutting this->manager = manager and this->name = name
    // not sure the actual "value" of this? 
    this->isActive = true;
}

void Entity::Update(float deltaTime) {
    // why auto& ? I mean, they HAVE TO BE Components, or at least things with Update in them?
    for (auto& component: components) {
        component->Update(deltaTime);
    }

}

void Entity::Render(){
    for (auto& component: components) {
        component->Render();
    }
}


void Entity::Destroy(){
    this->isActive=false;
}

bool Entity::IsActive() const {
    return this->isActive;
}


