#include "Engine.h"
#include <SFML/Audio.hpp>
sf::Music music;

using namespace sf;


void Engine::draw()
{
    
    //Setting Up Intro cutscene
    if (state == State::INTRO)
    {
        m_Window.clear();

        //draw the background image and the text
        m_Window.draw(spriteIntroComic);
        m_Window.draw(m_hud.getIntroText());

    }
    if (state == State::WIN)
    {
        m_Window.clear();

        //draw the background image and the text
        m_Window.draw(spriteWinComic);
        m_Window.draw(m_hud.getIntroText());

    }
    if (state == State::PLAYING)
    {
        // Clear the window to preaper for rendering 
        m_Window.clear();
        m_Window.setMouseCursorVisible(false);

        // set the mainView to be displayed in the m_Window
        // And draw everything related to it
        m_Window.setView(mainView);

        
        if (playerInsideCave)
        {
            m_Window.draw(caveBackground, &textureCaveBackground);
            if (DistanceToCave() > 300)
            {
                m_Window.draw(caveExit);
            }
            else if (DistanceToCave() <= 300)
            {
                m_Window.draw(caveExitPrompt);
            }

            
        }
        else {
            // Draw the background
            m_Window.draw(background, &textureBackground);

            if (DistanceToCave() > 300)
            {
                m_Window.draw(caveEntrance);
            }
            else if (DistanceToCave() <= 300)
            {
                m_Window.draw(caveEntrancePrompt);
            }
        }


           // Draw the zombie illusions if they are active 
           if (m_illusions) {
               // Draw the zombies
               for (int i = 0; i < 4; i++) {
                   
                   m_Window.draw(Illusions[i].getSprite());
           
               }
           }
           
           // Make sure that it active in the game
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
        // Draw the crosshair
        m_Window.draw(spriteCrosshair);

        // Switch to the HUD view
        m_Window.setView(m_hudView);

        if (playerInsideCave)
        {
            m_Window.draw(vigetteCave);

        }
        else {

            m_Window.draw(vigetteIsland);
        }

        m_Window.draw(m_hud.getAmmoBackgroud());
    
        // Draw all the HUD elements
        if (!m_HandWeaponActive2)
        {
            m_Window.draw(m_weaponIcons2[0].getSprite());
        }
        else
        {

            m_Window.draw(m_hud.getAmmoText());
        }
        if (!m_WoodWeaponActive2)
        {
            m_Window.draw(m_weaponIcons2[1].getSprite());
        }
        if (!m_StoneWeaponActive2)
        {
            m_Window.draw(m_weaponIcons2[2].getSprite());
        }
        if (!m_IronWeaponActive2)
        {
            m_Window.draw(m_weaponIcons2[3].getSprite());
        }
        if (!m_BowWeaponActive2)
        {
            m_Window.draw(m_weaponIcons2[4].getSprite());
        }

        // Draw ammo and score information
        m_Window.draw(m_hud.getScoreText());

       
        //Drawing Bar Background first
        //m_Window.draw(m_hud.getBarBackground());

        //Drawing Bar Background first
        m_Window.draw(m_hud.getBarBackground());
        // drawing the Health and Hunger bars in the game
        m_Window.draw(m_hud.getHealthBarBackground());
        m_Window.draw(m_hud.getHealthBar());
        m_Window.draw(m_hud.getHungerBarBackground());
        m_Window.draw(m_hud.getHungerBar());
        m_Window.draw(m_hud.getDarkness());
        //m_Window.draw(m_hud.getHungerText());
        //m_Window.draw(m_hud.getHealthText());
        //m_Window.draw(m_hud.getHungerText());
        //m_Window.draw(m_hud.getHealthText());
        
        //Draw inventory icons and quantities if the inventory is active
        /*
        if (m_inventoryActive) {
            m_Window.draw(m_hud.getInventoryBackgroud());
            //draw the inventory icons
            for (int i = 0; i < 4; i++)
            {
                m_Window.draw(m_inventoryIcons[i].getSprite());
            }
            m_Window.draw(m_hud.getSoulQuantityText());
            m_Window.draw(m_hud.getWoodQuantityText());
            m_Window.draw(m_hud.getStoneQuantityText());
            m_Window.draw(m_hud.getIronQuantityText());
        }*/
        m_Window.draw(m_hud.getInventoryBackgroud());
        for (int i = 0; i < 4; i++)
        {
            m_Window.draw(m_inventoryIcons[i].getSprite());
        }
        m_Window.draw(m_hud.getSoulQuantityText());
        m_Window.draw(m_hud.getWoodQuantityText());
        m_Window.draw(m_hud.getStoneQuantityText());
        m_Window.draw(m_hud.getIronQuantityText());
        //
        m_Window.draw(m_hud.getBackgroudWeapon());
        m_Window.draw(m_hud.getBackgroudWeaponSquare());
        m_Window.draw(m_hud.getBackgroudWeaponSquare2());
        m_Window.draw(m_hud.getBackgroudWeaponSquare3());
        m_Window.draw(m_hud.getBackgroudWeaponSquare4());
        m_Window.draw(m_hud.getBackgroudWeaponSquare5());
        m_Window.draw(m_hud.getBackgroudPressSquare());
        m_Window.draw(m_hud.getBackgroudPressSquare2());
        m_Window.draw(m_hud.getBackgroudPressSquare3());
        m_Window.draw(m_weaponIcons[0].getSprite());
        if (!m_WoodWeaponActive)
        {
            m_Window.draw(m_weaponIcons[1].getSprite());
        }
        if (!m_StoneWeaponActive)
        {
            m_Window.draw(m_weaponIcons[2].getSprite());
        }
        if (!m_IronWeaponActive)
        {
            m_Window.draw(m_weaponIcons[3].getSprite());
        }
        if (!m_BowWeaponActive)
        {
            m_Window.draw(m_weaponIcons[4].getSprite());
        }

        // Draw the number of weapons the player can use
        m_Window.draw(m_hud.getNumWeaponText());
        m_Window.draw(m_hud.getPressText());
        // Draw the Health and Hunger bar texture
        m_Window.draw(spriteHealthHunger);
        // Draw the craft
        m_Window.draw(spriteCraft);
        // Draw the inventory
        m_Window.draw(spriteInventory);
        
        // Draw the pause
        m_Window.draw(spritePause);
        m_Window.draw(m_hud.getAmmoDisplayText());
    }

    // Check if the game state have rules for the game
    if (state == State::RULE)
    {
        // Here is to add the colour for the background
        m_Window.clear(sf::Color(52, 43, 55));  // Black color with full alpha

        // Switch to the HUD view
        m_Window.setView(m_hudView);
        // here is the rules for the rules 
        m_Window.draw(m_hud.getGoBackMenuText());
        m_Window.draw(m_hud.getgameruleText());

    }

    // Check if hte game state is paused
    if (state == State::PAUSED)
    {
        m_Window.draw(m_hud.getPausedBackground());
       // Draw the pased text on the window
        m_Window.draw(m_hud.getPausedText());
        // Play the puase sound effect
        guiseletionsound.play();
        //Setting Mouse Cursor to be visible in the game
        m_Window.setMouseCursorVisible(true);
        // Draw the pause
        m_Window.draw(spritePause2);
    }

   // Check if the game state is Game Over
    if (state == State::GAME_OVER)
    {
        // Draw the main menu background
        m_Window.draw(spriteMainMenu);
        // Draw the Game Over text on the window
        m_Window.draw(m_hud.getGameOverText());
        // Draw the player's socre 
        m_Window.draw(m_hud.getScoreText());
        // Draw the high score 
        m_Window.draw(m_hud.getHighscoreText());
        //gameoversound.play();
        //Setting Mouse Cursor to be visible in the game
        m_Window.setMouseCursorVisible(true);
    }

    // Check if the game state is High Score
    if (state == State::HIGHSCORE) {

        m_Window.clear(sf::Color(52, 43, 55));  // Black color with full alpha

        // Switch to the HUD view
        m_Window.setView(m_hudView);
        // here is the rules for the rules 
        m_Window.draw(m_hud.getGoBackMenuText());
        // here is the high score
        m_Window.draw(m_hud.getHighscoreText());
        //Setting Mouse Cursor to be visible in the game
        m_Window.setMouseCursorVisible(true);
    }

    // Check if the game state is Main menu
    if (state == State::MAIN_MENU)
    {
        //draw the background image and the text
        m_Window.draw(spriteMainMenu);
        m_Window.draw(m_hud.getMainMenuText());
        //Setting Mouse Cursor to be visible in the game
        m_Window.setMouseCursorVisible(true);
    }

    // Check if the game state is Craft
    if (state == State::CRAFT)
    {
        // draw the background for the crafting 
        m_Window.draw(m_hud.getBackgroudCraft());

        // Draw the creafting selction
        select.draw(m_Window);

        // check if the player have't enohgy resources
        if (m_EnoughResources)
        {
            // Show a notification that player does;t have enough resources 
            m_Window.draw(m_hud.getNotEnoughResourcse());
          
        }

        // Play a sound effect gui seletion
        guiseletionsound.play();
        if (!m_inventoryActive)
        {
            m_inventoryActive = true;
        }
        // Check if the inventory is active
        if (m_inventoryActive) {
            //draw the inventory icons
            for (int i = 0; i < 4; i++)
            {
                m_Window.draw(m_inventoryIcons[i].getSprite());
            }
            //Draw text displaying th qunaitity of different resources in the invenory
            m_Window.draw(m_hud.getSoulQuantityText());
            m_Window.draw(m_hud.getWoodQuantityText());
            m_Window.draw(m_hud.getStoneQuantityText());
            m_Window.draw(m_hud.getIronQuantityText());
        }
        std::stringstream ssNumTreePickups;
        std::stringstream ssNumStonePickups;
        std::stringstream ssNumIronPickups;
        std::stringstream ssNumSoulPickups;

        // Update the tree pickup text
        ssNumTreePickups << "x " << numTreePickup;
        m_hud.setWoodQuantityText(ssNumTreePickups.str());
        // Update the stone pickup text
        ssNumStonePickups << "x " << numStonePickup;
        m_hud.setStoneQuantityText(ssNumStonePickups.str());
        // Update the iron pickup text
        ssNumIronPickups << "x " << numIronPickup;
        m_hud.setIronQuantityText(ssNumIronPickups.str());
        // Update the soul pickup text
        ssNumSoulPickups << "x " << numSoulPickup;
        m_hud.setSoulQuantityText(ssNumSoulPickups.str());
        m_Window.draw(m_hud.getExitBackgroud());
        m_Window.draw(m_hud.getUpBackgroud());
        m_Window.draw(m_hud.getDownBackgroud());
        m_Window.draw(m_hud.getShiftBackgroud());
        m_Window.draw(m_hud.getCraftText());
        m_Window.draw(spriteArrow);
        m_Window.draw(spriteArrowDown);
        m_Window.draw(spriteSelect);
        m_Window.draw(spriteExit);
    }

    // Update the game winow to disaply any change made during the process 
    m_Window.display();




}


