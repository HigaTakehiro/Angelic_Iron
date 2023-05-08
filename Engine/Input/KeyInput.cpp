#include "KeyInput.h"

void KeyInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinApp�̃C���X�^���X���L�^
	winApp_ = winApp;
	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput_, nullptr);
	//�L�[�{�[�h�f�o�C�X����
	result = dinput_->CreateDevice(GUID_SysKeyboard, &devkeyboard_, NULL);
	//���̓f�[�^�`���̃Z�b�g
	result = devkeyboard_->SetDataFormat(&c_dfDIKeyboard);
	//�r�����䃌�x���̃Z�b�g
	result = devkeyboard_->SetCooperativeLevel(winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void KeyInput::Update() {
	HRESULT result;

	//�O��̃L�[���͂�ۑ�
	memcpy(keyPre_, key_, sizeof(key_));
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard_->Acquire();
	//�S�L�[�̓��͏����擾����
	result = devkeyboard_->GetDeviceState(sizeof(key_), key_);
}

bool KeyInput::PushKey(BYTE keyNumber) {
	//�w��L�[�������Ă����true��Ԃ�
	if (key_[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool KeyInput::HoldKey(BYTE keyNumber) {
	if (keyPre_[keyNumber] && key_[keyNumber]) {
		return true;
	}
	return false;
}

bool KeyInput::TriggerKey(BYTE keyNumber) {
	//�O��͉����Ă��Ȃ��āA����͉����Ă����true��Ԃ�
	if (!keyPre_[keyNumber] && key_[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

KeyInput* KeyInput::GetIns()
{
	static KeyInput instance;
	return &instance;
}
