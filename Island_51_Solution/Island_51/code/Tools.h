#pragma once
//#include "Engine.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Tools
{
private:

	// How tough is each zombie type
	const float TREE_HEALTH = 5;
	const float STONE_HEALTH = 1;
	const float IRON_HEALTH = 3;

	int m_ScoreValue;
	float m_bossHealth = 50;
	int bossCount;

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// Where is this zombie?
	Vector2f m_Position;

	// A sprite for the zombie
	Sprite m_Sprite;

	// How fast can this one run/crawl?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive;

	//type of zombie
	int m_type;



	// Public prototypes go here	
public:

	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type , float scale);

	//Spawn a new boss
	void spawnBoss(float startX, float startY);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	Vector2f getPosCoordinates();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation);

	int killValue();

	int getType();
};