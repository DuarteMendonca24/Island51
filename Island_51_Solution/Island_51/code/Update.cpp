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
        m_currentHunger -= m_hungerTickAmount;
      

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

        // Update any bullets that are in-flight
        for (int i = 0; i < 100; i++)
        {
            if (bullets[i].isInFlight())
            {
                bullets[i].update(dtAsSeconds);
            }
        }

      

        //Update code for the enemies
        // ----------------------------------------------------------------------------------------
        
        // changing the loop to use a list
        std::list<Zombie*>::iterator it;
        for (it = m_EnemiesList.begin(); it != m_EnemiesList.end(); it++)
        {
        
           // cout << m_EnemiesList.size() <<"\n";

            if ((*it)->isAlive())
            {
                
                (*it)->update(dtAsSeconds, playerPosition);
            }
            else {

                //need to investigate this more 
               //m_EnemiesList.erase(it); // Erase the object from the list and get the next valid iterator
            }
        }

        // Have any zombies touched the player
       // Changed to use a list
        std::list<Zombie*>::iterator it2;
        for (it2 = m_EnemiesList.begin(); it2 != m_EnemiesList.end(); it2++)
        {
            if (player.getPosition().intersects((*it2)->getPosition()) && (*it2)->isAlive())
            {

                if (player.hit(gameTimeTotal))
                {

                    //if it is a chaser
                    if ((*it2)->getType() == 1) {

                        //decrease hunger bar
                        m_currentHunger -= 5;
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


        std::list<Zombie*>::iterator it3;
        for (int i = 0; i < 100; i++)
        {
            for (it3 = m_EnemiesList.begin(); it3 != m_EnemiesList.end(); it3++)
            {
                if (bullets[i].isInFlight() && (*it3)->isAlive())
                {
                    if (bullets[i].getPosition().intersects((*it3)->getPosition()))
                    {
                        // Stop the bullet unless the equipped gun is the railgun
                        bullets[i].stop();
                        // Register the hit and see if it was a kill
                        if ((*it3)->hit())
                        {
                            //Spawn pickup
                            std::list<Pickup*> newPickup = createPickup((*it3)->getPosCoordinates());
                            m_PickupList.insert(m_PickupList.end(), newPickup.begin(), newPickup.end());
                            // Not just a hit but a kill too
                            // Custom scores for each zombie type
                            score += (*it3)->killValue();
                 
                            //if zombie is a crawler , create two more enemies
                            if ((*it3)->getType() == 2) {
                                std::list<Zombie*> newZombies = createEnemies(2, (*it3)->getPosCoordinates(), 3);
                                m_EnemiesList.insert(m_EnemiesList.end(), newZombies.begin(), newZombies.end());
                            }

                             //numZombiesAlive = numZombies;
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
       
       

        

        //Update code for the tools
        // ----------------------------------------------------------------------------------------
        
        std::list<Tools*>::iterator it4;
        for (int i = 0; i < 100; i++)
        {
            for (it4 = m_ResourceList.begin(); it4 != m_ResourceList.end(); it4++)
            {
                if (bullets[i].isInFlight() && (*it4)->isAlive())
                {
                    if (bullets[i].getPosition().intersects((*it4)->getPosition()))
                    {
                        // Stop the bullet unless the equipped gun is the railgun
                        if (!woodSwordEquipped)
                        {
                            // Stop the bullet
                            bullets[i].stop();
                        }

                        // Register the hit and see if it was a kill
                        if ((*it4)->hit())
                        {
                            //Spawn pickup
                            std::list<Pickup*> newPickup = createPickup((*it4)->getPosCoordinates());
                            m_PickupList.insert(m_PickupList.end(), newPickup.begin(), newPickup.end());
                            numResourceAlive--;
                        }

                        // Make a splat sound
                        splat.play();
                    }
                }
            }
        } // End zombie being shot
        
       
       
        
        //Update code for the pickups
        //----------------------------------------------------------------------------------------
 
        std::list<Pickup*>::iterator it5;
        for (int i = 0; i < 100; i++)
        {
            for (it5 = m_PickupList.begin(); it5 != m_PickupList.end(); it5++)
            {
                    if (player.getPosition().intersects((*it5)->getPosition()) && (*it5)->isSpawned())
                    {
                        if ((*it5)->getType() == 1)
                        {
                            player.increaseHealthLevel((*it5)->gotIt());
                            m_PickupList.erase(it5); // This erases the pickup from the list
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
            //ammoText.setString(ssAmmo.str());
            m_hud.setAmmoText(ssAmmo.str());

            // Update the score text
            ssScore << "Points:" << score;
           // scoreText.setString(ssScore.str());
            m_hud.setScoreText(ssScore.str());

            // Update the high score text
           // ssHiScore << "Hi Score:" << hiScore;
           // hiScoreText.setString(ssHiScore.str());
            

            // Update the wave
            ssWave << "Wave:" << wave;
            //waveNumberText.setString(ssWave.str());
            m_hud.setWaveNumberText(ssWave.str());

            // Update the high score text
            ssZombiesAlive << "Zombies:" << numZombiesAlive;
           // zombiesRemainingText.setString(ssZombiesAlive.str());
            m_hud.setZombiesRemainingText(ssZombiesAlive.str());

            //health bar width is 300
            m_hud.setHealthSize(player.getHealth());

            m_hud.setHungerSize(m_currentHunger);

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