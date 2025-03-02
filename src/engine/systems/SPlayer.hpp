#pragma once


#include "engine/core/System.hpp"
#include "engine/core/Components.hpp"
#include "engine/core/EventHandler.hpp"
#include "engine/core/Events.hpp"


class SPlayer : public System
{
public:
    ~SPlayer();
    void Init(int UPS);
    void Update(float dt);

private:
    flecs::query<const CPlayerControlled, CRigidBody, CTransform> m_playerEntities;
    EventHandler m_eventHandler;

    void processEvents();

};