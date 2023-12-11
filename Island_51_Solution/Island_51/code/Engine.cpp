#include "Engine.h"


Engine::Engine() {
	//Loading Sounds
	loadSounds();
	// Get the screen resolution and create an SFML window and View
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	//state = State::MAIN_MENU;
	state = State::INTRO;
	
	m_Window.create(VideoMode(resolution.x, resolution.y), "Island 51", Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	m_hudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));
	select.position(m_Window.getSize().x, m_Window.getSize().y);
	//Load Level
	m_ArrayLevel2 = manageLevel.loadLevel(background);
	textureBackground = TextureHolder::GetTexture("graphics/tiles-sheet.png");
	textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	textureMainMenu = TextureHolder::GetTexture("graphics/MainMenu.png");
	textureIntroComic = TextureHolder::GetTexture("graphics/introComic.png");

	//Load Texture for Intro Comic
	spriteIntroComic.setTexture(textureIntroComic);
	spriteIntroComic.setPosition(resolution.x/2 - 271, resolution.y / 2 - 394.5);
	spriteIntroComic.setScale(Vector2f(resolution.x/1920, resolution.y / 1080));

	//Load Text For Skipping Into



	//Load Texture for Ammo Icon

	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	//Load Texture for Crosshair

	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	//Load Texture for GameOver

	spriteMainMenu.setTexture(textureMainMenu);
	spriteMainMenu.setPosition(0, 0);


	//Zombie Amount Decpends on wave number
<<<<<<< Updated upstream
	numZombies = 5 * wave;
	//the number of resource to spawn
	numResource = 20;
=======
	numZombies = 10;
	//numResource = 5 * wave;

	numResource = 30;
	// Delete the previously allocated memory (if it exists)
	//delete[] zombies;

	//m_EnemiesList = createHorde(numZombies, arena);
>>>>>>> Stashed changes
	Vector2i worldSize = manageLevel.getLevelSize();
	m_EnemiesList = createHorde(numZombies, arena);
	numZombiesAlive = numZombies;
	m_PickupList = createResorces(numResource);
	numResourceAlive = numResource;
	IntRect arena;
	arena.width = worldSize.x * TILE_SIZE;
	arena.height = worldSize.y * TILE_SIZE;
	arena.left = 0;
	arena.top = 0;
	// Spawn the player in the middle of the arena
	player.spawn(arena, resolution, TILE_SIZE);


	int spawnersAvailable = manageLevel.getSpawnerCount();
	int chooseSpawner = manageLevel.RandomBetween(0, spawnersAvailable);
	Vector2i spawnLocation = manageLevel.getSpawner(chooseSpawner);

	Illusionist[0].spawn(spawnLocation.x, spawnLocation.y, 0, 1); // Top Illusionist
	Illusionist[1].spawn(spawnLocation.x, spawnLocation.y, 0, 1); // Top Illusionist

	//spawning resources to be icons in the inventory

	m_inventoryIcons[0].spawnPickup(4,100, 400, 3.5);
	m_inventoryIcons[1].spawnPickup(5,100, 500, 3.5);
	m_inventoryIcons[2].spawnPickup(6,100, 600, 3.5);
	m_inventoryIcons[3].spawnPickup(3,70, 680, 2.5);
	music.play();

	//spawning weapon to be icons in the inventory
<<<<<<< Updated upstream
	m_weaponIcons[0].spawn(1, 1.1, resolution.x / 2 + 375, resolution.y - 73);
	m_weaponIcons[1].spawn(2, 1.1, resolution.x / 2 + 445, resolution.y - 85);
	m_weaponIcons[2].spawn(3, 1.1, resolution.x / 2 + 515, resolution.y - 85);
	m_weaponIcons[3].spawn(4, 1.1, resolution.x / 2 + 585, resolution.y - 85);
	m_weaponIcons[4].spawn(5, 1.1, resolution.x / 2 + 650, resolution.y - 85);
=======
	m_weaponIcons[0].spawn(1, 1.1, resolution.x / 2 - 90, resolution.y - 65);
	m_weaponIcons[1].spawn(2, 1.1, resolution.x / 2 - 15, resolution.y - 85);
	m_weaponIcons[2].spawn(3, 1.1, resolution.x / 2 + 55, resolution.y - 85);
	m_weaponIcons[3].spawn(4, 1.1, resolution.x / 2 + 125, resolution.y - 85);
	m_weaponIcons[4].spawn(5, 1.1, resolution.x / 2 + 190, resolution.y - 85);
>>>>>>> Stashed changes
	//spawning weapon to be icons 
	m_weaponIcons2[0].spawn(1, 2.5, 50, 1000);
	m_weaponIcons2[1].spawn(2, 2, 50, 950);
	m_weaponIcons2[2].spawn(3, 2, 50, 950);
	m_weaponIcons2[3].spawn(4, 2, 50, 950);
	m_weaponIcons2[4].spawn(5, 2, 50, 950);

	//Reading the highscores from the file
	std::ifstream readFile;
	readFile.open("scores/Highscore.txt");

	//Reading in saved high score variables
	if (readFile.is_open()) {

		while (!readFile.eof()) {

			for (int i = 0; i < 5; i++)
			{
				readFile >> m_scores[i];

			}

		}
	}

	readFile.close();

	//Changing color of illusionist bullets to red
	for (int i = 0; i != 100; ++i)
	{
		m_illusionsBullets[i].changeColor(Color::Color(255, 0, 0));
	}


}
void Engine::run() {
	

	// Timing 	
	Clock clock;
	//Loading All sounds
	loadSounds();
	while (m_Window.isOpen())
	{
	
		Time dt = clock.restart();
		// Update the total game time
		gameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();
		dtSinceDrawUpdate += dt.asSeconds();
		timeSinceLastUpdate = dt;
		//Taking Player Input
		input();
		//If in Intro state draw and update asfast as possible
		if (state == State::INTRO)
		{
			draw();
			update(gameTimeTotal.asSeconds());
			
		}
		//Otherwise update game 100 times a seconds and draw 50 times a second
		else
		{
			
			if (dtSinceDrawUpdate > 0.01)
			{
				update(dtAsSeconds);
			}
			if (dtSinceDrawUpdate > 0.02)
			{
				draw();
				dtSinceDrawUpdate = 0;
			}
		}
		
		

	}


}

int** Engine::getArrayLevel()
{
	return m_ArrayLevel2;
}