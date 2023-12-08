#include "Craft.h"
Craft::Craft()
{

}
void Craft::position(float width, float height)
{
	// load the font
	font.loadFromFile("fonts/Roboto-Light.ttf");
	select[0].setFont(font);// set the font    
	select[0].setFillColor(Color::Red);// color red in text
	select[0].setString("Wood Sword \nWoods : 3");// print the text
	select[0].setPosition(Vector2f(800, height / (MAX_NUMBER_OF_CRAFT + 1) * 1));// set the position

	select[1].setFont(font);// set the font 
	select[1].setFillColor(Color::White);// color white in text
	select[1].setString("Stone Sword \nWoods : 1	Stones : 2");// print the text
	select[1].setPosition(Vector2f(800, height / (MAX_NUMBER_OF_CRAFT + 1) * 2));// set the position

	select[2].setFont(font);// set the font 
	select[2].setFillColor(Color::White);// color white in text
	select[2].setString("Iron Sword \nWoods : 1		Irons : 2");// print the text
	select[2].setPosition(Vector2f(800, height / (MAX_NUMBER_OF_CRAFT + 1) * 3));// set the position

	select[3].setFont(font);// set the font 
	select[3].setFillColor(Color::White);// color white in text
	select[3].setString("Arrow \nWoods : 1		Stones : 1");// print the text
	select[3].setPosition(sf::Vector2f(800, height / (MAX_NUMBER_OF_CRAFT + 1) * 4));// set the position

	select[4].setFont(font);// set the font 
	select[4].setFillColor(Color::White);// color white in text
	select[4].setString("Boat \nSouls: 30");// print the text
	select[4].setPosition(sf::Vector2f(800, height / (MAX_NUMBER_OF_CRAFT + 1) * 5));// set the position

	select[5].setFont(font);// set the font 
	select[5].setFillColor(Color::White);// color white in text
	select[5].setString("Exit");// print the text
	select[5].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_CRAFT + 1) * 6));// set the position

	selectCraft = 0; //start at 0

}
// draw the menu
void Craft::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_CRAFT; i++)
	{
		window.draw(select[i]);
	}

}

// move up 
void Craft::MoveUp()
{
	if (selectCraft - 1 >= 0)
	{
		select[selectCraft].setFillColor(Color::White);
		selectCraft--;
		select[selectCraft].setFillColor(Color::Red);
	}
}

//move down
void Craft::MoveDown()
{
	if (selectCraft + 1 < MAX_NUMBER_OF_CRAFT)
	{
		select[selectCraft].setFillColor(Color::White);
		selectCraft++;
		select[selectCraft].setFillColor(Color::Red);
	}
}

//  get press or buy
int Craft::GetPressed()
{
	return selectCraft;

}