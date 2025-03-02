#pragma once

#include <string>
#include <unordered_map>
#include <raylib.h>
#include <engine/core/Events.hpp>

namespace Config
{
    inline const int screenWidth = 800;
    inline const int screenHeight = 800;
    inline const char * title = "Space Game";
    inline const int FPS = 120;
    inline const float damp = 0.06f;
    inline const std::string atlas = ASSETS_PATH"atlas.json";
}

enum class MouseState {
    MOUSE_BUTTON_PRESSED_LEFT     = 0,       //Button has been pressed once
    MOUSE_BUTTON_PRESSED_RIGHT    = 1,       
    MOUSE_BUTTON_PRESSED_MIDDLE   = 2,       
    MOUSE_BUTTON_PRESSED_SIDE     = 3,       
    MOUSE_BUTTON_PRESSED_EXTRA    = 4,       
    MOUSE_BUTTON_PRESSED_FORWARD  = 5,       
    MOUSE_BUTTON_PRESSED_BACK     = 6,       
    MOUSE_BUTTON_DOWN_LEFT        = 7,       //Button is being pressed
    MOUSE_BUTTON_DOWN_RIGHT       = 8,       
    MOUSE_BUTTON_DOWN_MIDDLE      = 9,       
    MOUSE_BUTTON_DOWN_SIDE        = 10,      
    MOUSE_BUTTON_DOWN_EXTRA       = 11,      
    MOUSE_BUTTON_DOWN_FORWARD     = 12,      
    MOUSE_BUTTON_DOWN_BACK        = 13,      
    MOUSE_BUTTON_RELEASED_LEFT    = 14,       // Button has been released once
    MOUSE_BUTTON_RELEASED_RIGHT   = 15,       
    MOUSE_BUTTON_RELEASED_MIDDLE  = 16,       
    MOUSE_BUTTON_RELEASED_SIDE    = 17,       
    MOUSE_BUTTON_RELEASED_EXTRA   = 18,       
    MOUSE_BUTTON_RELEASED_FORWARD = 19,       
    MOUSE_BUTTON_RELEASED_BACK    = 20,       
    MOUSE_WHEEL_MOVE              = 21,
    MOUSE_MOVE                    = 22
};

