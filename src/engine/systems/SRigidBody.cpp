/*
* Manages physical interactions of entities. Applies forces, velocity, and rotation. 
* Will eventually integrate Box2D
*/

#include "SRigidBody.hpp"
#include "engine/core/Engine.hpp"
#include <raymath.h>
#include <cmath>





SRigidBody::~SRigidBody()
{
}

void SRigidBody::Init(int updatesPerSecond)
{
    m_targetUPS = 1/float(updatesPerSecond);
    m_lastUpdate = std::chrono::high_resolution_clock::now();
    m_entites = ECS.query<const CRigidBody, CTransform>();
}

void SRigidBody::Update(float dt)
{
    if (!timeToUpdate()) return;

    m_entites.each([&dt](const CRigidBody& r, CTransform& t) {
        //probably all Box2D derived stuff
    });
    
    /*
    For all entities with CRigidBody
    
    for (auto const& entity : mEntities) {
        CRigidBody& r = gCoordinator.GetComponent<CRigidBody>(entity);
        CTransform& t = gCoordinator.GetComponent<CTransform>(entity);

        //Add force calcs here when relevant 
        //Combine all forces to create Vector2 Velocity
                
        r.linearV.current  = Vector2MoveTowards(r.linearV.current, Vector2Zero(), r.linearV.damp);
        r.linearV.current = Vector2Add(r.linearV.current, Vector2Add(r.forces.thrust, r.forces.gravity));
        r.linearV.current = Vector2ClampValue(r.linearV.current, -(r.linearV.max), r.linearV.max);
        
    }
    */
}

