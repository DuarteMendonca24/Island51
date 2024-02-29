#include "Engine.h"
#include "Zombie.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    if (state == State::INTRO)
    {
        if (introVoice.getStatus() != Sound::Playing)
        {

            introVoice.play();
            introVoice.setVolume(100);
        }

    }
    if (state == State::WIN)
    {
        if (winVoice.getStatus() != Sound::Playing)
        {

            winVoice.play();
            winVoice.setVolume(100);
        }

    }
    // Check if the game is in the playing state
    if (state == State::PLAYING)
    {
        // Check if the player's hunger is zero or below
        if (m_currentHunger <= 0)
        {
            // Decrease the player's health level based on hunger tick amount and time passed
            player.decreaseHealthLevel(m_hungerTickAmount * dtAsSeconds);
        }
        else // If the player's hunger is above zero
        {
            // Decrease the player's hunger by hunger tick amount and time passed
            m_currentHunger -= m_hungerTickAmount * dtAsSeconds;
       
        }
        // Run Players collision detection
        detectCollisions(player);

        // Where is the mouse pointer
        mouseScreenPosition = Mouse::getPosition();

        // Convert mouse position to world coordinates of mainView
        mouseWorldPosition = m_Window.mapPixelToCoords(Mouse::getPosition(), mainView);

        // Set the crosshair to the mouse world location
        spriteCrosshair.setPosition(mouseWorldPosition);

        // Update the player
        player.update(dtAsSeconds, Mouse::getPosition());

        // Make a note of the players new position
        Vector2f playerPosition(player.getCenter());

        mainView.reset((sf::FloatRect(0, 0, resolution.x, resolution.y)));
        // Make the view centre around the player
        mainView.setCenter(player.getCenter());
        
        // Update any bullets that are in-flight for player
        for (int i = 0; i < 100; i++)
        {
            // If the bullet is in-flight, update its position 
            if (bullets[i].isInFlight())
            {
                bullets[i].update(dtAsSeconds);
            }
        }
        // Update any bullets that are in-flight for illusions
        for (int i = 0; i < 100; i++)
        {
            // If the illusion's bullet is in-flight, update its position
            if (m_illusionsBullets[i].isInFlight())
            {
                m_illusionsBullets[i].update(dtAsSeconds);
            }
        }
        // Update any bullets that are in-flight for enemies
        for (int i = 0; i < 100; i++)
        {
            // If the enemy's bullet is in-flight, update its position 
            if (m_enemyBullets[i].isInFlight())
            {
                m_enemyBullets[i].update(dtAsSeconds);
            }
        }
        /*
        for (int i = 0; i < 4; i++)
        {
            m_inventoryIcons[i].update(dtAsSeconds,10);
        }*/
        if (m_inventoryActive)
        {
            for (int i = 0; i < 4; i++)
            {
                m_inventoryIcons[i].inventoryMove(dtAsSeconds, 1);
            }
            m_hud.moveTextRightWood(dtAsSeconds, 1);
            m_hud.moveTextRightStone(dtAsSeconds, 1);
            m_hud.moveTextRightIron(dtAsSeconds, 1);
            m_hud.moveTextRightSoul(dtAsSeconds, 1);
            if (300 <= backgroundInventory)
            {
                backgroundInventory = backgroundInventory;
            }
            else
            {
                backgroundInventory += 500 * dtAsSeconds;
            }
        }
        
        if (!m_inventoryActive)
        {
            for (int i = 0; i < 4; i++)
            {
                m_inventoryIcons[i].inventoryMoveLeft(dtAsSeconds, 1);
            }
            m_hud.moveTextLeftWood(dtAsSeconds, 1);
            m_hud.moveTextLeftStone(dtAsSeconds, 1);
            m_hud.moveTextLeftIron(dtAsSeconds, 1);
            m_hud.moveTextLeftSoul(dtAsSeconds, 1);
            if (0 >= backgroundInventory)
            {
                backgroundInventory = backgroundInventory;
            }
            else
            {
                backgroundInventory -= 500 * dtAsSeconds;
            }
        }
        //Update code for the enemies
        // ----------------------------------------------------------------------------------------

        // changing the loop to use a list
        std::list<Zombie*>::iterator it;
        for (it = m_EnemiesList.begin(); it != m_EnemiesList.end();)
        {
            //if the enemies is avile 
            if ((*it)->isAlive())
            {
                // Update the position and behavior of the enemy
                (*it)->update(dtAsSeconds, playerPosition);

                //I think I should move this to another place , here is more to update each zombioe
                //if its and explosive enemie and its close to the player
                if ((*it)->getType() == 4 && (*it)->distanceToPlayer(playerPosition) < 500) {
                    // Reduce the shooting fire rate
                    m_shootingFireRate -= dtAsSeconds;
                    // Check if it's time to shoot
                    if (m_shootingFireRate < 0) {
                        // Reset the shooting fire rate
                        m_shootingFireRate = 3;
                        //Increment the current bullet
                        currentBullet++;
                        // Set the range of the enemy bullet
                        m_enemyBullets[currentBullet].setRange(500);
                        // Shoot a bullet from the explosive enemy towards the player
                        m_enemyBullets[currentBullet].shoot((*it)->getPosCoordinates().x, (*it)->getPosCoordinates().y, playerPosition.x, playerPosition.y);
                        // Increment the bullet 
                        currentBullet++;
                        if (currentBullet > 99)
                        {
                            currentBullet = 0;
                        }
                    }
                }
                // Move to the next enemy in the list
                it++;
            }
            else {
                // Erase the object from the list and get the next valid iterator
                m_EnemiesList.erase(it++); 
            }
        }

        // Have any zombies touched the player
       // Changed to use a list
        std::list<Zombie*>::iterator it2;
        for (it2 = m_EnemiesList.begin(); it2 != m_EnemiesList.end(); it2++)
        {
            //Check if the player intersects the enemies
            if (player.getPosition().intersects((*it2)->getPosition()) && (*it2)->isAlive())
            {
                // Check if the player intersects with a living enemy
                if (player.hit(gameTimeTotal))
                {
                    //if it is a Hunger Taker enemies
                    if ((*it2)->getType() == 1) {
                        //decrease hunger bar
                        m_currentHunger -= 5;
                    }
                    // Play a hit sound effect
                    hit.play();
                }
            }
        } // End player touched

        //Check if the player health reach to zero
        if (player.getHealth() <= 0)
        {
            // Set the game state to GAME_OVER
            state = State::GAME_OVER;

        }
        // Iterate the list of enemy
        std::list<Zombie*>::iterator it3;
        for (int i = 0; i < 100; i++)
        {
            // Iterate over each zombie in the m_EnemiesList
            for (it3 = m_EnemiesList.begin(); it3 != m_EnemiesList.end(); it3++)
            {
                // Check if the bullet is in flight and the zombie is alive
                if (bullets[i].isInFlight() && (*it3)->isAlive())
                {
                    // Check for collision between bullet and zombie
                    if (bullets[i].getPosition().intersects((*it3)->getPosition()))
                    {
                        // Stop the bullet unless the equipped gun is the railgun
                        bullets[i].stop();
                        // Register the hit and see if it was a kill
                        if ((*it3)->hit())
                        {
                            // Spawn pickups at the zombie's position
                            std::list<Pickup*> newPickup = createPickup((*it3)->getPosCoordinates());
                            m_PickupList.insert(m_PickupList.end(), newPickup.begin(), newPickup.end());
                            // Update the player's score based on the killed zombie's type
                            m_score += (*it3)->killValue();

                            //if zombie is a crawler , create two more enemies
                            if ((*it3)->getType() == 2) {
                                std::list<Zombie*> newZombies = createEnemies(2, (*it3)->getPosCoordinates(), 3);
                                m_EnemiesList.insert(m_EnemiesList.end(), newZombies.begin(), newZombies.end());
                            }
                            // Otherwise respawn a brand new enemy
                            else
                            {
                                int type = RandomBetween(0, 4);//random between 0 and 4
                                int spawner = RandomBetween(0, manageLevel.current_spawn_block_counter);// spawn position in random position in the block
                                float x = (float)manageLevel.m_SpawnPoisitons[spawner].x;//Set the x axis position
                                float y = (float)manageLevel.m_SpawnPoisitons[spawner].y;//Set the y axis position
                                Vector2f location = Vector2f(x, y);//create a new position
                                std::list<Zombie*> newZombies = createEnemies(1, location, type);//create a new enemies
                                m_EnemiesList.insert(m_EnemiesList.end(), newZombies.begin(), newZombies.end());
                            }
                            // Update the highest wave score
                            if (wave >= m_hiScore)
                            {
                                m_hiScore = wave;
                            }
                            // Decrease the count of alive zombies
                            numZombiesAlive--;
                        }
                        // Play a splat sound
                        splat.play();
                    }
                }
            }
        } // End zombie being shot

        //make the illusionist look at player
        if (m_illusionist) {
           
            Illusionist[0].illusionBehaviour(playerPosition, dtAsSeconds);
            
        }

        //if its close to the player create the illusions
        if (Illusionist[0].distanceToPlayer(playerPosition) < 70 && !m_illusions) {

            //we delete the illusionist and create a new array with the illusions
            delete[] Illusionist;
            m_illusionist = false;
            //get random numnber between 0 and 3
            m_realOne = rand() % 4;
            Illusions = createIllusions(playerPosition);
        }

        //update the illusions , make them look at player
        if (m_illusions) {
            // loop through each illusion
            for (int i = 0; i < 4; i++)
            {
                // Update the behavior of the illusion based on the player's position and the elapsed time
                Illusions[i].illusionBehaviour(playerPosition, dtAsSeconds);
            }
            // Decrease the fire rate of illusions
            m_illusionsFireRate -= dtAsSeconds;
            //if the illusions fire rate less than 0
            if (m_illusionsFireRate < 0)
            {
                //Set the illusions fire rate to 1
                m_illusionsFireRate = 1;
                // Set the range for each illusion bullet and make them shoot towards the player
               m_illusionsBullets[currentBullet].setRange(100);
               m_illusionsBullets[currentBullet + 1].setRange(100);
               m_illusionsBullets[currentBullet + 2].setRange(100);
               m_illusionsBullets[currentBullet + 3].setRange(100);
               m_illusionsBullets[currentBullet].shoot(Illusions[0].getPosCoordinates().x, Illusions[0].getPosCoordinates().y, playerPosition.x, playerPosition.y);
               m_illusionsBullets[currentBullet + 1].shoot(Illusions[1].getPosCoordinates().x, Illusions[1].getPosCoordinates().y, playerPosition.x, playerPosition.y);
               m_illusionsBullets[currentBullet + 2].shoot(Illusions[2].getPosCoordinates().x, Illusions[2].getPosCoordinates().y, playerPosition.x, playerPosition.y);
               m_illusionsBullets[currentBullet + 3].shoot(Illusions[3].getPosCoordinates().x, Illusions[3].getPosCoordinates().y, playerPosition.x, playerPosition.y);

               // Increment the current bullet index and reset if it exceeds the limit
                currentBullet++;
                if (currentBullet > 99)
                {
                    currentBullet = 0;
                }
            }
            // Check for collisions between player bullets and illusions
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 4; j++) {
                    // Check if the player's bullet is in flight and illusion is alive
                    if (bullets[i].isInFlight() && Illusions[j].isAlive())
                    {
                        // Check if the player's bullet is in flight and intersects with the real illusion
                        if (bullets[i].getPosition().intersects(Illusions[j].getPosition()) && j == m_realOne)
                        {
                            // Delete the illusions array and set the illusion to false
                            if (Illusions[j].hit())
                            {
                                delete[] Illusions;
                                m_illusions = false;
                                numSoulPickup += 5;
                                
                                
                            }
                        }
                    }
                }

            }

        }

        //check if enemie bullets are colliding with player
        for (int i = 0; i < 100; i++) {
            // Check collision with bullets from regular enemies
            if (m_enemyBullets[i].isInFlight() && m_enemyBullets[i].getPosition().intersects(player.getPosition())) {
                // Player is hit by an enemy bullet
                player.hit(gameTimeTotal);
                // Play the hit sound
                hit.play();
                // Stop the enemy bullet
                m_enemyBullets[i].stop();
            }

            // Check collision with bullets from illusions
            if (m_illusionsBullets[i].isInFlight() && m_illusionsBullets[i].getPosition().intersects(player.getPosition())) {
                // Player is hit by an illusion bullet
                player.hit(gameTimeTotal);
                // Play the hit sound
                hit.play();
                // Stop the illusion bullet
                m_illusionsBullets[i].stop();
            }
        }
        //Update code for the pickups
        // ----------------------------------------------------------------------------------------

        //When a bullet colldies with the pickups(tree,stone,iron)
        std::list<Pickup*>::iterator it4;
        for (int i = 0; i < 100; i++)
        {
            // Loop through the pickup list
            for (it4 = m_PickupList.begin(); it4 != m_PickupList.end();it4++)
            {
                //if the player bullet is flight and is alive
                if (bullets[i].isInFlight() && (*it4)->isAlive())
                {
                    // Check for bullet collision and if it's not a health or hunger pickup
                    if (bullets[i].getPosition().intersects((*it4)->getPosition()) && (*it4)->getType() != 1 && (*it4)->getType() != 2)
                    {
                        // Stop the bullet
                        bullets[i].stop();
                        // Register the hit and see if it was a kill
                        if ((*it4)->hit())
                        {
                            // Generate new position and type for the respawned pickup
                            srand((int)time(0) * i); 
                            Vector2i spawnLocation = manageLevel.getRandomSpawner();
                            Vector2f position = Vector2f((float)spawnLocation.x, (float)spawnLocation.y);
                            float m_type = (rand() % 3) + 4;
                            // Create and insert the respawned pickup into the list
                            std::list<Pickup*> newPickup = createRespawnResorces(1, position.x, position.y, m_type);
                            m_PickupList.insert(m_PickupList.end(), newPickup.begin(), newPickup.end());

                            // Tree pickup
                            if ((*it4)->getType() == 4)
                            {
                                numTreePickup++;
                            }

                            // Stone pickup
                            else if ((*it4)->getType() == 5)
                            {
                                numStonePickup++;
                            }

                            // Iron pickup
                            else if ((*it4)->getType() == 6)
                            {
                                numIronPickup++;
                            }
                            // Decrease the count of alive pickups
                            numResourceAlive--;
                           
                        }
                        // Play a splat sound
                        splat.play();
                    }
                }
            }
        } // End pickup being shot



        
        //When the player collides with the pickups(health,food)
        std::list<Pickup*>::iterator it5;
        for (int i = 0; i < 100; i++) {
            // Loop through the pickup list
            for (it5 = m_PickupList.begin(); it5 != m_PickupList.end();) {
                // Check if player intersects with the pickup and the pickup is spawned
                if (player.getPosition().intersects((*it5)->getPosition()) && (*it5)->isSpawned()) {
                    // Handle different types of pickups
                    // Health Pickup
                    if ((*it5)->getType() == 1) {
                        player.increaseHealthLevel((*it5)->gotIt());
                        // Erase the pickup from the list and get the next valid iterator
                        it5 = m_PickupList.erase(it5);
                    }
                    // Food Pickup
                    else if ((*it5)->getType() == 2) {
                        m_currentHunger += 50;
                        if (m_currentHunger > 200)
                        {
                            m_currentHunger = 200;
                        }
                        // Erase the pickup from the list and get the next valid iterator
                        it5 = m_PickupList.erase(it5);
                    }
                    // Soul Pickup
                    else if ((*it5)->getType() == 3) {
                        numSoulPickup++;
                        int randomNum = RandomBetween(0, 3);
                        if (randomNum == 0)
                        {
                            numSoulPickup++;
                        }
                        // Erase the pickup from the list and get the next valid iterator
                        it5 = m_PickupList.erase(it5);
                    }
                    else {
                        it5++;  // Increment here only if neither condition is met
                    }

                    // Break the loop after handling the pickup
                    break;
                }
                else {
                    it5++;// Increment
                }
            }
        }

        //loop to delete pickups if they have been killed
        std::list<Pickup*>::iterator it6;
        for (it6 = m_PickupList.begin(); it6 != m_PickupList.end();) {
            // Check if the pickup is alive
            if ((*it6)->isAlive()) {
                // If alive, move to the next pickup in the list
                it6++;
            }
            else {
                // If not alive, erase the pickup from the list and get the next valid iterator
                it6 = m_PickupList.erase(it6++);
            }
        }
  
        //----------------------------------------------------------------------------------------
            

        // Update game HUD text
        std::stringstream ssAmmo;
        std::stringstream ssScore;
        std::stringstream ssHiScore;
        std::stringstream ssWave;
        std::stringstream ssZombiesAlive;
        //update resources
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
        // Update the ammo text
        if (handEquipped)
        {
            ssAmmo << static_cast<unsigned char>(236);
        }
        else
        {

            ssAmmo << bulletsInClip;
        }

        m_hud.setAmmoText(ssAmmo.str());
        // Update the score text
        ssScore << "Score:" << m_score;
        m_hud.setScoreText(ssScore.str());
        // Update the wave
        ssWave << "Wave:" << wave;
        m_hud.setWaveNumberText(ssWave.str());
         //health bar width is 300
        m_hud.setHealthSize(player.getHealth());
        // Hunger bar width is 
        m_hud.setHungerSize(m_currentHunger);
        m_hud.setBackgroundSize(backgroundInventory);
        //Update last the HUD frame
        framesSinceLastHUDUpdate = 0;
        //Update last the time since
        timeSinceLastUpdate = Time::Zero;
          
    } // End updating the scene

     // Check if the game is in the playing state
    if (state == State::MAIN_MENU)
    {
        //Check Collisions Between mouse and buttons
        if (startButtonHitBox.contains(mouseScreenPosition.x, mouseScreenPosition.y)) {
            startButton.setFillColor(hoverOverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = State::LEVELING_UP;
            }
        }
        else {
            startButton.setFillColor(startButtonColor);
        }

        if (exitButtonHitBox.contains(mouseScreenPosition.x, mouseScreenPosition.y)) {
            exitButton.setFillColor(hoverOverColor);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = State::EXIT;
            }
        }
        else {
            exitButton.setFillColor(exitButtonColor);
        }
    }
    // Check if the game is in the Craft state
    if (state == State::CRAFT)
    {
        
                
        // Check if m_EnoughResources is true
        if (m_EnoughResources)
        {
            // Increment m_SecondsSince by the elapsed time
            m_SecondsSince += 10 * dtAsSeconds;
        }
        // Check if m_SecondsSince is greater than or equal to 1 and m_EnoughResources is still true
        if (m_SecondsSince >= 1 && m_EnoughResources)
        {
            // Set m_EnoughResources to false
            m_EnoughResources = false;
            // Reset m_SecondsSince to 0
            m_SecondsSince = 0;
            // Play a sound 
            pickup.play();
        }
    }

    // Check if the game is in the Game Over state
    if (state == State::GAME_OVER) {
        // Open a file named "scores/Highscore.txt" for writing
        std::ofstream writeFile;
        writeFile.open("scores/Highscore.txt");
        // Check if the file is successfully opened
        if (writeFile.is_open()) {
            // Loop through the scores array
            for (int i = 0; i < 5; i++)
            {
                // Check if the current score is greater than a score in the array
                // and if the score hasn't been written to the file yet
                if (m_score > m_scores[i] && !m_scoreFile) {
                    // Update the score in the array
                    m_scores[i] = m_score;
                    // Set a flag indicating that the score has been written
                    m_scoreFile = true;

                }
                // Write each score to the file
                writeFile << m_scores[i] << "\n";
            }
        }
        // Close the file
        writeFile.close();
        m_score = 0;
    }
    // Check if the game is in the High Score state
    if (state == State::HIGHSCORE) {
        // Create a stringstream for formatting the high score text
        stringstream ssHighScore;
        // Update the high score text with the scores from the array
        ssHighScore << "\nHigh Scores" <<
            "\n\n 1 -> " << m_scores[0] << " pts" <<
            "\n\n 2 -> " << m_scores[1] << " pts" <<
            "\n\n 3 -> " << m_scores[2] << " pts" <<
            "\n\n 4 -> " << m_scores[3] << " pts" <<
            "\n\n 5 -> " << m_scores[4] << " pts";
        // Set the high score text in the game's HUD
        m_hud.setHighScore(ssHighScore.str());
    }
}

// Definition of the RandomBetween function
int Engine::RandomBetween(int min, int max)
{
    // Generating a random number using std::random_device and std::uniform_int_distribution
    std::random_device rd;  // A random device for obtaining seed
    std::uniform_int_distribution<int> dist(min, max);  // Uniform distribution between min and max
    // Returning a random integer within the specified range
    return dist(rd);
}