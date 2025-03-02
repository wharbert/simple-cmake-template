//System for managing AI agents
#pragma once

#include "engine/core/System.hpp"
#include "engine/core/Components.hpp"
#include "engine/core/EventHandler.hpp"

class SAgent : public System
{
public:
    SAgent();
    void Init(int updatesPerSecond);
    void Update(float deltaTime);

private:
    
    EventHandler m_eventHandler;
};
