#include "SceneManager.h"
#include "SceneChangeEffect.h"
#include "Reticle.h"

BaseScene* SceneManager::nowScene_ = nullptr;
int32_t SceneManager::stageNo_ = 1;
int32_t SceneManager::score_ = 0;
bool SceneManager::isBossScene_ = false;
CollisionManager* SceneManager::colManager_ = nullptr;

void SceneManager::Initialize() {
	//マウスカーソルを非表示にする
	ShowCursor(false);
	//DirectWrite初期化
	textDraw_ = std::make_unique<TextDraw>();
	textDraw_->Initialize();
	//レティクル初期化
	Reticle::GetIns()->Initialize();
	//シーン切り替え演出初期化
	SceneChangeEffect::GetIns()->Initialize();
	//シーン切り替え
	SceneChange(SceneName::Title);
}

void SceneManager::Update() {
	nowScene_->Update();
}

void SceneManager::Draw() {
	nowScene_->Draw();
}

void SceneManager::Finalize() {
	//現在のシーンの終了処理
	nowScene_->Finalize();
	//レティクル解放
	Reticle::GetIns()->Finalize();
	//シーン切り替え演出終了処理
	SceneChangeEffect::GetIns()->Finalize();
	//ベースシーン解放
	safe_delete(nowScene_);
	//カーソル可視化
	ShowCursor(true);
}

void SceneManager::AddScore(const int32_t score_) {
	SceneManager::score_ += score_;
}

void SceneManager::SetScore(const int32_t score_)
{
	SceneManager::score_ = score_;
}

void SceneManager::SceneChange(SceneName scene) {
	if (nowScene_ != nullptr) {
		nowScene_->Finalize();
		safe_delete(nowScene_);
	}

	switch (scene) {
	case SceneName::Title:
		nowScene_ = new TitleScene();
		nowScene_->Initialize();
		nowScene_->SetColManager(colManager_);
		break;

	case SceneName::Stage1_Rail:
		stageNo_ = 1;
		score_ = 0;
		nowScene_ = new RailScene();
		nowScene_->Initialize();
		nowScene_->SetColManager(colManager_);
		break;
	case SceneName::Stage1_Boss:
		nowScene_ = new BossScene();
		nowScene_->Initialize();
		nowScene_->SetColManager(colManager_);
		break;
	case SceneName::Stage2_Rail:
		stageNo_ = 2;
		score_ = 0;
		nowScene_ = new RailScene();
		nowScene_->Initialize();
		break;
	case SceneName::Stage2_Boss:
		nowScene_ = new BossScene();
		nowScene_->Initialize();
		break;
	case SceneName::Result:
		nowScene_ = new ResultScene();
		nowScene_->Initialize();
		break;
	case SceneName::GameOver:
		nowScene_ = new GameOverScene();
		nowScene_->Initialize();
		break;
	default:
		break;
	}
}