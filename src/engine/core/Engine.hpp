#pragma once


#include "engine/managers/AssetManager.hpp"
#include "engine/managers/config.hpp"
#include "engine/core/Logger.hpp"
#include "engine/managers/EventManager.hpp"
#include "engine/core/Components.hpp"
#include "flecs.h"
#include <memory>
#include "Logger.hpp"
#include <string>
#include "engine/systems/SAgent.hpp"
#include "engine/systems/SBackground.hpp"
#include "engine/systems/SCamera.hpp"
#include "engine/systems/SCollision.hpp"
#include "engine/systems/SInput.hpp"
#include "engine/systems/SPlayer.hpp"
#include "engine/systems/SRender.hpp"
#include "engine/systems/SRigidBody.hpp"
#include "engine/systems/SSprite.hpp"
#include "engine/systems/STransform.hpp"
#include "engine/systems/SObjects.hpp"


struct Systems {
	SAgent agent;
	SBackground background;
	SCamera camera;
	SCollision collision;
	SInput input;
	SPlayer player;
	SRender render;
	SRigidBody rigidbody;
	SSprite sprite;
	STransform transform;
	SObjects objects;
};


namespace MyEngine 
{

class Engine
{
public:
	static Engine& GetInstance();
	void Init();
	void UpdateSystems(float deltaTime);
	
	flecs::world& GetECS();
	AssetManager& GetAssetMan();
	std::shared_ptr<spdlog::logger> GetLogger(std::string logger);
	EventManager& GetEventManager();
	Systems& GetSystem();
	
private:
	Engine() = default;
	
	flecs::world m_ECS;
	AssetManager m_AssetManager;
	Logger m_Logger;
	EventManager m_EventManager;
	Systems m_Systems;
	
	void initSystems();
	
};

}

//MACROS
#define ENGINE				 MyEngine::Engine::GetInstance()
#define ECS					 MyEngine::Engine::GetInstance().GetECS()
#define ASSETMAN			 MyEngine::Engine::GetInstance().GetAssetMan()
#define EVENTMAN			 MyEngine::Engine::GetInstance().GetEventManager()
#define LOGGER(L)	         MyEngine::Engine::GetInstance().GetLogger(L)	   	
#define LOG_TRACE(L,...)     SPDLOG_LOGGER_TRACE(MyEngine::Engine::GetInstance().GetLogger(L), __VA_ARGS__);
#define LOG_INFO(L,...)      SPDLOG_LOGGER_INFO(MyEngine::Engine::GetInstance().GetLogger(L), __VA_ARGS__);
#define LOG_WARN(L,...)      SPDLOG_LOGGER_WARN(MyEngine::Engine::GetInstance().GetLogger(L), __VA_ARGS__);
#define LOG_ERROR(L,...)     SPDLOG_LOGGER_ERROR(MyEngine::Engine::GetInstance().GetLogger(L), __VA_ARGS__);
#define LOG_CRITCAL(L,...)   SPDLOG_LOGGER_CRITICAL(MyEngine::Engine::GetInstance().GetLogger(L), __VA_ARGS__);
