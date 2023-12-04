#include "Player.h"
#include "TextureHolder.h"

Player::Player()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/player_2.png"));
	m_SpriteWeapon = Sprite(TextureHolder::GetTexture(
		"graphics/melee_weapon2.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 10, 17, 50, 60 });
	m_SpriteWeapon.setTextureRect(sf::IntRect{ 24, 10, 16, 42 });
	ani_counter = 1;
	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(39/2, 37/2);
	m_SpriteWeapon.setOrigin(16 / 2, 42/ 2);
}

void Player::resetPlayerStats()
{
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	// Strore the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

}

Time Player::getLastHitTime()
{
	return m_LastHit;
}

bool Player::hit(Time timeHit)
{
	setSpriteFromSheet(sf::IntRect(15, 309, 180, 55));
	//move the rectangle to the appropriate cell
	moveTextureRect();
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)// 2 tenths of second
	{
		m_LastHit = timeHit;
		m_Health -= 10;
	

		return true;
	}
	else
	{
		return false;
	}

}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return m_Position;
}

float Player::getRotation()
{
	return m_Sprite.getRotation();
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

Sprite Player::getSpriteWeapon()
{
	return m_SpriteWeapon;
}

int Player::getHealth()
{
	return m_Health;
}

void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
	
	timeElapsed = elapsedTime;
	setSpriteFromSheet(sf::IntRect(15, 24, 180, 55));
	//move the rectangle to the appropriate cell
	moveTextureRect();
	if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
		//2nd row of sprite sheet 3 characters 150 pixels by 50 pixels
		setSpriteFromSheet(sf::IntRect(15, 95, 180, 55));
		//move the rectangle to the appropriate cell
		moveTextureRect();
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
		//1st row of sprite sheet 3 characters
		setSpriteFromSheet(sf::IntRect(15, 95, 180, 55));
		//move the rectangle to the appropriate cell
		moveTextureRect();
	}
	m_Sprite.setPosition(m_Position);

	// Keep the player in the arena
	/*
	if (m_Position.x > m_Arena.width - m_TileSize)
	{
		m_Position.x = m_Position.x - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize)
	{
		m_Position.x = m_Position.x + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize)  
	{
		m_Position.y = m_Position.y - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize)
	{
		m_Position.y = m_Position.y + m_TileSize;
	}
	*/
	// Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2,
		mousePosition.x - m_Resolution.x / 2)
		* 180) / 3.141;

	//m_Sprite.setRotation(angle);
	m_SpriteWeapon.setRotation(angle);
	// Calculate the offset for the weapon position
	float weaponOffsetX = 50.0f * cos(angle * 3.14 / 180);
	float weaponOffsetY = 50.0f * sin(angle * 3.14 / 180);

	// Set the position of the weapon sprite on the side of the player
	m_PositionWeapon.x = m_Position.x + weaponOffsetX;
	m_PositionWeapon.y = m_Position.y + weaponOffsetY;

	m_SpriteWeapon.setPosition(m_PositionWeapon);
	// Flip the weapon sprite horizontally if facing left
	if (angle > 90 || angle < -90) {
		m_SpriteWeapon.setScale(1, -1);
		m_Sprite.setScale(-1, 1);
	}
	else {
		m_SpriteWeapon.setScale(1, 1);
		m_Sprite.setScale(1, 1);
		
	}
	// Update the rect for all body parts
	FloatRect r = getPosition();
	// Feet
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;
	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
	m_Head.height = 1;
	// Right
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;
	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .5;
	m_Left.width = 1;
	m_Left.height = r.height * .3;
	m_Sprite.setPosition(m_Position);
}

void Player::upgradeSpeed()
{
	// 40% speed upgrade
	m_Speed += (START_SPEED * .4);
}

void Player::upgradeHealth()
{
	// 20HP max health upgrade
	m_MaxHealth = m_MaxHealth + 20;

}

void Player::increaseHealthLevel(int amount)
{
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
}

void Player::changePlayerSprite(int type)
{

	//Checking which sprite to equip
	if (type == 1)
	{
		//Handgun
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/player.png"));
		m_Sprite.setOrigin(39/2,37/2);
	}
	else if (type == 2)
	{
		//SMG
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/playerSmg.png"));
		m_Sprite.setOrigin(46 / 2, 37 / 2);
	}
	else
	{
		//Railgun
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/playerRailgun.png"));
		m_Sprite.setOrigin(44 / 2, 37 / 2);
	}
}

void Player::setSpriteFromSheet(sf::IntRect textureBox)
{
	//LevelManager l;
	//int tile_size = l.TILE_SIZE;
	int tile_size = 60;
	sheetCoordinate = Vector2i(textureBox.left, textureBox.top);
	spriteSize = Vector2i(tile_size, tile_size);
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

void Player::moveTextureRect()
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
	timePerFrame = 1.0 / 4.0;
	animationTimer = animationTimer + timeElapsed;
	if (animationTimer > timePerFrame)
	{
		ani_counter++;
		animationTimer = 0;
	}

}
void Player::getAttack(int type)
{
	// Store the type of this pickup
	m_Type = type;

	// Associate the texture with the sprite
	switch (m_Type) {
	case 1:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 70,75,50,42 });
		
		break;

	case 2:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 24, 10, 16, 42 });
		break;

	case 3:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 90, 10, 16, 42 });
		break;
	case 4:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 155, 10, 16, 42 });
		break;
	case 5:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 213, 10, 20, 42 });
		break;
	case 6:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 70,200,50,42 });
		break;
	case 7:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 70,135,50,42 });
		break;
	case 8:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 0,258,50,42 });
		break;
	case 9:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 85,260,24,24 });
		break;
	case 10:
		m_SpriteWeapon.setTextureRect(sf::IntRect{ 130,258,43,28 });
		break;
	}
}
FloatRect Player::getFeet()
{
	return m_Feet;
}

FloatRect Player::getHead()
{
	return m_Head;
}

FloatRect Player::getLeft()
{
	return m_Left;
}

FloatRect Player::getRight()
{
	return m_Right;
}
void Player::updateLeftRightHeadFeet()
{
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left + 7;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 14;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left + 7;
	m_Head.top = r.top;
	m_Head.width = r.width - 14;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 1;
	m_Right.top = r.top + r.height * .3;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .3;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

}
void Player::stopUp(float position)
{
	m_Position.y = position + getPosition().height;
	m_Sprite.setPosition(m_Position);
}
void Player::stopDown(float position)
{
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
}

void Player::stopRight(float position)
{

	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Player::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}