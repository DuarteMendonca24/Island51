#include "Engine.h"
#include "Zombie.h"
#include "Pickup.h"
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
std::list<Zombie*> Engine::createHorde(int numZombies, IntRect arena)
{
	std::list<Zombie*> zombiesList;

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
		//dont spawn the blowter aka The illusionist
		int type = (rand() % 5) + 1;

		Zombie* zombie = new Zombie();
		zombie->spawn(1200, 500, type, i);
		zombiesList.push_back(zombie);




	}
	return zombiesList;
}

Zombie* Engine::createIllusions(Vector2f playerPosition)
{
	Zombie* illusion = new Zombie[4];

	// Reference Illusionist position
	int refX = playerPosition.x; // X-coordinate of the reference illusionist
	int refY = playerPosition.y;  // Y-coordinate of the reference illusionist

	// Offsets for other illusionists
	int offset = 100;  // Offset to the left

	// Top Illusionist
	illusion[0].spawn(refX - offset, refY, 0, 1);     // left Illusionist
	illusion[1].spawn(refX, refY + offset, 0, 1);     // Bottom Illusionist
	illusion[2].spawn(refX, refY - offset, 0, 1);       // top
	illusion[3].spawn(refX + offset, refY, 0, 1);      // Right Illusionist

	m_illusions = true;

	return illusion;
}

//new function created to spawn enemies when one is killed
std::list<Zombie*> Engine::createEnemies(int numZombies, Vector2f position, int type)
{
	std::list<Zombie*> zombiesList;

	int x = position.x;
	int y = position.y;
	int xOffset = 25;

	for (int i = 0; i < numZombies; i++)
	{
		Zombie* zombie = new Zombie();
		zombie->spawn(x, y, type, i);
		zombiesList.push_back(zombie);

		x += xOffset;
	}

	return zombiesList;
}


//new function created to spawn enemies when one is killed
std::list<Pickup*> Engine::createPickup(Vector2f position)
{
	std::list<Pickup*> pickupList;

	float posX = position.x;
	float posY = position.y;
	int xOffset = 25;

	Pickup* pickup = new Pickup();
	srand((int)time(0));
	int type = (rand() % 2 + 1);
	pickup->spawnPickup(type, posX, posY,1);
	pickupList.push_back(pickup);

	//posX += xOffset;


	return pickupList;
}

//changing the function to return a list
std::list<Pickup*> Engine::createResorces(int numResource, IntRect arena)
{
	std::list<Pickup*> resorceList;

	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numResource; i++)
	{

		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 3);
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


	
		srand((int)time(0));
		int type = (rand() % 3) + 3; // Generates random numbers 3, 4, or 5


		Pickup* resource = new Pickup();
		resource->spawnPickup( type,400, 500, 1.5);
		resorceList.push_back(resource);



	}
	return resorceList;
}