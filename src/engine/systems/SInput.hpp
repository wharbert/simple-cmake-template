/*
* For entities with PlayerControlled
* Get keys and adust variables 
*/

#pragma once


#include "engine/core/System.hpp"
#include "flecs.h"
#include "engine/core/Components.hpp"
#include "engine/core/EventHandler.hpp"
#include "engine/core/Events.hpp"
#include <bitset>
#include <unordered_map>
#include <raylib.h>

class SInput : public System
{
public:
    void Init(int UPS);
    void Update(float dt);
    void UpdateBindings(); //Used for changing m_bindings
    void OnInputEvent(std::shared_ptr<EventData> data);

private:
    flecs::query<const CPlayerControlled> m_entities;
    EventHandler m_eventHandler;
    std::bitset<32> mouseState;
    KeyboardEvent m_keyEvent;
    MouseEvent m_mouseEvent;
    //std::shared_ptr<GamepadEvent> m_gamepadEvent; NYI
    std::unordered_map<KeyboardKey, EventId> m_bindings;

    void processEvents();
    void mapBindings();
    void dispatchKeyEvents();
    void dispatchMouseEvents();
    void dispatchGamepadEvents();
};

