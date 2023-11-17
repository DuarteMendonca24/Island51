#include "Tools.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;


void Tools::spawn(float startX, float startY, int type)
{
	switch (type)
	{
	case 0:
		// Bloater
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 95,22,18,24 });
		m_Health = TREE_HEALTH;
		m_type = type;
		break;

	case 1:
		// Chaser
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 64,47,14,14 });
		m_Health = STONE_HEALTH;
		m_type = type;

		break;

	case 2:
		// Crawler
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/forest__resources.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 80,60,14,14 });
		m_Health = IRON_HEALTH;
		m_type = type;
		break;

	}

	m_Position.x = startX;
	m_Position.y = startY;
	//m_Sprite.setScale(1.5,1.5);
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Tools::hit()
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

bool Tools::isAlive()
{
	return m_Alive;
}

FloatRect Tools::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Tools::getPosCoordinates() {

	return m_Position;
}


Sprite Tools::getSprite()
{
	return m_Sprite;
}


int Tools::getType()
{
	//Returning the score value for this zombie
	return m_type;
}

void Tools::update(float elapsedTime, Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)
	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);
}
