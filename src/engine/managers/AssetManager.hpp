#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "raylib.h"
#include "engine/core/Types.hpp"

class AssetManager 
{
  public:
	AssetManager();
	~AssetManager();
	  
	void Init();
	void LoadAtlas(std::string name);
	Sprite* GetSprite(std::string sprite);
	bool IsValidSprite(const char* asset);
	
	std::vector<Texture2D> m_atlas;
	std::unordered_map<std::string, Sprite> m_sprites;
  
  private:
};

/* Texture Atlas JSON format
{
	"atlas" : {
		"file" : "[ATLAS].png",
		"size" : {"width" : 0, "height" : 0},
		"object" : {
			"name" : "[NAME]",
			"rotation" : 0,  
			"size" : { "x" : 0, "y" : 0 },
			"animation" : {
				"name" : "[NAME]",
				"frameRate" : 8,
				"frame" : [
							{"x" : 0, "y" : 0},
						  ],
			},
		},
	},
}

*/