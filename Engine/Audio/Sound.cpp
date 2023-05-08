#include "Sound.h"
#include <fstream>
#include <cassert>

#pragma comment(lib,"xaudio2.lib")

bool Sound::Initialize() {
	HRESULT result;

	// XSound�G���W���̃C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if FAILED(result) {
		assert(0);
		return false;
	}

	// �}�X�^�[�{�C�X�𐶐�
	result = xAudio2_->CreateMasteringVoice(&masterVoice_);
	if FAILED(result) {
		assert(0);
		return false;
	}

	return true;
}

void Sound::PlaySoundData(const SoundData& soundData, bool isRoop, float volume)
{
	HRESULT result;

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = (BYTE*)soundData.pBuffer_;
	buf.pContext = soundData.pBuffer_;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.AudioBytes = soundData.data_.size_;
	if (isRoop == true) {
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	soundData.sound_->SetVolume(volume);

	// �g�`�f�[�^�̍Đ�
	if (!soundData.isPlay_) {
		result = soundData.sound_->SubmitSourceBuffer(&buf);
		result = soundData.sound_->Start();
	}

}

void Sound::StopSoundData(const SoundData& soundData, bool isPause)
{
	HRESULT result;
	XAUDIO2_VOICE_STATE voiceState;
	soundData.sound_->GetState(&voiceState);
	soundData.sound_->Stop();
	if (!isPause) {
		result = soundData.sound_->FlushSourceBuffers();
	}
}

void Sound::LoadSound(const std::string& fileName, SoundData& soundData)
{
	HRESULT result;
	// �t�@�C���X�g���[��
	std::ifstream file;
	// Wave�t�@�C�����J��
	file.open(fileName, std::ios_base::binary);
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}

	// RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk_.id_, "RIFF", 4) != 0) {
		assert(0);
	}

	// Format�`�����N�̓ǂݍ���
	FormatChunk format;
	file.read((char*)&format, sizeof(format));

	// Data�`�����N�̓ǂݍ���
	file.read((char*)&soundData.data_, sizeof(soundData.data_));

	// Data�`�����N�̃f�[�^���i�g�`�f�[�^�j�̓ǂݍ���
	soundData.pBuffer_ = new char[soundData.data_.size_];
	file.read(soundData.pBuffer_, soundData.data_.size_);

	// Wave�t�@�C�������
	file.close();

	WAVEFORMATEX wfex{};
	// �g�`�t�H�[�}�b�g�̐ݒ�
	memcpy(&wfex, &format.fmt_, sizeof(format.fmt_));
	wfex.wBitsPerSample = format.fmt_.nBlockAlign * 8 / format.fmt_.nChannels;

	// �g�`�t�H�[�}�b�g������SourceVoice�̐���
	result = xAudio2_->CreateSourceVoice(&soundData.sound_, &wfex, 0, 2.0f, &voiceCallback_);
}