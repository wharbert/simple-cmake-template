/*
* ## TODO ##
* SPhysics/SCollision/SRigidBody : Add Box2D to physics system, probably combine all systems with functions for each
* Reduce heap allocations as much as possible
* Make a plan to sprikle asserts all over the place - how to decide what to assert on?
* SCamera - Add LERP or smoothstep to camera zoom and move to functions
* SCamera - Add mouse drag and keyboard move features
* x - Move all header guards to #pragma once
* x - Game: Add event system to Game class
* x - Engine : Add macros for Engine features Engine class
* x - Engine : Restructure Engine to singleton class with GetX() methods for all singleton helpers (events, logger, etc...)
* x - Engine : Add Engine to namespace
* Engine : Refactor into external lib. Will need to use complex cmake template
* Engine : Create wrapper for ECS to abstract away flecs ?
* x - Engine : Keeps and maintain lists of active systems. Vector of systems in order of update? How to call functions from systems?
* x - Game : Rename Game class to engine?
* Logger : Maybe have a map of log objects so users can create logs for various systems? with corresponding config() method
* Logger : Why is setting a global and log level or TRACE not working?
* x - Logger : Composite into Engine and remove singleton
* x - Systems : Configure systems with variable refresh rates (Render = 60fps, physics = 10fps, ai = 2fps, etc...)
* x - Systems : Move init from constructor to Init()
* x - Systems : Create System parent class to implement standard functionality
* SInput : Where does key to action map live? Config
* SInput : Context specific key events? or how do I capture arbitrary text for text boxes?
* SInput : Update mouse routines to use custom extended enum?
* SInput : Add function to key map (eg. P1_Turn_Left = KEY_A) EventID MapKeytoAction(int key) can return EVENT::Action::Player_Up or EVENT::Keyboard::Key_W
* SInput : May refactor to dispatch events to specific systems (Eg. Push certain input events to SPlayer to update player info)
* SInput : Player comp to Input comp to be used by Input System (Allow for player and AI control of entity)
* SInput : How to map mouse events to bindings? General bindings mapper for KB/Mouse/Gamepad events?
* SBackground : Parallax background generator, also tile map
* x - SpaceGame : Add new Game class that is responsible for running the actual game logic. Allows for core game lib that can be in client or server
* SpaceGame : Includes game object flecs prototypes
* SpaceGame : Maintains various state machines and scene details
* AssetManager : Rename to ResourceManager?
* AssetManager : Add load and unload triggers
* AssetManager : Rework to load single images for backgrounds
* AssetManager : Rework to store concatenated "sprite::animation" names as hashed uint32_t (see Events.hpp)
* AssetManager : Need to rework Sprite and CSprite structs and all related processes
* EventManager : Try to rewrite with templates
* EventManager : New feature to bind on class of events (e.g. all player input events)
* EventManager : Look into creating EventPool then notify creates event in place, how to know when every listener has processed?
* EventManager : Look into refactoring to remove EventHandler composite - how would I manage the queue?
* EventManager : Use faster deligate than std::function
* EventManager : Implement immediate dispatch as well as queued dispatch?
* SProjectile : Manages lifecycle of projectile. May expand into general purpose game object manager
*   - CBullet - CLifetime
* Add UI
* 
* General game functions to add 
*  - Method to spawn objects 
*   - Create flecs templates
*   - How are object life times managed?
* 
* ## DEBUG ##
* Sometimes glfw takes a long time to start up
* 
* ## DESIGNS ##
* Add IMGUI tooling for adjusting game values while running. Option to overlay or pop-out
* Math functions
*   - Function to move to damp vector and bring to lower without jitter ( Vector2 DampenVector(Vector2 vec, float damp, float target) )
* SaveManager : Used for saving game state data to disk
*   - Look into using sqlite and having compact binary files
* ConfigManager : Load/Save and access for all game config settings
*   - Static class  
*   - Pulls configs from file
*   - Comes with default values
* StringManager : Use for all user visible strings and localization
* String to hash utility
*   - Similar system as used by events to convert strings into hashes for many internal uses (Events::Window::CLOSE = 3468461508U)
*   - Hash stored in enum/struct/namespace structured to allow easy access while programming and reduce collision space
*   - Map of hash to string for debugging/logging
*   - Some kind of preprocessing method to dump all the data in a hpp/cpp file (python processed strings file)
*   - Method to ifdef out lookup maps in release
* SAnimate/CAnimate : transform/sprite(?) animations over time sequence 
*  - Able to target animation over time period
*  - Multiple math animation functions defined
*  - Can combine animation functions/times into complex animations
* Main game state machine
* SPlayer for manipulating objects on behalf of the player?
*  - Registers for player bindings
*  - Updates CRidgidbody for player objects (Tags CPlayerControlled, CUnderPlayerControl)
* SCamera
*  - Add tag CCameraTrack
*  - Private methods
*   - track object
*   - track location
*   - frame objects
* Battle Screen manager?
* SBattle for managing battle gameplay
* Spawn bullets for specific time
* 
* ## NOTES ##
* Manager - stateful functionality
* Systems - stateless functionality
*/


//App settings
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define TOOLS_ON //Break down into more for specific engine tools (Editor, asset packer, etc...)
//#define FLECS_DEBUG

#include "game/SpaceGame.hpp"
#include <iostream>


int main()
{
  
  SpaceGame game;
  game.Init();
  game.Run();
  std::cout << "Some text"  << "\n";
  
  return 0;
}