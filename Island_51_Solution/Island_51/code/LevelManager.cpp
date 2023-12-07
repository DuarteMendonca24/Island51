#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include "LevelManager.h"
#include <iostream>

int** LevelManager::loadLevel(VertexArray& rVaLevel)
{
	// Anything we do to rVaLevel we are actually doing to background (in the main function)

	// How big is each tile/texture
	srand(time(NULL)); 
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;
	 

	// Load the appropriate level from a text file
	 
	//Player start position
	m_StartPosition.x = 500;
	m_StartPosition.y = 500; 
	ifstream inputFile(MAP_NAME);
	ofstream outputFile(NEW_MAP_NAME);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	int** arrayLevel = new int* [m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int y = 0;
	while (inputFile >> row)
	{
		for (int x = 0; x < row.length(); x++) {

			char val = row[x];

			//Check if tile is a resource or a grass tile
			if (val == '6')
			{
				val = randomiseTile(val);
			}
			else if (val == '1')
			{
				val = randomiseGrassTile(val);
				//Making Spawner
				if (current_spawn_block_counter != MAX_SPAWNERS_AVAILABLE && val == '3')
				{
					int randomNum = RandomBetween(1, 5);
					if (randomNum == 1)
					{
						createNewSpawner(x, y);
					}
				}
				
			}
			cout << val << " ";
			arrayLevel[y][x] = atoi(&val);
			outputFile << val;

		}
		outputFile << "\n";
		y++;
	}

	// close the input file
	inputFile.close();

	// close the output file
	outputFile.close();
	

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = 
				Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 1].position = 
				Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 2].position = 
				Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 3].position = 
				Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords = 
				Vector2f(0, 0 + verticalOffset);

			rVaLevel[currentVertex + 1].texCoords = 
				Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVaLevel[currentVertex + 2].texCoords = 
				Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVaLevel[currentVertex + 3].texCoords = 
				Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}
	//Setting main 2d array to equal the constructed array
	m_ArrayLevel = arrayLevel; 

	//return TILE_SIZE;
	return arrayLevel;
}

Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}

int LevelManager::getTileSize(){
	return TILE_SIZE;
}

int LevelManager::getCurrentLevel()
{
	//return m_CurrentLevel;
	return 1;
}

float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;

}
Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}



char LevelManager::randomiseTile(char tile)
{
	char newTile;
	int resourceNum = RandomBetween(1, 3);;
	/*
		Resources Generated:
		1. Wood = 7
		2. Iron = 8
		3. Stone = 9
	*/
	if (resourceNum == 1)
	{
		newTile = '7';
	}
	else if (resourceNum == 2)
	{
		newTile = '8';
	}
	else
	{
		newTile = '9';
	}


	return newTile;
}

char LevelManager::randomiseGrassTile(char tile)
{
	char newTile;
	int grassNum = RandomBetween(1,3);
	/*
		Resources Generated:
		1. Variation 1 = 1
		2. Variation 2 = 2
		3. Variation 3 = 3
	*/
	if (grassNum == 1)
	{
		newTile = '1';
	}
	else if (grassNum == 2)
	{
		newTile = '2';
	}
	else
	{
		newTile = '3';
	}

	return newTile;
}

void LevelManager::createNewSpawner(int x, int y)
{
	int randomNum = RandomBetween(1, 150);
	int coords_x = x * TILE_SIZE + randomNum;
	randomNum = RandomBetween(1, 150);
	int coords_y = y * TILE_SIZE + randomNum;

	Vector2i spawnerCoords = Vector2i(coords_x, coords_y);
	m_SpawnPoisitons[current_spawn_block_counter] = spawnerCoords;
	current_spawn_block_counter++;
}

Vector2i LevelManager::getSpawner(int i)
{
	return m_SpawnPoisitons[i];
}

int LevelManager::getSpawnerCount()
{
	return current_spawn_block_counter;
}

int LevelManager::RandomBetween(int min, int max)
{
	//Generating Random Number 
	std::random_device rd;
	std::uniform_int_distribution<int> dist(min, max);

	return dist(rd);
}

int** LevelManager::getArray()
{
	return m_ArrayLevel;
}