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
	if (bgmMap[bgmKey].data.size <= 0) {
		LoadBGM(bgmMap[bgmKey].fileName, bgmKey);
	}
	sound->PlaySoundData(bgmMap[bgmKey], isRoop, volume);
	bgmMap[bgmKey].isPlay = true;
}

void SoundManager::PlaySE(const SEKey seKey, const float volume)
{
	if (seMap[seKey].data.size <= 0) {
		LoadSE(seMap[seKey].fileName, seKey);
	}
	seMap[seKey].isPlay = false;
	sound->PlaySoundData(seMap[seKey], false, volume);
}

void SoundManager::StopBGM(const BGMKey bgmKey, const bool isPause)
{
	sound->StopSoundData(bgmMap[bgmKey], isPause);
	bgmMap[bgmKey].isPlay = false;
	if (!isPause) {
		bgmMap[bgmKey].data.size = 0;
	}
}

void SoundManager::StopSE(const SEKey seKey, const bool isPause)
{
	sound->StopSoundData(seMap[seKey], isPause);
	seMap[seKey].isPlay = false;
}

void SoundManager::LoadBGM(const std::string& fileName, BGMKey bgmKey)
{
	if (bgmMap[bgmKey].fileName.size() <= 0) {
		bgmMap[bgmKey].fileName = fileName;
	}
	sound->LoadSound(fileName, bgmMap[bgmKey]);
}

void SoundManager::LoadSE(const std::string& fileName, SEKey seKey)
{
	if (seMap[seKey].fileName.size() <= 0) {
		seMap[seKey].fileName = fileName;
	}
	sound->LoadSound(fileName, seMap[seKey]);
}
