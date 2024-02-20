#include "Engine.h"


Engine::Engine() {

	CaveGeneration cave;
	cave.Start();
	// Get the screen resolution and create an SFML window and View
	loadSounds();
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	state = State::INTRO;

	
	m_Window.create(VideoMode(resolution.x, resolution.y), "Island 51", Style::Fullscreen);
	m_Window.setFramerateLimit(120);
	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	m_hudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));
	select.position(m_Window.getSize().x, m_Window.getSize().y);
	//Load Level
	m_ArrayLevel2 = manageLevel.loadLevel(background);
	m_ArrayLevel1 = cave.loadLevel(caveBackground);
	textureBackground = TextureHolder::GetTexture("graphics/tiles-sheet.png");
	textureCaveBackground = TextureHolder::GetTexture("graphics/cave-tiles-sheet.png");
	textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	textureMainMenu = TextureHolder::GetTexture("graphics/MainMenu.png");
	textureIntroComic = TextureHolder::GetTexture("graphics/introComic.png");
	textureWin = TextureHolder::GetTexture("graphics/winComic.png");
	textureHealthHunger = TextureHolder::GetTexture("graphics/HungerHealthbg.png");
	textureCraft = TextureHolder::GetTexture("graphics/craft.png");
	textureInventory = TextureHolder::GetTexture("graphics/inventory.png");
	texturePause = TextureHolder::GetTexture("graphics/pause.png");
	//Load Texture for Intro Comic
	spriteIntroComic.setTexture(textureIntroComic);
	spriteIntroComic.setPosition(resolution.x / 2 - 271, resolution.y / 2 - 394.5);
	spriteIntroComic.setScale(Vector2f(resolution.x / 1920, resolution.y / 1080));

	//Load texture for Win comic

	spriteWinComic.setTexture(textureWin);
	spriteWinComic.setPosition(resolution.x / 2 - 348, resolution.y / 2 - 521.5);
	spriteWinComic.setScale(Vector2f(resolution.x / 2112, resolution.y / 1188));

	//Load Texture for Ammo Icon

	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	//Load Texture for Crosshair

	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	//Load Texture for GameOver

	spriteMainMenu.setTexture(textureMainMenu);
	spriteMainMenu.setPosition(0, 0);

	//Load Texture for Health and Hunger bar

	spriteHealthHunger.setTexture(textureHealthHunger);
	spriteHealthHunger.setPosition(resolution.x -205, resolution.y - 85);

	//Load Texture for craft
	spriteCraft.setTexture(textureCraft);
	spriteCraft.setPosition(resolution.x / 2 - 500, resolution.y - 30);
	spriteCraft.setRotation(-70);

	//Load Texture for inventory
	spriteInventory.setTexture(textureInventory);
	spriteInventory.setPosition(resolution.x / 2 - 405, resolution.y - 50);
	spriteInventory.setScale(0.7,0.7);

	//Load Texture for pause
	spritePause.setTexture(texturePause);
	spritePause.setPosition(resolution.x / 2 - 325, resolution.y - 50);
	spritePause.setScale(0.7, 0.7);
	//Zombie Amount Decpends on wave number
	numZombies = 5 * wave;
	//the number of resource to spawn
	numResource = 20;
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
	m_weaponIcons[0].spawn(1, 1.1, resolution.x / 2 - 90, resolution.y - 55);
	m_weaponIcons[1].spawn(2, 1.1, resolution.x / 2 - 15, resolution.y - 65);
	m_weaponIcons[2].spawn(3, 1.1, resolution.x / 2 + 55, resolution.y - 65);
	m_weaponIcons[3].spawn(4, 1.1, resolution.x / 2 + 125, resolution.y - 65);
	m_weaponIcons[4].spawn(5, 1.1, resolution.x / 2 + 190, resolution.y - 65);
	//spawning weapon to be icons 
	m_weaponIcons2[0].spawn(1, 2.5, 50, 1000);
	m_weaponIcons2[1].spawn(2, 2, 50, 950);
	m_weaponIcons2[2].spawn(3, 2, 50, 950);
	m_weaponIcons2[3].spawn(4, 2, 50, 950);
	m_weaponIcons2[4].spawn(5, 2, 50, 950);

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
	//Changing color of illusionist bullets to red
	for (int i = 0; i != 100; ++i)
	{
		m_illusionsBullets[i].setColor(Color::Color(255, 0, 0));
	}


}
void Engine::run() {
	// Timing 	
	Clock clock;
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
		else if (state == State::WIN)
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

void GenerateCave()
{

}