#include "Engine.h"


void Engine::draw()
{
    //Setting Mouse Cursor to be visible in the game
    m_Window.setMouseCursorVisible(true);

    // Load the font
	Font font;
	font.loadFromFile("fonts/zombiecontrol.ttf");

    View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    hungerBar.setFillColor(Color::Red);
    hungerBar.setPosition((190 / 2) - HungerBarStartWidth / 2, 100);

    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = HungerBarStartWidth / timeRemaining;

    

    // Paused
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");

	// Game Over
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(250, 850);
	gameOverText.setString("Press Enter to play");

	// Levelling up
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increase rate of fire || 300 points" <<
		"\n2- Increase clip size by x1.5 || 300 points" <<
		"\n3- Increase max health by 20HP || 300 points" <<
		"\n4- Increase run speed by x1.4 || 300 points" <<
		"\n5- More Pick Ups || 300 points" <<
		"\n6- SMG Weapon Upgrade || 1000 points"<<
		"\n7- Refill ammo + health (max)"<<
		"\n8- RailGun Weapon Upgrade || 4000 points"
		"\nSpace to Play Game";
	levelUpText.setString(levelUpStream.str());

	// Ammo
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(200, 980);

	// Score
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	// Hi Score
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// Zombies remaining
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(1500, 980);
	zombiesRemainingText.setString("Zombies: 100");

    
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition(1250, 980);
	waveNumberText.setString("Wave: 0");

    
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);

    if (state == State::PLAYING)
    {
        m_Window.clear();

        // set the mainView to be displayed in the m_Window
        // And draw everything related to it
        m_Window.setView(mainView);

        // Draw the background
        m_Window.draw(background, &textureBackground);

        // Draw the zombies
         for (int i = 0; i < 4; i++){

            if (m_illusions) {
                
                m_Window.draw(Illusions[i].getSprite());
            }
            else if(!m_test) {
                
                m_Window.draw(Illusionist[i].getSprite());
            }

         }

        // Draw the zombies with a list
        std::list<Zombie>::iterator it2;
        for (it2 = m_EnemiesList.begin(); it2 != m_EnemiesList.end(); it2++)
        {

            m_Window.draw((it2)->getSprite());
        }

        for (int i = 0; i < 100; i++)
        {
            if (bullets[i].isInFlight())
            {
                m_Window.draw(bullets[i].getShape());
            }
        }

        // Draw the player
        m_Window.draw(player.getSprite());

        // Draw the pickups is currently spawned
        if (ammoPickup.isSpawned())
        {
            m_Window.draw(ammoPickup.getSprite());
        }
        if (healthPickup.isSpawned())
        {
            m_Window.draw(healthPickup.getSprite());
        }
        if (moneyPickup.isSpawned())
        {
            m_Window.draw(moneyPickup.getSprite());
        }

        // Draw the crosshair
        m_Window.draw(spriteCrosshair);

        // Switch to the HUD view
        m_Window.setView(hudView);

        // Draw all the HUD elements
        m_Window.draw(spriteAmmoIcon);
        m_Window.draw(ammoText);
        m_Window.draw(scoreText);
        m_Window.draw(hiScoreText);
        m_Window.draw(healthBar);
        m_Window.draw(waveNumberText);
        m_Window.draw(zombiesRemainingText);
        m_Window.draw(hungerBar);
    }

    if (state == State::LEVELING_UP)
    {
        m_Window.draw(spriteGameOver);
        m_Window.draw(levelUpText);
        // Update the score text again
        std::stringstream ssScore;
        ssScore << "Points:" << score;
        scoreText.setString(ssScore.str());
        m_Window.draw(scoreText);
    }

    if (state == State::PAUSED)
    {
        m_Window.draw(pausedText);
    }

    if (state == State::GAME_OVER)
    {
        m_Window.draw(spriteGameOver);
        m_Window.draw(gameOverText);
        m_Window.draw(scoreText);
        m_Window.draw(hiScoreText);
    }

    if(state == State::MAIN_MENU)
    {
        

        // ScreenSize
        Vector2f screenDimensions;

        Vector2i mousePosition;

        // Button Coordinates
        float startButtonTop;
        float startButtonLeft;
        float exitButtonTop;
        float exitButtonLeft;
        float buttonWidth;
        float buttonHeight;

        // Background Variables
        //Texture background_Texture;
        Sprite background_Sprite;

        mousePosition = Mouse::getPosition();
        screenDimensions.x = VideoMode::getDesktopMode().width;
        screenDimensions.y = VideoMode::getDesktopMode().height;

        // Calculate positioning of the Buttons
        float buttonSpacing = screenDimensions.x / 20;
        buttonWidth = screenDimensions.x / 10;
        buttonHeight = screenDimensions.y / 10;
        startButtonTop = screenDimensions.y / 4;
        startButtonLeft = screenDimensions.x / 4;
        exitButtonTop = (screenDimensions.y / 4) + buttonSpacing;
        exitButtonLeft = (screenDimensions.x / 4) + buttonSpacing;

        // Initialising Buttons
        startButtonHitBox = FloatRect(startButtonLeft, startButtonTop, buttonWidth, buttonHeight);
        exitButtonHitBox = FloatRect(exitButtonLeft, exitButtonTop, buttonWidth, buttonHeight);
        startButton.setOrigin(startButtonLeft,startButtonTop);
        exitButton.setOrigin(exitButtonLeft,exitButtonTop);
        startButton.setSize(Vector2f(buttonWidth, buttonHeight));
        exitButton.setSize(Vector2f(buttonWidth, buttonHeight));


        // Initialising Textures for GUI
        background_Sprite = Sprite(GUI_background_Texture);

        // Setting Size Of Textures to fit the screen
        sf::Vector2f targetSize(screenDimensions.x, screenDimensions.y);

        background_Sprite.setScale(
            targetSize.x / background_Sprite.getLocalBounds().width,
            targetSize.y / background_Sprite.getLocalBounds().height);



        m_Window.draw(background_Sprite);
        m_Window.draw(startButton);
        m_Window.draw(exitButton);
    }

    m_Window.display();
}


	