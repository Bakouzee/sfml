#include "AudioManager.h"

sf::Sound sound;
sf::SoundBuffer hurtBuffer;
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
	gameMusic.openFromFile(getAssetPath() + "test.wav");
	//hurtBuffer.loadFromFile(getAssetPath() + "hurt.wav");
	//i.colorSwapBuffer.loadFromFile(getAssetPath() + "colorSwap.wav");
}

// Play 
void PlayHurtSound()
{
	PlaySoundFromBuffer(hurtBuffer);
	std::cout << "hurt" << std::endl;
	//i.sound.setBuffer(i.hurtBuffer);
	//i.sound.play();
}