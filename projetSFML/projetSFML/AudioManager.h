#pragma once
#include <SFML/Audio.hpp>
#include "AssetsPath.h"
#include <iostream>

void PlaySoundFromBuffer(const sf::SoundBuffer& soundBuffer);

void SetUpAudios();

void PlayHurtSound();
void PlayPlayerColorSwapSound();
void PlayWorldColorSwapSound();
void PlayBonusSound();

void PlayGameMusic();