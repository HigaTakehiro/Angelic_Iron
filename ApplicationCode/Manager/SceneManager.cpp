#include "SceneManager.h"
#include "SceneChangeEffect.h"
#include "Reticle.h"

BaseScene* SceneManager::nowScene_ = nullptr;
int32_t SceneManager::stageNo_ = 1;
int32_t SceneManager::score_ = 0;
bool SceneManager::isBossScene_ = false;
CollisionManager* SceneManager::colManager_ = nullptr;

void SceneManager::Initialize() {
	//�}�E�X�J�[�\�����\���ɂ���
	ShowCursor(false);
	//DirectWrite������
	textDraw_ = std::make_unique<TextDraw>();
	textDraw_->Initialize();
	//���e�B�N��������
	Reticle::GetIns()->Initialize();
	//�V�[���؂�ւ����o������
	SceneChangeEffect::GetIns()->Initialize();
	//�V�[���؂�ւ�
	SceneChange(SceneName::Title);
}

void SceneManager::Update() {
	nowScene_->Update();
}

void SceneManager::Draw() {
	nowScene_->Draw();
}

void SceneManager::Finalize() {
	//���݂̃V�[���̏I������
	nowScene_->Finalize();
	//���e�B�N�����
	Reticle::GetIns()->Finalize();
	//�V�[���؂�ւ����o�I������
	SceneChangeEffect::GetIns()->Finalize();
	//�x�[�X�V�[�����
	safe_delete(nowScene_);
	//�J�[�\������
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