#pragma once
#include <SFML/Graphics.hpp>


using namespace sf;

class Zombie
{
private:

	

	// How fast is each zombie type?
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;
	const float RAT_SPEED = 120;

	// How tough is each zombie type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;
	const float RAT_HEALTH = 1;

	// How much score does the zombie give?
	const int BLOATER_VALUE = 50;
	const int CHASER_VALUE = 20;
	const int CRAWLER_VALUE = 30;
	const int RAT_VALUE = 10;
	const int BOSS_VALUE = 200;

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
	void spawn(float startX, float startY, int type, int seed);

	//Spawn a new boss
	void spawnBoss(float startX, float startY);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	Vector2f getPosCoordinates();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// behaviour that makes the zombies chase the player if close
	void update(float elapsedTime, Vector2f playerLocation);

	//behaviour for the Illusionist enemy
	void illusionBehaviour(Vector2f enemyLocation);


	double distanceToPlayer(Vector2f playerLocation);

	int killValue();

	int getType();
};


