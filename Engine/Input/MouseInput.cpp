#include "MouseInput.h"

MouseInput* MouseInput::GetIns()
{
	static MouseInput instance;
	return &instance;
}

void MouseInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinApp�̃C���X�^���X���L�^
	winApp_ = winApp;
	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput_, nullptr);
	//�}�E�X�f�o�C�X����
	result = dinput_->CreateDevice(GUID_SysMouse, &devMouse_, NULL);
	if (devMouse_ != nullptr) {
		//���̓f�[�^�`���̃Z�b�g
		result = devMouse_->SetDataFormat(&c_dfDIMouse);
		//�r�����䃌�x���̃Z�b�g
		result = devMouse_->SetCooperativeLevel(winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}
}

void MouseInput::Update() {
	HRESULT result;

	//�O��̃}�E�X�̃N���b�N��ۑ�
	preMouseState = mouseState_;
	//�}�E�X���̍X�V
	if (devMouse_ != nullptr) {
		result = devMouse_->Acquire();
		//�}�E�X�̓��͏����擾����
		result = devMouse_->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState_);
		//�}�E�X�J�[�\���̈ʒu���擾
		GetCursorPos(&mousePoint_);
		//�擾�����J�[�\���̈ʒu���E�B���h�E��̈ʒu�ɕϊ�
		ScreenToClient(winApp_->GetHwnd(), &mousePoint_);
	}
}

bool MouseInput::PushClick(MouseState mouseClick) {
	//�w��L�[�������Ă����true��Ԃ�
	if (mouseState_.rgbButtons[(BYTE)mouseClick] & (0x80)) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool MouseInput::TriggerClick(MouseState mouseClick) {
	//�O��͉����Ă��Ȃ��āA����͉����Ă����true��Ԃ�
	if (!preMouseState.rgbButtons[(BYTE)mouseClick] && mouseState_.rgbButtons[(BYTE)mouseClick]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}