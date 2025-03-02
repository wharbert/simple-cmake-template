#pragma once

#include "engine/core/System.hpp"
#include "engine/core/Components.hpp"
#include "engine/core/EventHandler.hpp"


class SCamera : public System
{
public:
    SCamera();
    ~SCamera();

    void Init(int updatesPerSecond);
    void Update(float deltaTime);

    flecs::entity AddCamera(const char* cameraName, int viewWidth, int viewHeight);
    void SetCameraSize(flecs::entity& camera, int viewWidth, int viewHeight);
    void RemoveCamera(flecs::entity& camera);
    void TargetCoord(flecs::entity& camera, Vector2 coords);
    void TargetEntity(flecs::entity& camera, const flecs::entity& entity);
    void FrameEntities(flecs::entity& camera, flecs::entity firstEntity, flecs::entity secondEntity);
    flecs::entity GetCameraByName(const char* cameraName);

private:
    void processEvents();
    void zoomCamera(const char* camName, float zoom);
    bool isValidCamera(flecs::entity camera);

    flecs::query<CCamera> m_cameras;
    EventHandler m_eventHandler;
};