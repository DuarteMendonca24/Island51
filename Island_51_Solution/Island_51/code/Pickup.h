#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
	//Start value for health pickups
	const int HEALTH_START_VALUE = 50;
	//Start value for ammo pickups
	const int AMMO_START_VALUE = 12;
	//Start value for money pickups
	const int MONEY_START_VALUE = 100;
	//Start value for wait time
	const int START_WAIT_TIME = 10;
	// //Start value for Live
	const int START_SECONDS_TO_LIVE = 5;
	////Start value for food pickups
	const int FOOD_START_VALUE = 50;
	// How tough is each resource type
	const float TREE_HEALTH = 4;
	const float STONE_HEALTH = 6;
	const float IRON_HEALTH = 7;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive = true;

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
	Vector2f m_Position;
	// Public prototypes go here
public:

	//Parameterized Constructor
	//Pickup(int type);
	// Prepare a new pickup
	void setArena(IntRect arena);
	// Here is the function that call spawing for the pickip in a game
	void spawnPickup(int type, float startX, float startY , float scale);

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

	// this will allow the player to pick up the item 
	int getType();

	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();
	
	// Declaraton the function that respresgntinh positon coordinates 
	Vector2f getPosCoordinates();
};
#pragma once