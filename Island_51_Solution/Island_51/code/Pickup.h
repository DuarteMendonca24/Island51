#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
	//Start value for health pickups
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int MONEY_START_VALUE = 100;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	// How tough is each resource type
	const float TREE_HEALTH = 5;
	const float STONE_HEALTH = 1;
	const float IRON_HEALTH = 3;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

	// The sprite that represents this pickup
	Sprite m_Sprite;

	// The arena it exists in
	IntRect m_Arena;

	// How much is this pickup worth?
	int m_Value;

	// What type of pickup is this? 
	// 1 = health, 2 = ammo
	int m_Type;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	//Positon pickup
	float m_posX;
	float m_posY;
	// Public prototypes go here
public: 

	//Parameterized Constructor
	//Pickup(int type);
	// Prepare a new pickup
	void setArena(IntRect arena);

	void spawn(int type, float startX, float startY);

	// Check the position of a pickup
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	// Is this pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the pickup
	int gotIt();

	// Upgrade the value of each pickup
	void upgrade();

	int getType();

	void resource(float startX, float startY, int type);
};



