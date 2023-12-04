#include "HUD.h"
#include <sstream>

Hud::Hud(){

	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//load the font
	m_font.loadFromFile("fonts/zombiecontrol.ttf");

	// Paused
	m_pausedText.setFont(m_font);
	m_pausedText.setCharacterSize(155);
	m_pausedText.setFillColor(Color::White);
	m_pausedText.setPosition(400, 400);
	m_pausedText.setString("Press Enter \nto continue");

	// Game Over
	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(125);
	m_gameOverText.setFillColor(Color::White);
	m_gameOverText.setPosition(250, 850);
	m_gameOverText.setString("Press Enter to play");

	// Levelling up
	m_levelUpText.setFont(m_font);
	m_levelUpText.setCharacterSize(80);
	m_levelUpText.setFillColor(Color::White);
	m_levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increase rate of fire || 300 points" <<
		"\n2- Increase clip size by x1.5 || 300 points" <<
		"\n3- Increase max health by 20HP || 300 points" <<
		"\n4- Increase run speed by x1.4 || 300 points" <<
		"\n5- More Pick Ups || 300 points" <<
		"\n6- SMG Weapon Upgrade || 1000 points" <<
		"\n7- Refill ammo + health (max)" <<
		"\n8- RailGun Weapon Upgrade || 4000 points"
		"\nSpace to Play Game";
	m_levelUpText.setString(levelUpStream.str());

	// Ammo
	m_ammoText.setFont(m_font);
	m_ammoText.setCharacterSize(55);
	m_ammoText.setFillColor(Color::White);
	m_ammoText.setPosition(200, 980);

	// Score
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(55);
	m_scoreText.setFillColor(Color::White);
	m_scoreText.setPosition(20, 0);

	// wave
	m_waveNumberText.setFont(m_font);
	m_waveNumberText.setCharacterSize(55);
	m_waveNumberText.setFillColor(Color::White);
	m_waveNumberText.setPosition(800, 0);

	// wave
	m_zombiesRemainingText.setFont(m_font);
	m_zombiesRemainingText.setCharacterSize(55);
	m_zombiesRemainingText.setFillColor(Color::White);
	m_zombiesRemainingText.setPosition(1500, 0);

	m_healthBar.setSize(Vector2f(m_healthBarWidth, m_healthBarHeight));
	m_healthBar.setFillColor(Color::Red);
	m_healthBar.setPosition(450, 980); 

	m_hungerBar.setFillColor(Color::Red);
	m_hungerBar.setPosition((190 / 2) - m_hungerBarStartWidth / 2, 100);

	//wood quantity
	m_woodQuantityText.setFont(m_font);
	m_woodQuantityText.setCharacterSize(50);
	m_woodQuantityText.setFillColor(Color::White);
	m_woodQuantityText.setPosition(110, 330);
	m_woodQuantityText.setString("x 0");

	//stone quantity
	m_stoneQuantityText.setFont(m_font);
	m_stoneQuantityText.setCharacterSize(50);
	m_stoneQuantityText.setFillColor(Color::White);
	m_stoneQuantityText.setPosition(110, 415);
	m_stoneQuantityText.setString("x 0");

	//iron quantity
	m_ironQuantityText.setFont(m_font);
	m_ironQuantityText.setCharacterSize(50);
	m_ironQuantityText.setFillColor(Color::White);
	m_ironQuantityText.setPosition(110, 515);
	m_ironQuantityText.setString("x 0");

	//Background Craft
	m_backgroundCraft.setSize(Vector2f(m_backgroundWidth, m_backgroundHeight));
	m_backgroundCraft.setFillColor(Color::Blue);
	m_backgroundCraft.setPosition(600, 0);

	m_notEnoughResourse.setFont(m_font);
	m_notEnoughResourse.setCharacterSize(50);
	m_notEnoughResourse.setFillColor(Color::Yellow);
	m_notEnoughResourse.setPosition(500, 500);
	m_notEnoughResourse.setString("You don't have Sufficient Resources to Craft ");

}



Text Hud::getZombiesRemainingText() {

	return m_zombiesRemainingText;
}


Text Hud::getHiScoreText() {

	return m_hiScoreText;
}

Text Hud::getScoreText() {

	return m_scoreText;
}

Text Hud::getAmmoText() {

	return m_ammoText;
}

Text Hud::getLevelUpText() {

	return m_levelUpText;
}

Text Hud::getGameOverText() {

	return m_gameOverText;
}

Text Hud::getPausedText() {

	return m_pausedText;
}

Text Hud::getWoodQuantityText() {

	return m_woodQuantityText;
}

Text Hud::getStoneQuantityText() {

	return m_stoneQuantityText;
}


Text Hud::getIronQuantityText() {

	return m_ironQuantityText;
}


Text Hud::getWaveNumberText() {

	return m_waveNumberText;
}

Text Hud::getNotEnoughResourse() {

	return m_notEnoughResourse;
}

RectangleShape Hud::getHealthBar() {

	return m_healthBar;
}

RectangleShape Hud::getHungerBar() {

	return m_hungerBar;
}

RectangleShape Hud::getBackgroudCraft() {
	return m_backgroundCraft;
}

void Hud::setZombiesRemainingText(String text) {

	m_zombiesRemainingText.setString(text);
	
}

void Hud::setScoreText(String text) {

	m_scoreText.setString(text);

}

void Hud::setAmmoText(String text) {

	m_ammoText.setString(text);
}

void Hud::setWaveNumberText(String text) {

	m_waveNumberText.setString(text);
}

void Hud::setHealthSize(float size)
{
	m_healthBar.setSize(Vector2f(size, m_healthBar.getSize().y));
}

void Hud::setHungerSize(float size)
{
	m_hungerBar.setSize(Vector2f(size, m_healthBar.getSize().y));
}


void Hud::setWoodQuantityText(String text) {

	m_woodQuantityText.setString(text);
}

void Hud::setStoneQuantityText(String text) {

	m_stoneQuantityText.setString(text);
}


void Hud::setIronQuantityText(String text) {

	m_ironQuantityText.setString(text);
}

