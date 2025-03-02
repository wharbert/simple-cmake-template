//All user types used in engine features - How to eventually break between engine and game?

#pragma once

#include <vector>
#include <string>
#include "raylib.h"

/*
namespace MyEngine
{
}


namespace Camera 
{
    enum class TargetType{TARGET, FRAME, COORD};
}


namespace Events2
{
    enum class Window : std::uint32_t  {
        CLOSE                  = "Events::Window::CLOSE"_hash,
        RESIZED                = "Events::Window::RESIZED"_hash,
        MINIMIZED              = "Events::Window::MINIMIZED"_hash,
        MAXIMIZED              = "Events::Window::MAXIMIZED"_hash,
        MOVE                   = "Events::Window::MOVE"_hash
    };


}
*/

// Move Events Here
// Event IDs

// Event Structs


struct SpriteNew 
{
    uint32_t asset = 0; //hash of string or something like that
    Texture2D atlas;
    std::vector<Rectangle> frame;
    int frameCount = 0;
    int frameRate = 0;
    Vector2 origin = {0.0f, 0.0f};
};

struct Sprite {
    std::string name = "";
    std::string sequence = "";
    Texture2D atlas;
    std::vector<Rectangle> frame;
    int frameCount = 0;
    int frameRate = 0;
};


