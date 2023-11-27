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
        mainView.reset((sf::FloatRect(0, 0, resolution.x, resolution.y)));
        // Make the view centre around the player
        mainView.setCenter(player.getCenter());

<<<<<<< Updated upstream
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

                
                // Erase the object from the list and get the next valid iterator
                it = m_EnemiesList.erase(it);
            }

            if ((*it)->getType() == 4 && (*it)->isAlive()) {
               
              
                if (m_cooldown < 0)
                {

                    enemyBullets[currentBullet].shoot(
                        (*it)->getPosCoordinates().x, (*it)->getPosCoordinates().y,
                        playerPosition.x, playerPosition.y);
               

                    currentBullet++;
                    if (currentBullet > 99)
                    {
                        currentBullet = 0;
                    }
                    shoot.play();
                    bulletsInClip--;
                    m_cooldown = 3.0f;
                }
               
            }
        }

        m_cooldown -= dtAsSeconds;


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

                Illusions[i].illusionBehaviour(playerPosition);
               //Illusions[1].illusionBehaviour(playerPosition);
               //Illusions[2].illusionBehaviour(playerPosition);
               //Illusions[3].illusionBehaviour(playerPosition);
            }


           for (int i = 0; i < 100; i++)
           {
               for (int j = 0; j < 4; j++) {
           
                   if (bullets[i].isInFlight() && Illusions[j].isAlive())
                   {
           
                       if (bullets[i].getPosition().intersects(Illusions[j].getPosition()) && j == m_realOne)
                       {
                           
                           // Stop the bullet unless the equipped gun is the railgun
                           if (!railgunEquipped)
                           {
                               // Stop the bullet
                               bullets[i].stop();
                           }
           
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
=======
>>>>>>> Stashed changes

        // Update any bullets that are in-flight
        for (int i = 0; i < 100; i++)
        {
            if (bullets[i].isInFlight())
            {
                bullets[i].update(dtAsSeconds);
            }

            if (enemyBullets[i].isInFlight())
            {
                
                enemyBullets[i].update(dtAsSeconds);
            }
        }


        // Update the pickups
        healthPickup.update(dtAsSeconds);
        ammoPickup.update(dtAsSeconds);
        moneyPickup.update(dtAsSeconds);

        // Collision detection
        // Have any zombies been shot?
        // Changed to use a list
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
                       if (!railgunEquipped)
                       {
                           // Stop the bullet
                           bullets[i].stop();
                       }
      
                       // Register the hit and see if it was a kill
                       if ((*it3)->hit())
                       {
                           // Not just a hit but a kill too
                           // Custom scores for each zombie type
                           score += (*it3)->killValue();
                           // spawn another zombie when killed
                           // zombies[j].spawn(zombies[j].getPosCoordinates().x, zombies[j].getPosCoordinates().y,3,1);
                           //  Delete the previously allocated memory (if it exists)
                           // delete[] zombies;
                           //  Create new zombies and add them to m_EnemiesList
                  
                           //if zombie is a crawler , create two more enemies
                           if ((*it3)->getType() == 2) {
                               std::list<Zombie*> newZombies = createEnemies(2, (*it3)->getPosCoordinates(), 3);
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
        std::list<Zombie*>::iterator it4;
        for (it4 = m_EnemiesList.begin(); it4 != m_EnemiesList.end(); it4++)
        {
            if (player.getPosition().intersects((*it4)->getPosition()) && (*it4)->isAlive())
            {

                if (player.hit(gameTimeTotal))
                {
                    
                    //if it is a chaser
                    if ((*it4)->getType() == 1) {
                        
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


        //loop to check if enemy bullets intersect the player
        for (int i = 0; i < 100; i++) {

            if (enemyBullets[i].getPosition().intersects(player.getPosition()) && enemyBullets[i].isInFlight()) {

                if (player.hit(gameTimeTotal))
                {
                    // More here later
                    hit.play();
                }

                // Stop the bullet
                enemyBullets[i].stop();

            }
        }

        // Has the player touched health pickup
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
}