#include "Engine.h"


Engine::Engine(){
	// Get the screen resolution and create an SFML window and View
	
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	state = State::GAME_OVER;


	m_Window.create(VideoMode(resolution.x, resolution.y), "Island 51",Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	//Load Level
	manageLevel.loadLevel(background);

	//Initiate Zombie Count
	numZombies = 5;
	numZombiesAlive = 5;
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
		//draw();

		//Zombie Amount Decpends on wave number
		numZombies = 5 * wave;

		// Delete the previously allocated memory (if it exists)
		//delete[] zombies;
				
		//m_EnemiesList = createHorde(numZombies, arena);
		m_EnemiesList = createHorde(numZombies, arena);
		numZombiesAlive = numZombies;
	}

    
}