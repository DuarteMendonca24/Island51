#include "Engine.h"

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {


            if (event.type == Event::KeyPressed)
            {
                // Pause a game while playing
                if (event.key.code == Keyboard::Return &&
                    state == State::PLAYING)
                {
                    state = State::PAUSED;
                }

                // Restart while paused
                else if (event.key.code == Keyboard::Return &&
                    state == State::PAUSED)
                {
                    state = State::PLAYING;
                    // Reset the clock so there isn't a frame jump
                    clock.restart();
                }

                // Start a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return &&
                    state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                    wave = 0;
                    score = 0;

                    // Prepare the gun and ammo for next game
                    currentBullet = 0;
                    bulletsSpare = handBulletsSpare;
                    bulletsInClip = handBulletsInClip;
                    clipSize = handClipSize;
                    fireRate = handFireRate;



                    // Reset the player's stats
                    player.resetPlayerStats();
                }

                if (state == State::PLAYING)
                {
                    // Reloading
                    if (event.key.code == Keyboard::R)
                    {
                        if (bulletsSpare >= clipSize)
                        {
                            // Plenty of bullets. Reload.
                            bulletsInClip = clipSize;
                            bulletsSpare -= clipSize;
                            reload.play();
                        }
                        else if (bulletsSpare > 0)
                        {
                            // Only few bullets left
                            bulletsInClip = bulletsSpare;
                            bulletsSpare = 0;
                            reload.play();
                        }
                        else
                        {
                            // More here soon?!
                            reloadFailed.play();
                        }
                    }

                    // Inventory 
                    if (event.key.code == Keyboard::Tab) {

                        if (!m_inventoryActive) {

                            m_inventoryActive = true;
                        }
                        else if (m_inventoryActive) {

                            m_inventoryActive = false;
                        }

                    }

                    //Craft
                    if (event.key.code == Keyboard::Q)
                    {
                        state = State::CRAFT;

                    }
                }
            }
        }
        //Craft item
        if (state == State::CRAFT)
        {
            // moving up and down
            if (event.type == Event::KeyReleased)
            {
                //move up
                if (event.key.code == Keyboard::W)
                {
                    select.MoveUp();
                }
                //move down
                if (event.key.code == Keyboard::S)
                {
                    select.MoveDown();
                }
                // keypress enter to craft
                if (event.key.code == Keyboard::LShift)
                {
                    // craft wood sword
                    if (select.GetPressed() == 0 && numTreePickup == 3)
                    {
                    }
                    // craft stone sword
                    else if (select.GetPressed() == 1 && numTreePickup == 1 && numStonePickup == 2)
                    {
                    }
                    // craft iron sword
                    else if (select.GetPressed() == 2 && numTreePickup == 1 && numIronPickup == 2)
                    {
                    }
                    // craft arrow
                    else if (select.GetPressed() == 3 && numTreePickup == 1 && numStonePickup == 1)
                    {
                    }
                    // exit the craft
                    else if (select.GetPressed() == 4 && state == State::CRAFT)
                    {
                        state = State::PLAYING;
                        clock.restart();
                    }
                    else
                    {
                        if (!m_EnoughResoures) {

                            m_EnoughResoures = true;
                        }
                        else if (m_EnoughResoures) {

                            m_EnoughResoures = false;
                        }
                    }
                }
            }
        }
    }

    // Handle the player quitting
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        m_Window.close();
    }

    // Handle controls while playing
    if (state == State::PLAYING)
    {
        // Handle the pressing and releasing of the WASD keys
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            player.moveUp();
        }
        else
        {
            player.stopUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player.moveDown();
        }
        else
        {
            player.stopDown();
        }

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            player.moveLeft();
        }
        else
        {
            player.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            player.moveRight();
        }
        else
        {
            player.stopRight();
        }
        
        // Fire a bullet
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            player.getAttack(10);
            if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
            {

                // Pass the centre of the player and the centre of the crosshair
                // to the shoot function
                bullets[currentBullet].shoot(
                    player.getCenter().x, player.getCenter().y,
                    mouseWorldPosition.x, mouseWorldPosition.y);
                bullets[currentBullet].setRange(35);
                currentBullet++;
                if (currentBullet > 99)
                {
                    currentBullet = 0;
                }
                lastPressed = gameTimeTotal;
                shoot.play();
                bulletsInClip--;
            }

        } // End fire a bullet
        else
        {
            player.getAttack(9);
        }
        if (Keyboard::isKeyPressed(Keyboard::Num1))
        {
            // Equip Hand
            player.getAttack(9);
            handEquipped = true;
            woodSwordEquipped = false;
            stoneSwordEquipped = false;
            ironSwordEquipped = false;
            arrowEquipped = false;

            currentBullet = handCurrentBullet;
            bulletsSpare = handBulletsSpare;
            bulletsInClip = handBulletsInClip;
            clipSize = handClipSize;
            fireRate = handFireRate;
        }

        if (Keyboard::isKeyPressed(Keyboard::Num2))
        {
            // Equip Wood Sword if unlocked
            player.getAttack(2);
            handEquipped = false;
            woodSwordEquipped = true;
            stoneSwordEquipped = false;
            ironSwordEquipped = false;
            arrowEquipped = false;
            
            // Equipping the correct parameters for the Wood Sword
            currentBullet = woodSwordCurrentBullet;
            bulletsSpare = woodSwordBulletsSpare;
            bulletsInClip = woodSwordBulletsInClip;
            clipSize = woodSwordClipSize;
            fireRate = woodSwordFireRate;
        }

        if (Keyboard::isKeyPressed(Keyboard::Num3))
        {
            // Equip Stone Sword if unlocked
            player.getAttack(3);
            handEquipped = false;
            woodSwordEquipped = false;
            stoneSwordEquipped = true;
            ironSwordEquipped = false;
            arrowEquipped = false;
            // Equipping the correct parameters for the Stone Sword
            currentBullet = stoneSwordCurrentBullet;
            bulletsSpare = stoneSwordBulletsSpare;
            bulletsInClip = stoneSwordBulletsInClip;
            clipSize = stoneSwordClipSize;
            fireRate = stoneSwordFireRate;
        }

        if (Keyboard::isKeyPressed(Keyboard::Num4))
        {
            // Equip Iron Sword if unlocked
            player.getAttack(4);
            handEquipped = false;
            woodSwordEquipped = false;
            stoneSwordEquipped = false;
            ironSwordEquipped = true;
            arrowEquipped = false;

            // Equipping the correct parameters for the Iron Sword
            currentBullet = ironSwordCurrentBullet;
            bulletsSpare = ironSwordBulletsSpare;
            bulletsInClip = ironSwordBulletsInClip;
            clipSize = ironSwordClipSize;
            fireRate = ironSwordFireRate;
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Num5))
        {
            // Equip arrow if unlocked
            player.getAttack(5);
            handEquipped = false;
            woodSwordEquipped = false;
            stoneSwordEquipped = false;
            ironSwordEquipped = false;
            arrowEquipped = true;

            // Equipping the correct parameters for the arrow
            currentBullet = arrowCurrentBullet;
            bulletsSpare = arrowBulletsSpare;
            bulletsInClip = arrowBulletsInClip;
            clipSize = arrowClipSize;
            fireRate = arrowFireRate;
        }
        // Update ammo to corresponding gun
        if (handEquipped)
        {
            handCurrentBullet = currentBullet;
            handBulletsSpare = bulletsSpare;
            handBulletsInClip = bulletsInClip;
            handClipSize = clipSize;
            handFireRate = fireRate;
            bullets[currentBullet].setRange(35);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.getAttack(10);
            }
            else
            {
                player.getAttack(9);
            }
        }
        else if (woodSwordEquipped)
        {
            woodSwordCurrentBullet = currentBullet;
            woodSwordBulletsSpare = bulletsSpare;
            woodSwordBulletsInClip = bulletsInClip;
            woodSwordClipSize = clipSize;
            woodSwordFireRate = fireRate;
            bullets[currentBullet].setRange(50);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.getAttack(1);
            }
            else
            {
                player.getAttack(2);
            }
        }
        else if (stoneSwordEquipped)
        {
            stoneSwordCurrentBullet = currentBullet;
            stoneSwordBulletsSpare = bulletsSpare;
            stoneSwordBulletsInClip = bulletsInClip;
            stoneSwordClipSize = clipSize;
            stoneSwordFireRate = fireRate;
            bullets[currentBullet].setRange(60); 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.getAttack(7);
            }
            else
            {
                player.getAttack(3);
            }
        }
        else if (ironSwordEquipped)
        {
            ironSwordCurrentBullet = currentBullet;
            ironSwordBulletsSpare = bulletsSpare;
            ironSwordBulletsInClip = bulletsInClip;
            ironSwordClipSize = clipSize;
            ironSwordFireRate = fireRate;
            bullets[currentBullet].setRange(66);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.getAttack(6);
            }
            else
            {
                player.getAttack(4);
            }
            
        }
        else if (arrowEquipped)
        {
            arrowCurrentBullet = currentBullet;
            arrowBulletsSpare = bulletsSpare;
            arrowBulletsInClip = bulletsInClip;
            arrowClipSize = clipSize;
            arrowFireRate = fireRate;
            bullets[currentBullet].setRange(1000);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                player.getAttack(8);
            }
            else
            {
                player.getAttack(5);
            }
        }
    }

    if (event.key.code == Keyboard::Space)
    {
        // Continuing to the game after pressing space bar
        std::cout << "Space";
        state = State::PLAYING;
    }

    if (state == State::PLAYING)
    {
        // Increase the wave number
        wave++;

        // Prepare thelevel
        // We will modify the next two lines later
        Vector2i worldSize = manageLevel.getLevelSize();
        
        arena.width = worldSize.x * TILE_SIZE;
        arena.height = worldSize.y * TILE_SIZE;
        arena.left = 0;
        arena.top = 0;
        // Pass the vertex array by reference


        

        // Configure the pick-ups
        /*
        healthPickup.setArena(arena);
        ammoPickup.setArena(arena);
        moneyPickup.setArena(arena);
        */
        // if ((wave % 5) == 0)
        //
        //	//If Wave is a multiple of 5 then spawn a boss enemy
        //	// Create a horde of zombies
        //	//numZombies = 1;
        //	//
        //	//// Delete the previously allocated memory (if it exists)
        //	//delete[] zombies;
        //	//zombies = createHorde(numZombies, arena);
        //	//numZombiesAlive = numZombies;
        //

        // Play the powerup sound
        powerup.play();

        // Reset the clock so there isn't a frame jump
        clock.restart();
    }

    // Handle the levelling up state
    if (state == State::LEVELING_UP)
    {
        // Handle the player levelling up
        if (event.key.code == Keyboard::Num1)
        {
            if (score >= 300)
            {
                // Increase fire rate
                handFireRate++;
                woodSwordFireRate++;
                stoneSwordFireRate++;
                ironSwordFireRate++;
                score -= 300;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }

        if (event.key.code == Keyboard::Num2)
        {
            if (score >= 300)
            {
                // Increase clip size by 1.5x
                clipSize = clipSize + (clipSize / 2);
                score -= 300;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }

        if (event.key.code == Keyboard::Num3)
        {
            if (score >= 300)
            {
                // Increase health by 20HP
                player.upgradeHealth();
                score -= 300;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }

        if (event.key.code == Keyboard::Num4)
        {
            if (score >= 300)
            {
                // Increase speed by 40%
                player.upgradeSpeed();
                score -= 300;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }
        /*
        if (event.key.code == Keyboard::Num5)
        {
            // Upgrading all pickups
            if (score >= 300)
            {
                healthPickup.upgrade();
                ammoPickup.upgrade();
                moneyPickup.upgrade();
                score -= 300;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }
        */
        if (event.key.code == Keyboard::Num6)
        {
            if (score >= 1000)
            {
                // SMG UPGRADE (upgrade all smg stats by 2)
                woodSwordCurrentBullet *= 2;
                woodSwordBulletsSpare *= 2;
                woodSwordBulletsInClip *= 2;
                woodSwordClipSize *= 2;
                woodSwordFireRate *= 2;

                score -= 1000;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }

        if (event.key.code == Keyboard::Num7)
        {
            // Max ammo upgrade
            if (score >= 500)
            {
                bulletsSpare = 500;

                score -= 500;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }

        if (event.key.code == Keyboard::Num8)
        {
            // RAILGUN UPGRADE (UPGRADE ALL STATS BY 2)
            if (score >= 4000)
            {
                // SMG UPGRADE (upgrade all smg stats by 2)
                stoneSwordCurrentBullet *= 2;
                stoneSwordBulletsSpare *= 2;
                stoneSwordBulletsInClip *= 2;
                stoneSwordClipSize *= 2;
                stoneSwordFireRate *= 2;

                score -= 4000;
                buySuccess.play();
            }
            else
            {
                buyFailed.play();
            }
        }
    }
}