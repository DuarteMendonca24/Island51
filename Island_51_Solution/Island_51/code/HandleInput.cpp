#include "Engine.h"

void Engine::input()
{
	Event event;

	while (m_Window.pollEvent(event))
	{

		if (event.type == Event::KeyPressed)
		{

			//Input for when the game is being played
			if (state == State::PLAYING) {


				// Pause a game while playing
				if (event.key.code == Keyboard::Enter)
				{
					
					state = State::PAUSED;
				}

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

				//close game
				if (event.key.code == Keyboard::Escape)
				{
					m_Window.close();
				}


			}
			else if (state == State::PAUSED) {
			
				// Restart while paused
			    if (event.key.code == Keyboard::Enter)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
			}
			else if (state == State::GAME_OVER) {

				// Restart while paused
				if (event.key.code == Keyboard::Enter)
				{
					//need to check if this code is doing something 
					state = State::LEVELING_UP;
					wave = 0;
					m_score = 0;

					// Prepare the gun and ammo for next game
					currentBullet = 0;
					bulletsSpare = handBulletsSpare;
					bulletsInClip = handBulletsInClip;
					clipSize = handClipSize;
					fireRate = handFireRate;



					// Reset the player's stats
					player.resetPlayerStats();
				}
			}
			else if (state == State::MAIN_MENU) {

				
				if (event.key.code == Keyboard::Num1) {

					state = State::PLAYING;
				}
				else if (event.key.code == Keyboard::Num2) {

					state = State::RULE;
				}
				else if (event.key.code == Keyboard::Num3) {

					state = State::HIGHSCORE;
				}
				else if (event.key.code == Keyboard::Num4) {

					m_Window.close();
				}

				//close game
				if (event.key.code == Keyboard::Escape)
				{
					m_Window.close();
				}


			}
			else if (state == State::RULE) {

				//to go back to main menu
				if (event.key.code == Keyboard::Escape)
				{
					state = State::MAIN_MENU;
				}
			}
			else if (state == State::HIGHSCORE) {

				//to go back to main menu
				if (event.key.code == Keyboard::Escape)
				{
					state = State::MAIN_MENU;
				}
			}
		}

		//Craft item needs to be outside because it checks for key release events
		if (state == State::CRAFT)
		{
			// Inventory 
			if (event.key.code == Keyboard::Tab) {
				if (!m_inventoryActive) {

					m_inventoryActive = true;
				}
				else if (m_inventoryActive) {

					m_inventoryActive = false;
				}

			}
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
					if (select.GetPressed() == 0 && numTreePickup >= 3)
					{
						woodSwordCurrentBullet = woodSwordCurrentBullet + 30;
						numTreePickup = numTreePickup - 3;
					}
					// craft stone sword
					else if (select.GetPressed() == 1 && numTreePickup >= 1 && numStonePickup >= 2)
					{
						stoneSwordCurrentBullet = stoneSwordCurrentBullet + 50;
						numTreePickup = numTreePickup - 1;
						numStonePickup = numStonePickup - 2;
					}
					// craft iron sword
					else if (select.GetPressed() == 2 && numTreePickup >= 1 && numIronPickup >= 2)
					{
						ironSwordCurrentBullet = ironSwordCurrentBullet + 70;
						numTreePickup = numTreePickup - 1;
						numIronPickup = numIronPickup - 2;
					}
					// craft arrow
					else if (select.GetPressed() == 3 && numTreePickup >= 1 && numStonePickup >= 1)
					{
						arrowCurrentBullet = arrowCurrentBullet + 20;
						numTreePickup = numTreePickup - 1;
						numStonePickup = numStonePickup - 1;
					}
					else if (select.GetPressed() == 4 && numTreePickup >= 1 && numStonePickup >= 1)
					{
						arrowCurrentBullet = arrowCurrentBullet + 20;
						numTreePickup = numTreePickup - 1;
						numStonePickup = numStonePickup - 1;
					}
					// exit the craft
					else if (select.GetPressed() == 5 && state == State::CRAFT)
					{
						state = State::PLAYING;
						clock.restart();
					}
					else
					{
						if (m_EnoughResources)
						{
							m_EnoughResources = false;
						}
						else if (!m_EnoughResources)
						{
							m_EnoughResources = true;
						}

					}
				}
			}
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
					bullets[currentBullet].setRange(40);
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
				bullets[currentBullet].setRange(40);
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
	}

}