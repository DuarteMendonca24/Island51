#include "Pickup.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
using namespace std;
void Pickup::spawnPickup(int type, float startX, float startY , float scale)
{
	// Store the type of this pickup
	m_Type = type;
	
	// Associate the texture with the sprite
	switch (m_Type) {
	case 1:
		// Health spawns from enemies
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));

		// How much is pickup worth
		m_Value = HEALTH_START_VALUE;
		break;

	case 2:
		// Food
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/food.png"));

		m_Value = FOOD_START_VALUE;
		m_Type = type;
		break;

	case 3:
		// Food
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/soul.png"));

		m_Type = type;
		break;

	case 4:
		// Tree pickup
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 95, 22, 18, 24 });
		m_Health = TREE_HEALTH;
		m_Type = type;
		break; 

	case 5:
		// Stone
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 64, 47, 14, 14 });
		m_Health = STONE_HEALTH;
		m_Type = type;
		break;

	case 6:
		// Iron
		m_Sprite = Sprite(TextureHolder::GetTexture("graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 80, 65, 14, 14 });
		m_Health = IRON_HEALTH;
		m_Type = type;
		break;

	default:
		// Handle unexpected type
		break;
	}

	// set size of the spirte
	m_Sprite.setScale(scale, scale);
	// set the orgirin of the sprite
	m_Sprite.setOrigin(25, 25);

	// The time set the object will be stay in game
	m_SecondsToLive = START_SECONDS_TO_LIVE;
	
	// The time set the object will be wait in game
	m_SecondsToWait = START_WAIT_TIME;
	
	// set the initial position of the object to the specified coordinates 
	m_Position.x = startX;
	m_Position.y = startY;
	// Not currently spawned
	//m_Spawned = false;
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;
	// set the positon for the object 
	m_Sprite.setPosition(m_Position);
}

// The setArena function of the pickup class 
void Pickup::setArena(IntRect arena)
{
	// Copy the details of the arena to the pickup's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	//spawn();
}

//
FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

// Return the sprite from the pickup
Sprite Pickup::getSprite()
{
	return m_Sprite;
}

// Return the spawn after object have be pickup
bool Pickup::isSpawned()
{
	return m_Spawned;
}
// The pick as collected  
int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}
// update the pickup stated based on the elspased time 
void Pickup::update(float elapsedTime, float speed)
{
	// if the objetct is spawned 
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	// else if the object is not spawned 
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}

	// Do we need to hide a pickup?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Revove the pickup and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a pickup
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the pickup and reset the timer
		//spawn();
	}
	/*
	if (m_DirectionX > m_Position.x)
	{
		m_Position.x = m_Position.x + speed + elapsedTime;
	}
	if (m_DirectionX < m_Position.x)
	{
		m_Position.x = m_Position.x - speed + elapsedTime;
	}*/
	m_Sprite.setPosition(m_Position);
}
// Upgrade the pickup increaseing its valu 
void Pickup::upgrade()
{
	// If the pick up is of type 1 it will increased by 50%
	if (m_Type == 1)
	{
		m_Value += (HEALTH_START_VALUE * .5);
	}
	// else if the pick up is of type 2 it will increased by 50%
	else if (m_Type == 2)
	{
		m_Value += (FOOD_START_VALUE * .5);
	}

	// Make them more frequent and last longer
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 15);
	m_SecondsToWait -= (START_WAIT_TIME / 15);
}

// Get the type of the pickup
int Pickup::getType()
{
	//Returning the score value for this zombie
	return m_Type;
}

// Process a hit on the pickup
bool Pickup::hit()
{
	// decrement the health 
	m_Health--;
	// if the player is not longer alive after being hit  
	if (m_Health <= 0)
	{
		//we changed this to true for testing , it should be false
		m_Alive = false;
		//m_Sprite.setTexture(TextureHolder::GetTexture(
		//	"graphics/blood.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

// if the pickup is alive
bool Pickup::isAlive()
{
	return m_Alive;
}

// the position corrdinates of the pickup
Vector2f Pickup::getPosCoordinates() {

	return m_Position;
}

void Pickup::setPosition(Vector2f pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;

	m_Sprite.setPosition(m_Position);
}
void Pickup::inventoryMove(float dt, float speed)
{
	//move right
	if (finalDis < m_Position.x)
	{
		m_Position.x = finalDis - speed + dt;
	}
	else
	{
		m_Position.x += m_Position.x * speed * dt + 1;
	}
	m_Sprite.setPosition(m_Position);
}

void Pickup::inventoryMoveLeft(float dt, float speed)
{
	//move 
	m_Position.x -= m_Position.x * speed * dt +1;
	if (30 > m_Position.x)
	{
		m_Position.x += m_Position.x * speed * dt +1;
	}
	m_Sprite.setPosition(m_Position);
}
