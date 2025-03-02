#pragma once

//System uses Raylib to render objects to screen

#include "engine/core/System.hpp"
#include "engine/core/Components.hpp"
#include "raylib.h"
#include "flecs.h"
#include "engine/core/EventHandler.hpp"
#include "engine/core/Events.hpp"
#include <memory>


class SRender : public System
{
public:
    void Init(int UPS);
    void Update(float dt);
    void OnWindowEvent(std::shared_ptr<EventData> data);

    void CreateWindow(int screenWidth, int screenHeight, const char* windowTitle);
    void SetWindowSize(int screenWidth, int screenHeight);
    void SetWindowWindowed();
    void SetWindowFullscreen();
    void SetWindowBorderless();
    void DestroyWindow();

private:
    void processEvents(); 
    flecs::query<const CTransform, const CSprite, const CVisible> m_renderable;
    flecs::query<const CCamera> m_cameras;
    EventHandler m_eventHandler;

    //Temporary background solution
    Texture2D background;


};
