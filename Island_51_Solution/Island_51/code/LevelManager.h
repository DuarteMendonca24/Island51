#pragma once

#include <SFML/Graphics.hpp>
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
	//int** m_ArrayLevel = NULL;

public:

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
	 
};
