#include "AssetManager.hpp"
#include <iostream>

using json = nlohmann::json;



AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
    for (Texture2D& t : m_atlas) {
        UnloadTexture(t);
    }
}

void AssetManager::Init()
{
}

void AssetManager::LoadAtlas(std::string atlasPath) 
{ 
    // Read in json file
    std::ifstream f(atlasPath);
    json data = json::parse(f);

    for (auto const &[at, v] : data.items()) {
        std::string path = ASSETS_PATH + at;
        m_atlas.push_back(LoadTexture(path.c_str()));

        for (auto const &[o, v] : v["objects"].items()) {
            for (auto const &[an, v] : v.items()) {
                Sprite sp;
                sp.frameCount = v["frames"].size();
                sp.frameRate = v["frameRate"];
                for (int x = 0; x < sp.frameCount; x++) {
                    sp.frame.push_back({v["frames"][x]["x"], v["frames"][x]["y"],
                        v["frames"][x]["w"], v["frames"][x]["h"]});
                }
                sp.atlas = m_atlas.back();
                sp.name = o;
                sp.sequence = an;
                m_sprites[o+"::"+an] = sp;
            }
        }
    }
}

Sprite* AssetManager::GetSprite(std::string sprite)
{
    //Need some validation
    return &m_sprites[sprite];
}

bool AssetManager::IsValidSprite(const char* asset)
{
    if (m_sprites.find(asset) != m_sprites.end()) return true;
    return false;
}

