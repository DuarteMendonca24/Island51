#pragma once
#include "Engine.h"
#include <random>
class CaveGeneration {
private:
	//Variables for changing cave outlook
	int randomFillPercent = 47;
	bool useRandomSeed = false;

	//Size of the map generated
	static const int MAP_WIDTH = 100;
	static const int MAP_HEIGHT = 100;

	int** map;

	int mapSmoothIteration = 0;
	int spawnerIteration = 0;
	static const int MAX_SPAWNER_AMOUNT = 1000;
	Vector2i spawnerPositions[MAX_SPAWNER_AMOUNT];

public:
	//Default Constructor
	CaveGeneration();

	//Start function to the algorithm
	void Start();

	//Map Generation Function
	void GenerateMap();

	//Function to randomly fill the map with 1s and 0s
	void RandomFillMap();

	//Function to smooth out the map
	void SmoothMap();

	//Function to check neighbouring wall count
	int getSurroundingWallCount(int gridX, int gridY);

	//Function for randomly choosing a number
	int getFillValue();

	//Saves The Map in A text file
	void StoreMap();

	//Function to load the cave map
	int** loadLevel(VertexArray& rVaLevel);

	int RandomBetween(int min, int max);

	Vector2i getMapSize();


	//Vector2i* getSpawners(int& spawnerCount);



};
