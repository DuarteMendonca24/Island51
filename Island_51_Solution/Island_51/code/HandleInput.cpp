#include "Engine.h"

void Engine::input()
{
    Event event;
    while(m_Window.pollEvent(event))
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
					bulletsSpare = handgunBulletsSpare;
					bulletsInClip = handgunBulletsInClip;
					clipSize = handgunClipSize;
					fireRate = handgunFireRate;
					
					

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

            if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
            {

                // Pass the centre of the player and the centre of the crosshair
                // to the shoot function
                bullets[currentBullet].shoot(
                    player.getCenter().x, player.getCenter().y,
                    mouseWorldPosition.x, mouseWorldPosition.y);

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

        if (Keyboard::isKeyPressed(Keyboard::Num1))
        {
            // Equip Handgun
            player.changePlayerSprite(1);
            handgunEquipped = true;
            smgEquipped = false;
            railgunEquipped = false;

            currentBullet = handgunCurrentBullet;
            bulletsSpare = handgunBulletsSpare;
            bulletsInClip = handgunBulletsInClip;
            clipSize = handgunClipSize;
            fireRate = handgunFireRate;
        }

        if (Keyboard::isKeyPressed(Keyboard::Num2))
        {
            // Equip SMG if unlocked
            player.changePlayerSprite(2);
            handgunEquipped = false;
            smgEquipped = true;
            railgunEquipped = false;
            // Equipping the correct parameters for the smg
            currentBullet = smgCurrentBullet;
            bulletsSpare = smgBulletsSpare;
            bulletsInClip = smgBulletsInClip;
            clipSize = smgClipSize;
            fireRate = smgFireRate;
        }

        if (Keyboard::isKeyPressed(Keyboard::Num3))
        {
            // Equip Railgun if unlocked
            player.changePlayerSprite(3);
            handgunEquipped = false;
            smgEquipped = false;
            railgunEquipped = true;
            // Equipping the correct parameters for the railgun
            currentBullet = railgunCurrentBullet;
            bulletsSpare = railgunBulletsSpare;
            bulletsInClip = railgunBulletsInClip;
            clipSize = railgunClipSize;
            fireRate = railgunFireRate;
        }

        // Update ammo to corresponding gun
        if (handgunEquipped)
        {
            handgunCurrentBullet = currentBullet;
            handgunBulletsSpare = bulletsSpare;
            handgunBulletsInClip = bulletsInClip;
            handgunClipSize = clipSize;
            handgunFireRate = fireRate;
        }
        else if (smgEquipped)
        {
            smgCurrentBullet = currentBullet;
            smgBulletsSpare = bulletsSpare;
            smgBulletsInClip = bulletsInClip;
            smgClipSize = clipSize;
            smgFireRate = fireRate;
        }
        else if (railgunEquipped)
        {
            railgunCurrentBullet = currentBullet;
            railgunBulletsSpare = bulletsSpare;
            railgunBulletsInClip = bulletsInClip;
            railgunClipSize = clipSize;
            railgunFireRate = fireRate;
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
        healthPickup.setArena(arena);
        ammoPickup.setArena(arena);
        moneyPickup.setArena(arena);

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
                handgunFireRate++;
                smgFireRate++;
                railgunFireRate++;
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

        if (event.key.code == Keyboard::Num6)
        {
            if (score >= 1000)
            {
                // SMG UPGRADE (upgrade all smg stats by 2)
                smgCurrentBullet *= 2;
                smgBulletsSpare *= 2;
                smgBulletsInClip *= 2;
                smgClipSize *= 2;
                smgFireRate *= 2;

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
                railgunCurrentBullet *= 2;
                railgunBulletsSpare *= 2;
                railgunBulletsInClip *= 2;
                railgunClipSize *= 2;
                railgunFireRate *= 2;

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