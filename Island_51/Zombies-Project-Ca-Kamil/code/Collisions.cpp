#include "Collisions.h"


bool Collisions::checkCollisions(FloatRect objectOne, FloatRect objectTwo)
{
    bool objectsColliding;

    if(objectOne.intersects(objectTwo))
    {
        objectsColliding = true;
    }
    else{
        objectsColliding = false;
    }

    return objectsColliding;
}

Vector2f Collisions::findMidPointOfObjects(FloatRect objectOne, FloatRect objectTwo)
{
    //Uninitialised midpoint variables
    Vector2f midPointOfObjectOne;
    Vector2f midPointOfObjectTwo;

    //Uninitialised coordinates of objects
    Vector2f positionOfObjectOne;
    Vector2f positionOfObjectTwo;

    //Getting Top Left Coordinates of the rectangle one
    positionOfObjectOne.x = objectOne.left;
    positionOfObjectOne.y = objectOne.top;

    //Getting Top Left Coordinates of the rectangle one
    positionOfObjectTwo.x = objectTwo.left;
    positionOfObjectTwo.y = objectTwo.top;

    //Gathering Midpoints of each rectangle
    //Object 1
    midPointOfObjectOne.x = positionOfObjectOne.x + (objectOne.width / 2.0f);
    midPointOfObjectOne.y = positionOfObjectOne.y + (objectOne.height / 2.0f);
    //Object 2
    midPointOfObjectTwo.x = positionOfObjectTwo.x + (objectTwo.width / 2.0f);
    midPointOfObjectTwo.y = positionOfObjectTwo.y + (objectTwo.height / 2.0f);

    Vector2f midPointOfObjects;

    midPointOfObjects.x = (midPointOfObjectOne.x + midPointOfObjectTwo.x) / 2;
    midPointOfObjects.y = (midPointOfObjectOne.y + midPointOfObjectTwo.y) / 2;

    return midPointOfObjects;
}