#include "PadInput.h"

PadInput* PadInput::GetIns()
{
	static PadInput instance;
	return &instance;
}

void PadInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinAppのインスタンスを記録
	winApp_ = winApp;
	//DirectInputのインスタンス生成
	result = DirectInput8Create(winApp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput_, nullptr);
	//パッドデバイス生成
	result = dinput_->CreateDevice(GUID_Joystick, &devPad_, NULL);
	if (devPad_ != nullptr) {
		//入力データ形式のセット
		result = devPad_->SetDataFormat(&c_dfDIJoystick);
		//排他制御レベルのセット
		result = devPad_->SetCooperativeLevel(winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}
}

void PadInput::Update() {
	HRESULT result;

	if (devPad_ != nullptr) {
		//前回のパッドのボタン押下を保存
		prePadState_ = padState_;
		//パッド情報の更新
		result = devPad_->Acquire();
		//パッドの入力情報を取得する
		result = devPad_->GetDeviceState(sizeof(DIJOYSTATE), &padState_);
	}
}

bool PadInput::PushButton(BYTE buttonNumber) {
	//指定キーを押していればtrueを返す
	if (padState_.rgbButtons[buttonNumber] & (0x80)) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}

bool PadInput::TriggerButton(BYTE buttonNumber) {
	//前回は押していなくて、今回は押していればtrueを返す
	if (!prePadState_.rgbButtons[buttonNumber] && padState_.rgbButtons[buttonNumber]) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}

bool PadInput::PushCrossKey(LONG crossKeyNumber) {
	if (padState_.rgdwPOV[0] != 0xFFFFFFFF) {
		//指定キーを押していればtrueを返す
		if (padState_.rgdwPOV[0] == crossKeyNumber) {
			return true;
		}
	}
	//そうでないならfalseを返す
	return false;
}