#include "SInput.hpp"
#include "engine/core/Engine.hpp"
#include "engine/managers/EventManager.hpp"
#include "raymath.h"
#include <memory>
#include <raylib.h>
#include <unordered_map>
#include <engine/core/Events.hpp>
#include "engine/core/Engine.hpp"


void SInput::Init(int UPS)
{
    m_targetUPS = 1/float(UPS);
    m_lastUpdate = std::chrono::high_resolution_clock::now();

    m_bindings = {
        {KEY_F,       Events::Binding::TOGGLE_FULLSCREEN},
        {KEY_W,       Events::Binding::PLAYER_UP},
        {KEY_S,       Events::Binding::PLAYER_DOWN},
        {KEY_A,       Events::Binding::PLAYER_LEFT},
        {KEY_D,       Events::Binding::PLAYER_RIGHT},
        {KEY_SPACE,   Events::Binding::PLAYER_SHOOT},
        {KEY_R,       Events::Binding::PLAYER_RESET},
        {KEY_ONE,     Events::Binding::ACTIONBAR_1},
        {KEY_TWO,     Events::Binding::ACTIONBAR_2},
    };

}

void SInput::Update(float dt)
{
    if (!timeToUpdate()) return;
    
    dispatchKeyEvents();
    dispatchMouseEvents();   
}

void SInput::UpdateBindings()
{
}

void SInput::OnInputEvent(std::shared_ptr<EventData> data)
{
}

void SInput::processEvents()
{
}

void SInput::dispatchKeyEvents()
{
    for (const auto& p : m_bindings) {
        if (IsKeyDown(p.first)) {
            m_keyEvent.id = m_bindings[p.first];
            m_keyEvent.key_code = p.first;
            m_keyEvent.key_repeat = 0;
            EVENTMAN.Notify(std::make_shared<KeyboardEvent>(m_keyEvent));
        }
    }

    /*
    int key = GetKeyPressed();
    while (key) {
    //if (key) {
        if (m_bindings.contains(KeyboardKey(key))) {
            m_keyEvent.id = m_bindings[KeyboardKey(key)];
            m_keyEvent.key_code = key;
            m_keyEvent.key_repeat = 0;
        }
        else {
            m_keyEvent.id = Events::Keyboard::KEY_PRESSED;
            m_keyEvent.key_code = key;
            m_keyEvent.key_repeat = 0;
        }
        EventManager::getInstance().Notify(std::make_shared<KeyboardEvent>(m_keyEvent));
        key = GetKeyPressed();
    }
    */
}

void SInput::dispatchMouseEvents()
{
      
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseState.set(MOUSE_BUTTON_LEFT);
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) mouseState.set(MOUSE_BUTTON_RIGHT);
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) mouseState.set(MOUSE_BUTTON_MIDDLE);
    if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) mouseState.set(MOUSE_BUTTON_SIDE);
    if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA)) mouseState.set(MOUSE_BUTTON_EXTRA);
    if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD)) mouseState.set(MOUSE_BUTTON_FORWARD);
    if (IsMouseButtonPressed(MOUSE_BUTTON_BACK)) mouseState.set(MOUSE_BUTTON_BACK);
    if (GetMouseWheelMove() != 0.0f) mouseState.set(7);
    if (GetMouseDelta().x > 1.0f || GetMouseDelta().y > 1.0f ) mouseState.set(8);

    if (mouseState.any()) {
        m_mouseEvent.wheel = GetMouseWheelMove();
        m_mouseEvent.pos = GetMousePosition();
        m_mouseEvent.delta = GetMouseDelta();
        m_mouseEvent.mouseState = mouseState;
        
        if (mouseState[MOUSE_BUTTON_LEFT]) {
            m_mouseEvent.id = Events::Mouse::LEFT_CLICK;
            EVENTMAN.Notify(std::make_shared<MouseEvent>(m_mouseEvent));
        }
        if (mouseState[MOUSE_BUTTON_RIGHT]) {
            m_mouseEvent.id = Events::Mouse::RIGHT_CLICK;
            EVENTMAN.Notify(std::make_shared<MouseEvent>(m_mouseEvent));
        }
        if (mouseState[MOUSE_BUTTON_MIDDLE]) {
            m_mouseEvent.id = Events::Mouse::MIDDLE_CLICK;
            EVENTMAN.Notify(std::make_shared<MouseEvent>(m_mouseEvent));
        }
        if (mouseState[7]) {
            m_mouseEvent.id = Events::Mouse::WHEEL;
            EVENTMAN.Notify(std::make_shared<MouseEvent>(m_mouseEvent));
        }
        if (mouseState[8]) {
            m_mouseEvent.id = Events::Mouse::MOVE;
            EVENTMAN.Notify(std::make_shared<MouseEvent>(m_mouseEvent));
        }

    };

    mouseState.reset();

}

void SInput::dispatchGamepadEvents()
{

}
