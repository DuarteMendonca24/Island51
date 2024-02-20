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

	// Prepare Background Music
	musicBuffer.loadFromFile("sound/backgroundmusic.wav");
	music.setBuffer(musicBuffer);
	
	music.setLoop(true);
	music.setVolume(20);

	
	
}