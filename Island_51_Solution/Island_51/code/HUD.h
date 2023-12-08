#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	
	Font m_font;
	//Text Variables
	Text m_zombiesRemainingText;
	Text m_hiScoreText;
	Text m_scoreText;
	Text m_ammoText;
	Text m_levelUpText;
	Text m_gameOverText;
	Text m_pausedText;
	Text m_waveNumberText;
	Text m_woodQuantityText;
	Text m_stoneQuantityText;
	Text m_ironQuantityText;
	Text m_notEnoughResourcse;
	Text m_gameruleText;

	Text m_mainMenuText;
	

	//Health bar
	RectangleShape m_healthBar;
	float m_healthBarWidth = 100;
	float m_healthBarHeight = 40;

	//Hunger Bar
	RectangleShape m_hungerBar;
	float m_hungerBarStartWidth = 100;
	float m_hungerBarHeight = 40;
	
	// Shop background
	RectangleShape m_backgroundCraft;
	float m_backgroundWidth = 1000;
	float m_backgroundHeight = 1000;

	RectangleShape darkness;

public:
	Hud();
	Text getZombiesRemainingText();
	Text getHiScoreText();
	Text getScoreText();
	Text getAmmoText();
	Text getLevelUpText();
	Text getGameOverText();
	Text getPausedText();
	Text getWaveNumberText();
	Text getWoodQuantityText();
	Text getStoneQuantityText();
	Text getIronQuantityText();
	Text getNotEnoughResourcse();
	Text getgameruleText();
	Text getMainMenuText();
	RectangleShape getHealthBar();
	RectangleShape getHungerBar();
	RectangleShape getBackgroudCraft();
	RectangleShape getDarkness();

	void setZombiesRemainingText(String text);
	void setScoreText(String text);
	void setAmmoText(String text);
	void setWaveNumberText(String text);
	void setHealthSize(float size);
	void setHungerSize(float size);
	void setWoodQuantityText(String text);
	void setStoneQuantityText(String text);
	void setIronQuantityText(String text);
	void setDarkness(float darknessLevel);
	
	
	
	
	
};
