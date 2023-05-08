#include "KeyInput.h"

void KeyInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinAppのインスタンスを記録
	winApp_ = winApp;
	//DirectInputのインスタンス生成
	result = DirectInput8Create(winApp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput_, nullptr);
	//キーボードデバイス生成
	result = dinput_->CreateDevice(GUID_SysKeyboard, &devkeyboard_, NULL);
	//入力データ形式のセット
	result = devkeyboard_->SetDataFormat(&c_dfDIKeyboard);
	//排他制御レベルのセット
	result = devkeyboard_->SetCooperativeLevel(winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void KeyInput::Update() {
	HRESULT result;

	//前回のキー入力を保存
	memcpy(keyPre_, key_, sizeof(key_));
	//キーボード情報の取得開始
	result = devkeyboard_->Acquire();
	//全キーの入力情報を取得する
	result = devkeyboard_->GetDeviceState(sizeof(key_), key_);
}

bool KeyInput::PushKey(BYTE keyNumber) {
	//指定キーを押していればtrueを返す
	if (key_[keyNumber]) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}

bool KeyInput::HoldKey(BYTE keyNumber) {
	if (keyPre_[keyNumber] && key_[keyNumber]) {
		return true;
	}
	return false;
}

bool KeyInput::TriggerKey(BYTE keyNumber) {
	//前回は押していなくて、今回は押していればtrueを返す
	if (!keyPre_[keyNumber] && key_[keyNumber]) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}

KeyInput* KeyInput::GetIns()
{
	static KeyInput instance;
	return &instance;
}
