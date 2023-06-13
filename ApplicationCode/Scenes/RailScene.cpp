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
	restart_ = Button::CreateUniqueButton(ImageManager::ImageName::Restart, { 640, 600 }, { 256, 128 }, 0.0f);

	scoreSprite_ = Sprite::Create((UINT)ImageManager::ImageName::score, { 1180, 50 });
	scoreSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	scoreSprite_->SetSize({ scoreSprite_->GetSize().x / 2.0f, scoreSprite_->GetSize().y / 2.0f });
	textWindow_ = Sprite::Create((UINT)ImageManager::ImageName::TextWindow, { 580, 630 });
	textWindow_->SetAlpha(0.4f);
	textWindowSize_ = textWindow_->GetSize();
	textWindowSize_.y = 0;
	textWindow_->SetAnchorPoint({ 0.5f, 0.5f });
	faceWindow_ = Sprite::Create((UINT)ImageManager::ImageName::FaceWindow, { 90, 630 });
	faceWindowSize_ = faceWindow_->GetSize();
	faceWindowSize_.y = 0;
	faceWindow_->SetAlpha(0.4f);
	faceWindow_->SetAnchorPoint({ 0.5f, 0.5f });
	faceGraphicSize_ = { 160, 0 };
	for (int32_t i = 0; i < 3; i++) {
		opeNormal_[i] = Sprite::Create((UINT)ImageManager::ImageName::OPE_NORMAL, { 90, 630 });
		opeNormal_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeNormal_[i]->SetSize({ 160, 160 });
		opeNormal_[i]->SetColor({ 2, 2, 2 });
		opeNormal_[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSurprise_[i] = Sprite::Create((UINT)ImageManager::ImageName::OPE_SURPRISE, { 90, 630 });
		opeSurprise_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSurprise_[i]->SetSize({ 160, 160 });
		opeSurprise_[i]->SetColor({ 2, 2, 2 });
		opeSurprise_[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSmile_[i] = Sprite::Create((UINT)ImageManager::ImageName::OPE_SMILE, { 90, 630 });
		opeSmile_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSmile_[i]->SetSize({ 160, 160 });
		opeSmile_[i]->SetColor({ 2, 2, 2 });
		opeSmile_[i]->SetAnchorPoint({ 0.5f, 0.5f });

		bombTimerNumber_[i] = Sprite::Create((UINT)ImageManager::ImageName::scoreNumbers, { 0.0f, 0.0f });
		bombTimerNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		bombTimerNumber_[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		bombTimerNumber_[i]->SetSize({ 32, 32 });
	}
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i] = Sprite::Create((UINT)ImageManager::ImageName::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber_[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		scoreNumber_[i]->SetSize({ 32, 32 });
	}
	how_to_up_ = Sprite::Create((UINT)ImageManager::ImageName::How_to_Up, { 0, 0 });
	how_to_up_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_up_->SetSize({ 64.0f, 64.0f });
	how_to_up_alpha_ = 1.0f;
	how_to_down_ = Sprite::Create((UINT)ImageManager::ImageName::How_to_Down, { 0, 0 });
	how_to_down_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_down_->SetSize({ 64.0f, 64.0f });
	how_to_down_alpha_ = 1.0f;
	how_to_left_ = Sprite::Create((UINT)ImageManager::ImageName::How_to_Left, { 0, 0 });
	how_to_left_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_left_->SetSize({ 64.0f, 64.0f });
	how_to_left_alpha_ = 1.0f;
	how_to_right_ = Sprite::Create((UINT)ImageManager::ImageName::How_to_Right, { 0, 0 });
	how_to_right_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_right_->SetSize({ 64.0f, 64.0f });
	how_to_right_alpha_ = 1.0f;
	how_to_shot_ = Sprite::Create((UINT)ImageManager::ImageName::How_to_Shot, { 0, 0 });
	how_to_shot_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_shot_->SetSize({ 64.0f, 64.0f });
	how_to_shot_alpha_ = 1.0f;
	how_to_bomb_ = Sprite::Create((UINT)ImageManager::ImageName::How_to_Bomb, { 0, 0 });
	how_to_bomb_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_bomb_->SetSize({ 64.0f, 64.0f });
	how_to_bomb_alpha_ = 1.0f;

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

	//ステージデータ読み込み
	if (stageNo == 1) {
		player_->SetClearPos({ 130.0f, 20.0f, 55.0f });
		LoadRailPoint("Stage1RailPoints.aid");
		jsonLoader_->StageDataLoadandSet("stage1");
		enemyData_ = ExternalFileLoader::GetIns()->ExternalFileOpen("Stage1EnemyData.aid");
		textData_ = ExternalFileLoader::GetIns()->ExternalFileOpen("Stage1RailText.aid");
	}
	else if (stageNo == 2) {
		LoadRailPoint("Stage2RailPoints.aid");
		enemyData_ = ExternalFileLoader::GetIns()->ExternalFileOpen("Stage2EnemyData.aid");;
	}

	//ポストエフェクトの初期化
	postEffect_ = new PostEffect();
	postEffect_->Initialize();
	postEffectNo_ = PostEffect::PostEffectNo::NORMAL;

	//ゲームシーン用変数の初期化
	textAddTimer_ = 0;
	textSpeed_ = 1;
	textCount_ = 0;
	isTextDrawComplete_ = false;
	score_ = 0;
	clearTimer_ = clearTime;
	faceType_ = FaceGraphics::OPE_NORMALFACE;
	Reticle::GetIns()->SetIsSelectReticle(false);

	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

}

void RailScene::Update() {
	//スコアアイテムドロップ
	for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
		if (enemy->GetIsScoreItemDrop() && !enemy->GetIsTarget()) {
			std::unique_ptr<ScoreItem> scoreItem = std::make_unique<ScoreItem>();
			scoreItem->Initialize(enemy->GetEnemyObj()->GetMatWorld().r[3], player_, camera_);
			scoreItems_.push_back(std::move(scoreItem));
		}
	}

	//オブジェクトリスト解放処理
	enemies_.remove_if([](std::unique_ptr<BaseEnemy>& enemy) {return enemy->GetIsDead(); });
	particles2d_.remove_if([](std::unique_ptr<Particle2d>& particle) {return particle->IsDelete(); });
	scoreItems_.remove_if([](std::unique_ptr<ScoreItem>& scoreItem) {return scoreItem->GetIsDead(); });

	//丸影用プレイヤー座標セット
	light_->SetCircleShadowCasterPos(0, { player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[0], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[1], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[2] });
	//ポーズ切り替え
	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE) && player_->GetHPCount() != noneHP && !railCamera_->GetIsEnd()) {
		isPause_ = !isPause_;
	}
	//レールの最後までいったらクリア
	ClearPaformance();
	//プレイヤーが死亡しているか
	if (player_->GetIsDead()) {
		isDead_ = true;
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}

	//スコア表示
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i]->SetTextureRect({ (float)JudgeDigitNumber(score_, i), 0 }, { 64, 64 });
	}
	//レティクル更新処理
	Reticle::GetIns()->Update();
	Reticle::GetIns()->SetIsSelectReticle(false);

	if (!isPause_) {
		//エフェクト発生処理
		AddEffect();
		//当たり判定チェック
		CollisionCheck();
		//オブジェクト更新処理
		for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
			enemy->RockOnPerformance();
		}
		//ボム攻撃時にスローにする更新処理
		DelayUpdates();
		BombPerformance();
		//チュートリアル更新処理
		Tutorial();

		enemyParticle_->Update();
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
	for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
		enemy->Draw();
	}
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
	scoreSprite_->Draw();
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i]->Draw();
	}
	for (int32_t i = 0; i < 3; i++) {
		if (player_->GetIsBomb()) {
			bombTimerNumber_[i]->Draw();
		}
	}
	if (!isPause_) {
		textWindow_->Draw();
		faceWindow_->Draw();
		switch (faceType_) {
		case FaceGraphics::OPE_NORMALFACE:
			opeNormal_[faceAnimeCount_]->Draw();
			break;
		case FaceGraphics::OPE_SURPRISEFACE:
			opeSurprise_[faceAnimeCount_]->Draw();
			break;
		case FaceGraphics::OPE_SMILEFACE:
			opeSmile_[faceAnimeCount_]->Draw();
			break;
		}
	}
	how_to_up_->Draw();
	how_to_down_->Draw();
	how_to_left_->Draw();
	how_to_right_->Draw();
	if (enemies_.size() > 0) {
		how_to_bomb_->Draw();
	}
	how_to_shot_->Draw();
	player_->SpriteDraw();
	for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
		enemy->SpriteDraw();
	}
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
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect_->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	if (!isPause_) {
		TextMessageDraw();
	}
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect_->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo_, isRoop);
	DirectXSetting::GetIns()->PostDraw();
}

void RailScene::Finalize() {
	player_->Finalize();
	safe_delete(player_);
	safe_delete(camera_);
	safe_delete(railCamera_);
	safe_delete(postEffect_);
	safe_delete(pause_);
	safe_delete(scoreSprite_);
	safe_delete(light_);
	safe_delete(bombParticle_);
	safe_delete(gunParticle_);
	safe_delete(thrusterParticle_);
	safe_delete(enemyParticle_);
	safe_delete(textDraw_);
	safe_delete(textWindow_);
	safe_delete(faceWindow_);
	safe_delete(bulletManager_);
	for (int32_t i = 0; i < 3; i++) {
		safe_delete(opeNormal_[i]);
		safe_delete(opeSurprise_[i]);
		safe_delete(opeSmile_[i]);
		safe_delete(bombTimerNumber_[i]);
	}
	for (int32_t i = 0; i < 6; i++) {
		safe_delete(scoreNumber_[i]);
	}
	safe_delete(how_to_up_);
	safe_delete(how_to_down_);
	safe_delete(how_to_left_);
	safe_delete(how_to_right_);
	safe_delete(how_to_shot_);
	safe_delete(how_to_bomb_);
	jsonLoader_->Finalize();
}

void RailScene::EnemyDataUpdate() {
	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	Vector3 scale{};
	Vector3 movePoint{};
	std::vector<Vector3> movePoints{};
	std::string type;
	float moveTime = 120.0f;//2[s]
	int32_t lifeTime = 240;//4[s]
	int32_t shotIntervalTime = 60;//1[s]
	int32_t hp = 1;
	bool isPos = false;
	bool isRot = false;
	bool isStyle = false;
	bool isMovePoint = false;

	if (isWait_) {
		if (!isPause_) {
			waitTimer_--;
		}
		if (waitTimer_ <= 0) {
			isWait_ = false;
		}
		return;
	}

	while (getline(enemyData_, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "Pos") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isPos = true;
		}
		if (word == "Rot") {
			line_stream >> rot.x;
			line_stream >> rot.y;
			line_stream >> rot.z;
			isRot = true;
		}
		if (word == "Type") {
			line_stream >> type;
			isStyle = true;
		}
		if (word == "Move") {
			line_stream >> movePoint.x;
			line_stream >> movePoint.y;
			line_stream >> movePoint.z;
			movePoints.push_back(movePoint);
		}
		if (word == "End") {
			isMovePoint = true;
		}
		if (word == "MoveTime") {
			line_stream >> moveTime;
			//秒数換算なので60倍する
			moveTime *= 60.0f;
		}
		if (word == "LifeTime") {
			line_stream >> lifeTime;
			lifeTime *= 60;
		}
		if (word == "ShotCoolTime") {
			line_stream >> shotIntervalTime;
		}
		if (word == "Hp") {
			line_stream >> hp;
		}
		if (word == "Wait") {
			isWait_ = true;
			line_stream >> waitTimer_;

			break;
		}

		if (isPos && isRot && isStyle) {
			if (type == "STR") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<StraightEnemy>();
				newEnemy->Initialize("enemy1", pos, rot);
				newEnemy->SetRailScene(this);
				newEnemy->SetLifeTime(lifeTime);
				newEnemy->SetHP(hp);
				newEnemy->SetShotIntervalTime(shotIntervalTime);
				if (isMovePoint) {
					movePoints.insert(movePoints.begin(), pos);
					newEnemy->SetMaxTime(moveTime);
					newEnemy->SetMovePoints(movePoints);
				}
				newEnemy->SetBulletManager(bulletManager_);
				enemies_.push_back(std::move(newEnemy));
			}
			if (type == "AIM") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<AimingEnemy>();
				newEnemy->Initialize("enemy1", pos, rot);
				newEnemy->SetRailScene(this);
				newEnemy->SetPlayer(player_);
				newEnemy->SetLifeTime(lifeTime);
				newEnemy->SetHP(hp);
				newEnemy->SetShotIntervalTime(shotIntervalTime);
				if (isMovePoint) {
					movePoints.insert(movePoints.begin(), pos);
					newEnemy->SetMaxTime(moveTime);
					newEnemy->SetMovePoints(movePoints);
				}
				newEnemy->SetBulletManager(bulletManager_);
				enemies_.push_back(std::move(newEnemy));
			}
			if (type == "HOM") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<HomingEnemy>();
				newEnemy->Initialize("enemy1", pos, rot);
				newEnemy->SetRailScene(this);
				newEnemy->SetPlayer(player_);
				newEnemy->SetHP(hp);
				newEnemy->SetLifeTime(lifeTime);
				newEnemy->SetShotIntervalTime(shotIntervalTime);
				if (isMovePoint) {
					movePoints.insert(movePoints.begin(), pos);
					newEnemy->SetMaxTime(moveTime);
					newEnemy->SetMovePoints(movePoints);
				}
				newEnemy->SetBulletManager(bulletManager_);
				enemies_.push_back(std::move(newEnemy));
			}
			if (type == "SPR") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<SpreadEnemy>();
				newEnemy->Initialize("enemy1", pos, rot);
				newEnemy->SetRailScene(this);
				newEnemy->SetLifeTime(lifeTime);
				newEnemy->SetHP(hp);
				newEnemy->SetShotIntervalTime(shotIntervalTime);
				if (isMovePoint) {
					movePoints.insert(movePoints.begin(), pos);
					newEnemy->SetMaxTime(moveTime);
					newEnemy->SetMovePoints(movePoints);
				}
				newEnemy->SetBulletManager(bulletManager_);
				enemies_.push_back(std::move(newEnemy));
			}

			isPos = false;
			isRot = false;
			isStyle = false;
			isMovePoint = false;
		}
	}
}

void RailScene::LoadRailPoint(const std::string& filename) {
	//ファイルストリーム
	std::stringstream railcameraPointsData;
	railcameraPointsData = ExternalFileLoader::GetIns()->ExternalFileOpen(filename);

	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	rot = { 0, 0, 0 };
	Vector3 startPos{};
	bool isStart = false;
	bool isEnd = false;
	bool isRoop = false;
	bool isCameraRoop = false;
	bool isPoint = false;
	bool isTime = false;
	bool isRot = false;
	float splineTime = 0;
	int32_t stringCount = 0;
	RailCamera::MovePoints movePoints;

	while (getline(railcameraPointsData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "Start") {
			line_stream >> startPos.x;
			line_stream >> startPos.y;
			line_stream >> startPos.z;
			isStart = true;
		}

		if (word == "Pos") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isPoint = true;
		}

		if (word == "End") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isEnd = true;
		}

		if (word == "Roop") {
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isRoop = true;
		}

		if (word == "Time") {
			line_stream >> splineTime;
			isTime = true;
		}

		if (word == "Rot") {
			line_stream >> rot.x;
			line_stream >> rot.y;
			line_stream >> rot.z;
			isRot = true;
		}

		if (isStart) {
			points_.push_back(startPos);
			points_.push_back(startPos);
			cameraMoveTimes_.push_back(0);
			isStart = false;
		}
		else if (isEnd) {
			points_.push_back(pos);
			points_.push_back(pos);
			cameraRots_.emplace_back(cameraRots_.back());
			cameraMoveTimes_.push_back(0);
			isEnd = false;
		}
		else if (isRot) {
			if (cameraRots_.size() <= 0) {
				cameraRots_.push_back(rot);
			}
			cameraRots_.push_back(rot);
			isRot = false;
		}
		else if (isRoop) {
			points_.push_back(pos);
			points_.push_back(startPos);
			points_.push_back(startPos);
			isRoop = false;
			isCameraRoop = true;
		}
		else if (isTime) {
			splineTime *= 60;
			cameraMoveTimes_.push_back(splineTime);
			isTime = false;
		}
		else if (isPoint) {
			points_.push_back(pos);
		}

		stringCount++;
	}

	movePoints.points_ = points_;
	movePoints.cameraRot_ = cameraRots_;
	movePoints.moveTime_ = cameraMoveTimes_;

	assert(splineTime != 0);
	railCamera_->Initialize(startPos, cameraRots_.front(), movePoints, isCameraRoop);

}

void RailScene::TextMessageUpdate()
{
	std::string line;
	std::string face;
	std::string messageData;
	std::wstring messageDataW;

	if (isMessageWait_) {
		if (isTextDrawComplete_) {
			waitMessageTimer_--;
		}
		if (waitMessageTimer_ <= 0) {
			isMessageWait_ = false;
			textCount_ = 0;
			message_.clear();
			drawMessage_.clear();
		}
		return;
	}

	while (getline(textData_, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "OPEN") {
			isTextWindowOpen_ = true;
		}
		if (word == "FACE") {
			line_stream >> face;
			if (face == "OPE_NORMAL") {
				faceType_ = FaceGraphics::OPE_NORMALFACE;
			}
			else if (face == "OPE_SURPRISE") {
				faceType_ = FaceGraphics::OPE_SURPRISEFACE;
			}
			else if (face == "OPE_SMILE") {
				faceType_ = FaceGraphics::OPE_SMILEFACE;
			}
		}
		if (word == "TEXT") {
			line_stream >> messageData;
			messageDataW = ExternalFileLoader::GetIns()->StringToWstring(messageData);
			message_ = messageDataW;
		}
		if (word == "SPEED") {
			line_stream >> textSpeed_;
		}
		if (word == "WAIT") {
			isMessageWait_ = true;
			line_stream >> waitMessageTimer_;
			break;
		}
		if (word == "CLOSE") {
			isTextWindowOpen_ = false;
		}
	}
}

void RailScene::TextMessageDraw()
{
	//ウィンドウサイズ(クローズ時)
	const float closeWindowSizeY = 0.0f;
	//ウィンドウサイズ(オープン時)
	const float openWindowSizeY = 160.0f;

	//メッセージウィンドウ開閉処理
	//メッセージウィンドウ閉鎖処理
	if (!isTextWindowOpen_) {
		openWindowTimer_ = 0;
		closeWindowTimer_++;
		if (closeWindowTimer_ >= closeWindowTime) {
			closeWindowTimer_ = closeWindowTime;
		}
		//イーズインアウトでメッセージウィンドウを閉じる
		textWindowSize_.y = Easing::easeInOut((float)closeWindowTimer_, (float)closeWindowTime, closeWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)closeWindowTimer_, (float)closeWindowTime, closeWindowSizeY, faceWindowSize_.y);
		faceGraphicSize_.y = Easing::easeInOut((float)closeWindowTimer_, (float)closeWindowTime, closeWindowSizeY, faceGraphicSize_.y);
	}
	//メッセージウィンドウ開放処理
	else if (isTextWindowOpen_) {
		closeWindowTimer_ = 0;
		openWindowTimer_++;
		if (openWindowTimer_ >= openWindowTime) {
			openWindowTimer_ = openWindowTime;
		}
		//イーズインアウトでメッセージウィンドウを開く
		textWindowSize_.y = Easing::easeInOut((float)openWindowTimer_, (float)openWindowTime, openWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)openWindowTimer_, (float)openWindowTime, openWindowSizeY, faceWindowSize_.y);
		faceGraphicSize_.y = Easing::easeInOut((float)openWindowTimer_, (float)openWindowTime, openWindowSizeY, faceGraphicSize_.y);
	}

	//メッセージウィンドウサイズを変更
	textWindow_->SetSize(textWindowSize_);
	faceWindow_->SetSize(faceWindowSize_);
	for (int32_t i = 0; i < 3; i++) {
		opeNormal_[i]->SetSize(faceGraphicSize_);
		opeSurprise_[i]->SetSize(faceGraphicSize_);
		opeSmile_[i]->SetSize(faceGraphicSize_);
	}

	//顔グラフィックアニメーション時間加算
	faceAnimeTimer_++;
	if (faceAnimeTimer_ >= faceAnimeTime) {
		faceAnimeTimer_ = 0;
		faceAnimeCount_++;
		if (faceAnimeCount_ >= 3) {
			faceAnimeCount_ = 0;
		}
	}
	//読み込んだテキスト描画が完了していたら
	if (isTextDrawComplete_) {
		faceAnimeCount_ = 0;
		faceAnimeTimer_ = 0;
	}
	//テキストスピードが0以下にならないようにする
	if (textSpeed_ <= 0) {
		textSpeed_ = 1;
	}
	//テキスト描画範囲
	D2D1_RECT_F textDrawPos = {
		200, 560, 950, 700
	};
	D2D1_RECT_F bombMessageDrawPos = {
		400, 0, 900, 300
	};
	//テキストを1文字ずつ指定時間ごとに追加する
	textAddTimer_++;
	isTextDrawComplete_ = false;
	if (textAddTimer_ >= textSpeed_) {
		textAddTimer_ = 0;
		if (textCount_ < message_.size()) {
			if (message_.substr(textCount_, 1) != L"/") {
				drawMessage_ += message_.substr(textCount_, 1);
			}
			else {
				drawMessage_ += L"\n";
			}
			textCount_++;
		}
		//読み込んだテキスト描画が完了したら
		if (textCount_ >= message_.size()) {
			isTextDrawComplete_ = true;
		}
	}
	//現在追加されている文字を全て描画する
	textDraw_->Draw("meiryo", "white", drawMessage_, textDrawPos);
	if (player_->GetIsBomb()) {
		textDraw_->Draw("meiryo", "orange", L"時間内にできるだけ多くの敵を\nロックオンしてください。\n右クリックで発射可能", bombMessageDrawPos);
	}
}

bool RailScene::IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos) {
	const float aimPosCorrection = 20.0f;
	return (enemyPos.x >= aimPos.x - aimPosCorrection && enemyPos.x <= aimPos.x + aimPosCorrection && enemyPos.y >= aimPos.y - aimPosCorrection && enemyPos.y <= aimPos.y + aimPosCorrection);
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
		//敵出現処理
		EnemyDataUpdate();
		//テキスト更新処理
		TextMessageUpdate();

		//プレイヤーが生きている場合に更新
		if (player_->GetHPCount() > 0) {
			if (!railCamera_->GetIsEnd()) {
				railCamera_->Update();
			}
			for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
				enemy->Update();
				EnemyReactions(enemy.get());
			}
			for (std::unique_ptr<ScoreItem>& scoreItem : scoreItems_) {
				scoreItem->Update();
			}
		}

		bulletManager_->Update();
		for (std::unique_ptr<Particle2d>& particle2d : particles2d_) {
			particle2d->Update();
		}

		delayTimer_ = 0;
	}


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

void RailScene::CollisionCheck()
{
	for (const std::unique_ptr<BaseEnemy>& enemy : enemies_) {
		for (const std::unique_ptr<PlayerBullet>& playerBullet : bulletManager_->GetPlayerBullets()) {
			if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), enemy->GetEnemyObj(), 1.0f, 5.0f)) {
				score_ += 100;
				enemy->OnCollision();
				playerBullet->OnCollision();
			}
		}
	}

	for (const std::unique_ptr<EnemyBullet>& enemyBullet : bulletManager_->GetEnemyBullets()) {
		if (Collision::GetIns()->OBJSphereCollision(enemyBullet->GetEnemyBulletObj(), player_->GetPlayerObject(), 1.0f, 2.0f)) {
			if (!player_->GetIsDamage() && player_->GetHPCount() > noneHP) {
				player_->OnCollision();
			}
			enemyBullet->OnCollision();
			railCamera_->SetIsDamage();
		}
	}

	for (const std::unique_ptr<BaseEnemy>& enemy : enemies_) {
		for (const std::unique_ptr<Bomb>& bomb : bulletManager_->GetBombs()) {
			if (Collision::GetIns()->OBJSphereCollision(enemy->GetEnemyObj(), bomb->GetBullet(), 5.0f, 1.0f)) {
				score_ += 100;
				enemy->BombHitCollision();
				BombHitEffect(bomb.get());
				bomb->OnCollision();
			}
		}
	}

	for (const std::unique_ptr<ScoreItem>& scoreItem : scoreItems_) {
		if (Collision::GetIns()->OBJSphereCollision(scoreItem->GetScoreItemObj(), player_->GetPlayerObject(), 1.0f, 2.0f)) {
			score_ += 500;
			scoreItem->OnCollision();
		}
	}
}

void RailScene::EnemyReactions(BaseEnemy* enemy)
{
	const int32_t randMax = 4;

	//敵座標
	Vector3 enemyPos;
	enemyPos = enemy->GetEnemyObj()->GetMatWorld().r[3];

	//敵のHPが0ならパーティクルを発生させる
	if (enemy->GetHP() <= 0) {
		enemyParticle_->Add(30, enemyPos, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.02f, 0.0f }, 5.0f, 0.0f);
	}

	//ロックオン処理
	XMVECTOR enemy3dPos = { enemy->GetEnemyObj()->GetMatWorld().r[3] }; //ワールド座標
	XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
	enemy3dPos = XMVector3TransformCoord(enemy3dPos, matViewProjectionViewport); //スクリーン座標

	DirectX::XMFLOAT2 enemy2dPos = { enemy3dPos.m128_f32[0], enemy3dPos.m128_f32[1] };

	if (IsTargetCheck(enemy2dPos, Reticle::GetIns()->GetPos())) {
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (player_->GetIsBomb()) {
			enemy->SetTarget(true);
		}
	}

	//敵が死亡したらエフェクトを発生させる
	if (enemy->GetIsDead() && enemy->GetHP() <= 0) {
		const Vector3 explosionAcc = { 0.0f, 0.0f, 0.0f };
		const float startScale = 10.0f;
		const float endScale = 0.0f;
		const Vector3 startColor = { 1.0f, 1.0f, 1.0f };
		const Vector3 endColor = { 1.0f, 0.2f, 0.0f };
		for (int32_t i = 0; i < 32; i++) {
			const float rnd_vel = 2.0f;

			Vector3 particlePos = enemyPos;
			particlePos.x += (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			particlePos.y += (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			particlePos.z += (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			XMFLOAT3 acc{};
			const float rnd_acc = 0.01f;
			acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
			acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
			acc.z = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
			enemyParticle_->Add(20,
				particlePos,
				vel,
				acc,
				startScale,
				endScale,
				startColor,
				endColor);
		}
	}
}

void RailScene::AddEffect()
{
	//最終的な大きさ
	const float endScale = 0.0f;
	//デフォルト加速度
	const Vector3 defaultAcc = { 0.0f, 0.0f, 0.0f };

	//プレイヤーのHPが1以上ならエフェクトを発生させる
	if (player_->GetHPCount() > noneHP) {
		//乱数上限
		const int32_t randMax = 5;
		//パーティクル生成時間
		int32_t particleLife = 3;
		//初期アルファ値
		Vector3 initAlpha = { 0.0f, 0.0f, 0.6f };
		//最終的なアルファ値
		Vector3 endAlpha = { 1.0f, 1.0f, 1.0f };

		//プレイヤーのワールド行列からパーティクルの生成位置を求める
		XMVECTOR playerPos = { 0.0f, 1.2f, -1.0f };
		playerPos = XMVector3TransformCoord(playerPos, player_->GetPlayerObject()->GetMatWorld());
		Vector3 thrusterPos = playerPos;

		for (int32_t i = 0; i < 10; i++) {
			float thrusterPower = (float)(rand() % randMax);
			thrusterPower *= -0.1f;
			float startScale = (float)(rand() % (randMax - 2));
			XMVECTOR playerBack = { 0.0f, 0.0f, thrusterPower };
			playerBack = XMVector3TransformNormal(playerBack, player_->GetPlayerObject()->GetMatWorld());
			Vector3 thrusterDir = playerBack;
			thrusterParticle_->Add(
				particleLife,
				thrusterPos,
				thrusterDir,
				defaultAcc,
				startScale,
				endScale,
				initAlpha,
				endAlpha
			);
		}
	}

	//プレイヤーのHPが0ならエフェクトを発生させる
	if (player_->GetHPCount() <= noneHP && !isPlayerDead_) {
		XMVECTOR playerPos = { player_->GetPlayerPos().x, player_->GetPlayerPos().y, player_->GetPlayerPos().z };
		XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
		playerPos = XMVector3TransformCoord(playerPos, matVPV);

		XMFLOAT2 player2dPos = { playerPos.m128_f32[0] - 150, playerPos.m128_f32[1] - 140 };
		std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
		new2DParticle->Initialize(player2dPos, { 200, 200 }, 80, ImageManager::ImageName::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
		particles2d_.push_back(std::move(new2DParticle));
		isPlayerDead_ = true;
		SoundManager::GetIns()->StopBGM(SoundManager::BGMKey::STAGE1_RAIL);
	}

	//マズルフラッシュを発生させる
	if (player_->GetIsShot()) {
		Vector3 gunPos = player_->GetGunObject()->GetMatWorld().r[3];
		gunParticle_->Add(2, gunPos,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			5.0f, 0.0f,
			{ 0.5f, 0.0f, 0.0f },
			{ 0.5f, 0.3f, 0.0f }
		);
	}

	for (const std::unique_ptr<Bomb>& bomb : bulletManager_->GetBombs()) {
		//ボムの軌跡にパーティクルを発生させる
		Vector3 bombPos = bomb->GetBullet()->GetMatWorld().r[3];
		bombParticle_->Add(20, bombPos,
			{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
			3.0f, 0.0f, { 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f }, 1.0f, 0.0f);
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
	//定数
	const float iconSlidePos = 100.0f;

	if (enemies_.size() > 0) {
		isMoveUp_ = true;
		isMoveDown_ = true;
		isMoveLeft_ = true;
		isMoveRight_ = true;
		isShot_ = true;
	}

	//プレイヤーキャラの画面上の位置を求める
	XMVECTOR playerPos = { player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[0], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[1], player_->GetPlayerObject()->GetMatWorld().r[3].m128_f32[2] };
	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	playerPos = XMVector3TransformCoord(playerPos, matVPV);
	XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };

	//チュートリアルアイコンの座標を求める
	how_to_up_->SetPosition({ player2dPos.x, player2dPos.y - iconSlidePos });
	how_to_down_->SetPosition({ player2dPos.x, player2dPos.y + iconSlidePos });
	how_to_left_->SetPosition({ player2dPos.x - iconSlidePos, player2dPos.y });
	how_to_right_->SetPosition({ player2dPos.x + iconSlidePos, player2dPos.y });
	how_to_shot_->SetPosition({ Reticle::GetIns()->GetPos().x, Reticle::GetIns()->GetPos().y - iconSlidePos });
	how_to_bomb_->SetPosition({ Reticle::GetIns()->GetPos().x, Reticle::GetIns()->GetPos().y - iconSlidePos });

	//チュートリル完了したら透明にする
	if (KeyInput::GetIns()->TriggerKey(DIK_W)) {
		isMoveUp_ = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_S)) {
		isMoveDown_ = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_A)) {
		isMoveLeft_ = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_D)) {
		isMoveRight_ = true;
	}
	if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK)) {
		isShot_ = true;
	}
	if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::RIGHT_CLICK)) {
		isBombShot_ = true;
	}

	if (isMoveUp_ && how_to_up_alpha_ > 0) {
		how_to_up_alpha_ -= 0.05f;
		how_to_up_->SetAlpha(how_to_up_alpha_);
	}
	if (isMoveDown_ && how_to_down_alpha_ > 0) {
		how_to_down_alpha_ -= 0.05f;
		how_to_down_->SetAlpha(how_to_down_alpha_);
	}
	if (isMoveLeft_ && how_to_left_alpha_ > 0) {
		how_to_left_alpha_ -= 0.05f;
		how_to_left_->SetAlpha(how_to_left_alpha_);
	}
	if (isMoveRight_ && how_to_right_alpha_ > 0) {
		how_to_right_alpha_ -= 0.05f;
		how_to_right_->SetAlpha(how_to_right_alpha_);
	}
	if (isShot_ && how_to_shot_alpha_ > 0) {
		how_to_shot_alpha_ -= 0.05f;
		how_to_shot_->SetAlpha(how_to_shot_alpha_);
	}
	if (isBombShot_ && how_to_bomb_alpha_ > 0) {
		how_to_bomb_alpha_ -= 0.1f;
		how_to_bomb_->SetAlpha(how_to_bomb_alpha_);
	}
}

void RailScene::BombPerformance()
{
	for (int32_t i = 0; i < 3; i++) {
		bombTimerNumber_[i]->SetTextureRect({ (float)JudgeDigitNumber((player_->GetBombTimer() * 100 / 60), i), 0.0f }, { 64.0f, 64.0f });
		bombTimerNumber_[i]->SetPosition({ Reticle::GetIns()->GetPos().x - (30.0f * i) + 30.0f, Reticle::GetIns()->GetPos().y - 100.0f });
	}
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

	//デバッグ用
	//if (KeyInput::GetIns()->TriggerKey(DIK_N)) {
	//	SceneManager::AddScore(score_);
	//	SceneManager::SceneChange(SceneManager::Stage1_Boss);
	//}
}
