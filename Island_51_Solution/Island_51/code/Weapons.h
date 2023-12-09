#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Weapons
{
private:
	// Where is the player
	Vector2f m_Position;
	// Of course we will need a sprite
	Sprite m_Sprite;
	int m_Type;
	// All our public functions will come next
public:

	Weapons();

	void spawn(int type, float scale, float posX, float posY);
	// Where is the player
	FloatRect getPosition();
	// Where is the center of the player
	Vector2f getCenter();
	// Send a copy of the sprite to main
	Sprite getSprite();
};



#pragma once
