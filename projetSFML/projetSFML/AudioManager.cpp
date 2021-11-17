#include "AudioManager.h"

sf::Sound sound;
sf::SoundBuffer hurtBuffer;
sf::SoundBuffer playerDeathBuffer;
sf::SoundBuffer playerColorSwapBuffer;
sf::SoundBuffer worldColorSwapBuffer;
sf::SoundBuffer bonusBuffer;

sf::Music gameMusic;


void PlaySoundFromBuffer(const sf::SoundBuffer& soundBuffer)
{
	sound.setBuffer(soundBuffer);
	sound.play();
}

void SetUpAudios()
{
	gameMusic.openFromFile(getAssetPath() + "music.wav");
	hurtBuffer.loadFromFile(getAssetPath() + "hurt.wav");
	playerDeathBuffer.loadFromFile(getAssetPath() + "explosion.wav");
	//colorSwapBuffer.loadFromFile(getAssetPath() + "colorSwap.wav");
}

// Play
	// PLayer health
void PlayHurtSound()
{
	PlaySoundFromBuffer(hurtBuffer);
}
void PlayPlayerDeathSound()
{
	PlaySoundFromBuffer(playerDeathBuffer);
}
	// Colors swap
void PlayPlayerColorSwapSound()
{
	PlaySoundFromBuffer(playerColorSwapBuffer);
}
void PlayWorldColorSwapSound()
{
	PlaySoundFromBuffer(worldColorSwapBuffer);
}
	// Bonus
void PlayBonusSound()
{
	PlaySoundFromBuffer(bonusBuffer);
}

// Music
void PlayGameMusic()
{
	gameMusic.setLoop(true);
	gameMusic.play();
}
void StopGameMusic()
{
	gameMusic.stop();
}
