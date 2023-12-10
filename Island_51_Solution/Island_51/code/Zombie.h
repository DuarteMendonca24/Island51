#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Zombie 
{
private:
	// How fast is each enemies type?
	const float ILLUSIONIST_SPEED = 40;
	const float HUNGERTAKER_SPEED = 80;
	const float MUSHROOMGOLEM_SPEED = 20;
	const float SMALLMUSHROOM_SPEED = 120;

	// How tough is each enemies type
	const float ILLUSIONIST_HEALTH = 5;
	const float HUNGERTAKER_HEALTH = 1;
	const float MUSHROOMGOLEM_HEALTH = 3;
	const float SMALLMUSHROOM_HEALTH = 1;

	// How much score does the enemies give?
	const int ILLUSIONIST_VALUE = 50;
	const int HUNGERTAKER_VALUE = 20;
	const int MUSHROOMGOLEM_VALUE = 30;
	const int SMALLMUSHROOM_VALUE = 10;
	const int ORC_VALUE = 200;

	// Store the score value
	int m_ScoreValue;

	//Orc health
	float m_orcHealth = 50;

	//How many boss 
	int bossCount;

	// Make each enemies vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	

	// Where is this enemies?
	Vector2f m_Position;

	//Where is this enemies wandering to?
	Vector2f walkPoint;

	// A sprite for the enemies
	Sprite m_Sprite;

	// How fast can this one run?
	float m_Speed;

	// How much health has it got?
	float m_Health;

	// Is it still alive?
	bool m_Alive = true;

	//type of enemies
	int m_type;

	// Private variables and functions come next
	Vector2i sheetCoordinate; // Coordinate on spritesheet

	// Sprite Size
	Vector2i spriteSize;

	//Max animation iterations
	int animation_it_limit; 

	// Declaration of a boolean variable indicating the direction of animation
	bool horizontal{ true };

	// Declaration of a counter variable for animation progress
	int ani_counter{};

	// Declaration of a clock to measure elapsed time
	Clock clock;

	// Declaration of a floating-point variable to store elapsed time
	float timeElapsed;

	//50 ms for each frame
	float animationTimer = 0;
	// Public prototypes go here	
public:
	// Definition of states for the enemy
	enum EnemyState {
		WANDERING,  // State representing the enemy wandering
		TARGETING   // State representing the enemy targeting
	};

	// Declaration of a variable to hold the current state of the enemy
	EnemyState enemyState = EnemyState::TARGETING;


	// Handle when a bullet hits a enemies
	bool hit();

	// Find out if the enemies is alive
	bool isAlive();

	// Spawn a new enemies
	void spawn(float startX, float startY, int type, int seed);

	//Spawn a new boss
	void spawnBoss(float startX, float startY, float elapsedTime);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Return the position of coordinates
	Vector2f getPosCoordinates();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the enemies each frame
	void update(float elapsedTime, Vector2f playerLocation);

	//Creating a position to wander to
	Vector2f createWalkPoint();

	//behaviour for the Illusionist enemy
	void illusionBehaviour(Vector2f enemyLocation, float elapsedTime);

	//Follow the player position
	double distanceToPlayer(Vector2f playerLocation);

	//Return the score the player kills
	int killValue();

	//Return the type
	int getType();

	//setSprite to use correct animation cell
	void setSpriteFromSheet(sf::IntRect textureBox);

	//move the rectangle to the next cell in the animation
	void moveTextureRect();
};


