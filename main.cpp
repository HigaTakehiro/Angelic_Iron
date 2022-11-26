﻿#include "KeyInput.h"
#include "WinApp.h"
#include "DirectXSetting.h"
#include "Sound.h"
#include "GameScene.h"
#include "PostEffect.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "BaseScene.h"
#include "SceneManager.h"

using namespace DirectX;
using namespace Microsoft::WRL;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	
	//ポインタ置き場
	WinApp* winApp = nullptr;
	DirectXSetting* dxCommon = DirectXSetting::GetIns();
	SceneManager* gameScene = nullptr;
	Sound* sound = Sound::GetIns();

	//WindowsAPIの初期化
	winApp = new WinApp();
	winApp->SetWindowStyle(WS_SYSMENU | WS_CAPTION | WS_EX_CONTEXTHELP | WS_MINIMIZEBOX);
	winApp->Initialize();

	//DirectXの初期化
	dxCommon->Initialize(winApp);

	//入力の初期化
	KeyInput::GetIns()->Initialize(winApp);
	MouseInput::GetIns()->Initialize(winApp);
	PadInput::GetIns()->Initialize(winApp);

	//Soundの初期化
	if (!sound->Initialize()) {
		assert(0);
		return 1;
	}
	
	gameScene = new SceneManager();
	gameScene->Initialize();

	// DirectX初期化処理　ここまで

	while (true)  // ゲームループ
	{
		if (winApp->ProcessMessage()) {
			break;
		}

		if (KeyInput::GetIns()->PushKey(DIK_ESCAPE)) {
			break;
		}

		KeyInput::GetIns()->Update();
		MouseInput::GetIns()->Update();
		PadInput::GetIns()->Update();
		gameScene->Update();

		// DirectX毎フレーム処理　ここまで
		// ４．描画コマンドここから
		gameScene->Draw();

	}

	//GameScene解放
	gameScene->Finalize();
	safe_delete(gameScene);
	//WindowsAPI解放
	winApp->Finalize();
	safe_delete(winApp);
	return 0;
}