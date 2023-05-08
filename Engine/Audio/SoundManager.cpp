#include "SoundManager.h"

SoundManager* SoundManager::GetIns()
{
	static SoundManager instance;
	return &instance;
}

void SoundManager::Initialize(Sound* sound_)
{
	this->sound_ = sound_;
	LoadBGM("Engine/Resources/Sound/BGM/Speace_World.wav", BGMKey::TITLE);
	LoadBGM("Engine/Resources/Sound/BGM/JimS - Little Excitement.wav", BGMKey::STAGE1_RAIL);
	LoadSE("Engine/Resources/Sound/SE/damage.wav", SEKey::DAMAGE);
	LoadSE("Engine/Resources/Sound/SE/short_bomb.wav", SEKey::SHOT);
	LoadSE("Engine/Resources/Sound/SE/noise.wav", SEKey::NOISE);
	LoadSE("Engine/Resources/Sound/SE/reload.wav", SEKey::RELOAD);
}

void SoundManager::PlayBGM(const BGMKey bgmKey, const bool isRoop, const float volume)
{
	if (bgmMap_[bgmKey].data_.size_ <= 0) {
		LoadBGM(bgmMap_[bgmKey].fileName_, bgmKey);
	}
	sound_->PlaySoundData(bgmMap_[bgmKey], isRoop, volume);
	bgmMap_[bgmKey].isPlay_ = true;
}

void SoundManager::PlaySE(const SEKey seKey, const float volume)
{
	//XAUDIO2_VOICE_STATE voiceState;
	//seMap[seKey].sound_->GetState(&voiceState);

	//if (voiceState.BuffersQueued <= 0) {
	//	seMap[seKey].isPlay_ = false;
	//	StopSE(seKey);
	//}

	seMap_[seKey].pBuffer_ = nullptr;
	seMap_[seKey].sound_ = nullptr;
	seMap_[seKey].isPlay_ = false;
	seMap_[seKey].data_.size_ = 0;

	if (seMap_[seKey].data_.size_ <= 0) {
		LoadSE(seMap_[seKey].fileName_, seKey);
	}
	sound_->PlaySoundData(seMap_[seKey], false, volume);
	seMap_[seKey].isPlay_ = true;
}

void SoundManager::StopBGM(const BGMKey bgmKey, const bool isPause)
{
	sound_->StopSoundData(bgmMap_[bgmKey], isPause);
	bgmMap_[bgmKey].isPlay_ = false;
	if (!isPause) {
		bgmMap_[bgmKey].data_.size_ = 0;
	}
}

void SoundManager::StopSE(const SEKey seKey, const bool isPause)
{
	sound_->StopSoundData(seMap_[seKey], isPause);
	seMap_[seKey].isPlay_ = false;
	if (!isPause) {
		seMap_[seKey].data_.size_ = 0;
	}
}

void SoundManager::LoadBGM(const std::string& fileName_, BGMKey bgmKey)
{
	if (bgmMap_[bgmKey].fileName_.size() <= 0) {
		bgmMap_[bgmKey].fileName_ = fileName_;
	}
	sound_->LoadSound(fileName_, bgmMap_[bgmKey]);
}

void SoundManager::LoadSE(const std::string& fileName_, SEKey seKey)
{
	if (seMap_[seKey].fileName_.size() <= 0) {
		seMap_[seKey].fileName_ = fileName_;
	}
	sound_->LoadSound(fileName_, seMap_[seKey]);
}
