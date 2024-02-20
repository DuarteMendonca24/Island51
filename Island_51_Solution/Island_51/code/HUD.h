#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	
	Font m_font;
	Font m_font2;
	Font m_font3;
	//Text Variables
	Text m_scoreText;
	Text m_ammoText;
	Text m_levelUpText;
	Text m_gameOverText;
	Text m_pausedText;
	Text m_waveNumberText;
	Text m_woodQuantityText;
	Text m_stoneQuantityText;
	Text m_ironQuantityText;
	Text m_soulQuantityText;
	Text m_notEnoughResourcse;
	Text m_gameruleText;
	Text m_goBackMenuText;
	Text m_highScoreText;
	Text m_numWeaponText;
	Text m_mainMenuText;
	Text m_introSkipText;
	Text m_pressText;
	Text m_hungerText;
	Text m_healthText;

	//Health bar
	RectangleShape m_healthBar;
	float m_healthBarWidth = 200;
	float m_healthBarHeight = 40;

	//Health bar background
	RectangleShape m_healthBarBackground;
	

	//Hunger Bar
	RectangleShape m_hungerBar;
	float m_hungerBarStartWidth = 200;
	float m_hungerBarHeight = 40;

	//Hunger Bar
	RectangleShape m_hungerBarBackground;
	
	
	// Craft background
	RectangleShape m_backgroundCraft;
	float m_backgroundWidth = 1000;
	float m_backgroundHeight = 1000;

	// Weapon background
	RectangleShape m_backgroundWeapon;
	float m_backgroundWeaponWidth = 360;
	float m_backgroundWeaponHeight = 80;

	// Weapon Square background
	RectangleShape m_backgroundWeaponSquare;
	RectangleShape m_backgroundWeaponSquare2;
	RectangleShape m_backgroundWeaponSquare3;
	RectangleShape m_backgroundWeaponSquare4;
	RectangleShape m_backgroundWeaponSquare5;
	float m_backgroundWeaponSquareWidth = 50;
	float m_backgroundWeaponSquareHeight = 50;

	// Press Square background
	RectangleShape m_backgroundPressSquare;
	RectangleShape m_backgroundPressSquare2;
	RectangleShape m_backgroundPressSquare3;
	float m_backgroundPressSquareWidth = 70;
	float m_backgroundPressSquareHeight = 70;

	RectangleShape darkness;
	RectangleShape m_barBackground;

public:
	Hud();
	Text getScoreText();
	Text getAmmoText();
	Text getLevelUpText();
	Text getGameOverText();
	Text getPausedText();
	Text getWaveNumberText();
	Text getWoodQuantityText();
	Text getStoneQuantityText();
	Text getIronQuantityText();
	Text getSoulQuantityText();
	Text getNotEnoughResourcse();
	Text getgameruleText();
	Text getMainMenuText();
	Text getGoBackMenuText();
	Text getHighscoreText();
	Text getNumWeaponText();
	Text getIntroText();
	Text getPressText();
	Text getHungerText();
	Text getHealthText();
	RectangleShape getHealthBar();
	RectangleShape getHealthBarBackground();
	RectangleShape getHungerBar();
	RectangleShape getHungerBarBackground();
	RectangleShape getBackgroudCraft();
	RectangleShape getBackgroudWeapon();
	RectangleShape getDarkness();
	RectangleShape getBackgroudWeaponSquare();
	RectangleShape getBackgroudWeaponSquare2();
	RectangleShape getBackgroudWeaponSquare3();
	RectangleShape getBackgroudWeaponSquare4();
	RectangleShape getBackgroudWeaponSquare5();
	RectangleShape getBarBackground();
	RectangleShape getBackgroudPressSquare();
	RectangleShape getBackgroudPressSquare2();
	RectangleShape getBackgroudPressSquare3();

	//Setter Function
	void setScoreText(String text);
	void setAmmoText(String text);
	void setWaveNumberText(String text);
	void setHealthSize(float size);
	void setHungerSize(float size);
	void setWoodQuantityText(String text);
	void setStoneQuantityText(String text);
	void setIronQuantityText(String text);
	void setSoulQuantityText(String text);
	void setDarkness(float darknessLevel);
	void setHighScore(String text);
	void setNumWeapon(int num);
	
	
	
	
	
};
