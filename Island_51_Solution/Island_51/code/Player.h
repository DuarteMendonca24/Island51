#pragma once
#include <SFML/Graphics.hpp>
#include "LevelManager.h"
using namespace sf;

class Player
{
private:
	// The starting of the speed for player in the entity of the game 
	const float START_SPEED = 500;
	// The starting of the health for player in the entity of the game 
	const float START_HEALTH = 200;

	// Where is the player
	Vector2f m_Position;
	// where the player might hold the weapon
	Vector2f m_PositionWeapon;
	// Of course we will need a sprite
	Sprite m_Sprite;

	Sprite m_SpriteWeapon;
	// And a texture
	// !!Watch this space!!
	//Texture m_Texture;

	// What is the screen resolution
	Vector2f m_Resolution;

	// What size is the current arena
	IntRect m_Arena;

	// How big is each tile of the arena
	int m_TileSize;

	// Which directions is the player currently moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	// How much health has the player got?
	float m_Health;
	// What is the maximum health the player can have
	float m_MaxHealth;

	// When was the player last hit
	Time m_LastHit;

	// Speed in pixels per second
	float m_Speed;

	int m_Type;
	// Private variables and functions come next
	Vector2i sheetCoordinate; // Coordinate on spritesheet
	Vector2i spriteSize;
	int animation_it_limit; //Max animation iterations
	bool horizontal{ true };
	int ani_counter{};

	// Called the function for clock object to measuers the time 
	Clock clock;
	// This stone
	float timeElapsed;
	//50 ms for each frame
	float animationTimer = 0;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;
	// All our public functions will come next
public:
	// The function from the player class
	Player();

	// Call this at the end of every game
	void resetPlayerStats();

	// Function declarartion for spawning game elements within a specified araea 
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// How long ago was the player last hit
	Time getLastHitTime();

	// Where is the player
	FloatRect getPosition();

	// Where is the center of the player
	Vector2f getCenter();

	// Which angle is the player facing
	float getRotation();

	// Send a copy of the sprite to main
	Sprite getSprite();
	Sprite getSpriteWeapon();

	// How much health has the player currently got?
	int getHealth();

	// The next four functions move the player
	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	// Stop the player moving in a specific direction
	void stopLeft();

	void stopRight();

	void stopUp();

	void stopDown();

	// We will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	// Give player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Here is the health for the player
	void setHealth(float x);

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);
	// Decrease the maximum amount of health the player can have
	void decreaseHealthLevel(float amount);

	//setSprite to use correct animation cell
	void setSpriteFromSheet(sf::IntRect textureBox);

	//move the rectangle to the next cell in the animation
	void moveTextureRect();
	void getAttack(int type);

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();
	void updateLeftRightHeadFeet();

	// Make the character stand firm
	void stopDown(float position);
	void stopUp(float position);
	void stopRight(float position);
	void stopLeft(float position);

};



#pragma once
