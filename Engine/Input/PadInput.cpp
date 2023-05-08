#include "PadInput.h"

PadInput* PadInput::GetIns()
{
	static PadInput instance;
	return &instance;
}

void PadInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinApp�̃C���X�^���X���L�^
	winApp_ = winApp;
	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput_, nullptr);
	//�p�b�h�f�o�C�X����
	result = dinput_->CreateDevice(GUID_Joystick, &devPad_, NULL);
	if (devPad_ != nullptr) {
		//���̓f�[�^�`���̃Z�b�g
		result = devPad_->SetDataFormat(&c_dfDIJoystick);
		//�r�����䃌�x���̃Z�b�g
		result = devPad_->SetCooperativeLevel(winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}
}

void PadInput::Update() {
	HRESULT result;

	if (devPad_ != nullptr) {
		//�O��̃p�b�h�̃{�^��������ۑ�
		prePadState_ = padState_;
		//�p�b�h���̍X�V
		result = devPad_->Acquire();
		//�p�b�h�̓��͏����擾����
		result = devPad_->GetDeviceState(sizeof(DIJOYSTATE), &padState_);
	}
}

bool PadInput::PushButton(BYTE buttonNumber) {
	//�w��L�[�������Ă����true��Ԃ�
	if (padState_.rgbButtons[buttonNumber] & (0x80)) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool PadInput::TriggerButton(BYTE buttonNumber) {
	//�O��͉����Ă��Ȃ��āA����͉����Ă����true��Ԃ�
	if (!prePadState_.rgbButtons[buttonNumber] && padState_.rgbButtons[buttonNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool PadInput::PushCrossKey(LONG crossKeyNumber) {
	if (padState_.rgdwPOV[0] != 0xFFFFFFFF) {
		//�w��L�[�������Ă����true��Ԃ�
		if (padState_.rgdwPOV[0] == crossKeyNumber) {
			return true;
		}
	}
	//�����łȂ��Ȃ�false��Ԃ�
	return false;
}