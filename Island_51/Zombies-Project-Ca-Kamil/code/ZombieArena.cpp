#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ZombieArena.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"
#include "LevelManager.h"


using namespace sf;


int main()
{
	// Here is the instabce of TextureHolder
	TextureHolder holder;

	// The game will always be in one of four states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	

	// Create the background
	VertexArray background;

	// Load the texture for our background vertex array
	Texture textureBackground = TextureHolder::GetTexture(
		"graphics/background_sheet.png");

	// Prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = NULL;

	// 1000 bullets should do
	Bullet bullets[1000];
	int currentBullet;
	int bulletsSpare;
	int bulletsInClip;
	int clipSize;
	float fireRate;
	bool smgUpgrade = false;

	//Handgun parameters
	int handgunCurrentBullet = 0;
	int handgunBulletsSpare = 30;
	int handgunBulletsInClip = 15;
	int handgunClipSize = 15;
	float handgunFireRate = 0.6;

	//Smg Parameters 
	int smgCurrentBullet = 0;
	int smgBulletsSpare = 120;
	int smgBulletsInClip = 30;
	int smgClipSize = 30;
	float smgFireRate = 4;

	//Railgun Parameters
	int railgunCurrentBullet = 0;
	int railgunBulletsSpare = 20;
	int railgunBulletsInClip = 5;
	int railgunClipSize = 5;
	float railgunFireRate = 0.4;

	// When was the fire button last pressed?
	Time lastPressed;

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);
	Pickup moneyPickup(3);

	// About the game
	int score = 0;
	int hiScore = 0;

	// For the home/game over screen
	Sprite spriteGameOver;
	Texture textureGameOver = TextureHolder::GetTexture("graphics/background.png");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Create a view for the HUD
	View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a sprite for the ammo icon
	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	// Load the font
	Font font;
	font.loadFromFile("fonts/zombiecontrol.ttf");

	// Paused
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");

	// Game Over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(250, 850);
	gameOverText.setString("Press Enter to play");

	// Levelling up
	Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increase rate of fire || 300 points" <<
		"\n2- Increase clip size by x1.5 || 300 points" <<
		"\n3- Increase max health by 20HP || 300 points" <<
		"\n4- Increase run speed by x1.4 || 300 points" <<
		"\n5- More Pick Ups || 300 points" <<
		"\n6- SMG Weapon Upgrade || 1000 points"<<
		"\n7- Refill ammo + health (max)"<<
		"\n8- RailGun Weapon Upgrade || 4000 points"
		"\nSpace to Play Game";
	levelUpText.setString(levelUpStream.str());

	// Ammo
	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(200, 980);

	// Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	// Hi Score
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// Zombies remaining
	Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(1500, 980);
	zombiesRemainingText.setString("Zombies: 100");

	// Weapons Equipped
	bool handgunEquipped = true;
	bool smgEquipped = false;
	bool railgunEquipped = false;

	// Wave number
	int wave = 0;
	Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition(1250, 980);
	waveNumberText.setString("Wave: 0");

	// Health bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);
		
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

	// Prepare the hit sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	SoundBuffer splatBuffer;
	splatBuffer.loadFromFile("sound/splat.wav");
	sf::Sound splat;
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sound/shoot.wav");
	Sound shoot;
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	SoundBuffer reloadBuffer;
	reloadBuffer.loadFromFile("sound/reload.wav");
	Sound reload;
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	SoundBuffer reloadFailedBuffer;
	reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	//Prepare the failed buy sound
	SoundBuffer buyFailedBuffer;
	buyFailedBuffer.loadFromFile("sound/notBought.wav");
	Sound buyFailed;
	buyFailed.setBuffer(buyFailedBuffer);

	//Prepare the successful buy sound
	SoundBuffer buySuccessBuffer;
	buySuccessBuffer.loadFromFile("sound/bought.wav");
	Sound buySuccess;
	buySuccess.setBuffer(buySuccessBuffer);

	// Prepare the powerup sound
	SoundBuffer powerupBuffer;
	powerupBuffer.loadFromFile("sound/powerup.wav");
	Sound powerup;
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("sound/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
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
		}// End event polling


		 // Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
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

			if (Keyboard::isKeyPressed(Keyboard::Num1))
			{
				//Equip Handgun
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
				//Equip SMG if unlocked
				player.changePlayerSprite(2);
				handgunEquipped = false;
				smgEquipped = true;
				railgunEquipped = false;
				//Equipping the correct parameters for the smg
				currentBullet = smgCurrentBullet;
				bulletsSpare = smgBulletsSpare;
				bulletsInClip = smgBulletsInClip;
				clipSize = smgClipSize;
				fireRate = smgFireRate;
			}

			if (Keyboard::isKeyPressed(Keyboard::Num3))
			{
				//Equip Railgun if unlocked
				player.changePlayerSprite(3);
				handgunEquipped = false;
				smgEquipped = false;
				railgunEquipped = true;
				//Equipping the correct parameters for the railgun
				currentBullet = railgunCurrentBullet;
				bulletsSpare = railgunBulletsSpare;
				bulletsInClip = railgunBulletsInClip;
				clipSize = railgunClipSize;
				fireRate = railgunFireRate;
			}

			//Update ammo to corresponding gun
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


			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (gameTimeTotal.asMilliseconds()
					- lastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
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

			}// End fire a bullet

		}// End WASD while playing

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
				//Upgrading all pickups
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
				if ((score >= 1000)&&(!smgUpgrade))
				{
					//SMG UPGRADE (upgrade all smg stats by 2)
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
				//Max ammo upgrade
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
				//RAILGUN UPGRADE (UPGRADE ALL STATS BY 2)
				if (score >= 4000)
				{
					//SMG UPGRADE (upgrade all smg stats by 2)
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


			if (event.key.code == Keyboard::Space)
			{
				//Continuing to the game after pressing space bar
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Increase the wave number
				wave++;

				// Prepare thelevel
				// We will modify the next two lines later
				arena.width = 500 * wave;
				arena.height = 500 * wave;
				arena.left = 0;
				arena.top = 0;
				LevelManager lvlManager;
				// Pass the vertex array by reference 
				
				// to the createBackground function
				int tileSize = lvlManager.loadLevel(background);

				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Configure the pick-ups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);
				moneyPickup.setArena(arena);


				if ((wave % 5) == 0)
				{
					//If Wave is a multiple of 5 then spawn a boss enemy
					// Create a horde of zombies
					numZombies = 1;

					// Delete the previously allocated memory (if it exists)
					delete[] zombies;
					zombies = createHorde(numZombies, arena);
					numZombiesAlive = numZombies;
				}
				else
				{
					// Create a horde of zombies
					numZombies = 5 * wave;

					// Delete the previously allocated memory (if it exists)
					delete[] zombies;
					zombies = createHorde(numZombies, arena);
					numZombiesAlive = numZombies;
				}
				

				



				// Play the powerup sound
				powerup.play();

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		}// End levelling up

		 /*
		 ****************
		 UPDATE THE FRAME
		 ****************
		 */
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;
			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			// Set the crosshair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);

			// Update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			// Make a note of the players new position
			Vector2f playerPosition(player.getCenter());

			// Make the view centre around the player				
			mainView.setCenter(player.getCenter());

			// Loop through each Zombie and update them
			for (int i = 0; i < numZombies; i++)
			{
				if (zombies[i].isAlive())
				{
					zombies[i].update(dt.asSeconds(), playerPosition);
				}
			}

			// Update any bullets that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}

			// Update the pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);
			moneyPickup.update(dtAsSeconds);

			// Collision detection
			// Have any zombies been shot?
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numZombies; j++)
				{
				{
					if (bullets[i].isInFlight() && 
						zombies[j].isAlive())
					{
						if (bullets[i].getPosition().intersects
							(zombies[j].getPosition()))
						{
							//Stop the bullet unless the equipped gun is the railgun
							if (!railgunEquipped)
							{
								// Stop the bullet
								bullets[i].stop();
							}

							

							// Register the hit and see if it was a kill
							if (zombies[j].hit()) {
								// Not just a hit but a kill too
								//Custom scores for each zombie type
								score += zombies[j].killValue();
								//spawn another zombie when killed
								zombies[j].spawn(zombies[j].getPosCoordinates().x, zombies[j].getPosCoordinates().y,1,1);
								if (wave >= hiScore)
								{
									hiScore = wave;
								}
								
								numZombiesAlive--;

								// When all the zombies are dead (again)
								if (numZombiesAlive == 0) {
									state = State::LEVELING_UP;
								}
							}	

							// Make a splat sound
							splat.play();
							
						}
					}

				}
			}// End zombie being shot

			// Have any zombies touched the player			
			for (int i = 0; i < numZombies; i++)
			{
				if (player.getPosition().intersects
					(zombies[i].getPosition()) && zombies[i].isAlive())
				{

					if (player.hit(gameTimeTotal))
					{
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
			}// End player touched

			// Has the player touched health pickup
			if (player.getPosition().intersects
				(healthPickup.getPosition()) && healthPickup.isSpawned())
			{
				player.increaseHealthLevel(healthPickup.gotIt());
				// Play a sound
				pickup.play();
				
			}

			// Has the player touched ammo pickup
			if (player.getPosition().intersects
				(ammoPickup.getPosition()) && ammoPickup.isSpawned())
			{
				bulletsSpare += ammoPickup.gotIt();
				// Play a sound
				reload.play();
				
			}

			// Has the player touched ammo pickup
			if (player.getPosition().intersects
			(moneyPickup.getPosition()) && moneyPickup.isSpawned())
			{
				score += moneyPickup.gotIt();
				// Play a sound
				pickup.play();

			}

			// size up the health bar
			healthBar.setSize(Vector2f(player.getHealth() * 3, 70));

			// Increment the amount of time since the last HUD update
			timeSinceLastUpdate += dt;
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
			}// End HUD update

		}// End updating the scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);

			// Draw the zombies
			for (int i = 0; i < numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}

			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}

			// Draw the player
			window.draw(player.getSprite());

			// Draw the pickups is currently spawned
			if (ammoPickup.isSpawned())
			{
				window.draw(ammoPickup.getSprite());
			}
			if (healthPickup.isSpawned())
			{
				window.draw(healthPickup.getSprite());
			}
			if (moneyPickup.isSpawned())
			{
				window.draw(moneyPickup.getSprite());
			}

			//Draw the crosshair
			window.draw(spriteCrosshair);

			// Switch to the HUD view
			window.setView(hudView);

			// Draw all the HUD elements
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);
		}

		if (state == State::LEVELING_UP)
		{
			window.draw(spriteGameOver);
			window.draw(levelUpText);
			// Update the score text again
			std::stringstream ssScore;
			ssScore << "Points:" << score;
			scoreText.setString(ssScore.str());
			window.draw(scoreText);
		}

		if (state == State::PAUSED)
		{
			window.draw(pausedText);
		}

		if (state == State::GAME_OVER)
		{
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
		}

		window.display();

	}// End game loop

	
}
return 0;
}