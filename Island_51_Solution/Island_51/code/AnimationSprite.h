#pragma once
#include "SFML/Graphics.hpp"
#include "LevelManager.h"
using namespace sf;
class AnimationSprite
{
public:
	//setSprite to use correct animation cell
	void setSpriteFromSheet(sf::IntRect textureBox);
	//move the rectangle to the next cell in the animation
	void moveTextureRect();

protected:
	// Private variables and functions come next
	Vector2i sheetCoordinate; // Coordinate on spritesheet
	Vector2i spriteSize;
	int animation_it_limit; //Max animation iterations
	bool horizontal{ true };
	//which direction is the character headed? used to see if we need to reset the animation to first frame as we have changed direction
	Vector2f direction{ 0, 1 }; //default value is left
	// Of course we will need a sprite
	Sprite m_Sprite;
	Clock clock;
	float timeElapsed;
	//50 ms for each frame
	float animationTimer = 0;
	int ani_counter{};
};