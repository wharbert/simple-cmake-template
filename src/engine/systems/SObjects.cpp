#include "SObjects.hpp"
#include "engine/core/Engine.hpp"
#include "flecs.h"
#include <iostream>

SObjects::SObjects()
{
}

void SObjects::Init(int updatesPerSecond)
{
    m_targetUPS = 1/float(updatesPerSecond);
    m_lastUpdate = std::chrono::high_resolution_clock::now();
    m_entities = ECS.query<CLifeTime>();

    m_eventHandler.Subscribe(Events::Spawner::SPAWN);
    m_eventHandler.Subscribe(Events::Spawner::DESPAWN);

    createPrefabs();
}

void SObjects::Update(float deltaTime)
{
    if (!timeToUpdate()) return;
    processEvents();
    auto now = std::chrono::high_resolution_clock::now();
    
    ECS.defer_begin();
    m_entities.each([&](flecs::entity e, CLifeTime& l) {
        if (l.expirationTime < now) {
            std::cout << e.name() << "\n";
            e.destruct();
        }
    });
    ECS.defer_end();
}

flecs::entity SObjects::SpawnObject(std::string object, std::string name, float heading, Vector2 position)
{
    //TODO: Add catches for invalid object and wrap into std::optional
    if (m_prefabs.find(object) != m_prefabs.end()) {
        //TODO: Only do sprite init if CSprite present
        flecs::entity e = ECS.entity(name.c_str()).is_a(m_prefabs[object])
            .set([&](CTransform& t,CSprite& s, CRigidBody& r, CProjectile& p) {
            t.position = position;
            t.heading = heading;
            s.sprite = ASSETMAN.GetSprite(s.asset);
            s.width = s.sprite->frame.at(0).width;
            s.height = s.sprite->frame.at(0).height;
            s.origin.x = s.width / 2.0f;
            s.origin.y = s.height / 2.0f;
            r.currentLinearVelocity.x += sin(heading * DEG2RAD) * p.velocity;
            r.currentLinearVelocity.y += -(cos(heading * DEG2RAD)) * p.velocity;
            });
        if (e.has<CLifeTime>()) {
            auto now = std::chrono::high_resolution_clock::now();
            auto l = e.get_mut<CLifeTime>();
            l->expirationTime = now + std::chrono::milliseconds(l->timeToLive);
        }
        return e;
    }
}

void SObjects::LoadPrefabs()
{
}

void SObjects::despawnObject(flecs::entity entity)
{
    entity.destruct();
}

void SObjects::createPrefabs() //TODO: rebuild into loader for flecs script
{
    //emulate pulling this from flecs script
    
    m_prefabs["projectile1"] = ECS.prefab("projectile1")
         .set_override([](CProjectile& p,CSprite& s, CLifeTime& l) {
         p.velocity = 10.0f;
         p.damage = 100;
         s.asset = "projectile-cannon::firing";
         l.timeToLive = 1000;})
         .add<CVisible>()
         .add<CTransform>()
         .add<CRigidBody>();

    m_prefabs["projectile2"] = ECS.prefab("projectile2")
        .set([](CProjectile& p,CSprite& s, CLifeTime& l) {
        p.velocity = 15.0f;
        p.damage = 100;
        s.asset = "projectile-rocket::firing";
        l.timeToLive = 10000;})
        .add<CVisible>()
        .add<CRigidBody>();

    m_prefabs["planet-green"] = ECS.prefab("planet-green")
        .set([](CSprite& s) {
        s.asset = "planet-green::spinning";})
        .add<CVisible>()
        .add<CAnimated>();

    m_prefabs["player-ship"] = ECS.prefab("player-ship")
        .set([](CSprite& s) {
        s.asset = "ship-100::base";})
        .add<CVisible>()
        .add<CTransform>()
        .add<CRigidBody>()
        .add<CPlayerControlled>();
}

void SObjects::processEvents()
{
    while (auto event = m_eventHandler.GetEvent()) {
        switch (event.value()->id)
        {
        case Events::Spawner::SPAWN:
        {
            auto e = std::static_pointer_cast<SpawnEvent>(event.value());
            SpawnObject(e->object, e->name, e->heading, e->position);
            break;
        }
        case Events::Spawner::DESPAWN:
        {
            auto e = std::static_pointer_cast<SpawnEvent>(event.value());
            despawnObject(ECS.lookup(e->name.c_str()));
            break;
        }
        default:
            break;
        }
    }
}

