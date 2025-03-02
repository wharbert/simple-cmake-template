
#pragma once

#include "engine/core/System.hpp"
#include "flecs.h"
#include "engine/core/Components.hpp"


class SSprite : public System
{
public:
    void Init(int updatesPerSecond);
    void Update(float dt);
    
    void SetSprite(flecs::entity const& entity, const char* asset);

private:
    flecs::query<CSprite, const CVisible> m_entities;
};

