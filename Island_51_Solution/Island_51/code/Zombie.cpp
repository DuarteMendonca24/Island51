
#include <SFML/Audio.hpp>
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
		// the Illusionist 
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/boss3.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 205, 11, 30, 58 });
		m_Speed = ILLUSIONIST_SPEED;
		m_Health = ILLUSIONIST_HEALTH;
		m_ScoreValue = ILLUSIONIST_VALUE;
		m_type = type;
		break;

	case 1:
		// Hunger Taker(takes player hunger bar)
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/enemy3.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = HUNGERTAKER_SPEED;
		m_Health = HUNGERTAKER_HEALTH;
		m_ScoreValue = HUNGERTAKER_VALUE;
		m_type = type;

		break;

	case 2:
		// Mushroom Golem(spawns 2 rats when killed)
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/boss2.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = MUSHROOMGOLEM_SPEED;
		m_Health = MUSHROOMGOLEM_HEALTH;
		m_ScoreValue = MUSHROOMGOLEM_VALUE;
		m_type = type;
		break;

	case 3:
		// Small murshroom
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/enemy4.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = SMALLMUSHROOM_SPEED;
		m_Health = SMALLMUSHROOM_HEALTH;
		m_ScoreValue = SMALLMUSHROOM_VALUE;
		m_type = type;
		break;
	
	case 4:

		// Explosive enemies (sends bullets in all directions)
		m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/acid_boss.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = HUNGERTAKER_SPEED;
		m_Health = HUNGERTAKER_HEALTH;
		m_ScoreValue = HUNGERTAKER_VALUE;
		m_type = type;

		break;
	default:
		// Mushroom Golem(spawns 2 rats when killed)
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/boss2.png"));
		m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
		m_Speed = MUSHROOMGOLEM_SPEED;
		m_Health = MUSHROOMGOLEM_HEALTH;
		m_ScoreValue = MUSHROOMGOLEM_VALUE;
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
	// Assuming these variables are declared and initialized
	m_Position.x = startX;
	m_Position.y = startY;

	// Set the origin of the sprite (assumed to be a circle with a radius of 25)
	m_Sprite.setOrigin(25, 25);

	// Set the position of the sprite using the m_Position coordinates
	m_Sprite.setPosition(m_Position);
	//Initialising walk point
	walkPoint = createWalkPoint();
}

void Zombie::spawnBoss(float startX, float startY, float elapsedTime)
{
	// Load boss texture and set sprite properties
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/boss.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 209, 11, 52, 58 });
	// Set initial position of the boss
	m_Position.x = startX;
	m_Position.y = startY;
	// Set initial health of the boss (m_orcHealth is a member variable)
	m_Health = m_orcHealth;
	//Incrementing Health of boss by 10 and the bossCount which keeps track of amount of bosses that the player has went through
	m_orcHealth += 10;
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
	// Set the origin and position of the boss sprite
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
	//Return the enemies is alive
	return m_Alive;
}

FloatRect Zombie::getPosition()
{
	//Return the enemies position global bounds
	return m_Sprite.getGlobalBounds();
}

Vector2f Zombie::getPosCoordinates() {
	//Return the position
	return m_Position;
}


Sprite Zombie::getSprite()
{
	//Return the sprite
	return m_Sprite;
}

void Zombie::update(float elapsedTime,Vector2f playerLocation)
{
	//variables are declared 
	double d = distanceToPlayer(playerLocation);
	if (d <= 250)
	{
		// If the distance between the enemies and the player is less than or equal to 250:
		// Set the state of the enemies to targeting mode
		enemyState = EnemyState::TARGETING;
		// Create a sound buffer to load the sound file
		SoundBuffer spottedBuffer;
		// Load the sound file "SpottedGrowl.wav" into the sound buffer
		spottedBuffer.loadFromFile("sound/SpottedGrowl.wav");
		// Create a sound object
		Sound spotted;
		// Set the sound buffer for the sound object
		spotted.setBuffer(spottedBuffer);
		// Set the attenuation of the sound (gradual decrease in volume as listener moves away)
		spotted.setAttenuation(90);
		// Set the position of the sound source (assumed to be in 2D space, z-coordinate set to 0)
		spotted.setPosition(Vector3f(m_Position.x, m_Position.y, 0));
		// Set the volume of the sound
		spotted.setVolume(25);
		// Play the sound
		spotted.play();
	}
	else
	{
		// If the distance is greater than 250:
		// Set the state of the zombie to wandering mode
		enemyState = EnemyState::WANDERING;
	}

	// If the enemies is in targeting 
	if (enemyState == EnemyState::TARGETING)
	{
		// Get the x and y coordinates of the player
		float playerX = playerLocation.x;
		float playerY = playerLocation.y;
		// Store the elapsed time
		timeElapsed = elapsedTime;
		// Set the sprite from a sprite sheet with the specified texture coordinates
		setSpriteFromSheet(sf::IntRect(15, 80, 180, 65));
		// Move the rectangle to the appropriate cell (assuming this is related to sprite animation)
		moveTextureRect();
		// Update the enemies position variables
		if (playerX > m_Position.x)
		{
			m_Position.x = m_Position.x +
				m_Speed * elapsedTime;
			m_Sprite.setScale(1, 1);
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
			m_Sprite.setScale(-1, 1);
		}

		if (playerY < m_Position.y)
		{
			m_Position.y = m_Position.y -
				m_Speed * elapsedTime;
		}
		// Move the sprite
		m_Sprite.setPosition(m_Position);
	}

	//Function to make the enemy wander around 
	if (enemyState == EnemyState::WANDERING) 
	{// If the enemies is in wandering mode:

		if (m_Position.x < walkPoint.x + 10 &&
			m_Position.x > walkPoint.x - 10 &&
			m_Position.y < walkPoint.y + 10 &&
			m_Position.y > walkPoint.y - 10)
		{
			// If the zombie is close to the current walking point
			// Generate a new random walking point
			walkPoint = createWalkPoint();
		}
		else
		{
			// If the enemies is not close to the current walking point
			// Store the x and y coordinates of the current walking point
			float walkPoint_x = walkPoint.x;
			float walkPoint_y = walkPoint.y;
			// Store the elapsed time
			timeElapsed = elapsedTime;
			// Set the sprite from a sprite sheet with the specified texture coordinates
			setSpriteFromSheet(sf::IntRect(15, 80, 180, 65));
			// Move the rectangle to the appropriate cell
			moveTextureRect();
			// Update the enemies position variables
			if (walkPoint_x > m_Position.x)
			{
				m_Position.x = m_Position.x +
					m_Speed * elapsedTime;
				m_Sprite.setScale(1, 1);
			}
			if (walkPoint_y > m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}
			if (walkPoint_x < m_Position.x)
			{
				m_Position.x = m_Position.x -
					m_Speed * elapsedTime;
				m_Sprite.setScale(-1, 1);
			}
			if (walkPoint_y < m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}
			//move the sprite
			m_Sprite.setPosition(m_Position);
		}
	}
}

void Zombie::illusionBehaviour(Vector2f playerLocation, float elapsedTime) {
	// Get the x and y coordinates of the player
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;
	// Store the elapsed time
	timeElapsed = elapsedTime;
	setSpriteFromSheet(sf::IntRect(15, 80, 180, 65));
	//move the rectangle to the appropriate cell
	moveTextureRect();
	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;
	//Flip sprite if the is 90 angle
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
	// Get the x and y coordinates of the player
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	//its using 25 because of player being a 50x50 image , dont forget to see player size
	int x1 = playerX + 25; // center of player
	int y1 = playerY + 25; // center of player
	int x2 = m_Position.x + 25; //centre of the enemies
	int y2 = m_Position.y + 25;//centre of the enemies
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
	int tile_size = 60;
	// Extract the left-top coordinates of the texture region
	sheetCoordinate = Vector2i(textureBox.left, textureBox.top);
	// Specify the size of each sprite in the sprite sheet
	spriteSize = Vector2i(tile_size, tile_size);
	if (textureBox.width > tile_size)
	{
		// If the specified region is wider than a single sprite, determine the number of sprites horizontally
		animation_it_limit = textureBox.width / tile_size;
		horizontal = true;
	}
	else if (textureBox.height > tile_size)
	{
		// If the specified region is taller than a single sprite, determine the number of sprites vertically
		animation_it_limit = textureBox.height / tile_size;
		horizontal = false;
	}
	else
	{
		// If the specified region is too small, throw an exception
		throw std::logic_error("Animation bounding box must contain multiple sprites. setSprite(sf::IntRect )\n");
	}
	// Set the texture rectangle for the sprite based on the calculated coordinates and size
	m_Sprite.setTextureRect(sf::IntRect{ sheetCoordinate, spriteSize });
}

void Zombie::moveTextureRect()
{
	// If the animation counter exceeds the animation limit, reset it to 0
	if (ani_counter == animation_it_limit)
	{
		ani_counter = 0;
	}

	// Update the texture rectangle based on whether the animation is horizontal or vertical
	if (horizontal) {
		m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(spriteSize.x * ani_counter, 0), spriteSize));
	}
	else {
		m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(0, spriteSize.y * ani_counter), spriteSize));
	}

	// Increment the animation counter to point to the next frame
	double timePerFrame;
	timePerFrame = 1.0 / 4.0; // Assuming 4 frames per second, adjust accordingly
	animationTimer = animationTimer + timeElapsed;
	if (animationTimer > timePerFrame)
	{
		ani_counter++;
		animationTimer = 0; // Reset the animation timer
	}
}

Vector2f Zombie::createWalkPoint()
{
	// Get the current position of the enemies
	float x_pos = m_Position.x;
	float y_pos = m_Position.y;
	// Set the radius within which the zombie can randomly walk
	int radius = 400;
	bool isWater = true;

	//Generating Random Values
	std::random_device rd;
	std::uniform_int_distribution<int> dist(-radius, radius);

	//Adding Random values to current position
	x_pos += (float)dist(rd);
	y_pos += (float)dist(rd);
	// Return the new random position as a Vector2f
	return Vector2f(x_pos, y_pos);
}

void Zombie::setEnemyPosition(Vector2f location)
{
	m_Position.x = location.x;
	m_Position.y = location.y;
}


