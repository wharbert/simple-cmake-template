#include "SpaceGame.hpp"
#include "engine/core/Engine.hpp"
#include <iostream>

void SpaceGame::Init()
{
	spdlog::set_level(spdlog::level::trace);
	std::cout << spdlog::get_level() << "\n";
	ENGINE.Init();
	std::cout << LOGGER("CORE")->level() << "\n";
	//ENGINE.GetSystem().render.CreateWindow(Config::screenWidth, Config::screenHeight, Config::title);
	
	
}

void SpaceGame::Load()
{
	
}

void SpaceGame::Run()
{
    float deltaTime = 0.0f;

	flecs::entity camera = ENGINE.GetSystem().camera.AddCamera("main", Config::screenWidth, Config::screenHeight);

	


	
	createObject("planet", "planet-green", Vector2{200.0f, 200.0f}, 0.0f);
	//createObject("player", "player-ship", Vector2{400.0f, 400.0f}, 0.0f);


	auto ship = ENGINE.GetSystem().objects.SpawnObject("player-ship","ship", 0.0f, {400.0f, 400.0f});
	
	//ENGINE.GetSystem().camera.TargetCoord(camera, Vector2{400.0f, 400.0f});
	ENGINE.GetSystem().camera.TargetEntity(camera, ship);

	while (!WindowShouldClose()) {
		auto startTime = std::chrono::high_resolution_clock::now();
		//Begin Update loops

		ENGINE.UpdateSystems(deltaTime);

		//End Update loops
		auto stopTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}

}

void SpaceGame::createObject(std::string objName, std::string object, Vector2 position, float heading)
{
	SpawnEvent e;
	e.heading = heading;
	e.id = Events::Spawner::SPAWN;
	e.name = objName;
	e.object = object;
	e.position = position;
	EVENTMAN.Notify(std::make_shared<SpawnEvent>(e));
}
