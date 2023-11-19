#include "Pickup.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
using namespace std;
void Pickup::spawn(int type, float startX, float startY)
{
	// Store the type of this pickup
	m_Type = type;

	// Associate the texture with the sprite
	if (m_Type == 1)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/health_pickup.png"));

		// How much is pickup worth
		m_Value = HEALTH_START_VALUE;

	}
	else if (m_Type == 2)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/ammo_pickup.png"));

		// How much is pickup worth
		m_Value = AMMO_START_VALUE;
	}
	else
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/moneyBag.png"));
		//how much is pickup worth
		m_Value = MONEY_START_VALUE;
	}

	m_Sprite.setOrigin(25, 25);

	m_SecondsToLive = START_SECONDS_TO_LIVE;
	m_SecondsToWait = START_WAIT_TIME;

	m_Position.x = startX;
	m_Position.y = startY;
	// Not currently spawned
	//m_Spawned = false;
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;

	m_Sprite.setPosition(m_Position);
}

void Pickup::resource(float startX, float startY, int type, float scale)
{
	switch (type)
	{
	case 0:
		// Tree
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 95,22,18,24 });
		m_Health = TREE_HEALTH;
		m_Type = type;
		break;

	case 1:
		// Stone
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 64,47,14,14 });
		m_Health = STONE_HEALTH;
		m_Type = type;

		break;

	case 2:
		// Iron
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 80,60,14,14 });
		m_Health = IRON_HEALTH;
		m_Type = type;
		break;

	}
	m_Position.x = startX;
	m_Position.y = startY;
	m_Sprite.setScale(scale, scale);
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}
void Pickup::setArena(IntRect arena)
{

	// Copy the details of the arena to the pickup's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	//spawn();
}

FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
	return m_Sprite;
}

bool Pickup::isSpawned()
{
	return m_Spawned;
}

int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

void Pickup::update(float elapsedTime)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
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

}

void Pickup::upgrade()
{
	if (m_Type == 1)
	{
		m_Value += (HEALTH_START_VALUE * .5);
	}
	else if (m_Type == 2)
	{
		m_Value += (AMMO_START_VALUE * .5);
	}
	else
	{
		m_Value += (MONEY_START_VALUE * .25);
	}

	// Make them more frequent and last longer
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 15);
	m_SecondsToWait -= (START_WAIT_TIME / 15);
}

int Pickup::getType()
{
	//Returning the score value for this zombie
	return m_Type;
}

bool Pickup::hit()
{
	m_Health--;

	if (m_Health <= 0)
	{
		//we changed this to true for testing , it should be false
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

bool Pickup::isAlive()
{
	return m_Alive;
}

Vector2f Pickup::getPosCoordinates() {

	return m_Position;
}