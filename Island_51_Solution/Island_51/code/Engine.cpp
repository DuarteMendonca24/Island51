#include "Engine.h"


Engine::Engine() {
	// Get the screen resolution and create an SFML window and View
	//loadSounds();
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	state = State::MAIN_MENU;

	
	m_Window.create(VideoMode(resolution.x, resolution.y), "Island 51", Style::Default);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	m_hudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));
	select.position(m_Window.getSize().x, m_Window.getSize().y);
	//Load Level
	m_ArrayLevel2 = manageLevel.loadLevel(background);
	/*
	textureBackground = holder.GetTexture("graphics/tiles-sheet.png");
	textureAmmoIcon = holder.GetTexture("graphics/ammo_icon.png");
	textureCrosshair = holder.GetTexture("graphics/crosshair.png");
	textureGameOver = holder.GetTexture("graphics/background.png");
	*/
	textureBackground = TextureHolder::GetTexture("graphics/tiles-sheet.png");
	textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");

	textureMainMenu = TextureHolder::GetTexture("graphics/MainMenu.png");



	//Load Texture for Ammo Icon

	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	//Load Texture for Crosshair

	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	//Load Texture for GameOver

	spriteMainMenu.setTexture(textureMainMenu);
	spriteMainMenu.setPosition(0, 0);

	//Setting HungerBar Up 
	//hungerBar.setSize(Vector2f(HungerBarStartWidth, HungerBarHeight));


	//Zombie Amount Decpends on wave number
	numZombies = 5 * wave;
	//numResource = 5 * wave;

	numResource = 20;
	// Delete the previously allocated memory (if it exists)
	//delete[] zombies;

	//m_EnemiesList = createHorde(numZombies, arena);
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
	m_inventoryIcons[0].spawnPickup(3,100, 400, 3.5);
	m_inventoryIcons[1].spawnPickup(4,100, 500, 3.5);
	m_inventoryIcons[2].spawnPickup(5,100, 600, 3.5);

	music.play();

	//Reading the highscores from the file
	std::ifstream readFile;
	readFile.open("scores/Highscore.txt");

	if (readFile.is_open()) {

		while (!readFile.eof()) {

			for (int i = 0; i < 5; i++)
			{
				readFile >> m_scores[i];

			}

		}
	}

	readFile.close();



}
void Engine::run() {

	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
	
		Time dt = clock.restart();
		// Update the total game time
		gameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();
		dtSinceDrawUpdate += dt.asSeconds();
		timeSinceLastUpdate = dt;

		input();
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

int** Engine::getArrayLevel()
{
	return m_ArrayLevel2;
}