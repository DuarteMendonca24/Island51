#include "Engine.h"
#include "Zombie.h"
#include <list>

/*Zombie* createHorde(int numZombies, IntRect arena)
{
	Zombie* zombies = new Zombie[numZombies];

	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numZombies; i++)
	{

		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;

		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;

		case 2:
			// top
			x = (rand() % maxX) + minX;
			y = minY;
			break;

		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		if (numZombies == 1)
		{
			//Spawn Boss Enemy
			zombies[i].spawnBoss(x, y);
		}
		else
		{
			// Bloater, crawler, runner, rat
			srand((int)time(0) * i * 2);
			int type = (rand() % 4);

			// Spawn the new zombie into the array
			zombies[i].spawn(x, y, type, i);
		}
		

	}
	return zombies;
}*/

//changing the function to return a list
std::list<Zombie> Engine::createHorde(int numZombies, IntRect arena)
{
	std::list<Zombie> zombiesList;

	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numZombies; i++)
	{

		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;

		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;

		case 2:
			// top
			x = (rand() % maxX) + minX;
			y = minY;
			break;

		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		
		// Bloater, crawler, runner, rat
		srand((int)time(0) * i * 2);
		int type = (rand() % 4);

		Zombie zombie;
		zombie.spawn(x, y, type, i);
		zombiesList.push_back(zombie);
		


	}
	return zombiesList;
}



//new function created to spawn enemies when one is killed
std::list<Zombie> Engine::createEnemies(int numZombies, Vector2f position, int type)
{
	std::list<Zombie> zombiesList;

	int x = position.x;
	int y = position.y;

	for (int i = 0; i < numZombies; i++)
	{
		Zombie zombie;
		zombie.spawn(x, y, type, i);
		zombiesList.push_back(zombie);
	}

	return zombiesList;
}
