#pragma once

#include <vector>
#include "raylib.h"

 

class BackgroundManager {
public:
    void Init(int updatesPerSecond);
    void Update(float deltaTime);
    void CreateBackground();

private:
    std::vector<Texture2D> backgroundImage;
    std::vector<int> parallaxRate;  
};