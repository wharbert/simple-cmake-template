#pragma once

#include "engine/core/System.hpp"
#include "flecs.h"
#include "engine/core/Components.hpp"

class SRigidBody : public System
{
public:

    ~SRigidBody();
    void Init(int updatesPerSecond);
    void Update(float dt);

private:
    flecs::query<const CRigidBody, CTransform> m_entites;
    
};

