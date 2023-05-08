#include "MouseInput.h"

MouseInput* MouseInput::GetIns()
{
	static MouseInput instance;
	return &instance;
}

void MouseInput::Initialize(WinApp* winApp) {
	HRESULT result = S_FALSE;

	//WinAppのインスタンスを記録
	winApp_ = winApp;
	//DirectInputのインスタンス生成
	result = DirectInput8Create(winApp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput_, nullptr);
	//マウスデバイス生成
	result = dinput_->CreateDevice(GUID_SysMouse, &devMouse_, NULL);
	if (devMouse_ != nullptr) {
		//入力データ形式のセット
		result = devMouse_->SetDataFormat(&c_dfDIMouse);
		//排他制御レベルのセット
		result = devMouse_->SetCooperativeLevel(winApp_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}
}

void MouseInput::Update() {
	HRESULT result;

	//前回のマウスのクリックを保存
	preMouseState = mouseState_;
	//マウス情報の更新
	if (devMouse_ != nullptr) {
		result = devMouse_->Acquire();
		//マウスの入力情報を取得する
		result = devMouse_->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState_);
		//マウスカーソルの位置を取得
		GetCursorPos(&mousePoint_);
		//取得したカーソルの位置をウィンドウ上の位置に変換
		ScreenToClient(winApp_->GetHwnd(), &mousePoint_);
	}
}

bool MouseInput::PushClick(MouseState mouseClick) {
	//指定キーを押していればtrueを返す
	if (mouseState_.rgbButtons[(BYTE)mouseClick] & (0x80)) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}

bool MouseInput::TriggerClick(MouseState mouseClick) {
	//前回は押していなくて、今回は押していればtrueを返す
	if (!preMouseState.rgbButtons[(BYTE)mouseClick] && mouseState_.rgbButtons[(BYTE)mouseClick]) {
		return true;
	}
	//そうでなければfalseを返す
	return false;
}