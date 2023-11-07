#pragma once
#include "Zombie.h"

using namespace sf;

int loadLevel(VertexArray& rVA);
Zombie* createHorde(int numZombies, IntRect arena);
