#include "Engine.h"
#include <SFML/Audio.hpp>
sf::Music music;

using namespace sf;


void Engine::draw()
{
    //Setting Mouse Cursor to be visible in the game
    m_Window.setMouseCursorVisible(true);

    //// Playing background music inside the game 
    //if (!music.openFromFile("sound/backgroundmusic.wav"))
    //{
    //    return; // error
    //
    //    
    //    music.play();
    //}

    //View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));


    // Load the high score from a text file/
    std::ifstream inputFile("gamedata/scores.txt");
    if (inputFile.is_open())
    {
        inputFile >> hiScore;
        inputFile.close();
    }


    if (state == State::PLAYING)
    {
        m_Window.clear();

        // set the mainView to be displayed in the m_Window
        // And draw everything related to it
        m_Window.setView(mainView);

        // Draw the background
        m_Window.draw(background, &textureBackground);



      
           if (m_illusions) {
               // Draw the zombies
               for (int i = 0; i < 4; i++) {
                   
                   
                   m_Window.draw(Illusions[i].getSprite());
           
               }
           }
           
           if (m_illusionist) {
           
               for (int i = 0; i < 4; i++) {
           
                  
                   m_Window.draw(Illusionist[i].getSprite());
           
               }
              
           }

        

        // Draw the zombies with a list
        std::list<Zombie*>::iterator it2;
        for (it2 = m_EnemiesList.begin(); it2 != m_EnemiesList.end(); it2++)
        {

            m_Window.draw((*it2)->getSprite());
        }

        // Draw the pickup with a list
        std::list<Pickup*>::iterator it3;
        for (it3 = m_PickupList.begin(); it3 != m_PickupList.end(); it3++)
        {

            m_Window.draw((*it3)->getSprite());
        }
        for (int i = 0; i < 100; i++)
        {
            if (bullets[i].isInFlight())
            {
                m_Window.draw(bullets[i].getShape());
            }

        }

        for (int i = 0; i < 100; i++)
        {


            if (m_illusionsBullets[i].isInFlight())
            {
                m_Window.draw(m_illusionsBullets[i].getShape());
            }
        }

        for (int i = 0; i < 100; i++)
        {


            if (m_enemyBullets[i].isInFlight())
            {
                m_Window.draw(m_enemyBullets[i].getShape());
            }
        }

        // Draw the player
        m_Window.draw(player.getSprite());
        m_Window.draw(player.getSpriteWeapon());

        // Draw the pickups is currently spawned
        /*
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
        */

        // Draw the crosshair
        m_Window.draw(spriteCrosshair);

        // Switch to the HUD view
        m_Window.setView(m_hudView);

        // Draw all the HUD elements

        m_Window.draw(spriteAmmoIcon);
        m_Window.draw(m_hud.getAmmoText());
        m_Window.draw(m_hud.getScoreText());
        //m_Window.draw(m_hud.getHiScoreText());
        m_Window.draw(m_hud.getHealthBar());
        // m_Window.draw(m_hud.getWaveNumberText());
        m_Window.draw(m_hud.getZombiesRemainingText());
        m_Window.draw(m_hud.getHungerBar());
        m_Window.draw(m_hud.getDarkness());


        if (m_inventoryActive) {
            //draw the inventory icons
            for (int i = 0; i < 3; i++)
            {
                m_Window.draw(m_inventoryIcons[i].getSprite());
            }
            m_Window.draw(m_hud.getWoodQuantityText());
            m_Window.draw(m_hud.getStoneQuantityText());
            m_Window.draw(m_hud.getIronQuantityText());
        }

    }

    if (state == State::RULE)
    {
        // here is the rules for the rules 
        m_Window.draw(m_hud.getgameruleText());

    }

    if (state == State::LEVELING_UP)
    {
        m_Window.draw(spriteGameOver);
        
        m_Window.draw(m_hud.getLevelUpText());
                
        // Update the score text again
        std::stringstream ssScore;
        ssScore << "Points:" << score;
        //scoreText.setString(ssScore.str());
        //m_Window.draw(scoreText);
    }
    
    if (state == State::PAUSED)
    {
        m_Window.draw(m_hud.getPausedText());
        guiseletionsound.play();
    }

    if (state == State::GAME_OVER)
    {
        m_Window.draw(spriteGameOver);
        m_Window.draw(m_hud.getGameOverText());
        m_Window.draw(m_hud.getScoreText());
        m_Window.draw(m_hud.getHiScoreText());
        //gameoversound.play();
    }

    if (state == State::MAIN_MENU)
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
        Texture background_Texture;
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
        startButton.setOrigin(startButtonLeft, startButtonTop);
        exitButton.setOrigin(exitButtonLeft, exitButtonTop);
        startButton.setSize(Vector2f(buttonWidth, buttonHeight));
        exitButton.setSize(Vector2f(buttonWidth, buttonHeight));


        // Initialising Textures for GUI
        background_Sprite = Sprite(GUI_background_Texture);

        // Setting Size Of Textures to fit the screen
        sf::Vector2f targetSize(screenDimensions.x, screenDimensions.y);

        background_Sprite.setScale(
            targetSize.x / background_Sprite.getLocalBounds().width * 2,
            targetSize.y / background_Sprite.getLocalBounds().height);



        m_Window.draw(background_Sprite);
        m_Window.draw(startButton);
        m_Window.draw(exitButton);
        guiseletionsound.play();
    }

    if (state == State::CRAFT)
    {
        m_Window.draw(m_hud.getBackgroudCraft());
        select.draw(m_Window);
        if (m_EnoughResources)
        {
            m_Window.draw(m_hud.getNotEnoughResourcse());
          
        }
        guiseletionsound.play();
        if (m_inventoryActive) {
            //draw the inventory icons
            for (int i = 0; i < 3; i++)
            {
                m_Window.draw(m_inventoryIcons[i].getSprite());
            }
            m_Window.draw(m_hud.getWoodQuantityText());
            m_Window.draw(m_hud.getStoneQuantityText());
            m_Window.draw(m_hud.getIronQuantityText());
        }
    }

    m_Window.display();




}


