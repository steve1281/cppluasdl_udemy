#include <iostream>

#include "./EntityManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/NoSuchComponent.h"

void EntityManager::ClearData() {
    for (auto& entity: entities) {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() {
    return entities.size() == 0;
}

void EntityManager::Update(float deltaTime) {
    for (auto& entity: entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (int layerNumber =0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
            entity->Render();
        }
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> selectedEntities;
    for (auto& entity: entities) {
        if (entity->layer == layer) {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() {
    return entities.size();
}

// as per execerise add ListOut* methods

void EntityManager::ListOutEntities() {
    for (auto& entity: entities) {
        std::cout<< "Entity Name: " << entity->name << std::endl;
        entity->ListOutComponents();
    }
}

void EntityManager::AnyTransforms() {
    for (auto& entity: entities) {
        std::cout << (entity->HasComponent<TransformComponent>() ? "has TransformComponent":"no TransformComponent")  << std::endl;
        std::cout << (entity->HasComponent<SpriteComponent>() ? "has SpriteComponent":"no SpriteComponent")  << std::endl;
        std::cout << (entity->HasComponent<NoSuchComponent>() ? "has NoSuchComponent":"no NoSuchComponent")  << std::endl;
    }
}

