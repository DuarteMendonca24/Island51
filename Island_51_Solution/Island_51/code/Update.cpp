#include "Engine.h"
#include "Zombie.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
    

    if (state == State::PLAYING)
    {
        //Update the Hunger Bar
        currentHunger -= HungerTickAmount;
        hungerBar.setSize(Vector2f(currentHunger, HungerBarHeight));

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

        // Make the view centre around the player
        mainView.setCenter(player.getCenter());

        // changing the loop to use a list
        std::list<Zombie>::iterator it;
        for (it = m_EnemiesList.begin(); it != m_EnemiesList.end(); it++)
        {
        
           // cout << m_EnemiesList.size() <<"\n";

            if ((it)->isAlive())
            {

                (it)->update(dtAsSeconds, playerPosition);
            }
            else {

                //need to investigate this more 
              //  m_EnemiesList.erase(it); // Erase the object from the list and get the next valid iterator
            }
        }

        //make the illusionist look at player
        Illusionist[0].illusionBehaviour(playerPosition);

        //if its close to the player create the illusions
        if (Illusionist[0].distanceToPlayer(playerPosition) < 70 && !m_illusions) {
            
            //we delete the illusionist and create a new array with the illusions
            delete[] Illusionist;
            m_test = true;
            //get random numnber betwwen 0 and 3
            m_realOne = rand() % 4;
            Illusions = createIllusions(playerPosition);
          

        }

        //update the illusions , make them look at player
        if (m_illusions) {

            for (int i = 0; i < 4; i++)
            {

                Illusions[0].illusionBehaviour(playerPosition);
                Illusions[1].illusionBehaviour(playerPosition);
                Illusions[2].illusionBehaviour(playerPosition);
                Illusions[3].illusionBehaviour(playerPosition);
            }


            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 100; j++) {

                    if (bullets[i].isInFlight() && Illusions[j].isAlive())
                    {

                        if (bullets[i].getPosition().intersects(Illusions[j].getPosition()) && j == m_realOne)
                        {
                            cout << "Entrou";
                          

                            // Register the hit and see if it was a kill
                            if (Illusions[j].hit())
                            {
                                
                                delete[]Illusions;
                                m_illusions = false;
                              
                                // Not just a hit but a kill too
                                // Custom scores for each zombie type
                                score += Illusions[j].killValue();
                            }
                        }
                    }




                }
              
            }

        }
       
        // Loop through each Zombie and update them
        // for (int i = 0; i < numZombies; i++)
        //{
        //	if (zombies[i].isAlive())
        //	{
        //		zombies[i].update(dt.asSeconds(), playerPosition);
        //	}
        //}

        // Update any bullets that are in-flight
        for (int i = 0; i < 100; i++)
        {
            if (bullets[i].isInFlight())
            {
                bullets[i].update(dtAsSeconds);
            }
        }
        std::list<Tools>::iterator it7;
        for (int i = 0; i < 100; i++)
        {
            for (it7 = m_ResourceList.begin(); it7 != m_ResourceList.end(); it7++)
            {
                if (bullets[i].isInFlight() && (it7)->isAlive())
                {
                    if (bullets[i].getPosition().intersects((it7)->getPosition()))
                    {
                        // Stop the bullet unless the equipped gun is the railgun
                        if (!woodSwordEquipped)
                        {
                            // Stop the bullet
                            bullets[i].stop();
                        }

                        // Register the hit and see if it was a kill
                        if ((it7)->hit())
                        {
                            //Spawn pickup
                            std::list<Pickup> newPickup = createPickup((it7)->getPosCoordinates());
                            m_PickupList.insert(m_PickupList.end(), newPickup.begin(), newPickup.end());
                            // Not just a hit but a kill too
                            // Custom scores for each zombie type
                            // spawn another zombie when killed
                            // zombies[j].spawn(zombies[j].getPosCoordinates().x, zombies[j].getPosCoordinates().y,3,1);
                            //  Delete the previously allocated memory (if it exists)
                            // delete[] zombies;
                            //  Create new zombies and add them to m_EnemiesList

                            numResourceAlive--;
                        }

                        // Make a splat sound
                        splat.play();
                    }
                }
            }
        } // End zombie being shot
        // Update the pickups
        /*
        healthPickup.update(dtAsSeconds);
        ammoPickup.update(dtAsSeconds);
        moneyPickup.update(dtAsSeconds);
        */
        // Collision detection
        // Have any zombies been shot?
        // Changed to use a list
       std::list<Zombie>::iterator it3;
       for (int i = 0; i < 100; i++)
       {
           for (it3 = m_EnemiesList.begin(); it3 != m_EnemiesList.end(); it3++)
           {
               if (bullets[i].isInFlight() && (it3)->isAlive())
               {
                   if (bullets[i].getPosition().intersects((it3)->getPosition()))
                   {
                      
                      
      
                       // Register the hit and see if it was a kill
                       if ((it3)->hit())
                       {
                           // Not just a hit but a kill too
                           // Custom scores for each zombie type
                           score += (it3)->killValue();
                           // spawn another zombie when killed
                           // zombies[j].spawn(zombies[j].getPosCoordinates().x, zombies[j].getPosCoordinates().y,3,1);
                           //  Delete the previously allocated memory (if it exists)
                           // delete[] zombies;
                           //  Create new zombies and add them to m_EnemiesList
                  
                           //if zombie is a crawler , create two more enemies
                           if ((it3)->getType() == 2) {
                               std::list<Zombie> newZombies = createEnemies(2, (it3)->getPosCoordinates(), 3);
                               m_EnemiesList.insert(m_EnemiesList.end(), newZombies.begin(), newZombies.end());
                           }
                        
                           // numZombiesAlive = numZombies;
                           if (wave >= hiScore)
                           {
                               hiScore = wave;
                           }
      
                           numZombiesAlive--;
      
                           // When all the zombies are dead (again)
                           if (numZombiesAlive == 0)
                           {
                               state = State::LEVELING_UP;
                           }
                       }
      
                       // Make a splat sound
                       splat.play();
                   }
               }
           }
       } // End zombie being shot
       
        std::list<Zombie>::iterator it5;
        for (int i = 0; i < 100; i++)
        {
            for (it5 = m_EnemiesList.begin(); it5 != m_EnemiesList.end(); it5++)
            {
                if (bullets[i].isInFlight() && (it5)->isAlive())
                {
                    if (bullets[i].getPosition().intersects((it5)->getPosition()))
                    {
                        // Stop the bullet unless the equipped gun is the railgun
                        if (!woodSwordEquipped)
                        {
                            // Stop the bullet
                            bullets[i].stop();
                        }

                        // Register the hit and see if it was a kill
                        if ((it5)->hit())
                        {
                            //Spawn pickup
                            std::list<Pickup> newPickup = createPickup((it5)->getPosCoordinates());
                            m_PickupList.insert(m_PickupList.end(), newPickup.begin(), newPickup.end());
                            // Not just a hit but a kill too
                            // Custom scores for each zombie type
                            score += (it5)->killValue();
                            // spawn another zombie when killed
                            // zombies[j].spawn(zombies[j].getPosCoordinates().x, zombies[j].getPosCoordinates().y,3,1);
                            //  Delete the previously allocated memory (if it exists)
                            // delete[] zombies;
                            //  Create new zombies and add them to m_EnemiesList
                   
                            //if zombie is a crawler , create two more enemies
                            if ((it5)->getType() == 2) {
                                std::list<Zombie> newZombies = createEnemies(2, (it5)->getPosCoordinates(), 3);
                                m_EnemiesList.insert(m_EnemiesList.end(), newZombies.begin(), newZombies.end());
                            }
                         
                            // numZombiesAlive = numZombies;
                            if (wave >= hiScore)
                            {
                                hiScore = wave;
                            }

                            numZombiesAlive--;

                            // When all the zombies are dead (again)
                            if (numZombiesAlive == 0)
                            {
                                state = State::LEVELING_UP;
                            }
                        }

                        // Make a splat sound
                        splat.play();
                    }
                }
            }
        } // End zombie being shot

        // Have any zombies touched the player
        // Changed to use a list
        std::list<Zombie>::iterator it4;
        for (it4 = m_EnemiesList.begin(); it4 != m_EnemiesList.end(); it4++)
        {
            if (player.getPosition().intersects((it4)->getPosition()) && (it4)->isAlive())
            {

                if (player.hit(gameTimeTotal))
                {
                    
                    //if it is a chaser
                    if ((it4)->getType() == 1) {
                        
                        //decrease hunger bar
                        currentHunger -= 5;
                    }
                 
                    // More here later
                    hit.play();
                }

                if (player.getHealth() <= 0)
                {
                    state = State::GAME_OVER;

                    std::ofstream outputFile("gamedata/scores.txt");
                    outputFile << hiScore;
                    outputFile.close();
                }
            }
        } // End player touched
        
        std::list<Pickup>::iterator it9;
        for (int i = 0; i < 100; i++)
        {
            for (it9 = m_PickupList.begin(); it9 != m_PickupList.end(); it9++)
            {
                    if (player.getPosition().intersects((it9)->getPosition()) && (it9)->isSpawned())
                    {
                        if ((it9->getType() == 1))
                        {
                            player.increaseHealthLevel((it9)->gotIt());
                            m_PickupList.erase(it9); // This erases the pickup from the list
                        }
                       
                        break;// Break the loop after erasing the pickup
                    }
                
            }
        }
        // Has the player touched health pickup
        /*
        if (player.getPosition().intersects(healthPickup.getPosition()) && healthPickup.isSpawned())
        {
            player.increaseHealthLevel(healthPickup.gotIt());
            // Play a sound
            pickup.play();
        }

        // Has the player touched ammo pickup
        if (player.getPosition().intersects(ammoPickup.getPosition()) && ammoPickup.isSpawned())
        {
            bulletsSpare += ammoPickup.gotIt();
            // Play a sound
            reload.play();
        }

        // Has the player touched ammo pickup
        if (player.getPosition().intersects(moneyPickup.getPosition()) && moneyPickup.isSpawned())
        {
            score += moneyPickup.gotIt();
            // Play a sound
            pickup.play();
        }
        */
        // size up the health bar
        healthBar.setSize(Vector2f(player.getHealth() * 3, 70));

        
        // Increment the number of frames since the last HUD calculation
        framesSinceLastHUDUpdate++;
        // Calculate FPS every fpsMeasurementFrameInterval frames
        if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
        {

            // Update game HUD text
            std::stringstream ssAmmo;
            std::stringstream ssScore;
            std::stringstream ssHiScore;
            std::stringstream ssWave;
            std::stringstream ssZombiesAlive;

            // Update the ammo text
            ssAmmo << bulletsInClip << "/" << bulletsSpare;
            ammoText.setString(ssAmmo.str());

            // Update the score text
            ssScore << "Points:" << score;
            scoreText.setString(ssScore.str());

            // Update the high score text
            ssHiScore << "Hi Score:" << hiScore;
            hiScoreText.setString(ssHiScore.str());

            // Update the wave
            ssWave << "Wave:" << wave;
            waveNumberText.setString(ssWave.str());

            // Update the high score text
            ssZombiesAlive << "Zombies:" << numZombiesAlive;
            zombiesRemainingText.setString(ssZombiesAlive.str());

            framesSinceLastHUDUpdate = 0;
            timeSinceLastUpdate = Time::Zero;
        } // End HUD update

    } // End updating the scene



    if(state == State::MAIN_MENU)
    {
        //Check Collisions Between mouse and buttons
        if(startButtonHitBox.contains(mouseScreenPosition.x , mouseScreenPosition.y)){
            startButton.setFillColor(hoverOverColor);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = State::LEVELING_UP;
            }
        }
        else{
            startButton.setFillColor(startButtonColor);
        }

        if(exitButtonHitBox.contains(mouseScreenPosition.x , mouseScreenPosition.y)){
            exitButton.setFillColor(hoverOverColor);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                state = State::EXIT;
            }
        }
        else{
            exitButton.setFillColor(exitButtonColor);
        }
    }
}