#include "engine/systems/STransform.hpp"
#include "engine/core/Engine.hpp"
#include "raymath.h"
#include <iostream>

void STransform::Init(int updatesPerSecond) {
    m_targetUPS = 1/float(updatesPerSecond);
    m_lastUpdate = std::chrono::high_resolution_clock::now();
    m_entities = ECS.query<CTransform, CRigidBody>();
}

void STransform::Update(float dt) 
{
    if(!timeToUpdate()) return;

    m_entities.each([&dt](CTransform& t, CRigidBody& r){
        //Lots of speed reduction code needs to moved to SRidgidBody
        
        t.heading += r.currentAngularVelocity;
        if (r.currentAngularVelocity > r.angularDamp) r.currentAngularVelocity -= r.angularDamp;
        if (r.currentAngularVelocity < -(r.angularDamp)) r.currentAngularVelocity += r.angularDamp;
        if (t.heading > 360) t.heading -= 360;
        if (t.heading < 0) t.heading += 360;
        
        //t.position = Vector2Add(t.position, Vector2Scale(r.currentLinearVelocity, dt));
        t.position = Vector2Add(t.position, r.currentLinearVelocity);
        
        r.currentLinearVelocity = Vector2MoveTowards(r.currentLinearVelocity, Vector2 {0.0f, 0.0f}, r.linearDamp);
        //r.currentLinearVelocity = Vector2Scale(r.currentLinearVelocity, 0.99f);

        
        });
}
