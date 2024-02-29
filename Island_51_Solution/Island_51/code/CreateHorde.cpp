#include "Engine.h"
#include "Zombie.h"
#include "Pickup.h"
#include <list>



//changing the function to return a list
std::list<Zombie*> Engine::createHorde(int numZombies, IntRect arena)
{ 
	// Create an empty list to store Zombie pointers
	std::list<Zombie*> zombiesList;
	// Get the number of available spawners
	int spawnersAvailable = manageLevel.getSpawnerCount();
	// Define boundaries for random spawn locations within the arena
	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;
	// Loop to create the specified number of zombies
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


		// enemies randomly 
		srand((int)time(0) * i * 2);
		//dont spawn the The illusionist
		int type = (rand() % 5) + 1;
		// Create a new Enemy object and spawn it
		Zombie* zombie = new Zombie();
		//Getting Spawner Location To Spawn Zombie
		Vector2i spawnLocation = manageLevel.getRandomSpawner();
		//sapwn the enemies
		zombie->spawn(spawnLocation.x, spawnLocation.y, type, i);
		// Add the zombie to the list
		zombiesList.push_back(zombie);
	}
	// Return the list of Zombie pointers
	return zombiesList;
}

Zombie* Engine::createIllusions(Vector2f playerPosition)
{
	// Create an array of four Zombie objects representing illusionists
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
	// Set the flag indicating that illusions are active
	m_illusions = true;

	// Return the array of Zombie pointers representing illusionists
	return illusion;
}

//new function created to spawn enemies when one is killed
std::list<Zombie*> Engine::createEnemies(int numZombies, Vector2f position, int type)
{
	// Create an empty list to store Zombie pointers
	std::list<Zombie*> zombiesList;
	// Initial position for spawning enemies
	int x = position.x;
	int y = position.y;
	// Offset between the X positions of enemies
	int xOffset = 25;
	// Loop to create the specified number of enemies
	for (int i = 0; i < numZombies; i++)
	{
		// Create a new Zombie object and spawn it at the current position
		Zombie* zombie = new Zombie();
		zombie->spawn(x, y, type, i);
		// Add the zombie to the list
		zombiesList.push_back(zombie);
		// Update the X position for the next enemy
		x += xOffset;
	}
	// Return the list of Zombie pointers representing enemies
	return zombiesList;
}


//new function created to spawn enemies when one is killed
std::list<Pickup*> Engine::createPickup(Vector2f position)
{
	// Create an empty list to store Pickup pointers
	std::list<Pickup*> pickupList;
	// Extract X and Y coordinates from the specified position
	float posX = position.x;
	float posY = position.y;
	
	// Offset between consecutive pickups along the X-axis
	int xOffset = 25;
	// Create a new Pickup object
	Pickup* pickup = new Pickup();
	// Generate a random type for the pickup (1 to 3)
	srand(static_cast<int>(time(0)));
	int type = (rand() % 3) + 1;
	// Spawn the pickup at the specified position with the random type
	if (type == 3)
	{
		pickup->spawnPickup(type, posX, posY, 2.5);

	}
	else
	{
		pickup->spawnPickup(type, posX, posY, 1);
	}
	// Add the pickup to the list
	pickupList.push_back(pickup);
	// Return the list of Pickup pointers representing the spawned pickup
	return pickupList;
}

//changing the function to return a list
std::list<Pickup*> Engine::createResorces(int numResources)
{

	// Loop to create the specified number of resources
	for (int i = 0; i < numResources; i++)
	{

		Vector2i spawnLocation = manageLevel.getRandomSpawner();
		Vector2f position = Vector2f((float)spawnLocation.x, (float)spawnLocation.y);
		
		// Getting Random position from available spawn locations
		// Generate a random type for the resource (4 to 6)
		srand(static_cast<int>(time(0)) * i);
		int type = (rand() % 3) + 4;
		// Create a new Pickup object for each resource
		Pickup* resource = new Pickup();
		resource->spawnPickup(type, position.x, position.y, 2.5);
		// Add the resource to the list
		resourceList.push_back(resource);
	}
	// Return the list of Pickup pointers representing the spawned resources
	return resourceList;
}

std::list<Pickup*> Engine::createRespawnResorces(int numResources, float positionX, float positionY,int type)
{
	// Create an empty list to store Pickup pointers
	std::list<Pickup*> resourceList;
	// Loop to create the specified number of resources
	for (int i = 0; i < numResources; i++)
	{
		// Copy the specified type and position for the resource
		int m_type = type;
		float posX = positionX;
		float posY = positionY;
		// Create a new Pickup object for each resource
		Pickup* resource = new Pickup();
		resource->spawnPickup(m_type, posX, posY, 2.5);
		// Add the resource to the list
		resourceList.push_back(resource);
	}
	// Return the list of Pickup pointers representing the spawned resources
	return resourceList;
}
