#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"

#define DIRECTINPUT_VERSION     0x0800   // DirectInputのバージョン指定
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class MouseInput final
{
public: //enum
	enum class MouseState {
		LEFT_CLICK,
		RIGHT_CLICK,
		WHEEL_CLICK
	};

private: //エイリアス
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MouseInput() = default;

	/// <summary>
    /// デストラクタ
    /// </summary>
	~MouseInput() = default;

	/// <summary>
	/// コピーコンストラクタを禁止
	/// </summary>
	MouseInput(const MouseInput& obj) = delete;

	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	MouseInput& operator=(const MouseInput& obj) = delete;

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// クリック検知
	/// </summary>
	bool PushClick(MouseState mouseClick);

	/// <summary>
	/// クリックした瞬間のみ検知
	/// </summary>
	bool TriggerClick(MouseState mouseClick);

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static MouseInput* GetIns();

	/// <summary>
	/// マウスポインタの位置取得
	/// </summary>
	/// <returns></returns>
	const POINT& GetMousePoint() { return mousePoint_; }

	/// <summary>
	/// マウスポインタの1フレームでの移動量取得(X軸)
	/// </summary>
	/// <returns>1フレームでの移動量</returns>
	float GetMouseXVelocity() { return (float)mouseState_.lX; }

	/// <summary>
	/// マウスポインタの1フレームでの移動量取得(Y軸)
	/// </summary>
	/// <returns>1フレームでの移動量</returns>
	float GetMouseYVelocity() { return (float)mouseState_.lY; }

private: //メンバ変数
	//DirectInputのインスタンス
	ComPtr<IDirectInput8> dinput_;
	//マウスのデバイス
	ComPtr<IDirectInputDevice8> devMouse_;
	//マウスの情報
	DIMOUSESTATE mouseState_;
	DIMOUSESTATE preMouseState;
	POINT mousePoint_;
	//WindowsAPI
	WinApp* winApp_ = nullptr;
};

