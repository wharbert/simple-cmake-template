// How to manage various state machines? 
// Manage Game Screens (Start, battle, navigation, trade, colony, diplomacy, etc...)
// How to design to separate from graphics if needed for server/client app?

#pragma once

#include "engine/core/Engine.hpp"


// Game specific ENUMS

// Game Specific Structs

// 


//Does this really need to be a class?
class SpaceGame {
public:

    void Init();
    void Load();
    void Run();

private:
    void createObject(std::string objName, std::string asset, Vector2 position, float heading);

};