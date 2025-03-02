//Manage sprites and animations
#include "SSprite.hpp"
#include "engine/core/Engine.hpp"
#include "engine/core/Components.hpp"


void SSprite::Init(int updatesPerSecond)
{
    m_targetUPS = 1/float(updatesPerSecond);
    m_lastUpdate = std::chrono::high_resolution_clock::now();
    m_entities = ECS.query<CSprite, const CVisible>();
}

void SSprite::Update(float dt){
    if (!timeToUpdate()) return;

    m_entities.each([&dt](flecs::entity e, CSprite& s, const CVisible v) {
        if (e.has<CAnimated>() && s.sprite->frameCount > 1) {
            s.frameCounter++;
            if (s.frameCounter >= (60 / s.sprite->frameRate)) {
                s.frameCounter = 0;
                s.currentFrame++;
                if (s.currentFrame > (s.sprite->frameCount - 1)) {
                    s.currentFrame = 0;
                }
            }
        }
        });
}

void SSprite::SetSprite(flecs::entity const& entity, const char* asset)
{
    if (ASSETMAN.IsValidSprite(asset)) {
        if (entity.has<CSprite>()) {
            CSprite* s = entity.get_mut<CSprite>();
            s->asset = asset;
            s->sprite = ASSETMAN.GetSprite(asset);
            s->width = s->sprite->frame.at(0).width;
            s->height = s->sprite->frame.at(0).height;
            s->origin.x = s->width / 2.0f;
            s->origin.y = s->height / 2.0f;
        }
    }
}


