#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <random>
#include "LevelManager.h"

using namespace std;


void Zombie::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		// Bloater aka the Illusionist 
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/boss3.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 205, 11, 30, 58 });
		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		m_ScoreValue = BLOATER_VALUE;
		m_type = type;
		break;

	case 1:
		// Chaser(takes player hunger bar)
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/enemy3.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		m_ScoreValue = CHASER_VALUE;
		m_type = type;

		break;

	case 2:
		// Crawler(spawns 2 rats when killed)
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/boss2.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		m_ScoreValue = CRAWLER_VALUE;
		m_type = type;
		break;

	case 3:
		// Rat
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/enemy4.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = RAT_SPEED;
		m_Health = RAT_HEALTH;
		m_ScoreValue = RAT_VALUE;
		m_type = type;
		break;
	
	case 4:

		// Explosive enemies (sends bullets in all directions)
		m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/acid_boss.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		m_ScoreValue = CHASER_VALUE;
		m_type = type;

		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	std::srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

void Zombie::spawnBoss(float startX, float startY, float elapsedTime)
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/boss.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
	m_Position.x = startX;
	m_Position.y = startY;

	m_Health = m_bossHealth;
	//Incrementing Health of boss by 10 and the bossCount which keeps track of amount of bosses that the player has went through
	m_bossHealth += 10;
	bossCount++;
	//Setting The Boss Speed Depending on Round
	if (bossCount >= 4)
	{
		if (bossCount > 5)
		{
			m_Speed = 130;
		}
		else
		{
			m_Speed = 70;
		}
	}
	else
	{
		m_Speed = 10;
	}
	m_Sprite.setOrigin(32, 32);
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit()
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

bool Zombie::isAlive()
{
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Zombie::getPosCoordinates() {

	return m_Position;
}


Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime,Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	double d = distanceToPlayer(playerLocation);
	timeElapsed = elapsedTime;
	setSpriteFromSheet(sf::IntRect(15, 80, 180, 65));
	//move the rectangle to the appropriate cell
	moveTextureRect();
	// Update the zombie position variables
	if (playerX > m_Position.x && d < 200)
	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
		m_Sprite.setScale(1, 1);
	}

	if (playerY > m_Position.y && d < 200)
	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x && d < 200)
	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
		m_Sprite.setScale(-1, 1);
	}

	if (playerY < m_Position.y && d < 200)
	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	//float angle = (atan2(playerY - m_Position.y,
		//playerX - m_Position.x)
		//* 180) / 3.141;

	//m_Sprite.setRotation(angle);


}

void Zombie::illusionBehaviour(Vector2f playerLocation, float elapsedTime) {

	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	timeElapsed = elapsedTime;
	setSpriteFromSheet(sf::IntRect(15, 80, 180, 65));
	//move the rectangle to the appropriate cell
	moveTextureRect();
	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;
	
	//m_Sprite.setRotation(angle);
	if (angle > 90 || angle < -90) {
		m_Sprite.setScale(-1, 1);
	}
	else {
		m_Sprite.setScale(1, 1);
	}
	// Move the sprite
	m_Sprite.setPosition(m_Position);

}

double Zombie::distanceToPlayer(Vector2f playerLocation) {

	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	//its using 25 because of pacman being a 50x50 image , dont forget to see player size
	int x1 = playerX + 25; // center of pacman
	int y1 = playerY + 25; // center of pacman
	int x2 = m_Position.x + 25; //centre of the ghost
	int y2 = m_Position.y + 25;//centre of the ghost
	int xsquared = (x2 - x1) * (x2 - x1);
	int ysquared = (y2 - y1) * (y2 - y1);
	double d = sqrt(xsquared + ysquared);

	return d;

}


int Zombie::killValue()
{
	//Returning the score value for this zombie
	return m_ScoreValue;
}

int Zombie::getType()
{
	//Returning the score value for this zombie
	return m_type;
}

void Zombie::setSpriteFromSheet(sf::IntRect textureBox)
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

void Zombie::moveTextureRect()
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



