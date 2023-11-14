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
	//Health bar
	RectangleShape m_healthBar;
	float m_healthBarWidth = 100;
	float m_healthBarHeight = 40;


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
	RectangleShape getHealthBar();

	void setZombiesRemainingText(String text);
	void setScoreText(String text);
	void setAmmoText(String text);
	void setWaveNumberText(String text);
	void setHealthSize(float size);
	
	
	
	
	
};
