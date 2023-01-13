#include "SoundManager.h"

SoundManager* SoundManager::GetIns()
{
    static SoundManager instance;
    return &instance;
}

void SoundManager::Initialize(Sound* sound)
{
    this->sound = sound;
    LoadBGM("Engine/Resources/Sound/BGM/Speace_World.wav", TITLE);
    LoadBGM("Engine/Resources/Sound/BGM/JimS - Little Excitement.wav", STAGE1_RAIL);
}

void SoundManager::PlayBGM(const BGMKey bgmKey, const bool isRoop, const float volume)
{
    sound->PlaySoundData(bgmMap[bgmKey], isRoop, volume);
    bgmMap[bgmKey].isPlay = true;
}

void SoundManager::PlaySE(const SEKey seKey, const float volume)
{
    seMap[seKey].isPlay = false;
    sound->PlaySoundData(seMap[seKey], false, volume);
}

void SoundManager::StopBGM(const BGMKey bgmKey)
{
    sound->StopSoundData(bgmMap[bgmKey]);
    bgmMap[bgmKey].isPlay = false;
}

void SoundManager::StopSE(const SEKey seKey)
{
    sound->StopSoundData(seMap[seKey]);
    seMap[seKey].isPlay = false;
}

void SoundManager::LoadBGM(const char* fileName, BGMKey bgmKey)
{
    sound->LoadSound(fileName, bgmMap[bgmKey]);
}

void SoundManager::LoadSE(const char* fileName, SEKey seKey)
{
    sound->LoadSound(fileName, seMap[seKey]);
}
