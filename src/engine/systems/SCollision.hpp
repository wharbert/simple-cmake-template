#pragma once



#include "engine/core/System.hpp"
#include "engine/core/Components.hpp"


class SCollision : public System
{
public:
    SCollision();
    ~SCollision();
    void Init(int updatesPerSecond);
    void Update(float deltaTime);

private:
    flecs::query<const CCamera> m_entities;
};