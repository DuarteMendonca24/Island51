#include "Engine.h"
using namespace std;
#include <iostream>;
bool Engine::detectCollisions(Player& character)
{

	bool reachedGoal = false;
	// Make a rect for all his parts
	FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around Enemy to detect collisions
//	Apr 29th changed zone
// 21 11 2022 introducded rounding to allow for small differences
	int startX = (int)(detectionZone.left / TILE_SIZE) - 3;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 2;

	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	if (playerInsideCave)
	{
		if (startX < 0)startX = 0;
		if (startY < 0)startY = 0;
		if (endX >= 100 * TILE_SIZE)
			endX = 100 * TILE_SIZE;
		if (endY >= 100 * TILE_SIZE)
			endY = 100 * TILE_SIZE;
	}
	else
	{
		if (startX < 0)startX = 0;
		if (startY < 0)startY = 0;
		if (endX >= manageLevel.getLevelSize().x)
			endX = manageLevel.getLevelSize().x;
		if (endY >= manageLevel.getLevelSize().y)
			endY = manageLevel.getLevelSize().y;
	}
	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array



	// Has the character fallen out of the map?
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!This can be part of level manager!!!!!!!!!!!!!!!!!!!!!!!!
	FloatRect level(0, 0, manageLevel.getLevelSize().x * TILE_SIZE, manageLevel.getLevelSize().y * TILE_SIZE);
	//cout << "ENDX" << endX <<"\n";
	//cout << "STARTX" << startX << "\n";

	/*
		Calculating Player Location on the map
	*/
	Vector2f characterLocation = character.getCenter();
	float locationX = characterLocation.x;
	float locationY = characterLocation.y;
	int playerLocationXInt = (int)locationX / TILE_SIZE;
	int playerLocationYInt = (int)locationY / TILE_SIZE;
	//cout << playerLocationXInt << "   " << playerLocationYInt << endl; // Which tile is the player on currently?
	bool* neighbours = checkNeighbours(playerLocationXInt, playerLocationYInt);

	if (neighbours[0])
	{
		character.stopLeft();
		leftTime.RestartTimer();
	}

	if (neighbours[1])
	{
		character.stopRight();
		rightTime.RestartTimer();
	}

	if (neighbours[2])
	{
		character.stopDown();
		feetTime.RestartTimer();
	}

	if (neighbours[3])
	{
		character.stopUp();
		headTime.RestartTimer();
	}
	



	// All done, return, a new level might be required
	return reachedGoal;
}

bool* Engine::checkNeighbours(int posX, int posY)
{
	//BOOLEAN ARRAY 
	//INDEX 0 - LEFT
	//INDEX 1 - RIGHT
	//INDEX 2 - FEET
	//INDEX 3 - HEAD
	bool neighbourCheck[4] = { false,false,false,false };
	int leftX = posX - 1;
	int rightX = posX + 1;
	int feetY = posY + 1;
	int headY = posY - 1;
	//m_ArrayLevel1
	if (playerInsideCave)
	{
		if (m_ArrayLevel1[posY][leftX] < 1)
		{
			//Left
			neighbourCheck[0] = true;
		}

		if (m_ArrayLevel1[posY][rightX] < 1)
		{
			//Right
			neighbourCheck[1] = true;
		}

		if (m_ArrayLevel1[feetY][posX] < 1)
		{
			//Feet
			neighbourCheck[2] = true;
		}

		if (m_ArrayLevel1[headY][posX] < 1)
		{
			//Head
			neighbourCheck[3] = true;
		}
	}
	else if(!playerInsideCave)
	{
		if (m_ArrayLevel2[posY][leftX] < 1)
		{
			//Left
			neighbourCheck[0] = true;
		}

		if (m_ArrayLevel2[posY][rightX] < 1)
		{
			//Right
			neighbourCheck[1] = true;
		}

		if (m_ArrayLevel2[feetY][posX] < 1)
		{
			//Feet
			neighbourCheck[2] = true;
		}

		if (m_ArrayLevel2[headY][posX] < 1)
		{
			//Head
			neighbourCheck[3] = true;
		}
	}

	

	return neighbourCheck;
}