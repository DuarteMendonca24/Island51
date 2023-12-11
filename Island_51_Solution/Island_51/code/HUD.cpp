#include "HUD.h"
#include <sstream>

Hud::Hud(){

	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	

	//load the font
	m_font.loadFromFile("fonts/zombiecontrol.ttf");
	m_font2.loadFromFile("fonts/Roboto-Light.ttf");
	m_font3.loadFromFile("fonts/ammo.otf");


	//Intro Text
	m_introSkipText.setFont(m_font);
	m_introSkipText.setCharacterSize(30);
	m_introSkipText.setFillColor(Color::White);
	m_introSkipText.setPosition(Vector2f(resolution.x - 300, resolution.y - 100));
	m_introSkipText.setString("ENTER to skip");

	// Paused
	m_pausedText.setFont(m_font);
	m_pausedText.setCharacterSize(155);
	m_pausedText.setFillColor(Color::White);
	m_pausedText.setPosition(400, 400);
	m_pausedText.setString("Press Enter \nto continue");

	// Game Over
	m_gameOverText.setFont(m_font);
	m_gameOverText.setCharacterSize(125);
	m_gameOverText.setFillColor(Color::Color(255,50,0));
	m_gameOverText.setPosition(250, 850);
	m_gameOverText.setString("YOU DIED, PRESS SPACE TO CONTINUE");

	// Levelling up
	m_levelUpText.setFont(m_font);
	m_levelUpText.setCharacterSize(80);
	m_levelUpText.setFillColor(Color::White);
	m_levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"Island 51" <<
		"Space to Play Game" <<
		"\n Press this button G to view the Rule";
	m_levelUpText.setString(levelUpStream.str());


	// Rule of the Survival game
	m_gameruleText.setFont(m_font);
	m_gameruleText.setCharacterSize(40);
	m_gameruleText.setFillColor(Color::White);
	m_gameruleText.setPosition(150, 250);
	std::stringstream ruleStream;
	ruleStream <<
		"Here is the rule of the Survival game " <<
		"\n1- After killing the Enemy they will drop item " <<
		"\n2- The player can create new wepons using the craft system" <<
		"\n3- If the hunger reach 0, the player heath bar will start decreasing" <<
		"\n4- When the player dies, they can continue from where they died but their score is set to 0 " <<
		"\n5- Enemies sometimes drop their soul which is needed to create the boat to escape " <<
		"\n Credits: Kamil, Duarte, Jeff and Emmanuel "<<
		"\n" <<
		"\n Controls:"<<
		"\n WASD - Move Around"<<
		"\n Q - Open Crafting" <<
		"\n Left Shift - Confirm Crafting" <<
		"\n TAB - Open Inventory" <<
		"\n Left Mouse Button - Shoot/Punch" <<
		"\n 1-5 - Select Weapon";
		
	m_gameruleText.setString(ruleStream.str());

	// Ammo
	m_ammoText.setFont(m_font3);
	m_ammoText.setCharacterSize(20);
	m_ammoText.setFillColor(Color::White);
	m_ammoText.setPosition(200, 1000);

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


	m_healthBar.setSize(Vector2f(m_healthBarWidth, m_healthBarHeight));
	m_healthBar.setFillColor(Color::Red);
	m_healthBar.setPosition(resolution.x - m_healthBarWidth - 5, resolution.y - m_healthBarHeight - 5);

	//background of health bar
	m_healthBarBackground.setSize(Vector2f(m_healthBarWidth, m_healthBarHeight));
	m_healthBarBackground.setFillColor(Color(52, 43, 55));
	m_healthBarBackground.setPosition(resolution.x - m_healthBarWidth - 5, resolution.y - m_healthBarHeight - 5);


	m_hungerBar.setSize(Vector2f(m_hungerBarStartWidth,m_hungerBarHeight));
	m_hungerBar.setFillColor(Color(205, 133, 63));
	m_hungerBar.setPosition(resolution.x - m_hungerBarStartWidth - 5, resolution.y - m_hungerBarHeight - m_healthBarHeight - 5);


	//background of hunger bar
	m_hungerBarBackground.setSize(Vector2f(m_hungerBarStartWidth, m_hungerBarHeight));
	m_hungerBarBackground.setFillColor(Color(52, 43, 55));
	m_hungerBarBackground.setPosition(resolution.x - m_hungerBarStartWidth - 5, resolution.y - m_hungerBarHeight - m_healthBarHeight - 5);

	//background of weapon
	m_backgroundWeapon.setSize(Vector2f(m_backgroundWeaponWidth, m_backgroundWeaponHeight));
	m_backgroundWeapon.setFillColor(Color(52, 43, 55));
	m_backgroundWeapon.setPosition(resolution.x / 2 + 350, resolution.y - 100);
	m_backgroundWeapon.setFillColor(Color(52, 43, 55, 150));
	m_backgroundWeapon.setPosition(resolution.x / 2 - 110, resolution.y - m_backgroundWeaponHeight - 5);

	//background of weapon square
	m_backgroundWeaponSquare.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare.setPosition(resolution.x / 2 + 360, resolution.y - 85);

	m_backgroundWeaponSquare2.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare2.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare2.setPosition(resolution.x / 2 + 430, resolution.y - 85);
	
	m_backgroundWeaponSquare3.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare3.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare3.setPosition(resolution.x / 2 + 500, resolution.y - 85);

	m_backgroundWeaponSquare4.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare4.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare4.setPosition(resolution.x / 2 + 570, resolution.y - 85);

	m_backgroundWeaponSquare5.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare5.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare5.setPosition(resolution.x / 2 + 640, resolution.y - 85);
	m_backgroundWeaponSquare.setPosition(resolution.x / 2 - 100, resolution.y - m_backgroundWeaponSquareHeight - 20);

	m_backgroundWeaponSquare2.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare2.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare2.setPosition(resolution.x / 2 - 30, resolution.y - m_backgroundWeaponSquareHeight - 20);
	
	m_backgroundWeaponSquare3.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare3.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare3.setPosition(resolution.x / 2 + 40, resolution.y - m_backgroundWeaponSquareHeight - 20);

	m_backgroundWeaponSquare4.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare4.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare4.setPosition(resolution.x / 2 + 110, resolution.y - m_backgroundWeaponSquareHeight - 20);

	m_backgroundWeaponSquare5.setSize(Vector2f(m_backgroundWeaponSquareWidth, m_backgroundWeaponSquareHeight));
	m_backgroundWeaponSquare5.setFillColor(Color(126, 132, 247));
	m_backgroundWeaponSquare5.setPosition(resolution.x / 2 + 180, resolution.y - m_backgroundWeaponSquareHeight - 20);
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

	//soul quantity
	m_soulQuantityText.setFont(m_font);
	m_soulQuantityText.setCharacterSize(50);
	m_soulQuantityText.setFillColor(Color::White);
	m_soulQuantityText.setPosition(110, 615);
	m_soulQuantityText.setString("x 0");

	//Background Craft
	m_backgroundCraft.setSize(Vector2f(m_backgroundWidth, m_backgroundHeight));
	m_backgroundCraft.setFillColor(Color::Color(0,0,255,1));
	m_backgroundCraft.setPosition(490, 0);

	m_notEnoughResourcse.setFont(m_font2);
	m_notEnoughResourcse.setCharacterSize(50);
	m_notEnoughResourcse.setFillColor(Color::Yellow);
	m_notEnoughResourcse.setPosition(500, 500);
	m_notEnoughResourcse.setString("You don't have Sufficient Resources to Craft ");

	//darkness
	darkness.setFillColor(Color::Color(0,0,0, 100));
	darkness.setOrigin(Vector2f(0, 0));
	darkness.setSize(Vector2f(3000.0f,3000.0f));

	//main menu text
	m_mainMenuText.setFont(m_font);
	m_mainMenuText.setCharacterSize(50);
	m_mainMenuText.setOutlineColor(Color::Black);
	m_mainMenuText.setOutlineThickness(3);
	m_mainMenuText.setFillColor(Color::White);
	m_mainMenuText.setPosition(500, 60);
	std::stringstream mainMenuStream;
	mainMenuStream <<
		"ISLAND 51" <<
		"\n\n\n1 - Play Game" <<
		"\n\n\n2 - Rules & Controls " <<
		"\n\n\n3 - High Scores " <<
		"\n\n\n4 - Exit";
	m_mainMenuText.setString(mainMenuStream.str());

	//instruction to tell the player what key to press to go back to menu
	m_goBackMenuText.setFont(m_font);
	m_goBackMenuText.setCharacterSize(50);
	m_goBackMenuText.setFillColor(Color::White);
	m_goBackMenuText.setPosition(10, 10);
	m_goBackMenuText.setString("Press Escape to go back to main menu");

	//instruction to tell the player what key to press to go back to menu
	m_highScoreText.setFont(m_font);
	m_highScoreText.setCharacterSize(50);
	m_highScoreText.setFillColor(Color::White);
	m_highScoreText.setPosition(700, 60);

	//Numberes of weapons
	m_numWeaponText.setFont(m_font2);
	m_numWeaponText.setCharacterSize(20);
	m_numWeaponText.setFillColor(Color::White);
	m_numWeaponText.setPosition(resolution.x / 2 + 350, resolution.y - 100);
	m_numWeaponText.setPosition(resolution.x / 2 - 110, resolution.y - m_backgroundWeaponHeight - 5);
	m_numWeaponText.setString("1			2			3			4			5");

	//Bar Background
	m_barBackground.setFillColor(Color::Color(0, 0, 0, 70)); //Transparent Black
	Vector2f barBackgroundSize = Vector2f((float)resolution.x / 8.0f,(float) resolution.y / 8.0f);
	m_barBackground.setSize(barBackgroundSize);
	m_barBackground.setPosition(resolution.x - barBackgroundSize.x, resolution.y - barBackgroundSize.y);
}

/*
	GETTER FUNCTIONS
*/


Text Hud::getScoreText() {

	return m_scoreText;
}

Text Hud::getAmmoText() {

	return m_ammoText;
}

Text Hud::getLevelUpText() {

	return m_levelUpText; 
}

Text Hud::getgameruleText() {

	return m_gameruleText;
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

Text Hud::getSoulQuantityText() {

	return m_soulQuantityText;
}

Text Hud::getWaveNumberText() {

	return m_waveNumberText;
}

Text Hud::getNotEnoughResourcse() {

	return m_notEnoughResourcse;
}

Text Hud::getMainMenuText() {

	return m_mainMenuText;
}

Text Hud::getGoBackMenuText() {

	return m_goBackMenuText;
}

Text Hud::getHighscoreText() {

	return m_highScoreText;
}

Text Hud::getNumWeaponText() {

	return m_numWeaponText;
}

Text Hud::getIntroText()
{
	return m_introSkipText;
}

RectangleShape Hud::getHealthBar() {

	return m_healthBar;
}

RectangleShape Hud::getHealthBarBackground() {

	return m_healthBarBackground;
}

RectangleShape Hud::getHungerBar() {

	return m_hungerBar;
}

RectangleShape Hud::getHungerBarBackground() {

	return m_hungerBarBackground;
}

RectangleShape Hud::getBackgroudWeapon() {

	return m_backgroundWeapon;
}

RectangleShape Hud::getBackgroudWeaponSquare() {

	return m_backgroundWeaponSquare;
}

RectangleShape Hud::getBackgroudWeaponSquare2() {

	return m_backgroundWeaponSquare2;
}

RectangleShape Hud::getBackgroudWeaponSquare3() {

	return m_backgroundWeaponSquare3;
}

RectangleShape Hud::getBackgroudWeaponSquare4() {

	return m_backgroundWeaponSquare4;
}

RectangleShape Hud::getBackgroudWeaponSquare5() {

	return m_backgroundWeaponSquare5;
}

RectangleShape Hud::getBackgroudCraft() {
	return m_backgroundCraft;
}

RectangleShape Hud::getDarkness()
{
	return darkness;
}

RectangleShape Hud::getBarBackground()
{
	return m_barBackground;
}

/*
	SETTER FUNCTIONS
*/

void Hud::setDarkness(float darknessLevel)
{
	darkness.setFillColor(Color::Color(0, 0, 0, darknessLevel));
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

void Hud::setSoulQuantityText(String text) {

	m_soulQuantityText.setString(text);
}

void Hud::setHighScore(String text)
{
	m_highScoreText.setString(text);
}

