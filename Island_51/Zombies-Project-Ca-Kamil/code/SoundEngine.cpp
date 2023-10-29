#include "Engine.h"

void Engine::loadSounds(){
    // Prepare the hit sound
	hitBuffer.loadFromFile("sound/hit.wav");
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	splatBuffer.loadFromFile("sound/splat.wav");
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	shootBuffer.loadFromFile("sound/shoot.wav");
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	reloadBuffer.loadFromFile("sound/reload.wav");
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	reloadFailed.setBuffer(reloadFailedBuffer);

	//Prepare the failed buy sound
	buyFailedBuffer.loadFromFile("sound/notBought.wav");
	buyFailed.setBuffer(buyFailedBuffer);

	//Prepare the successful buy sound
	buySuccessBuffer.loadFromFile("sound/bought.wav");
	buySuccess.setBuffer(buySuccessBuffer);

	// Prepare the powerup sound
	powerupBuffer.loadFromFile("sound/powerup.wav");
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	pickupBuffer.loadFromFile("sound/pickup.wav");
	pickup.setBuffer(pickupBuffer);
}