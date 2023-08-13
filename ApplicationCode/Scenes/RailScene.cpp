#include "RailScene.h"
#include "FBXObject3d.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Collision.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "SafeDelete.h"
#include "StraightEnemy.h"
#include "AimingEnemy.h"
#include "HomingEnemy.h"
#include "SpreadEnemy.h"
#include "DirectXSetting.h"
#include "ExternalFileLoader.h"
#include <algorithm>
#include <fstream>

using namespace DirectX;
using namespace Microsoft::WRL;

void RailScene::Initialize() {

	//SoundManager::GetIns()->PlayBGM(SoundManager::BGMKey::STAGE1_RAIL, true, 0.2f);

	//カメラ初期化
	camera_ = new Camera;
	camera_->SetEye(XMFLOAT3(50, 1, -100));
	camera_->SetTarget(XMFLOAT3(50, 0, 0));
	railCamera_ = new RailCamera;

	//デバッグテキスト初期化
	debugText_.Initialize(debugTextNumber);

	//弾管理クラスの初期化
	bulletManager_ = new BulletManager();

	//スプライト画像初期化
	pause_ = Sprite::Create((UINT)ImageManager::ImageName::Pause, { 640, 100 });
	pause_->SetAnchorPoint({ 0.5f, 0.5f });

	titleBackButton_ = Button::CreateUniqueButton(ImageManager::ImageName::TitleBack, { 640, 300 }, { 256, 128 }, 0.0f);
	back_ = Button::CreateUniqueButton(ImageManager::ImageName::Back, { 640, 450 }, { 256, 128 }, 0.0f);
	restart_ = Button::CreateUniqueButton(ImageManager::ImageName::Restart, { 640, 600 }, { 320, 64 }, 0.0f);

	uiManager_ = new UIManager();
	uiManager_->Initialize();

	//ライト初期化
	light_ = LightGroup::Create();
	for (int32_t i = 0; i < 3; i++) {
		light_->SetDirLightActive(0, true);
		light_->SetPointLightActive(i, false);
		light_->SetSpotLightActive(i, false);
	}
	light_->SetCircleShadowActive(0, true);
	light_->SetDirLightDirection(0, { 0, -1, 0 });
	light_->SetCircleShadowDir(0, { 0, -1, 0 });
	light_->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light_->SetCircleShadowDistanceCasterLight(0, 1000.0f);
	light_->SetCircleShadowAngle(0, { 0.0f, 0.5f });
	Object3d::SetLight(light_);

	//3dオブジェクト初期化
	int32_t stageNo;
	stageNo = SceneManager::GetStageNo();

	//ステージ背景オブジェクト初期化
	jsonLoader_ = std::make_unique<JsonLoader>();

	//プレイヤー初期化
	player_ = new Player;
	player_->Initialize(camera_, clearTime);
	player_->SetRailScene(this);
	player_->SetBulletManager(bulletManager_);

	//パーティクル初期化
	bombParticle_ = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera_);
	enemyParticle_ = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera_);
	gunParticle_ = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera_);
	thrusterParticle_ = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera_);

	enemyManager_ = new EnemyManager();
	enemyManager_->SetBulletManager(bulletManager_);
	enemyManager_->SetPlayer(player_);
	enemyManager_->SetRailScene(this);
	enemyManager_->SetParticleManager(enemyParticle_);

	railTutorial_ = new RailTutorial();
	messageWindow_ = new MessageWindow();
	//ステージデータ読み込み
	if (stageNo == 1) {
		player_->SetClearPos({ 130.0f, 20.0f, 55.0f });
		railCamera_->Initialize("Stage1RailPoints.aid");
		jsonLoader_->StageDataLoadandSet("stage1");
		enemyManager_->Initialize("Stage1EnemyData.aid");
		messageWindow_->Initialize("Stage1RailText.aid");
		railTutorial_->Initialize();
	}
	else if (stageNo == 2) {
		railCamera_->Initialize("Stage2RailPoints.aid");
	}

	//ポストエフェクトの初期化
	postEffect_ = new PostEffect();
	postEffect_->Initialize();
	postEffectNo_ = PostEffect::PostEffectNo::NORMAL;

	//ゲームシーン用変数の初期化
	score_ = 0;
	clearTimer_ = clearTime;
	//faceType_ = FaceGraphics::OPE_NORMALFACE;
	Reticle::GetIns()->SetIsSelectReticle(false);

	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

}

void RailScene::Update() {
	//スコアアイテムドロップ
	for (std::unique_ptr<BaseEnemy>& enemy : enemyManager_->GetEnemies()) {
		if (enemy->GetIsScoreItemDrop() && !enemy->GetIsTarget()) {
			std::unique_ptr<ScoreItem> scoreItem = std::make_unique<ScoreItem>();
			scoreItem->Initialize(enemy->GetEnemyObj()->GetMatWorld().r[3], player_, camera_);
			scoreItems_.push_back(std::move(scoreItem));
		}
	}

	//オブジェクトリスト解放処理
	particles2d_.remove_if([](std::unique_ptr<Particle2d>& particle) {return particle->IsDelete(); });
	scoreItems_.remove_if([](std::unique_ptr<ScoreItem>& scoreItem) {return scoreItem->GetIsDead(); });

	//丸影用プレイヤー座標セット
	light_->SetCircleShadowCasterPos(0, { player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[0], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[1], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[2] });
	//ポーズ切り替え
	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE) && player_->GetHPCount() != noneHP && !railCamera_->GetIsEnd()) {
		isPause_ = !isPause_;
	}
	//クリア演出
	ClearPaformance();
	//プレイヤーが死亡しているか
	if (player_->GetIsDead()) {
		isDead_ = true;
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}

	//ui更新処理
	uiManager_->Update(isPause_, player_);
	uiManager_->SetScore(score_);

	//レティクル更新処理
	Reticle::GetIns()->Update();
	Reticle::GetIns()->SetIsSelectReticle(false);

	if (!isPause_) {
		//エフェクト発生処理
		AddEffect();
		//オブジェクト更新処理
		enemyManager_->EnemyRockOnPerformance();
		//ボム攻撃時にスローにする更新処理
		DelayUpdates();
		//チュートリアル更新処理
		Tutorial();
		colManager_->Update();

		bombParticle_->Update();
		gunParticle_->Update();
		thrusterParticle_->Update();
		jsonLoader_->Update();
		light_->Update();

		player_->Update(railCamera_->GetIsEnd());
	}
	else {
		Pause();
	}

	//シーン切り替え処理
	SceneChangeEffect::GetIns()->Update();
	SceneChange();
}

void RailScene::ClearPaformance()
{
	//レールカメラが最終地点に到達したとき
	if (railCamera_->GetIsEnd()) {
		clearTimer_--;
	}
	//クリア演出後シーンを切り替える
	if (clearTimer_ <= 0) {
		isClear_ = true;
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}
}

void RailScene::Draw() {
	//背景色
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	bool isRoop = false;

	if (player_->GetIsDamage()) {
		postEffectNo_ = PostEffect::PostEffectNo::DAMAGE;
	}
	else {
		postEffectNo_ = PostEffect::PostEffectNo::NORMAL;
		isRoop = true;
	}

	if (player_->GetIsBomb()) {
		postEffectNo_ = PostEffect::PostEffectNo::SLOW;
		isRoop = false;
	}

	postEffect_->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//スプライト描画処理(背景)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	jsonLoader_->Draw();
	bulletManager_->Draw();
	if (!isDead_) {
		player_->ObjectDraw();
	}
	enemyManager_->Draw();
	for (std::unique_ptr<ScoreItem>& scoreItem : scoreItems_) {
		scoreItem->Draw();
	}
	enemyParticle_->Draw(DirectXSetting::GetIns()->GetCmdList());
	bombParticle_->Draw(DirectXSetting::GetIns()->GetCmdList());
	gunParticle_->Draw(DirectXSetting::GetIns()->GetCmdList());
	thrusterParticle_->Draw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//スプライト描画処理(UI等)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	if (!isPause_) {
		messageWindow_->SpriteDraw();
	}
	railTutorial_->Draw();
	player_->SpriteDraw();
	enemyManager_->SpriteDraw();
	for (std::unique_ptr<Particle2d>& particle2d : particles2d_) {
		particle2d->Draw();
	}
	if (isPause_) {
		pause_->Draw();
		titleBackButton_->Draw();
		back_->Draw();
		restart_->Draw();
	}
	Reticle::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	if (!isPause_) {
		messageWindow_->TextMessageDraw(player_->GetIsBomb());
	}
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, isRoop);

	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	uiManager_->Draw(isPause_, player_);
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();
	DirectXSetting::GetIns()->PostDraw();
}

void RailScene::Finalize() {
	player_->Finalize();
	safe_delete(player_);
	safe_delete(camera_);
	safe_delete(railCamera_);
	safe_delete(postEffect_);
	safe_delete(pause_);
	safe_delete(light_);
	safe_delete(bombParticle_);
	safe_delete(gunParticle_);
	safe_delete(thrusterParticle_);
	safe_delete(enemyParticle_);
	safe_delete(bulletManager_);
	safe_delete(uiManager_);
	safe_delete(enemyManager_);
	safe_delete(messageWindow_);
	safe_delete(railTutorial_);
	jsonLoader_->Finalize();
	colManager_->Finalize();
}

std::list<std::unique_ptr<BaseEnemy>>& RailScene::GetEnemyObj()
{
	return enemyManager_->GetEnemies();
}

void RailScene::DelayUpdates()
{
	//スロー演出用タイマー
	float delayTime = 0.0f;
	if (player_->GetIsBomb()) {
		delayTime = 3.0f;
	}
	delayTimer_++;

	//スロー演出
	if (delayTimer_ >= delayTime) {
		//テキスト更新処理
		messageWindow_->Update();

		//プレイヤーが生きている場合に更新
		if (player_->GetHPCount() > 0) {
			if (!railCamera_->GetIsEnd()) {
				railCamera_->Update();
			}
			enemyManager_->Update(isPause_);
			for (std::unique_ptr<ScoreItem>& scoreItem : scoreItems_) {
				scoreItem->Update(score_);
			}
		}

		bulletManager_->Update(score_);
		for (std::unique_ptr<Particle2d>& particle2d : particles2d_) {
			particle2d->Update();
		}

		delayTimer_ = 0;
	}


}

void RailScene::BombHitEffect(Bomb* bomb) {
	for (int32_t i = 0; i < 10; i++) {
		XMFLOAT3 pos = {
			bomb->GetBullet()->GetMatWorld().r[3].m128_f32[0],
			bomb->GetBullet()->GetMatWorld().r[3].m128_f32[1],
			bomb->GetBullet()->GetMatWorld().r[3].m128_f32[2]
		};
		pos.x += rand() % 40 - 20;
		pos.y += rand() % 40 - 20;
		pos.z += rand() % 40 - 20;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.01f;
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.z = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		bombParticle_->Add(30, pos, vel, acc, 8.0f, 0.0f, { 0.6f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	}
}

void RailScene::Pause()
{
	titleBackButton_->Update();
	back_->Update();
	restart_->Update();

	SoundManager::GetIns()->StopBGM(SoundManager::BGMKey::STAGE1_RAIL);

	if (titleBackButton_->GetIsClick()) {
		isTitleBack_ = true;
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}
	//ポーズ解除ボタンを選択中
	if (back_->GetIsClick()) {
		isPause_ = !isPause_;
	}

	//リスタートボタンを選択中
	if (restart_->GetIsClick()) {
		isRestart_ = true;
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}
}

void RailScene::Tutorial()
{
	//プレイヤーキャラの画面上の位置を求める
	XMVECTOR playerPos = { player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[0], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[1], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[2] };
	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	playerPos = XMVector3TransformCoord(playerPos, matVPV);
	XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };

	railTutorial_->SetPlayer2DPos(player2dPos);
	railTutorial_->Update();

}

void RailScene::SceneChange()
{
	//シーン切り替え
	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		//死亡フラグが立っている場合
		if (isDead_ && !isClear_) {
			SceneManager::AddScore(score_);
			SceneManager::SceneChange(SceneManager::SceneName::GameOver);
		}
		//クリアフラグが立っている場合
		else if (isClear_ && !isDead_) {
			SceneManager::AddScore(score_);
			//ステージ番号により派生
			if (SceneManager::GetStageNo() == 1) {
				SceneManager::SceneChange(SceneManager::SceneName::Stage1_Boss);
			}
			else if (SceneManager::GetStageNo() == 2) {
				SceneManager::SceneChange(SceneManager::SceneName::Stage2_Boss);
			}
			SoundManager::GetIns()->StopBGM(SoundManager::BGMKey::STAGE1_RAIL);
		}
		//タイトルバックボタンが押された場合
		else if (isTitleBack_) {
			SceneManager::SceneChange(SceneManager::SceneName::Title);
		}
		//リスタートボタンが押された場合
		else if (isRestart_) {
			//ステージ番号により派生
			if (SceneManager::GetStageNo() == 1) {
				SceneManager::SceneChange(SceneManager::SceneName::Stage1_Rail);
			}
			else if (SceneManager::GetStageNo() == 2) {
				SceneManager::SceneChange(SceneManager::SceneName::Stage2_Rail);
			}
		}
	}

}
