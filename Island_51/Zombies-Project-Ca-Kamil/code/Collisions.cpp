#include "Collisions.h"


bool Collisions::checkCollisions(FloatRect hitBoxOne, FloatRect hitBoxTwo)
{
    bool objectsColliding;

    if(hitBoxOne.intersects(hitBoxTwo))
    {
        objectsColliding = true;
    }
    else{
        objectsColliding = false;
    }

    return objectsColliding;
}

Vector2f Collisions::findMidPointOfObjects(FloatRect hitBoxOne, FloatRect hitBoxTwo)
{
    //Uninitialised midpoint variables
    Vector2f midPointOfObjectOne;
    Vector2f midPointOfObjectTwo;

    //Uninitialised coordinates of objects
    Vector2f positionOfObjectOne;
    Vector2f positionOfObjectTwo;

    //Getting Top Left Coordinates of the rectangle one
    positionOfObjectOne.x = hitBoxOne.left;
    positionOfObjectOne.y = hitBoxOne.top;

    //Getting Top Left Coordinates of the rectangle one
    positionOfObjectTwo.x = hitBoxTwo.left;
    positionOfObjectTwo.y = hitBoxTwo.top;

    //Gathering Midpoints of each rectangle
    //Object 1
    midPointOfObjectOne.x = positionOfObjectOne.x + (hitBoxOne.width / 2.0f);
    midPointOfObjectOne.y = positionOfObjectOne.y + (hitBoxOne.height / 2.0f);
    //Object 2
    midPointOfObjectTwo.x = positionOfObjectTwo.x + (hitBoxTwo.width / 2.0f);
    midPointOfObjectTwo.y = positionOfObjectTwo.y + (hitBoxTwo.height / 2.0f);

    //Creating a vector2f to save the coordinates of the midpoint of between the two hitboxes
    Vector2f midPointOfObjects;

    midPointOfObjects.x = (midPointOfObjectOne.x + midPointOfObjectTwo.x) / 2;
    midPointOfObjects.y = (midPointOfObjectOne.y + midPointOfObjectTwo.y) / 2;

    return midPointOfObjects;
}
