#include "System.hpp"

bool System::timeToUpdate()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<float, std::chrono::seconds::period>(now - m_lastUpdate);
    if (duration.count() < m_targetUPS) return false;
    m_lastUpdate = std::chrono::high_resolution_clock::now();
    return true;
}
