#include "./EntityManager.h"

void EntityManager::ClearData(){
    for (auto& entity: entities) {
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime){
    for (auto& entity: entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render(){
    for (auto& entity: entities) {
        entity->Render();
    }
}

bool EntityManager::HasNoEntities(){
    return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName){
    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const{
    return entities;
}

unsigned int EntityManager::GetEntityCount(){
    return entities.size();
}


