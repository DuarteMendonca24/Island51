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

	//Step Sounds
	//step sound buffers
	cave_step1_buffer.loadFromFile("sound/StepsCave/step1.wav");
	cave_step2_buffer.loadFromFile("sound/StepsCave/step2.wav");
	cave_step3_buffer.loadFromFile("sound/StepsCave/step3.wav");
	cave_step4_buffer.loadFromFile("sound/StepsCave/step4.wav");
	cave_step5_buffer.loadFromFile("sound/StepsCave/step5.wav");
	island_step1_buffer.loadFromFile("sound/StepsIsland/step1.wav");
	island_step2_buffer.loadFromFile("sound/StepsIsland/step2.wav");
	island_step3_buffer.loadFromFile("sound/StepsIsland/step3.wav");
	island_step4_buffer.loadFromFile("sound/StepsIsland/step4.wav");
	island_step5_buffer.loadFromFile("sound/StepsIsland/step5.wav");
	island_step6_buffer.loadFromFile("sound/StepsIsland/step6.wav");
	island_step7_buffer.loadFromFile("sound/StepsIsland/step7.wav");
	island_step8_buffer.loadFromFile("sound/StepsIsland/step8.wav");
	//Cave Step Sounds
	cave_step1.setBuffer(cave_step1_buffer);
	cave_step2.setBuffer(cave_step2_buffer);
	cave_step3.setBuffer(cave_step3_buffer);
	cave_step4.setBuffer(cave_step4_buffer);
	cave_step5.setBuffer(cave_step5_buffer);

	//Island Step Sounds
	island_step1.setBuffer(island_step1_buffer);
	island_step2.setBuffer(island_step2_buffer);
	island_step3.setBuffer(island_step3_buffer);
	island_step4.setBuffer(island_step4_buffer);
	island_step5.setBuffer(island_step5_buffer);
	island_step6.setBuffer(island_step6_buffer);
	island_step7.setBuffer(island_step7_buffer);
	island_step8.setBuffer(island_step8_buffer);


	cave_step1.setVolume(20);
	cave_step2.setVolume(20);
	cave_step3.setVolume(20);
	cave_step4.setVolume(20);
	cave_step5.setVolume(20);
	island_step1.setVolume(20);
	island_step2.setVolume(20);
	island_step3.setVolume(20);
	island_step4.setVolume(20);
	island_step5.setVolume(20);
	island_step6.setVolume(20);
	island_step7.setVolume(20);
	island_step8.setVolume(20);
	
	islandMusic.setLoop(true);
	islandMusic.setVolume(40);

	caveBackgroundMusic.setLoop(true);
	caveBackgroundMusic.setVolume(50);

	mainMenuMusic.setLoop(true);
	mainMenuMusic.setVolume(50);

	
	
}

void Engine::playRandomFootstep()
{
	if (stepTime.GetElapsedTime() > 0.25f)
	{
		
		if (playerInsideCave)
		{
			int stepToPlay = manageLevel.RandomBetween(0, 5);
			switch (stepToPlay) {
			case 1:
				cave_step1.play();
				break;
			case 2:
				cave_step2.play();
				break;
			case 3:
				cave_step3.play();
				break;
			case 4:
				cave_step4.play();
				break;
			case 5:
				cave_step5.play();
				break;
			}
		}
		else
		{
			int stepToPlay = manageLevel.RandomBetween(0, 8);
			switch (stepToPlay) {
			case 1:
				island_step1.play();
				break;
			case 2:
				island_step2.play();
				break;
			case 3:
				island_step3.play();
				break;
			case 4:
				island_step4.play();
				break;
			case 5:
				island_step5.play();
				break;
			case 6:
				island_step6.play();
				break;
			case 7:
				island_step7.play();
				break;
			case 8:
				island_step8.play();
				break;
			}
		}

		stepTime.RestartTimer();
	}
}