

#pragma once
//Including All Header files and libraries needed
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <iostream>
#include <assert.h>
#include "Zombie.h"
#include "LevelManager.h"
#include "State.h"
#include "TextureHolder.h"
#include "Player.h"
#include "Bullet.h"
#include "Pickup.h"

using namespace sf;

class Engine
{
public:
    //int loadLevel(VertexArray& rVA);

   
 

    Engine(TextureHolder holder);
    void run();
    void input();
    void draw();
    void loadSounds();

    std::list<Zombie*> createHorde(int numZombies, IntRect arena);
    std::list<Zombie*> createEnemies(int numZombies, Vector2f position, int type);

    Zombie* createIllusions(Vector2f playerPosition);
    


private:

    int numberOnList = 0;
    //variable to store in which position of the array is the real illusionist
    int m_realOne;

    bool m_test = false;
    
    //are illusions activated
    bool m_illusions = false;
   
    //array for the number of illusionist enemies
    Zombie* Illusionist = new Zombie[4];
    //this array will handle the illusions created
    Zombie* Illusions = NULL;

    //Level Manager Object
    LevelManager manageLevel;

    //Horde Object
    //CreateHorde
    //Zombie List

    /*
        LIST OF VARIABLES NEEDED FOR OTHER CLASSES
    */
    int TILE_SIZE;
    // Prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
    //Gun Variables
	int currentBullet = 1;
	int bulletsSpare = 12;
	int bulletsInClip = 12;
	int clipSize = 12;
	float fireRate = 1;
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
    // About the game
	int score = 0;
	int hiScore = 0;
    int wave = 1;
    // Weapons Equipped
	bool handgunEquipped = true;
	bool smgEquipped = false;
	bool railgunEquipped = false;
    
    // Update Function For All Classes
    void update(float dtAsSeconds);

    // A regular RenderWindow
	RenderWindow m_Window;

    //view for the background
	View m_BGMainView;

    //view for the background
	View mainView;

    //State ENUM for 
    State state;

    /**
     * TIME VARIABLES
    */
	// Here is our clock for timing everything
	Clock clock;

	// How long has the PLAYING state been active
	Time gameTimeTotal;

    // When was the fire button last pressed?
	Time lastPressed;

    // What time was the last update
	Time timeSinceLastUpdate;

    //Frame Measurements
    // When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

    /*  
        VECTOR VARIABLES
    */
    // Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;

	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

    //Game Resolution
    Vector2f resolution;

    // Create an instance of the Player class
	Player player;

    // The boundaries of the arena
	IntRect arena;

    // Create the background
	VertexArray background;

    //Textures
    // Here is the instabce of TextureHolder
	

    //Text Variables
    Text zombiesRemainingText;
	Text hiScoreText;
	Text scoreText;
	Text ammoText;
	Text levelUpText;
	Text gameOverText;
	Text pausedText;
	Text waveNumberText;

    //Texture Variables
    Texture textureBackground;
    Texture textureAmmoIcon;
    Texture textureCrosshair;
    Texture textureGameOver;

    //Sprites variables
    Sprite spriteCrosshair;
    Sprite spriteGameOver;
    Sprite spriteAmmoIcon;

    //SoundBuffer Variables
    SoundBuffer splatBuffer;
    SoundBuffer shootBuffer;
    SoundBuffer hitBuffer;
    SoundBuffer reloadBuffer;
    SoundBuffer reloadFailedBuffer;
    SoundBuffer buyFailedBuffer;
    SoundBuffer buySuccessBuffer;
    SoundBuffer powerupBuffer;
    SoundBuffer pickupBuffer;

    //Sound Variables
    Sound hit;
    Sound splat; //sf::
    Sound shoot;
    Sound reload;
    Sound reloadFailed;
    Sound buyFailed;
    Sound buySuccess;
    Sound powerup;
    Sound pickup;
    //Bar Variables
    // Health bar
	RectangleShape healthBar;
    //Hunger Bar
    RectangleShape hungerBar;
    float HungerBarStartWidth = 100;
    float HungerTickAmount = 0.1;
    float HungerBarHeight = 40;
    float currentHunger = HungerBarStartWidth;



    //Create PickUps
    // Create a couple of pickups
	Pickup healthPickup = Pickup(1);
	Pickup ammoPickup = Pickup(2);
	Pickup moneyPickup = Pickup(3);

    //Zombie List
    Zombie* zombies = NULL;

	//changing the array to a list
	std::list<Zombie*> m_EnemiesList;

    // 1000 bullets should do
    Bullet bullets[1000];


    //bullets for the enemies
    Bullet enemyBullets[1000];

    //cooldown for the shooting of the enemies
    float m_cooldown = 3.0f;

};
    