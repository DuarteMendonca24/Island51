#include "Engine.h"


Engine::Engine(TextureHolder holder){
	// Get the screen resolution and create an SFML window and View
	
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	state = State::GAME_OVER;


	m_Window.create(VideoMode(resolution.x, resolution.y), "Island 51",Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	
	//Load Level
	TILE_SIZE = manageLevel.loadLevel(background);
	
	textureBackground = holder.GetTexture("graphics/background_sheet.png");
	textureAmmoIcon = holder.GetTexture("graphics/ammo_icon.png");
	textureCrosshair = holder.GetTexture("graphics/crosshair.png");
	textureGameOver = holder.GetTexture("graphics/background.png");

	//Load Texture for Ammo Icon

	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	//Load Texture for Crosshair

	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	//Load Texture for GameOver

	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	//Setting HungerBar Up 
	hungerBar.setSize(Vector2f(HungerBarStartWidth, HungerBarHeight));


	//Zombie Amount Decpends on wave number
	numZombies = 5 * wave;

	// Delete the previously allocated memory (if it exists)
	//delete[] zombies;

	//m_EnemiesList = createHorde(numZombies, arena);
	Vector2i worldSize = manageLevel.getLevelSize();
	m_EnemiesList = createHorde(numZombies, arena);
	numZombiesAlive = numZombies;
	IntRect arena;
	arena.width = worldSize.x * TILE_SIZE;
	arena.height = worldSize.y * TILE_SIZE;
	arena.left = 0;
	arena.top = 0;
	// Spawn the player in the middle of the arena
	player.spawn(arena, resolution, TILE_SIZE);

}

void Engine::run(){

    // Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time
		gameTimeTotal += dt;
		timeSinceLastUpdate = dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();

	}

    
}