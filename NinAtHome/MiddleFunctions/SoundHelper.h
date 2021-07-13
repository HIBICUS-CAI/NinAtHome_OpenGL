#pragma once

#include "main.h"
#include <string>
#ifdef NIN_AT_HOME
#include <xaudio2.h>
#else
#include <nn/atk.h>
#endif // NIN_AT_HOME

#ifdef NIN_AT_HOME
using SOUND_HANDLE = IXAudio2SourceVoice*;
using LOAD_HANDLE = std::string;
#else
using SOUND_HANDLE = nn::atk::SoundArchive::ItemId;
using LOAD_HANDLE = unsigned int;
#endif // NIN_AT_HOME

bool InitSound();

void UninitSound();

void UpdateSound();

void ClearSoundPool();

void LoadSound(std::string name, LOAD_HANDLE path);

void PlayBGM(std::string soundName);

void StopBGM(std::string soundName);

void StopBGM();

void SetVolumeBGM(float volume, int delayFrame = 0);

void PlaySE(std::string soundName);

