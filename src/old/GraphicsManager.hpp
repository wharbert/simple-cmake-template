#pragma once



#include <string>
#include "raylib.h"
#include "flecs.h"
#include "core/Components.hpp"


class GraphicsManager
{
    public:
        
        GraphicsManager();
        ~GraphicsManager();
        void Init();
        void CreateWindow(int screenWidth, int screenHeight, const char* windowTitle);
        void SetWindowSize(int screenWidth, int screenHeight);
        void SetWindowWindowed();
        void SetWindowFullscreen();
        void SetWindowBorderless();
        void DestroyWindow();
        flecs::entity AddCamera(const char* camName, int viewWidth, int viewHeight);
        void SetCameraSize(const char* camName, int viewWidth, int viewHeight);
        void RemoveCamera(const char* camName);
        void SetSprite(flecs::entity const& entity, const char* sprite, const char* animation);

    private:


};