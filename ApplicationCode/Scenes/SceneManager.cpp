#include "SceneManager.h"
#include "SceneChangeEffect.h"
#include "Reticle.h"

BaseScene* SceneManager::nowScene = nullptr;
int32_t SceneManager::stageNo = 1;
int32_t SceneManager::score = 0;
bool SceneManager::isBossScene = false;

void SceneManager::Initialize() {
	//マウスカーソルを非表示にする
	ShowCursor(false);
	//DirectWrite初期化
	textDraw = std::make_unique<TextDraw>();
	textDraw->Initialize();
	//レティクル初期化
	Reticle::GetIns()->Initialize();
	//シーン切り替え演出初期化
	SceneChangeEffect::GetIns()->Initialize();
	//シーン切り替え
	SceneChange(Title);
}

void SceneManager::Update() {
	nowScene->Update();
}

void SceneManager::Draw() {
	nowScene->Draw();
}

void SceneManager::Finalize() {
	//現在のシーンの終了処理
	nowScene->Finalize();
	//レティクル解放
	Reticle::GetIns()->Finalize();
	//シーン切り替え演出終了処理
	SceneChangeEffect::GetIns()->Finalize();
	//ベースシーン解放
	safe_delete(nowScene);
	//カーソル可視化
	ShowCursor(true);
}

void SceneManager::AddScore(const int32_t score) {
	SceneManager::score += score;
}

void SceneManager::SetScore(const int32_t score)
{
	SceneManager::score = score;
}

void SceneManager::SceneChange(SceneName scene) {
	if (nowScene != nullptr) {
		nowScene->Finalize();
		safe_delete(nowScene);
	}

	switch (scene) {
	case Title:
		nowScene = new TitleScene();
		nowScene->Initialize();
		break;

	case Stage1_Rail:
		stageNo = 1;
		score = 0;
		nowScene = new RailScene();
		nowScene->Initialize();
		break;
	case Stage1_Boss:
		nowScene = new BossScene();
		nowScene->Initialize();
		break;
	case Stage2_Rail:
		stageNo = 2;
		score = 0;
		nowScene = new RailScene();
		nowScene->Initialize();
		break;
	case Stage2_Boss:
		nowScene = new BossScene();
		nowScene->Initialize();
		break;
	case Result:
		nowScene = new ResultScene();
		nowScene->Initialize();
		break;
	case GameOver:
		nowScene = new GameOverScene();
		nowScene->Initialize();
		break;
	default:
		break;
	}
}