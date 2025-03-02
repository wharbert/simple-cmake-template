#include "Engine.hpp"
//Maybe include all 
#include "Components.hpp"
#include "Logger.hpp"
#include <memory>




MyEngine::Engine& MyEngine::Engine::GetInstance()
{
	static Engine instance;
	return instance;
}

void MyEngine::Engine::Init()
{
	//m_Logger = Logger();
	//m_EventManager = EventManager();
	
	m_Logger.AddLogger("CORE","[%T] [%n] [%^%L%$] [%s:%#] - %v", spdlog::level::trace);
	m_EventManager.Init();
	m_AssetManager.Init();

	initSystems(); 

	m_AssetManager.LoadAtlas(Config::atlas);

}

flecs::world& MyEngine::Engine::GetECS()
{
	return m_ECS;
}

AssetManager& MyEngine::Engine::GetAssetMan()
{
	return m_AssetManager;
}

std::shared_ptr<spdlog::logger> MyEngine::Engine::GetLogger(std::string logger)
{
	assert(logger != "");
	return m_Logger.GetLogger(logger);
}

EventManager& MyEngine::Engine::GetEventManager()
{
	//TODO: add assert that mEventManager is not null
	return m_EventManager;
}

Systems& MyEngine::Engine::GetSystem()
{
	//add assert not null
	return m_Systems;
}

void MyEngine::Engine::initSystems()
{
	m_Systems.agent.Init(60);
	m_Systems.background.Init(60);
	m_Systems.camera.Init(60);
	m_Systems.objects.Init(60);
	m_Systems.collision.Init(60);
	m_Systems.input.Init(60);
	m_Systems.player.Init(60);
	m_Systems.render.Init(60);
	m_Systems.rigidbody.Init(60);
	m_Systems.sprite.Init(60);
	m_Systems.transform.Init(60);
}

void MyEngine::Engine::UpdateSystems(float deltaTime)
{
	m_Systems.agent.Update(deltaTime);
	m_Systems.objects.Update(deltaTime);
	//m_Systems.background.Update(deltaTime);
	m_Systems.camera.Update(deltaTime);
	m_Systems.collision.Update(deltaTime);
	m_Systems.input.Update(deltaTime);
	m_Systems.player.Update(deltaTime);
	m_Systems.rigidbody.Update(deltaTime);
	m_Systems.sprite.Update(deltaTime);
	m_Systems.transform.Update(deltaTime);
	m_Systems.render.Update(deltaTime);
}

