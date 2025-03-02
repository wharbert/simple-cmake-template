#pragma once

#include <chrono>

class System
{
public:

protected:
    float m_targetUPS = 0.0f;
    std::chrono::high_resolution_clock::time_point m_lastUpdate;
    bool timeToUpdate();
};



