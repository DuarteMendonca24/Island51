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
	select[0].setPosition(Vector2f(800, (height / (MAX_NUMBER_OF_CRAFT + 1) * 0)+30));// set the position
	select[0].setOutlineThickness(2);
	select[0].setOutlineColor(Color::Black);
	select[0].setCharacterSize(50);

	select[1].setFont(font);// set the font 
	select[1].setFillColor(Color::White);// color white in text
	select[1].setString("Stone Sword \nWoods : 1	Stones : 2");// print the text
	select[1].setPosition(Vector2f(800, (height / (MAX_NUMBER_OF_CRAFT + 1) * 1) + 30));// set the position
	select[1].setOutlineThickness(2);
	select[1].setOutlineColor(Color::Black);
	select[1].setCharacterSize(50);

	select[2].setFont(font);// set the font 
	select[2].setFillColor(Color::White);// color white in text
	select[2].setString("Iron Sword \nWoods : 1		Irons : 2");// print the text
	select[2].setPosition(Vector2f(800, (height / (MAX_NUMBER_OF_CRAFT + 1) * 2) + 30));// set the position
	select[2].setOutlineThickness(2);
	select[2].setOutlineColor(Color::Black);
	select[2].setCharacterSize(50);

	select[3].setFont(font);// set the font 
	select[3].setFillColor(Color::White);// color white in text
	select[3].setString("Arrow \nWoods : 1		Stones : 1");// print the text
	select[3].setPosition(sf::Vector2f(800, (height / (MAX_NUMBER_OF_CRAFT + 1) * 3) + 30));// set the position
	select[3].setOutlineThickness(2);
	select[3].setOutlineColor(Color::Black);
	select[3].setCharacterSize(50);

	select[4].setFont(font);// set the font 
	select[4].setFillColor(Color::Yellow);// color white in text
	select[4].setString("Boat \nSouls: 30");// print the text
	select[4].setPosition(sf::Vector2f(800, (height / (MAX_NUMBER_OF_CRAFT + 1) * 4) + 30));// set the position
	select[4].setOutlineThickness(2);
	select[4].setOutlineColor(Color::Black);
	select[4].setCharacterSize(50);

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
		if (selectCraft == MAX_NUMBER_OF_CRAFT)
		{
			select[selectCraft].setFillColor(Color::Yellow);
		}
		else
		{
			select[selectCraft].setFillColor(Color::White);
		}
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