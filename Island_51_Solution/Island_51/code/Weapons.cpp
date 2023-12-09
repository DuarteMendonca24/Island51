#include "Weapons.h"
#include "TextureHolder.h"
#include <iostream>
Weapons::Weapons()
{
	// Associate a texture with the sprite
	// !!Watch this space!!
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
	m_Position.x = posX;
	m_Position.y = posY;
	m_Sprite.setScale(scale, scale);
	m_Sprite.setPosition(m_Position);
}

FloatRect Weapons::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Weapons::getCenter()
{
	return m_Position;
}

Sprite Weapons::getSprite()
{
	return m_Sprite;
}
