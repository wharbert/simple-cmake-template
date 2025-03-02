#include "SPlayer.hpp"
#include "engine/core/Events.hpp"
#include "engine/core/Engine.hpp"
#include <engine/core/Components.hpp>

SPlayer::~SPlayer()
{

}

void SPlayer::Init(int UPS)
{
    m_targetUPS = 1/float(UPS);
    m_lastUpdate = std::chrono::high_resolution_clock::now();

    m_playerEntities = ECS.query<const CPlayerControlled, CRigidBody, CTransform>();

    m_eventHandler.Subscribe(Events::Binding::PLAYER_DOWN);
    m_eventHandler.Subscribe(Events::Binding::PLAYER_UP);
    m_eventHandler.Subscribe(Events::Binding::PLAYER_LEFT);
    m_eventHandler.Subscribe(Events::Binding::PLAYER_RIGHT);
    m_eventHandler.Subscribe(Events::Binding::PLAYER_RESET);
    m_eventHandler.Subscribe(Events::Binding::PLAYER_SHOOT);
}

void SPlayer::Update(float dt)
{
    if (!timeToUpdate()) return;

    processEvents();
}

void SPlayer::processEvents()
{
    //eventually include component that represents players ship stats or possibly 
    while (auto event = m_eventHandler.GetEvent()) {
        m_playerEntities.each([this, event](const CPlayerControlled& p, CRigidBody& r, CTransform& t) {
            switch (event.value()->id)
            {
            case Events::Binding::PLAYER_DOWN:
                r.currentLinearVelocity.x += -(sin(t.heading * DEG2RAD)) * 0.3f;
                r.currentLinearVelocity.y += (cos(t.heading * DEG2RAD)) * 0.3f;
                break;
            case Events::Binding::PLAYER_UP:
                r.currentLinearVelocity.x += sin(t.heading * DEG2RAD) * 0.3f;
                r.currentLinearVelocity.y += -(cos(t.heading * DEG2RAD)) * 0.3f;
                break;
            case Events::Binding::PLAYER_LEFT:
                r.currentAngularVelocity -= 6;
                if (r.currentAngularVelocity < -(r.maxAngularVelocity)) r.currentAngularVelocity = -(r.maxAngularVelocity);
                break;
            case Events::Binding::PLAYER_RIGHT:
                r.currentAngularVelocity += 6;
                if (r.currentAngularVelocity > r.maxAngularVelocity) r.currentAngularVelocity = r.maxAngularVelocity;
                break;
            case Events::Binding::PLAYER_RESET:
                r.currentLinearVelocity = Vector2{0.0f,0.0f};
                r.currentAngularVelocity = 0.0f;
                t.position = Vector2{400.0f, 400.0f};
                t.heading = 0.0f;
                break;
            case Events::Binding::PLAYER_SHOOT:
            {
                SpawnEvent e;
                e.heading = t.heading;
                e.id = Events::Spawner::SPAWN;
                e.name = "";
                e.object = "projectile2";
                e.position = t.position;
                EVENTMAN.Notify(std::make_shared<SpawnEvent>(e));
                break;
            }
            default:
                break;
            }
        });
    }
    
    
    
    
    
}
