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
      //  m_currentHunger -= m_hungerTickAmount;
        
  
        if (m_currentHunger <= 0)
        {
            //float health = player.getHealth();
            //health -= m_hungerTickAmount ;
            //player.setHealth(health);
            player.decreaseHealthLevel(m_hungerTickAmount * dtAsSeconds);
        }
        else
        {
            //Update the Hunger Bar
            cout << "BeforeHunger: " << m_currentHunger;
            m_currentHunger -= m_hungerTickAmount * dtAsSeconds;
            cout << "AfterHunger: " << m_currentHunger;
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
        
        // Update any bullets that are in-flight
        for (int i = 0; i < 100; i++)
        {
            if (bullets[i].isInFlight())
            {
                bullets[i].update(dtAsSeconds);
            }


        }

        for (int i = 0; i < 100; i++)
        {

            if (m_illusionsBullets[i].isInFlight())
            {

                m_illusionsBullets[i].update(dtAsSeconds);
            }
        }

        for (int i = 0; i < 100; i++)
        {

            if (m_enemyBullets[i].isInFlight())
            {

                m_enemyBullets[i].update(dtAsSeconds);
            }
        }

        //Update code for the enemies
        // ----------------------------------------------------------------------------------------

        // changing the loop to use a list
        std::list<Zombie*>::iterator it;
        for (it = m_EnemiesList.begin(); it != m_EnemiesList.end();)
        {

            // cout << m_EnemiesList.size() <<"\n";

            if ((*it)->isAlive())
            {

                (*it)->update(dtAsSeconds, playerPosition);

                //I think I should move this to another place , here is more to update each zombioe
                //if its and explosive enemie and its close to the player
                if ((*it)->getType() == 4 && (*it)->distanceToPlayer(playerPosition) < 500) {

                    m_shootingFireRate -= dtAsSeconds;

                    if (m_shootingFireRate < 0) {


                        m_shootingFireRate = 3;
 
                        currentBullet++;

                        m_enemyBullets[currentBullet].setRange(500);


                        m_enemyBullets[currentBullet].shoot((*it)->getPosCoordinates().x, (*it)->getPosCoordinates().y, playerPosition.x, playerPosition.y);



                        currentBullet++;
                        if (currentBullet > 99)
                        {
                            currentBullet = 0;
                        }
                    }


                }

                it++;
            }
            else {


                m_EnemiesList.erase(it++); // Erase the object from the list and get the next valid iterator
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

                
            }
        } // End player touched

        if (player.getHealth() <= 0)
        {
            
            state = State::GAME_OVER;

        }

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
                            m_score += (*it3)->killValue();

                            //if zombie is a crawler , create two more enemies
                            if ((*it3)->getType() == 2) {
                                std::list<Zombie*> newZombies = createEnemies(2, (*it3)->getPosCoordinates(), 3);
                                m_EnemiesList.insert(m_EnemiesList.end(), newZombies.begin(), newZombies.end());
                            }
                            //numZombiesAlive = numZombies;
                            if (wave >= m_hiScore)
                            {
                                m_hiScore = wave;
                            }

                            numZombiesAlive--;

                            // When all the zombies are dead (again)
                            /*
                            if (numZombiesAlive == 0)
                            {
                                state = State::LEVELING_UP;
                            }*/
                        }

                        // Make a splat sound
                        
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
            //get random numnber betwwen 0 and 3
            m_realOne = rand() % 4;
            Illusions = createIllusions(playerPosition);


        }

        //update the illusions , make them look at player
        if (m_illusions) {

            for (int i = 0; i < 4; i++)
            {

                Illusions[i].illusionBehaviour(playerPosition, dtAsSeconds);

            }

            m_illusionsFireRate -= dtAsSeconds;
            if (m_illusionsFireRate < 0)
            {
                m_illusionsFireRate = 2;



               m_illusionsBullets[currentBullet].setRange(100);
               m_illusionsBullets[currentBullet + 1].setRange(100);
               m_illusionsBullets[currentBullet + 2].setRange(100);
               m_illusionsBullets[currentBullet + 3].setRange(100);
               m_illusionsBullets[currentBullet].shoot(Illusions[0].getPosCoordinates().x, Illusions[0].getPosCoordinates().y, playerPosition.x, playerPosition.y);
               m_illusionsBullets[currentBullet + 1].shoot(Illusions[1].getPosCoordinates().x, Illusions[1].getPosCoordinates().y, playerPosition.x, playerPosition.y);
               m_illusionsBullets[currentBullet + 2].shoot(Illusions[2].getPosCoordinates().x, Illusions[2].getPosCoordinates().y, playerPosition.x, playerPosition.y);
               m_illusionsBullets[currentBullet + 3].shoot(Illusions[3].getPosCoordinates().x, Illusions[3].getPosCoordinates().y, playerPosition.x, playerPosition.y);


                currentBullet++;
                if (currentBullet > 99)
                {
                    currentBullet = 0;
                }


                // //shoot.play();
                // bulletsInClip--;
            }




            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 4; j++) {

                    if (bullets[i].isInFlight() && Illusions[j].isAlive())
                    {

                        if (bullets[i].getPosition().intersects(Illusions[j].getPosition()) && j == m_realOne)
                        {
                           // cout << "Entrou";


                            // Register the hit and see if it was a kill
                            if (Illusions[j].hit())
                            {
                                delete[] Illusions;
                                m_illusions = false;
                                
                            }
                        }
                    }
                }

            }

        }

        //check if enemie bullets are colliding with player
        for (int i = 0; i < 100; i++)
        {
            if (m_enemyBullets[i].isInFlight() && m_enemyBullets[i].getPosition().intersects(player.getPosition())) {

                player.hit(gameTimeTotal);
                hit.play();
                m_enemyBullets[i].stop();
              
          

            }

            if (m_illusionsBullets[i].isInFlight() && m_illusionsBullets[i].getPosition().intersects(player.getPosition())) {

                player.hit(gameTimeTotal);
                hit.play();
                m_illusionsBullets[i].stop();
               
       

            }

        }



        //Update code for the pickups
        // ----------------------------------------------------------------------------------------

        //When a bullet colldies with the pickups(tree,stone,iron)
        std::list<Pickup*>::iterator it4;
        for (int i = 0; i < 100; i++)
        {
            for (it4 = m_PickupList.begin(); it4 != m_PickupList.end(); it4++)
            {
                if (bullets[i].isInFlight() && (*it4)->isAlive())
                {
                    //check for bullet collision and if its not helath or hunger pickup
                    if (bullets[i].getPosition().intersects((*it4)->getPosition()) && (*it4)->getType() != 1 && (*it4)->getType() != 2)
                    {

                        // Stop the bullet
                        bullets[i].stop();

                        // Register the hit and see if it was a kill
                        if ((*it4)->hit())
                        {
                            srand((int)time(0)* i);
                            float posX = (rand() % 3651) + 2380;
                            float posY = (rand() % 1951) + 450;
                            float m_type = (rand() % 3) + 3;
                            std::list<Pickup*> newPickup = createRespawnResorces(1,posX,posY,m_type);
                            m_PickupList.insert(m_PickupList.end(), newPickup.begin(), newPickup.end());
                            //Tree pickup
                            if ((*it4)->getType() == 3) {

                                numTreePickup++;

                            }

                            //Stone pickup
                            if ((*it4)->getType() == 4) {

                                numStonePickup++;
                            }

                            //Iron pickup
                            if ((*it4)->getType() == 5) {

                                numIronPickup++;
                            }



                            numResourceAlive--;
                        }

                        // Make a splat sound
                        splat.play();

                        // Make a enemy sound
                        //enemysound.play();
                    }


                }

            }
        } // End zombie being shot


        
        //When the player collides with the pickups(health,food)
        std::list<Pickup*>::iterator it5;
        for (int i = 0; i < 100; i++)
        {
            for (it5 = m_PickupList.begin(); it5 != m_PickupList.end();)
            {
                if (player.getPosition().intersects((*it5)->getPosition()) && (*it5)->isSpawned())
                {
                    // Health Pickup
                    if ((*it5)->getType() == 1)
                    {
                        player.increaseHealthLevel((*it5)->gotIt());
                        it5 = m_PickupList.erase(it5);
                    }
                    // Ammo Pickup
                    else if ((*it5)->getType() == 2)
                    {
                        (*it5)->hit();
                       
                        m_currentHunger += 30;
                        it5 = m_PickupList.erase(it5);
                    
                    }
                    else
                    {
                        it5++;  // Increment here only if neither condition is met
                    }

                    // Break the loop after handling the pickup
                    break;
                }
                else
                {
                    it5++;
                }
            }
        }

        

            //----------------------------------------------------------------------------------------


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
                //update resources
                std::stringstream ssNumTreePickups;
                std::stringstream ssNumStonePickups;
                std::stringstream ssNumIronPickups;

                ssNumTreePickups << "x " << numTreePickup;
                m_hud.setWoodQuantityText(ssNumTreePickups.str());

                ssNumStonePickups << "x " << numStonePickup;
                m_hud.setStoneQuantityText(ssNumStonePickups.str());

                ssNumIronPickups << "x " << numIronPickup;
                m_hud.setIronQuantityText(ssNumIronPickups.str());





                // Update the ammo text
                ssAmmo << bulletsInClip << "/" << bulletsSpare;
                //ammoText.setString(ssAmmo.str());
                m_hud.setAmmoText(ssAmmo.str());

                // Update the score text
                ssScore << "Score:" << m_score;
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
                // Hunger bar width is 
                m_hud.setHungerSize(m_currentHunger);

                framesSinceLastHUDUpdate = 0;
                timeSinceLastUpdate = Time::Zero;
            } // End HUD update


        
    } // End updating the scene

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
    
    if (state == State::CRAFT)
    {
        // Check if m_EnoughResources is true
        if (m_EnoughResources)
        {
            m_SecondsSince += dtAsSeconds;
           // cout << "m_SecondsSince " << m_SecondsSince;
        }

        if (m_SecondsSince >= 1 && m_EnoughResources)
        {
            m_EnoughResources = false;
            m_SecondsSince = 0;
        }
    }


    if (state == State::GAME_OVER) {
        
        //stringstream ssGameOver;

        //m_finalScore = int(m_score - m_GameTime) + 1;
        //// Update the highscore text
        //ssGameOver << "\n\tGame Over" <<
        //    "\n\n\nTime: " << (int)m_GameTime << " s" <<
        //    "\n\nScore: " << m_score << " pts" <<
        //    "\n\nFinal Score: " << m_finalScore << " pts";
        //
        //m_Hud.setGameOver(ssGameOver.str());

        std::ofstream writeFile;
        writeFile.open("scores/Highscore.txt");

        if (writeFile.is_open()) {

            for (int i = 0; i < 5; i++)
            {
                if (m_score > m_scores[i] && !m_scoreFile) {

                    m_scores[i] = m_score;

                    m_scoreFile = true;


                }

                writeFile << m_scores[i] << "\n";
            }


        }

        writeFile.close();

    }

    if (state == State::HIGHSCORE) {
        stringstream ssHighScore;
        cout << "ENTROU";
        // Update the highscore text
        ssHighScore << "High Scores" <<
            "\n\n\n 1 -> " << m_scores[0] << " pts" <<
            "\n\n 2 -> " << m_scores[1] << " pts" <<
            "\n\n 3 -> " << m_scores[2] << " pts" <<
            "\n\n 4 -> " << m_scores[3] << " pts" <<
            "\n\n 5 -> " << m_scores[4] << " pts";


        m_hud.setHighScore(ssHighScore.str());

    }
}