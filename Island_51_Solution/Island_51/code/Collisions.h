#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Collisions
{
private:

public:

//Checking collisions between two hitboxes
bool checkCollisions(FloatRect hitBoxOne, FloatRect hitBoxTwo);

//Finding MidPoint of two rectangles returning the point
Vector2f findMidPointOfObjects(FloatRect hitBoxOne, FloatRect hitBoxTwo);

};