#include "engine/core/Engine.hpp"
#include "engine/managers/EventManager.hpp"
#include "engine/core/Events.hpp"
#include "raylib.h"
#include "raymath.h"
#include "SRender.hpp"
#include <engine/core/Components.hpp>
#include <memory>

void SRender::Init(int updatesPerSecond)
{
    m_targetUPS = 1/float(updatesPerSecond);
    m_lastUpdate = std::chrono::high_resolution_clock::now();
    m_renderable = ECS.query<const CTransform, const CSprite, const CVisible>();
    m_cameras = ECS.query<const CCamera>();

    
    //Temporary background solution
    CreateWindow(Config::screenWidth, Config::screenHeight, Config::title);
    background = LoadTexture(ASSETS_PATH"background.png"); //need to remove so the above can be removed
}


void SRender::Update(float dt)
{   
    
    
    if (!timeToUpdate()) return;

    //check if window changed and fire event, will just manually update for now
    if (IsWindowResized()) {
        WindowEvent event;
        event.width = GetScreenWidth();
        event.height = GetScreenHeight();
        event.id = Events::Window::RESIZED;
        EVENTMAN.Notify(std::make_shared<WindowEvent>(event));
    }

    m_cameras.each([&dt, this](const CCamera& cam) {
        BeginTextureMode(cam.renderTexture);
        ClearBackground(WHITE);
        BeginMode2D(cam.camera);
        DrawTexture(background, 0, 0, WHITE);
        m_renderable.each([&dt](flecs::entity e, const CTransform& t, const CSprite& s, const CVisible) {
            if (e.is_alive()) {
                Rectangle dest = {t.position.x, t.position.y, s.width, s.height};
                DrawTexturePro(s.sprite->atlas, s.sprite->frame.at(s.currentFrame), dest,  s.origin, t.heading, WHITE);
            }

        });
        EndMode2D();
        EndTextureMode();
        BeginDrawing();
        DrawTextureRec(cam.renderTexture.texture, cam.view, Vector2{0.0f, 0.0f}, WHITE);
        DrawText(TextFormat("X : %.1f , Y : %.1f", cam.camera.target.x, cam.camera.target.y ), 0, 700, 20, GRAY);
        EndDrawing();
    });
}

void SRender::OnWindowEvent(std::shared_ptr<EventData> event)
{
    
}

void SRender::CreateWindow(int screenWidth, int screenHeight, const char* windowTitle)
{
    if (!IsWindowReady()) {
        InitWindow(screenWidth, screenHeight, windowTitle);
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }
}

void SRender::SetWindowSize(int screenWidth, int screenHeight)
{
    if ((screenWidth > 0) && (screenWidth <= GetMonitorWidth(GetCurrentMonitor()))) {
        if ((screenHeight > 0) && (screenHeight <= GetMonitorHeight(GetCurrentMonitor()))) {
            SetWindowSize(screenWidth, screenHeight );
        }
    }
}

void SRender::SetWindowWindowed()
{
    if (!IsWindowState(FLAG_WINDOW_RESIZABLE)) SetWindowState(FLAG_WINDOW_RESIZABLE);
}

void SRender::SetWindowFullscreen()
{
    if (!IsWindowState(FLAG_FULLSCREEN_MODE)) ToggleFullscreen();
}

void SRender::SetWindowBorderless()
{
    if (!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) ToggleBorderlessWindowed();
}

void SRender::DestroyWindow()
{
    CloseWindow();
}

void SRender::processEvents()
{
    while (auto event = m_eventHandler.GetEvent()) {
        switch (event.value()->id)
        {
        case Events::Keyboard::KEY_DOWN:
            OnWindowEvent(event.value());
            break;
        default:
            break;
        }
    }
}


