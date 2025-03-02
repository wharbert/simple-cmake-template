#pragma once

#include "raylib.h"
#include <cstdint>
#include <unordered_map>
#include <bitset>
#include "flecs.h"


constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count) //Hash function used in _hash
{
    return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator "" _hash(char const* s, std::size_t count) //Define _hash operator used to turn event strings into uint32
{
    return fnv1a_32(s, count);
}

using EventId = std::uint32_t;
//using ParamId = std::uint32_t;

namespace Events::Window {
    const EventId CLOSE                  = "Events::Window::CLOSE"_hash;
    const EventId RESIZED                = "Events::Window::RESIZED"_hash;
    const EventId MINIMIZED              = "Events::Window::MINIMIZED"_hash;
    const EventId MAXIMIZED              = "Events::Window::MAXIMIZED"_hash;
    const EventId MOVE                   = "Events::Window::MOVE"_hash;
}

namespace Events::Keyboard {
    const EventId KEY_DOWN               = "Events::Keyboard::KEY_DOWN"_hash;
    const EventId KEY_UP                 = "Events::Keyboard::KEY_UP"_hash;
    const EventId KEY_PRESSED            = "Events::Keyboard::KEY_PRESSED"_hash;
}

namespace Events::Mouse {
    const EventId ANY                    = "Events::Mouse::ANY"_hash;
    const EventId MOVE                   = "Events::Mouse::MOVE"_hash;
    const EventId CLICK                  = "Events::Mouse::CLICK"_hash;
    const EventId LEFT_CLICK             = "Events::Mouse::LEFT_CLICK"_hash;
    const EventId RIGHT_CLICK            = "Events::Mouse::RIGHT_CLICK"_hash;
    const EventId MIDDLE_CLICK           = "Events::Mouse::MIDDLE_CLICK"_hash;
    const EventId DOUBLE_CLICK           = "Events::Mouse::DOUBLE_CLICK"_hash;
    const EventId WHEEL                  = "Events::Mouse::WHEEL"_hash;
    const EventId DRAG                   = "Events::Mouse::DRAG"_hash;
}

namespace Events::Binding {
    const EventId TOGGLE_FULLSCREEN      = "Events::Binding::TOGGLE_FULLSCREEN"_hash;
    const EventId PLAYER_UP              = "Events::Binding::PLAYER_UP"_hash;
    const EventId PLAYER_DOWN            = "Events::Binding::PLAYER_DOWN"_hash;
    const EventId PLAYER_LEFT            = "Events::Binding::PLAYER_LEFT"_hash;
    const EventId PLAYER_RIGHT           = "Events::Binding::PLAYER_RIGHT"_hash;
    const EventId PLAYER_SHOOT           = "Events::Binding::PLAYER_SHOOT"_hash;
    const EventId PLAYER_RESET           = "Events::Binding::PLAYER_RESET"_hash;
    const EventId ACTIONBAR_1            = "Events::Binding::ACTIONBAR_1"_hash;
    const EventId ACTIONBAR_2            = "Events::Binding::ACTIONBAR_2"_hash;
}

namespace Events::Spawner {
    const EventId SPAWN                  = "Events::Spawner::SPAWN"_hash;
    const EventId DESPAWN                = "Events::Spawner::DESPAWN"_hash;
    const EventId OBJECT_SPAWNED         = "Events::Spawner::OBJECT_SPAWNED"_hash;
    const EventId OBJECT_DESPAWNED       = "Events::Spawner::OBJECT_DESPAWNED"_hash;
}

namespace Events::Camera {
    const EventId TARGET_ENTITY          = "Events::Camera::TARGET_ENTITY"_hash;
    const EventId TARGET_COORD           = "Events::Camera::TARGET_COORD"_hash;
}

namespace Events{
#ifdef _DEBUG
    static std::unordered_map<EventId, const char *> EventMap = {
        {Events::Window::CLOSE,              "Events::Window::CLOSE"},
        {Events::Window::RESIZED,            "Events::Window::RESIZED"},
        {Events::Window::MINIMIZED,          "Events::Window::MINIMIZED"},
        {Events::Window::MAXIMIZED,          "Events::Window::MAXIMIZED"},
        {Events::Window::MOVE,               "Events::Window::MOVE"},
        {Events::Keyboard::KEY_DOWN,         "Events::Keyboard::KEY_DOWN"},
        {Events::Keyboard::KEY_UP,           "Events::Keyboard::KEY_UP"},
        {Events::Keyboard::KEY_PRESSED,      "Events::Keyboard::KEY_PRESSED"},
        {Events::Mouse::MOVE,                "Events::Mouse::MOVE"},
        {Events::Mouse::CLICK,               "Events::Mouse::CLICK"},
        {Events::Mouse::LEFT_CLICK,          "Events::Mouse::LEFT_CLICK"},
        {Events::Mouse::MIDDLE_CLICK,        "Events::Mouse::MIDDLE_CLICK"},
        {Events::Mouse::RIGHT_CLICK,         "Events::Mouse::RIGHT_CLICK"},
        {Events::Mouse::DOUBLE_CLICK,        "Events::Mouse::DOUBLE_CLICK"},
        {Events::Mouse::WHEEL,               "Events::Mouse::WHEEL"},
        {Events::Mouse::DRAG,                "Events::Mouse::DRAG"},
        {Events::Binding::TOGGLE_FULLSCREEN, "Events::Binding::TOGGLE_FULLSCREEN"},
        {Events::Binding::PLAYER_UP,         "Events::Binding::PLAYER_UP"},
        {Events::Binding::PLAYER_DOWN,       "Events::Binding::PLAYER_DOWN"},
        {Events::Binding::PLAYER_LEFT,       "Events::Binding::PLAYER_LEFT"},
        {Events::Binding::PLAYER_RIGHT,      "Events::Binding::PLAYER_RIGHT"},
        {Events::Binding::PLAYER_SHOOT,      "Events::Binding::PLAYER_SHOOT"},
        {Events::Binding::PLAYER_RESET,      "Events::Binding::PLAYER_RESET"},
        {Events::Binding::ACTIONBAR_1,       "Events::Binding::ACTIONBAR_1"},
        {Events::Binding::ACTIONBAR_2,       "Events::Binding::ACTIONBAR_2"},
        {Events::Spawner::SPAWN,             "Events::Spawner::SPAWN"},
        {Events::Spawner::DESPAWN,           "Events::Spawner::DESPAWN"},
        {Events::Spawner::OBJECT_SPAWNED,    "Events::Spawner::OBJECT_SPAWNED"},
        {Events::Spawner::OBJECT_DESPAWNED,  "Events::Spawner::OBJECT_DESPAWNED"},
        {Events::Camera::TARGET_ENTITY,      "Events::Camera::TARGET_ENTITY"},
        {Events::Camera::TARGET_COORD,       "Events::Camera::TARGET_COORD"}
    };
#endif // DEBUG
}

struct EventData {
    EventId id = 0;
    virtual ~EventData() = default;
};

struct KeyboardEvent : public EventData
{
    int key_code = 0;
    int key_repeat = 0;
    int modifier_keys = 0; //Need to work into a bitmask with cooresponding enum class
};

struct MouseEvent  : public EventData
{
    Vector2 pos = {0, 0};
    Vector2 delta = {0, 0};
    float wheel = 0;
    std::bitset<32> mouseState = 0;
};

struct WindowEvent  : public EventData
{
    int windowState = 0; //Fullscreen, windows, borderless (BITMASK)
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
};

struct SpawnEvent : public EventData
{
    std::string object = "";
    std::string name = "";
    Vector2 position = {0.0f, 0.0f};
    float heading = 0.0f;
};

struct CameraEvent : public EventData
{
    flecs::entity targetEntity;
    Vector2 targetCoords = {0.0f, 0.0f};
    float zoom = 1.0;


};

