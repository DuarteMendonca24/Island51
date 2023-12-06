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
	int startY = (int)(detectionZone.top / TILE_SIZE) -2;
	
	//02/12/21 changed 2 to 1 for Endx
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= manageLevel.getLevelSize().x)
		endX = manageLevel.getLevelSize().x;
	if (endY >= manageLevel.getLevelSize().y)
		endY = manageLevel.getLevelSize().y;


	// Has the character fallen out of the map?
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!This can be part of level manager!!!!!!!!!!!!!!!!!!!!!!!!
	FloatRect level(0, 0, manageLevel.getLevelSize().x * TILE_SIZE, manageLevel.getLevelSize().y * TILE_SIZE);
	//cout << "ENDX" << endX <<"\n";
	//cout << "STARTX" << startX << "\n";
	for (int x = startX; x < endX; x++)
	{	
		
		for (int y = startY; y < endY; y++)
		{
			
			// Initialize the starting position of the current block

			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

		
			// Is character colliding with a regular block i.e platform
			if (m_ArrayLevel2[y][x] == 4)
			{
				
				//cout << "COLLISION";
				if (character.getRight().intersects(block))
				{
					//cout << "COLLISION RIGHT" << "\n";
					character.stopRight(block.left);
					break;
				}
				else if (character.getLeft().intersects(block))
				{
					//cout << "COLLISION LEFT" <<"\n";
					character.stopLeft(block.left);
					break;
				}
				else if (character.getFeet().intersects(block))
				{
					//cout << "COLLISION FEET" << "\n";
					character.stopDown(block.top);
					break;
				}
				 else if (character.getHead().intersects(block))
				{
					//cout << "COLLISION HEAD" << "\n";
					character.stopUp((block.top));
					break;
				}
			}

		}

	}

	// All done, return, a new level might be required
	return reachedGoal;
}