#include "Engine.h"


void Engine::loadSounds(){

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
	//
	//// Prepare the reload sound
	reloadBuffer.loadFromFile("sound/reload.wav");
	reload.setBuffer(reloadBuffer);
	//
	//// Prepare the failed sound
	reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	reloadFailed.setBuffer(reloadFailedBuffer);
	//
	////Prepare the failed buy sound
	buyFailedBuffer.loadFromFile("sound/notBought.wav");
	buyFailed.setBuffer(buyFailedBuffer);
	//
	////Prepare the successful buy sound
	buySuccessBuffer.loadFromFile("sound/bought.wav");
	buySuccess.setBuffer(buySuccessBuffer);
	//
	//// Prepare the powerup sound
	powerupBuffer.loadFromFile("sound/powerup.wav");
	powerup.setBuffer(powerupBuffer);
	//
	//// Prepare the pickup sound
	pickupBuffer.loadFromFile("sound/pickup.wav");
	pickup.setBuffer(pickupBuffer);
	//
	//// Prepare the Enemy sound
	enemysoundBuffer.loadFromFile("sound/EnemySound/enemysound1.wav");
	enemysound.setBuffer(enemysoundBuffer);
	
	// Prepare the player grunts sound
	playergruntBuffer.loadFromFile("sound/playergrunts/playergrunt1.wav");
	playergruntsound.setBuffer(playergruntBuffer);
	
	// Prepare the walking grass sound
	grasswalkingBuffer.loadFromFile("sound/walkingsounds/grassound1.wav");
	grasswalkingsound.setBuffer(grasswalkingBuffer);
	
	// Prepare the walking sand sound
	sandwalkingBuffer.loadFromFile("sound/walkingsounds/Sandsound1.wav");
	sandwalkingsound.setBuffer(sandwalkingBuffer);
	
	// Prepare the breaking iron sound
	breakingironBuffer.loadFromFile("sound/breakironsound.wav");
	breakingironsound.setBuffer(breakingironBuffer);
	
	// Prepare the breaks stone sound
	breakstoneBuffer.loadFromFile("sound/breakstonesound.wav");
	breakstoneingsound.setBuffer(breakstoneBuffer);
	
	// Prepare the breaks wood sound
	breakingwoodBuffer.loadFromFile("sound/breakwoodsound.wav");
	breakingwoodsound.setBuffer(breakingwoodBuffer);
	
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

	// Prepare Background Music
	musicBuffer.loadFromFile("sound/backgroundmusic.wav");
	music.setBuffer(musicBuffer);
	
	music.setLoop(true);
	music.setVolume(20);

	
	
}