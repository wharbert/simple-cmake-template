#include "engine/systems/SCamera.hpp"
#include "engine/core/Engine.hpp"
#include "engine/core/Components.hpp"
#include <iostream>

SCamera::SCamera()
{
}

SCamera::~SCamera()
{
}

void SCamera::Init(int updatesPerSecond)
{
    m_targetUPS = 1/float(updatesPerSecond);
    m_lastUpdate = std::chrono::high_resolution_clock::now();
    m_cameras = ECS.query<CCamera>();

    m_eventHandler.Subscribe(Events::Window::RESIZED);
    m_eventHandler.Subscribe(Events::Mouse::WHEEL);
    
    ECS.component<CCameraTarget>().add(flecs::Exclusive);
}

void SCamera::Update(float deltaTime)
{
    processEvents();
    
    m_cameras.each([&deltaTime, this](flecs::entity e, CCamera& cam) {
        switch (cam.focusType)
        {
            case COORD:
            //cam.camera.target = Vector2MoveTowards(cam.camera.target, cam.targetPosition, 1.0f);
            break;
            case TARGET:
            cam.targetPosition = e.target<CCameraTarget>().get<CTransform>()->position;
            break;
            case FRAME:
            //?!? getFrame
            break;
        }
        cam.camera.target = Vector2MoveTowards(cam.camera.target, cam.targetPosition, 1.0f);
    });
}

flecs::entity SCamera::AddCamera(const char* camName, int viewWidth, int viewHeight)
{
    if (!ECS.lookup(camName)) {
    flecs::entity cam = ECS.entity(camName)
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
    //std::optional - return error

}

void SCamera::SetCameraSize(flecs::entity& camera, int viewWidth, int viewHeight)
{
    if (camera.has<CCamera>()) {
        CCamera * c = camera.get_mut<CCamera>();
        c->view = Rectangle{ 0.0f,0.0f,(float)viewWidth, (float)-viewHeight };
        UnloadRenderTexture(c->renderTexture);
        c->renderTexture = LoadRenderTexture(viewWidth, viewHeight);
        LOG_INFO("CORE", "Resize Camera : {} x {}", c->view.width, c->view.height);
    }
}

void SCamera::zoomCamera(const char* cameraName, float zoom)
{
    auto camera = ECS.lookup(cameraName);
    if (camera.has<CCamera>()) {
        CCamera* c = camera.get_mut<CCamera>();
        c->camera.zoom = Clamp(c->camera.zoom + (zoom * 0.05f), c->minZoom, c->maxZoom);
        LOG_INFO("CORE", "Set Camera Zoom : {}", c->camera.zoom);
    } 
    else {
        //TODO: return invalid entity
    }
}

void SCamera::RemoveCamera(flecs::entity& camera)
{
    if (camera.has<CCamera>()) {
        //TODO: decommision cam texture and delete entity
    } 
    else {
        //TODO: return invalid entity
    }
    
}

void SCamera::TargetCoord(flecs::entity& camera, Vector2 coords)
{
    if (camera.has<CCamera>()) {
        CCamera* c = camera.get_mut<CCamera>();
        c->focusType = COORD;
        c->targetPosition = coords;
    }
    else {
        //TODO: return invalid entity
    }
}

void SCamera::TargetEntity(flecs::entity& camera, const flecs::entity& entity)
{
    if (camera.has<CCamera>()) {
        camera.get_mut<CCamera>()->focusType = TARGET;
        camera.add<CCameraTarget>(entity);
    }
    else {
        //TODO: return invalid entity
    }
}

void SCamera::FrameEntities(flecs::entity& camera, flecs::entity firstEntity, flecs::entity secondEntity)
{
}

flecs::entity SCamera::GetCameraByName(const char* cameraName)
{
    return ECS.lookup(cameraName);
}

void SCamera::processEvents()
{
    while (auto event = m_eventHandler.GetEvent()) {
        switch (event.value()->id)
        {
        case Events::Window::RESIZED:
        {
            auto e = std::static_pointer_cast<WindowEvent>(event.value());
            auto camera = ECS.lookup("main"); 
            SetCameraSize(camera, e->width, e->height);
            break;
        }
        case Events::Mouse::WHEEL:
        {
            auto e = std::static_pointer_cast<MouseEvent>(event.value());
            zoomCamera("main", e->wheel);
            break;
        }
        default:
            break;
        }
    }
}


