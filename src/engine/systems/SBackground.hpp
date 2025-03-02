//Generates scrolling background images
#pragma once

#include "engine/core/System.hpp"
#include "engine/core/Components.hpp"
#include "engine/core/EventHandler.hpp"

class SBackground : public System
{
public:

    void Init(int updatesPerSecond);
    void Update(float dt);

private:
    
    EventHandler m_eventHandler;
};

