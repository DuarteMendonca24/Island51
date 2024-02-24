#include "CaveGeneration.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
std::ostream;
CaveGeneration::CaveGeneration()
{
	map = new int* [MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; ++i)
	{
		// Add a new array into each array element
		map[i] = new int[MAP_HEIGHT];
	}
}
//Start function to the algorithm
void CaveGeneration::Start() {
	GenerateMap();
	//VisualizeMap();
}

//Map Generation Function
void CaveGeneration::GenerateMap() {
	RandomFillMap();
	
	for (int i = 0; i != 10; ++i)
	{
		SmoothMap();
		
	}
	StoreMap();
}

void CaveGeneration::SmoothMap()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			int neighbourWallTiles = getSurroundingWallCount(x, y);

			if (neighbourWallTiles > 4)
			{
				map[x][y] = 1;
			}
			else if (neighbourWallTiles < 4)
			{
				map[x][y] = 0;
			}
		}
	}
}

int CaveGeneration::getSurroundingWallCount(int gridX, int gridY)
{
	int wallCount = 0;
	for (int neighbourX = gridX - 1; neighbourX <= gridX + 1; neighbourX++)
	{
		for (int neighbourY = gridY - 1; neighbourY <= gridY + 1; neighbourY++)
		{
			if (gridX != 0 && gridX != MAP_WIDTH - 1 && gridY != 0 && gridY != MAP_HEIGHT - 1)
			{
				if (neighbourX >= 0 && neighbourX < MAP_WIDTH && neighbourY >= 0 && neighbourY < MAP_HEIGHT) {

					if (neighbourX != gridX || neighbourY != gridY)
					{
						wallCount += map[neighbourX][neighbourY];
					}
				}
				else
				{
					wallCount++;
				}
			}
			
		}
	}
	return wallCount;
}

//Function to randomly fill the map with 1s and 0s
void CaveGeneration::RandomFillMap() {
	ofstream outputFile("map/CAVE_MAP.txt");
	
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			//Making Borders always be a cave wall
			if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
			{
				map[x][y] = 0;
			}
			else if ((x >= 10) && (y >= 10) && (x < 20) && (y < 20))
			{
				map[x][y] = 1;
			}
			else
			{
				map[x][y] = getFillValue();
			}
		}
	}
}



int CaveGeneration::getFillValue()
{
	int returnValue;
	//Generating Random Number 
	std::random_device rd;

	std::uniform_int_distribution<int> dist(0, 100);

	if (dist(rd) < randomFillPercent)
	{
		returnValue = 0;
	}
	else
	{
		returnValue = 1;
	}

	return returnValue;
}

void CaveGeneration::StoreMap()
{
	//Concaconate String
	std::stringstream ss_FileName;
	ss_FileName << "map/CAVE_MAP" << mapSmoothIteration << ".txt";
	string fileName = ss_FileName.str();

	//Increment Iterator
	mapSmoothIteration++;

	//Save Map into File
	ofstream outputFile(fileName);
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			outputFile << map[x][y];
		}
		outputFile << "\n";
	}
	outputFile.close();
}

int** CaveGeneration::loadLevel(VertexArray& rVaLevel)
{
	
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++) {

			//Check if tile is a resource or a ground tile
			if (map[x][y] == 1){
				map[x][y] = RandomBetween(1, 3);
			}

		}
		y++;
	}



	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVaLevel.resize(MAP_WIDTH * MAP_HEIGHT * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
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
			int verticalOffset = map[y][x] * TILE_SIZE;

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

	return map;
}

int CaveGeneration::RandomBetween(int min, int max)
{
	//Generating Random Number 
	std::random_device rd;
	std::uniform_int_distribution<int> dist(min, max);

	return dist(rd);
}

Vector2i CaveGeneration::getMapSize() {
	Vector2i mapSize = Vector2i(MAP_WIDTH, MAP_HEIGHT);

	return mapSize;
}


