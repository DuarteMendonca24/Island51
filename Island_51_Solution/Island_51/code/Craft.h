#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
const int MAX_NUMBER_OF_CRAFT = 6; // max number of the item

class Craft
{
public:
	Craft();// shop width and height
	void position(float width, float height);
	void draw(RenderWindow& window);// draw craft menu
	void MoveUp();// move up to select
	void MoveDown();// move down
	int GetPressed();// get press 

private:
	int selectCraft; // select the craft at the current time
	Font font; // font
	Text select[MAX_NUMBER_OF_CRAFT]; // writing text 
};