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
#include "HUD.h"
#include "Craft.h"
#include "Weapons.h"
#include "Timer.h"
#include "CaveGeneration.h"
using namespace sf;

static class Engine
{
public:
    //Creating Timer
    Timer headTime;
    Timer feetTime;
    Timer leftTime;
    Timer rightTime;

    //Horde Object
    //CreateHorde
    //Zombie List
    //Pickup List
    /*
        LIST OF VARIABLES NEEDED FOR OTHER CLASSES
    */
    std::list<Zombie*> createHorde(int numZombies, IntRect arena);
    std::list<Zombie*> createEnemies(int numZombies, Vector2f position, int type);
    std::list<Pickup*> createPickup(Vector2f position);
    std::list<Pickup*> createResorces(int numResource);
    std::list<Pickup*> createRespawnResorces(int numResource, float positionX, float positionY, int type);
    Engine();
    void run();
    void input();
    void draw();
    void loadSounds();
    int** getArrayLevel();
    int RandomBetween(int min, int max);

    Zombie* createIllusions(Vector2f playerPosition);

    // A regular RenderWindow
    RenderWindow m_Window;

    //Level Manager Object
    LevelManager manageLevel;
    bool playerInsideCave = true;

private:

    //used to write to file
    bool m_scoreFile = false;

    int numberOnList = 0;
    //variable to store in which position of the array is the real illusionist
    int m_realOne;

    bool m_illusionist = true;

    //are illusions activated
    bool m_illusions = false;

    //array for the number of illusionist enemies
    Zombie* Illusionist = new Zombie[4];
    //this array will handle the illusions created
    Zombie* Illusions = NULL;


    //TextureHolder object
    TextureHolder m_TextureHolder;

    //number of each type of pickup the player has 
    int numTreePickup =  10;
    int numStonePickup = 10;
    int numIronPickup =  10;
    int numSoulPickup =  10;

    //the tile size
    const int TILE_SIZE = 50;
    // Prepare for a horde of zombies
    int numZombies;
    int numZombiesAlive;
    // Prepare for a horde of resource
    int numResource;
    int numResourceAlive;
    //Gun Variables
    int currentBullet = 1;
    int bulletsInClip = 12;
    float fireRate = 1;
    //Hand parameters
    int handCurrentBullet = 0;
    int handBulletsInClip = 99999999999;
    float handFireRate = 0.4;
    //Wood Sword Parameters 
    int woodSwordCurrentBullet = 0;
    int woodSwordBulletsInClip = 0;
    float woodSwordFireRate = 0.6;
    //Stone Sword Parameters
    int stoneSwordCurrentBullet = 0;
    int stoneSwordBulletsInClip = 0;
    float stoneSwordFireRate = 1.0;
    //Iron Sword Parameters
    int ironSwordCurrentBullet = 0;
    int ironSwordBulletsInClip =0;
    float ironSwordFireRate = 3.0;
    //Arrow Parameters
    int arrowCurrentBullet = 0;
    int arrowBulletsInClip = 0;
    float arrowFireRate = 0.5;
    // About the game
    int m_score = 0;
    int m_hiScore = 0;
    int wave = 1;
    //array to get the scores from the file
    int m_scores[5];
    // Weapons Equipped
    bool handEquipped = true;
    bool woodSwordEquipped = false;
    bool stoneSwordEquipped = false;
    bool ironSwordEquipped = false;
    bool arrowEquipped = false;
    // Update Function For All Classes
    void update(float dtAsSeconds);

    //view for the background
    View m_BGMainView;

    //view for the background
    View mainView;

    //view for HUD
    View m_hudView;

    Hud m_hud;

    //to check if inevntory is active
    bool m_inventoryActive = false;


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

    //Create the cave Background
    VertexArray caveBackground;

    //Textures
    // Here is the instabce of TextureHolder


    //Buttons FloatRect objects hitboxes
    FloatRect startButtonHitBox;
    FloatRect exitButtonHitBox;
    //GUI Button Rectangles
    RectangleShape startButton;
    RectangleShape exitButton;
    // Button Colors
    //  Rectangle Colors
    Color startButtonColor = Color::Green;
    Color exitButtonColor = Color::Red;
    Color hoverOverColor = Color::Magenta;


    //Texture Variables
    Texture textureBackground;
    Texture textureCaveBackground;
    Texture textureIntroComic;
    Texture textureAmmoIcon;
    Texture textureCrosshair;
    Texture textureMainMenu;
    Texture GUI_background_Texture;
    Texture textureRule;
    Texture textureWin;
    
    //Sprites variables
    Sprite spriteCrosshair;
    Sprite spriteMainMenu;
    Sprite spriteAmmoIcon;
    Sprite spriteIntroComic;
    Sprite spriteWinComic;

    //SoundBuffer Variables

    SoundBuffer introVoiceBuffer;
    SoundBuffer splatBuffer;
    SoundBuffer punchBuffer;
    SoundBuffer bowShotBuffer;
    SoundBuffer hitBuffer;
    SoundBuffer reloadBuffer;
    SoundBuffer reloadFailedBuffer;
    SoundBuffer buyFailedBuffer;
    SoundBuffer buySuccessBuffer;
    SoundBuffer powerupBuffer;
    SoundBuffer pickupBuffer;
    SoundBuffer enemysoundBuffer;
    SoundBuffer playergruntBuffer;
    SoundBuffer grasswalkingBuffer;
    SoundBuffer sandwalkingBuffer;
    SoundBuffer breakingironBuffer;
    SoundBuffer breakstoneBuffer;
    SoundBuffer breakingwoodBuffer;
    SoundBuffer guiseletionBuffer;
    SoundBuffer metalclashBuffer;
    SoundBuffer gameoverBuffer;
    SoundBuffer musicBuffer;
    SoundBuffer spottedBuffer;
    SoundBuffer gameStartBuffer;
    SoundBuffer swordBuffer;
    SoundBuffer UI_SoundBuffer;
    SoundBuffer winVoiceBuffer;

    //Sound Variables
    Sound introVoice;
    Sound hit;
    Sound splat; 
    Sound punch;
    Sound bowShot;
    Sound reload;
    Sound reloadFailed;
    Sound buyFailed;
    Sound buySuccess;
    Sound powerup;
    Sound pickup;
    Sound enemysound;
    Sound playergruntsound;
    Sound grasswalkingsound;
    Sound sandwalkingsound;
    Sound breakingironsound;
    Sound breakstoneingsound;
    Sound breakingwoodsound;
    Sound guiseletionsound;
    Sound metalclashsound;
    Sound gameoversound;
    Sound music;
    Sound spotted;
    Sound gameStart;
    Sound sword;
    Sound UI_Sound;
    Sound winVoice;



    //Bar Variables

    float m_currentHunger = 200;

    float m_hungerTickAmount = 2.5;
    float dtSinceDrawUpdate;

    //Zombie List
    Zombie* zombies = NULL;
    //changing the array to a list
    std::list<Zombie*> m_EnemiesList;
    std::list<Pickup*> m_PickupList;

    //array to display inventory resource items
    Pickup m_inventoryIcons[4];

    //array to display inventory weapon items
    Weapons m_weaponIcons[5];
    Weapons m_weaponIcons2[5];

    // 1000 bullets should do
    Bullet bullets[1000];
    Bullet m_illusionsBullets[100];
    Bullet m_enemyBullets[100];
    //illusions fire rate
    float m_illusionsFireRate = 1;
    float m_shootingFireRate = 3;
    //craft item select
    Craft select;

    // Run will call all the private functions
    bool detectCollisions(Player& character);
    // The 2d array with the map for the level
    // A pointer to a pointer
    int** m_ArrayLevel1 = NULL;
    int** m_ArrayLevel2 = NULL;


    //Check the Resourse is enough
    bool m_EnoughResources = false;
    //Set time to display
    float m_SecondsSince = 0;

    //Check the weapons in inventory
    bool m_WoodWeaponActive = false;
    bool m_StoneWeaponActive = false;
    bool m_IronWeaponActive = false;
    bool m_BowWeaponActive = false;
    //Check the weapons in icon
    bool m_HandWeaponActive2 = false;
    bool m_WoodWeaponActive2 = false;
    bool m_StoneWeaponActive2 = false;
    bool m_IronWeaponActive2 = false;
    bool m_BowWeaponActive2 = false;
};
