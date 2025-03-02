#pragma once

#include "engine/core/System.hpp"
#include "flecs.h"
#include "engine/core/Components.hpp"

class STransform  : public System
{
public:
  
    void Init(int updatesPerSecond);
    void Update(float dt);

private:
    flecs::query<CTransform, CRigidBody> m_entities;
};

