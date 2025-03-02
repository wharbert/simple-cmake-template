#include "GraphicsManager.hpp"
#include "core/Engine.hpp"
#include "raylib.h"
#include "flecs.h"

GraphicsManager::GraphicsManager()
{
}

GraphicsManager::~GraphicsManager()
{
}

void GraphicsManager::Init()
{

}

flecs::entity GraphicsManager::AddCamera(const char* camName, int viewWidth, int viewHeight) {
    //if camName not in use
    flecs::entity cam = ECS->entity()
        .set([viewWidth, viewHeight](CCamera& c, CRigidBody& r) {
        c.camera.offset = Vector2{ (float)viewWidth / 2.0f, (float)viewHeight / 2.0f };
        c.renderTexture = LoadRenderTexture(viewWidth, viewHeight);
        c.view = Rectangle{ 0.0f,0.0f,(float)viewWidth, (float)-viewHeight };
        c.camera.target = Vector2{ 400.0f, 400.0f };
        c.camera.rotation = 0.0f;
        c.camera.zoom = 1.0f;
        });

    return cam;
}

void GraphicsManager::SetCameraSize(const char* camName, int viewWidth, int viewHeight)
{
    auto e = ECS->lookup(camName);
    if (e) {
        auto cam = e.get_mut<CCamera>();
        cam->view = Rectangle{ 0.0f,0.0f,(float)viewWidth, (float)-viewHeight };
    }
}

void GraphicsManager::RemoveCamera(const char* camName) {
    //if camName valid
    //  delete entity
    
}

void GraphicsManager::SetSprite(flecs::entity const& entity, const char* sprite, const char* animation)
{
    
    if (ASSETMAN->IsValidSprite(sprite, animation)) {
        
    }

/*
    if (gAssetMan.objects.find(sprite) != gAssetMan.objects.end()) { //if sprite valid
    if ((gAssetMan.objects[sprite].animation.find(animation) !=
    gAssetMan.objects[sprite].animation.end())) { // if animations valid
    CSprite& cSprite = gCoordinator.GetComponent<CSprite>(entity);
    cSprite.name = sprite;
    cSprite.atlas = &gAssetMan.objects[sprite].atlas;
    cSprite.animation = animation;
    cSprite.sourceFrame = &gAssetMan.objects[sprite].animation[animation].frame;
    cSprite.width = cSprite.sourceFrame->at(0).width;
    cSprite.height = cSprite.sourceFrame->at(0).height;
    cSprite.origin = Vector2{cSprite.width / 2.0f, cSprite.height / 2.0f};
    cSprite.frameRate = gAssetMan.objects[sprite].animation[animation].frameRate;
    cSprite.frameCount = gAssetMan.objects[sprite].animation[animation].frameCount;
    cSprite.frameCounter = 0;

    cSprite.currentFrame = 0;
    }
    }
*/
}

void GraphicsManager::CreateWindow(int screenWidth, int screenHeight, const char* windowTitle)
{
    if (!IsWindowReady()) {
        InitWindow(screenWidth, screenHeight, windowTitle);
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    }
    
}

void GraphicsManager::DestroyWindow()
{
    CloseWindow();
}

void GraphicsManager::SetWindowSize(int screenWidth, int screenHeight)
{
    if ((screenWidth > 0) && (screenWidth <= GetMonitorWidth(GetCurrentMonitor()))) {
        if ((screenHeight > 0) && (screenHeight <= GetMonitorHeight(GetCurrentMonitor()))) {
            SetWindowSize(screenWidth, screenHeight );
        }
    }
}

void GraphicsManager::SetWindowWindowed()
{
    if (!IsWindowState(FLAG_WINDOW_RESIZABLE)) SetWindowState(FLAG_WINDOW_RESIZABLE);
}

void GraphicsManager::SetWindowFullscreen()
{
    if (!IsWindowState(FLAG_FULLSCREEN_MODE)) ToggleFullscreen();
}

void GraphicsManager::SetWindowBorderless()
{
    if (!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)) ToggleBorderlessWindowed();
}



