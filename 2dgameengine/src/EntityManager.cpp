#include <iostream>

#include "./EntityManager.h"

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
    // this will dump what he wants, but a better way would to create and maintain a map of components/identifiers.
    // I think I will leave this as is for now, until I see what he actually has in mind.
    for (auto& entity: entities) {
        std::cout<< "Entity Name: " << entity->name << std::endl;
        for (auto& component: entity->components) {
            std::cout << "\t" << typeid(*component).name() << std::endl;
        }
    }
}

