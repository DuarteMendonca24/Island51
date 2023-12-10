#include "Weapons.h"
#include "TextureHolder.h"
#include <iostream>
Weapons::Weapons()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/melee_weapon2.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 24, 10, 16, 42 });
}

void Weapons::spawn(int type, float scale, float posX, float posY)
{
	// Store the type of this pickup
	m_Type = type;
	switch (m_Type) {
	case 1:
		m_Sprite.setTextureRect(sf::IntRect{ 85,260,24,24 });
		break;
	case 2:
		m_Sprite.setTextureRect(sf::IntRect{ 24, 10, 16, 42 });
		break;
	case 3:
		m_Sprite.setTextureRect(sf::IntRect{ 90, 10, 16, 42 });
		break;
	case 4:
		m_Sprite.setTextureRect(sf::IntRect{ 155, 10, 16, 42 });
		break;
	case 5:
		m_Sprite.setTextureRect(sf::IntRect{ 213, 10, 20, 42 });
		break;

	}
	// Assuming these variables are declared and initialized
	m_Position.x = posX;
	m_Position.y = posY;
	//Set the scale size of the sprite
	m_Sprite.setScale(scale, scale);
	// Set the position of the sprite using the m_Position 
	m_Sprite.setPosition(m_Position);
}

FloatRect Weapons::getPosition()
{
	//Return the position global bounds
	return m_Sprite.getGlobalBounds();
}

Vector2f Weapons::getCenter()
{
	//Return the sprite position
	return m_Position;
}

Sprite Weapons::getSprite()
{
	//Return the sprite
	return m_Sprite;
}
