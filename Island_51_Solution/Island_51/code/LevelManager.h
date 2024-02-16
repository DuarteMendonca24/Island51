#pragma once

#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;
using namespace std;


class LevelManager
{
private:
	Vector2i m_LevelSize;
	Vector2f m_StartPosition;
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	const string MAP_NAME = "map/Island_51_PreGen.txt";
	const string NEW_MAP_NAME = "map/Island_51_PostGen.txt";
	const int MAX_RESOURCE_NUM = 3;
	const int RESOURCE_VARIATIONS = 2;
	
	int** m_ArrayLevel;

public:

	static const int MAX_SPAWNERS_AVAILABLE = 1000;
	int current_spawn_block_counter = 0;
	Vector2i m_SpawnPoisitons[MAX_SPAWNERS_AVAILABLE];
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	float getTimeLimit();

	Vector2f getStartPosition();

	int** loadLevel(VertexArray& rVaLevel);
	
	Vector2i getLevelSize();

	int getTileSize();

	int getCurrentLevel();


	char randomiseTile(char tile);

	char randomiseGrassTile(char tile);

	void createNewSpawner(int x, int y);
	
	Vector2i getSpawner(int i);

	int getSpawnerCount();

	int RandomBetween(int min, int max);

	int** getArray();
	Vector2i getRandomSpawner();

};
