//System for managing game objects. Mostly spawn and despawn objects
#pragma once

#include "engine/core/System.hpp"
#include "engine/core/Components.hpp"
#include "engine/core/EventHandler.hpp"
#include <unordered_map>
#include <string>
#include "flecs.h"

class SObjects : public System
{
public:
    SObjects();
    void Init(int updatesPerSecond);
    void Update(float deltaTime);

    flecs::entity SpawnObject(std::string object, std::string name, float heading, Vector2 position); //generates new object based on prefab 
    void LoadPrefabs();


private:
    void despawnObject(flecs::entity entity);
    //flecs::entity spawnObject(std::string prefab, float heading, Vector2 position); //generates new object based on prefab 
    void createPrefabs();
    void processEvents();

    flecs::query<CLifeTime> m_entities;
    EventHandler m_eventHandler;
    std::unordered_map<std::string, flecs::entity> m_prefabs;
};
