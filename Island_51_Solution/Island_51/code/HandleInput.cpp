#include "Engine.h"

void Engine::input()
{
	Event event;

	
	while (m_Window.pollEvent(event))
	{
		// Checking that the key has be pressed
		if (event.type == Event::KeyPressed)
		{
			if (state == State::INTRO)
			{
				//Close Cutscene if enter is pressed
				if (event.key.code == Keyboard::Enter)
				{

					state = State::MAIN_MENU;
					introVoice.stop();
					UI_Sound.play();
					mainMenuMusic.play();
				}
			}
			if (state == State::WIN)
			{
				//Close Cutscene if enter is pressed
				if (event.key.code == Keyboard::Enter)
				{

					state = State::MAIN_MENU;
					winVoice.stop();
					UI_Sound.play();
				}
			}
			//Input for when the game is being played
			if (state == State::PLAYING) {


				// Pause a game while playing
				if (event.key.code == Keyboard::Enter)
				{
					// Showing the pasued game
					state = State::PAUSED;
				}

				// Inventory 
				if (event.key.code == Keyboard::M) {
					teleportEnemiesAndResources();
					if (!playerInsideCave) {

						playerInsideCave = true;
						mainMenuMusic.stop();
						islandMusic.stop();
						caveBackgroundMusic.play();
					}
					else if (playerInsideCave) {

						playerInsideCave = false;
						mainMenuMusic.stop();
						islandMusic.play();
						caveBackgroundMusic.stop();
					}

				}

				// Inventory 
				if (event.key.code == Keyboard::Tab) {
					UI_Sound.play();
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
					UI_Sound.play();
				}

				//close game
				if (event.key.code == Keyboard::Escape)
				{
					//m_Window.close();
					state = State::MAIN_MENU;
				}


			}
			// Showing the paused game 
			else if (state == State::PAUSED) {
			
				// Restart while paused
			    if (event.key.code == Keyboard::Enter)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
			}
			// Game Over
			else if (state == State::GAME_OVER) {

				state = State::MAIN_MENU;
				// Reset the player's stats
				player.resetPlayerStats();
				
			}
			// Going to the Main Menu
			else if (state == State::MAIN_MENU) {
				mainMenuMusic.play();
				// If 1 press play game from the menu
				if (event.key.code == Keyboard::Num1) {

					state = State::PLAYING;

					mainMenuMusic.stop();
					gameStart.play();
					islandMusic.play();
				}
				// If 2 press Check rule from the menu
				else if (event.key.code == Keyboard::Num2) {

					state = State::RULE;
					UI_Sound.play();
				}
				// If 3 press Check High Score from the menu
				else if (event.key.code == Keyboard::Num3) {

					state = State::HIGHSCORE;
					UI_Sound.play();
				}
				// If 4 press Check High Score from the menu
				else if (event.key.code == Keyboard::Num4) {

					UI_Sound.play();
					m_Window.close();

				}

				//close game
				if (event.key.code == Keyboard::Escape)
				{
					m_Window.close();
				}

			}
			// Ruels state
			else if (state == State::RULE) {

				//to go back to main menu
				if (event.key.code == Keyboard::Escape)
				{
					state = State::MAIN_MENU;
					UI_Sound.play();
				}
			}
			// Highs Score state
			else if (state == State::HIGHSCORE) {

				//to go back to main menu
				if (event.key.code == Keyboard::Escape)
				{
					state = State::MAIN_MENU;
					UI_Sound.play();
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
					UI_Sound.play();
				}
				//move down
				if (event.key.code == Keyboard::S)
				{
					select.MoveDown();
					UI_Sound.play();
				}
				// keypress enter to craft
				if (event.key.code == Keyboard::LShift)
				{
					// craft wood sword
					if (select.GetPressed() == 0 && numTreePickup >= 3)
					{
						woodSwordBulletsInClip = woodSwordBulletsInClip + 30;
						numTreePickup = numTreePickup - 3;
						pickup.play();
					}
					// craft stone sword
					else if (select.GetPressed() == 1 && numTreePickup >= 1 && numStonePickup >= 2)
					{
						stoneSwordBulletsInClip = stoneSwordBulletsInClip + 50;
						numTreePickup = numTreePickup - 1;
						numStonePickup = numStonePickup - 2;
						pickup.play();
					}
					// craft iron sword
					else if (select.GetPressed() == 2 && numTreePickup >= 1 && numIronPickup >= 2)
					{
						ironSwordBulletsInClip = ironSwordBulletsInClip + 60;
						numTreePickup = numTreePickup - 1;
						numIronPickup = numIronPickup - 2;
						pickup.play();
					}
					// craft arrow
					else if (select.GetPressed() == 3 && numTreePickup >= 2 && numStonePickup >= 2)
					{
						arrowBulletsInClip = arrowBulletsInClip + 20;
						numTreePickup = numTreePickup - 1;
						numStonePickup = numStonePickup - 1;
						pickup.play();
					}
					else if (select.GetPressed() == 4 && numSoulPickup >= 30)
					{
						state = State::WIN;
						numSoulPickup -= 30;
						pickup.play();


					}
					// exit the craft
					else if (select.GetPressed() == 5 && state == State::CRAFT)
					{
						state = State::PLAYING;
						clock.restart();
					}
					else
					{
						// having enough resources for the crafting 
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
			if ((Keyboard::isKeyPressed(Keyboard::W))&&(headTime.GetElapsedTime()>0.01f))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if ((Keyboard::isKeyPressed(Keyboard::S)) && (feetTime.GetElapsedTime() > 0.01f))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if ((Keyboard::isKeyPressed(Keyboard::A)) && (leftTime.GetElapsedTime() > 0.01f))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if ((Keyboard::isKeyPressed(Keyboard::D)) && (rightTime.GetElapsedTime() > 0.01f))
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
				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 500 / fireRate && bulletsInClip > 0)
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
					//Playing Accurate Sounds
					if (handEquipped)
					{
						punch.play();
						bullets[currentBullet].setColor(sf::Color::Color(0, 255, 0, 0));
					}
					else if (woodSwordEquipped)
					{
						sword.play();
						bullets[currentBullet].setColor(sf::Color::Color(0, 255, 0, 0));
					}
					else if (stoneSwordEquipped)
					{
						sword.play();
						bullets[currentBullet].setColor(sf::Color::Color(0, 255, 0, 0));
					}
					else if (ironSwordEquipped)
					{
						sword.play();
						bullets[currentBullet].setColor(sf::Color::Color(0, 255, 0, 0));
					}
					else if (arrowEquipped)
					{
						bowShot.play();
						bullets[currentBullet].setColor(sf::Color::Color(0, 255, 0));
					}
					else
					{
						pickup.play();
					}
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

				m_HandWeaponActive2 = false;
				m_WoodWeaponActive2 = true;
				m_StoneWeaponActive2 = true;
				m_IronWeaponActive2 = true;
				m_BowWeaponActive2 = true;

				currentBullet = handCurrentBullet;
				bulletsInClip = handBulletsInClip;
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

				m_HandWeaponActive2 = true;
				m_WoodWeaponActive2 = false;
				m_StoneWeaponActive2 = true;
				m_IronWeaponActive2 = true;
				m_BowWeaponActive2 = true;
				// Equipping the correct parameters for the Wood Sword
				currentBullet = woodSwordCurrentBullet;
				bulletsInClip = woodSwordBulletsInClip;
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

				m_HandWeaponActive2 = true;
				m_WoodWeaponActive2 = true;
				m_StoneWeaponActive2 = false;
				m_IronWeaponActive2 = true;
				m_BowWeaponActive2 = true;
				// Equipping the correct parameters for the Stone Sword
				currentBullet = stoneSwordCurrentBullet;
				bulletsInClip = stoneSwordBulletsInClip;
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

				m_HandWeaponActive2 = true;
				m_WoodWeaponActive2 = true;
				m_StoneWeaponActive2 = true;
				m_IronWeaponActive2 = false;
				m_BowWeaponActive2 = true;
				// Equipping the correct parameters for the Iron Sword
				currentBullet = ironSwordCurrentBullet;
				bulletsInClip = ironSwordBulletsInClip;
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

				m_HandWeaponActive2 = true;
				m_WoodWeaponActive2 = true;
				m_StoneWeaponActive2 = true;
				m_IronWeaponActive2 = true;
				m_BowWeaponActive2 = false;
				// Equipping the correct parameters for the arrow
				currentBullet = arrowCurrentBullet;
				bulletsInClip = arrowBulletsInClip;
				fireRate = arrowFireRate;
			}
			// Update ammo to corresponding gun
			if (handEquipped)
			{
				handCurrentBullet = currentBullet;
				handBulletsInClip = bulletsInClip;
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
				if (handBulletsInClip == 0)
				{
					handEquipped = true;
					woodSwordEquipped = false;
					stoneSwordEquipped = false;
					ironSwordEquipped = false;
					arrowEquipped = false;
					m_HandWeaponActive2 = true;
					currentBullet = handCurrentBullet;
					bulletsInClip = handBulletsInClip;
					fireRate = handFireRate;
				}
				else
				{
					m_HandWeaponActive2 = false;
				}
			}
			else if (woodSwordEquipped)
			{
				woodSwordCurrentBullet = currentBullet;
				woodSwordBulletsInClip = bulletsInClip;
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
				// Check if bullets are zero, switch to handEquipped
				if (woodSwordBulletsInClip == 0)
				{
					handEquipped = true;
					woodSwordEquipped = false;
					stoneSwordEquipped = false;
					ironSwordEquipped = false;
					arrowEquipped = false;
					m_WoodWeaponActive2 = true;
					currentBullet = handCurrentBullet;
					bulletsInClip = handBulletsInClip;
					fireRate = handFireRate;
				}
				else
				{
					m_WoodWeaponActive2 = false;
				}
			}
			else if (stoneSwordEquipped)
			{
				stoneSwordCurrentBullet = currentBullet;
				stoneSwordBulletsInClip = bulletsInClip;
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
				// Check if bullets are zero, switch to handEquipped
				if (stoneSwordBulletsInClip == 0)
				{
					handEquipped = true;
					woodSwordEquipped = false;
					stoneSwordEquipped = false;
					ironSwordEquipped = false;
					arrowEquipped = false;
					m_StoneWeaponActive2 = true;
					currentBullet = handCurrentBullet;
					bulletsInClip = handBulletsInClip;
					fireRate = handFireRate;
				}
				else
				{
					m_StoneWeaponActive2 = false;
				}
			}
			else if (ironSwordEquipped)
			{
				ironSwordCurrentBullet = currentBullet;
				ironSwordBulletsInClip = bulletsInClip;
				ironSwordFireRate = fireRate;
				bullets[currentBullet].setRange(66);
				m_IronWeaponActive2 = false;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					player.getAttack(6);
				}
				else
				{
					player.getAttack(4);
				}
				// Check if bullets are zero, switch to handEquipped
				if (ironSwordBulletsInClip == 0)
				{
					handEquipped = true;
					woodSwordEquipped = false;
					stoneSwordEquipped = false;
					ironSwordEquipped = false;
					arrowEquipped = false;
					m_IronWeaponActive2 = true;
					currentBullet = handCurrentBullet;
					bulletsInClip = handBulletsInClip;
					fireRate = handFireRate;
				}
				else
				{
					m_IronWeaponActive2 = false;
				}
			}
			else if (arrowEquipped)
			{
				arrowCurrentBullet = currentBullet;
				arrowBulletsInClip = bulletsInClip;
				arrowFireRate = fireRate;
				bullets[currentBullet].setRange(1000);
				m_BowWeaponActive2 = false;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					player.getAttack(8);
				}
				else
				{
					player.getAttack(5);
				}
				// Check if bullets are zero, switch to handEquipped
				if (arrowBulletsInClip == 0)
				{
					handEquipped = true;
					woodSwordEquipped = false;
					stoneSwordEquipped = false;
					ironSwordEquipped = false;
					arrowEquipped = false;

					m_BowWeaponActive2 = true;

					currentBullet = handCurrentBullet;
					bulletsInClip = handBulletsInClip;
					fireRate = handFireRate;
				}
				else
				{
					m_BowWeaponActive2 = false;
				}
			}
			// Check if bullets are zero, display melee weapon
			if (woodSwordBulletsInClip == 0)
			{
				m_WoodWeaponActive = true;
			}
			else
			{
				m_WoodWeaponActive = false;
			}
			if (stoneSwordBulletsInClip == 0)
			{
				m_StoneWeaponActive = true;
			}
			else
			{
				m_StoneWeaponActive = false;
			}
			if (ironSwordBulletsInClip == 0 )
			{
				m_IronWeaponActive = true;
			}
			else
			{
				m_IronWeaponActive = false;
			}
			if (arrowBulletsInClip == 0)
			{
				m_BowWeaponActive = true;
			}
			else
			{
				m_BowWeaponActive = false;
			}

			
			
		}
	}

}