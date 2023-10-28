#pragma once
//Including All Header files and libraries needed
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <iostream>
#include <assert.h>
#include "Zombie.h"
#include "LevelManager.h"

using namespace sf;

class Engine
{
public:
    int loadLevel(VertexArray& rVA);

    std::list<Zombie> createHorde(int numZombies, IntRect arena);
    std::list<Zombie> createEnemies(int numZombies, Vector2f position, int type);

    Engine();
    void run();


private:
    Time m_GameTimeTotal;

    // Update Function For All Classes
    void update(float dtAsSeconds);




};