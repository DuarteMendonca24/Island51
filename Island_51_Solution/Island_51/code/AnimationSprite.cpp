#include "AnimationSprite.h"

void AnimationSprite::setSpriteFromSheet(sf::IntRect textureBox)
{
	LevelManager l;
	int tile_size = 60;
	sheetCoordinate = sf::Vector2i(textureBox.left, textureBox.top);
	spriteSize = sf::Vector2i(tile_size, tile_size);
	if (textureBox.width > tile_size)
	{
		animation_it_limit = textureBox.width / tile_size;

		horizontal = true;
	}
	else if (textureBox.height > tile_size)
	{
		animation_it_limit = textureBox.height / tile_size;
		horizontal = false;
	}
	else
		throw std::logic_error("Animation bounding box must contain multiply sprites, setSprite(sf::IntRect )\n");
	m_Sprite.setTextureRect(sf::IntRect{ sheetCoordinate, spriteSize });

}

void AnimationSprite::moveTextureRect()
{
	// if the animation counter is greater than the animation limit reset to 1;
	if (ani_counter == animation_it_limit)
	{
		ani_counter = 0;
	}

	if (horizontal) {
		m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(spriteSize.x * ani_counter, 0), spriteSize));
	}
	else {
		m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(0, spriteSize.y * ani_counter), spriteSize));
	}

	//increment animation counter to point to the next frame
	double timePerFrame;
	timePerFrame = 1.0 / 6.0;
	animationTimer = animationTimer + timeElapsed;
	if (animationTimer > timePerFrame)
	{
		ani_counter++;
		animationTimer = 0;
	}

}