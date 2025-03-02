#pragma once


#include "raylib.h"
#include "raymath.h"
#include "flecs.h"
#include <vector>
#include <string>
#include <cstdint>
#include "engine/core/Types.hpp"
#include <chrono>

//GENERAL PURPOSE STRUCTS THAT SHOULD BE MOVED TO TYPES.HPP
//I guess my key mapping and extra enums could be included here




// ###### COMPONENTS ######

struct CActor { };

struct CStage { };

using CPosition = Vector2; //maybe break transform into 3 components?


struct CLifeTime { 
    long long timeToLive = 0; //Lifetime in ms
    std::chrono::high_resolution_clock::time_point expirationTime; 
};

struct CProjectile { //Mostly read only
    float velocity = 0.0f;
    float rateOfFire = 0.0f; //delay in ms between shots
    int damage = 0;
    int damageType = 0; //Some enum the resolves into kinetic, heat, blast, etc...
    int damageHitBox = 0; //How to make this for point damage, piercing damange, area damage
    //Some stuff indicating damage multipliers?
};

struct CMissile { //Mostly read only
    float maxVelocity = 0.0f;
    float acceleration = 0.0;
    float turnRate = 0.0;
    int damage = 0;
    int damageType = 0; //Some enum the resolves into kinetic, heat, blast, etc...
    int damageHitBox = 0; //How to make this for point damage, piercing damange, area damage
    //Some stuff indicating damage multipliers?
};


struct CDamage {

};

struct CTransform {
    Vector2 position = {0.0f, 0.0f};
    float heading = 0.0f; //Direction facing
};

struct CForce {
    Vector2 pointOfApplication = {0.0f, 0.0f}; //Point on object where force is applied. 0,0 represents center mass
    Vector2 force = {0.0f, 0.0f}; //Vector of force applied (direction and magnitude) over time described below
    float timeRemaining = 0.0f; // -1 it non-impulse force (engines) >0 means force is somehow lerped over the period
};

struct CLinearVelocity {
    Vector2 currentLinearVelocity = {0.0f, 0.0f};
    float maxLinearVelocity = 500.0f;
    float linearDamp = 0.01f;
};

struct CAngularVelocity {
    float currentAngularVelocity = 0.0f;
    float maxAngularVelocity = 5.0f;
    float angularDamp = 0.2f;
};

struct CRigidBody
{
    //How to manage applied forces?
    //How to implement complex force applications? e.g. a lateral force at the nose makes object spin, may be Box2D question
    //Break into CLinearVelocity and CAngularVelocity?
    Vector2 currentLinearVelocity = {0.0f, 0.0f};
    float maxLinearVelocity = 500.0f;
    float linearDamp = 0.01f;
    float currentAngularVelocity = 0.0f;
    float maxAngularVelocity = 5.0f;
    float angularDamp = 0.2f;
};

struct CBackground { };

enum CameraTarget {TARGET, FRAME, COORD}; //Possibly break into two comps?

struct CCamera {
    Camera2D camera;
    RenderTexture2D renderTexture;
    Rectangle view = { 0.0f, 0.0f, 0.0f, 0.0f }; 
    float maxZoom = 2.0f; //Move to system or config?
    float minZoom = 0.5f; //Move to system or config?
    float zoom = 1.0f;
    CameraTarget focusType = COORD;
    Vector2 targetPosition = {0.0f, 0.0f};
};

struct CSpriteNew
{
    uint32_t asset = 0; //hash of string or something like that
    uint16_t currentFrame = 0;
    uint16_t frameCounter = 0;
    Sprite* sprite = nullptr;
};

struct CSprite
{
    std::string asset = ""; //convert to uint32_t hash
    float width = 0;
    float height = 0;
    uint8_t currentFrame = 0;
    uint8_t frameCounter = 0;
    Vector2 origin = {0.0f, 0.0f}; //Move to Sprite struct
    Sprite* sprite = nullptr;
};


// ###### TAGS #######

struct CPlayerControlled {};

struct CVisible {};

struct CAnimated {};

struct CTargets {};

struct CCameraTarget {};