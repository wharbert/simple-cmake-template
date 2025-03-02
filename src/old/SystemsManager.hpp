//Ehh, just do this all in Engine.cpp for now

#pragma once


#include <string>
#include "raylib.h"
#include "flecs.h"
#include "core/Components.hpp"

class SystemsManager
{
public:
    SystemsManager();
    ~SystemsManager();
    
    void Init();
    void LoadSystem();
    void Update(float dt);
    void GetSystem();

private:

};
