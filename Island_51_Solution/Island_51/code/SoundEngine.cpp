#include "Engine.h"


void Engine::loadSounds(){
	//Ai Voice Over Intro
	introVoiceBuffer.loadFromFile("sound/introVoice.wav");
	introVoice.setBuffer(introVoiceBuffer);

	winVoiceBuffer.loadFromFile("sound/winVoice.wav");
	winVoice.setBuffer(winVoiceBuffer);

    // Prepare the hit sound
	hitBuffer.loadFromFile("sound/hit.wav");
	hit.setBuffer(hitBuffer);
	//
	//// Prepare the splat sound
	splatBuffer.loadFromFile("sound/splat.wav");
	splat.setBuffer(splatBuffer);
	//
	//// Prepare the punch Sound
	punchBuffer.loadFromFile("sound/Punch.wav");
	punch.setBuffer(punchBuffer);

	//Prepare the bow sound
	bowShotBuffer.loadFromFile("sound/ArrowShot.wav");
	bowShot.setBuffer(bowShotBuffer);

	//// Prepare the powerup sound
	powerupBuffer.loadFromFile("sound/powerup.wav");
	powerup.setBuffer(powerupBuffer);
	//
	//// Prepare the pickup sound
	pickupBuffer.loadFromFile("sound/pickup.wav");
	pickup.setBuffer(pickupBuffer);
	
	// Prepare the GUI select sound
	guiseletionBuffer.loadFromFile("sound/guiselectionsounds.wav");
	guiseletionsound.setBuffer(guiseletionBuffer);
	
	// Prepare the Metal clashing sound
	metalclashBuffer.loadFromFile("sound/metalclashingsounds.wav");
	metalclashsound.setBuffer(metalclashBuffer);
	
	 //Prepare the game over sound
	gameoverBuffer.loadFromFile("sound/gameoversound.wav");
	gameoversound.setBuffer(gameoverBuffer);
	

	// Prepare player sighted sound
	spottedBuffer.loadFromFile("sound/SpottedGrowl.wav");
	spotted.setBuffer(spottedBuffer);

	// Prepare Game Started Sound
	gameStartBuffer.loadFromFile("sound/StartGameSound.wav");
	gameStart.setBuffer(gameStartBuffer);

	// Prepare Sword Sounds
	swordBuffer.loadFromFile("sound/swordSound.wav");
	sword.setBuffer(swordBuffer);

	//Prepare UI Sounds
	UI_SoundBuffer.loadFromFile("sound/UI_Select.wav");
	UI_Sound.setBuffer(UI_SoundBuffer);

	// Prepare Background Music for Island
	islandMusicBuffer.loadFromFile("sound/backgroundmusic.wav");
	islandMusic.setBuffer(islandMusicBuffer);

	// Prepare Background Music for Caves
	caveBackgroundMusicBuffer.loadFromFile("sound/cavebackgroundmusic.wav");
	caveBackgroundMusic.setBuffer(caveBackgroundMusicBuffer);

	// Prepare Background Music for MainMenu
	mainMenuMusicBuffer.loadFromFile("sound/mainmenumusic.wav");
	mainMenuMusic.setBuffer(mainMenuMusicBuffer);
	
	islandMusic.setLoop(true);
	islandMusic.setVolume(20);

	caveBackgroundMusic.setLoop(true);
	caveBackgroundMusic.setVolume(50);

	mainMenuMusic.setLoop(true);
	mainMenuMusic.setVolume(50);

	
	
}