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
    for (auto& entity: entities) {
        entity->Render();
    }
}

Entity& EntityManager::AddEntity(std::string entityName) {
    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
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

