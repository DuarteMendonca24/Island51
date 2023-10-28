#pragma once
#include "Zombie.h"
#include <list>

using namespace sf;

int loadLevel(VertexArray& rVA);
//Zombie* createHorde(int numZombies, IntRect arena);
std::list<Zombie> createHorde(int numZombies, IntRect arena);
std::list<Zombie> createEnemies(int numZombies, Vector2f position, int type);
