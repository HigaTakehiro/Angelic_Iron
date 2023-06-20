//#include "EnemyManager.h"
//#include "ExternalFileLoader.h"
//#include "StraightEnemy.h"
//#include "AimingEnemy.h"
//#include "HomingEnemy.h"
//#include "SpreadEnemy.h"
//#include "MouseInput.h"
//
//void EnemyManager::Initialize(const std::string& fileName)
//{
//	enemyData_ = ExternalFileLoader::GetIns()->ExternalFileOpen(fileName);
//	LoadEnemyData();
//}
//
//void EnemyManager::Update(bool isPause)
//{
//	enemies_.remove_if([](std::unique_ptr<BaseEnemy>& enemy) {return enemy->GetIsDead(); });
//	if (!isPause) {
//		EnemyDataUpdate(isPause);
//		particles_->Update();
//		for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
//			enemy->Update();
//			EnemyReactions(enemy.get());
//		}
//	}
//}
//
//void EnemyManager::Draw()
//{
//	for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
//		enemy->Draw();
//	}
//}
//
//void EnemyManager::SpriteDraw()
//{
//	for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
//		enemy->SpriteDraw();
//	}
//}
//
//void EnemyManager::EnemyDataUpdate(bool isPause)
//{
//	if (isWait_) {
//		if (!isPause) {
//			waitTimer_--;
//			if (waitTimer_ <= 0) {
//				isWait_ = false;
//			}
//		}
//		return;
//	}
//
//	if (it_ == enemyDatas_.end()) {
//		return;
//	}
//
//	if (it_->type_ == "STR") {
//		std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<StraightEnemy>();
//		newEnemy->Initialize("enemy1", it_->pos_, it_->rot_);
//		newEnemy->SetRailScene(railScene_);
//		newEnemy->SetLifeTime(it_->lifeTime_);
//		newEnemy->SetHP(it_->hp_);
//		newEnemy->SetShotIntervalTime(it_->shotInterval_);
//		if (it_->movePoints_.size() > 0) {
//			it_->movePoints_.insert(it_->movePoints_.begin(), it_->pos_);
//			newEnemy->SetMaxTime(it_->moveTime_);
//			newEnemy->SetMovePoints(it_->movePoints_);
//		}
//		newEnemy->SetBulletManager(bulletManager_);
//		enemies_.push_back(std::move(newEnemy));
//	}
//	if (it_->type_ == "AIM") {
//		std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<AimingEnemy>();
//		newEnemy->Initialize("enemy1", it_->pos_, it_->rot_);
//		newEnemy->SetRailScene(railScene_);
//		newEnemy->SetPlayer(player_);
//		newEnemy->SetLifeTime(it_->lifeTime_);
//		newEnemy->SetHP(it_->hp_);
//		newEnemy->SetShotIntervalTime(it_->shotInterval_);
//		if (it_->movePoints_.size() > 0) {
//			it_->movePoints_.insert(it_->movePoints_.begin(), it_->pos_);
//			newEnemy->SetMaxTime(it_->moveTime_);
//			newEnemy->SetMovePoints(it_->movePoints_);
//		}
//		newEnemy->SetBulletManager(bulletManager_);
//		enemies_.push_back(std::move(newEnemy));
//	}
//	if (it_->type_ == "HOM") {
//		std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<HomingEnemy>();
//		newEnemy->Initialize("enemy1", it_->pos_, it_->rot_);
//		newEnemy->SetRailScene(railScene_);
//		newEnemy->SetPlayer(player_);
//		newEnemy->SetHP(it_->hp_);
//		newEnemy->SetLifeTime(it_->lifeTime_);
//		newEnemy->SetShotIntervalTime(it_->shotInterval_);
//		if (it_->movePoints_.size() > 0) {
//			it_->movePoints_.insert(it_->movePoints_.begin(), it_->pos_);
//			newEnemy->SetMaxTime(it_->moveTime_);
//			newEnemy->SetMovePoints(it_->movePoints_);
//		}
//		newEnemy->SetBulletManager(bulletManager_);
//		enemies_.push_back(std::move(newEnemy));
//	}
//	if (it_->type_ == "SPR") {
//		std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<SpreadEnemy>();
//		newEnemy->Initialize("enemy1", it_->pos_, it_->rot_);
//		newEnemy->SetRailScene(railScene_);
//		newEnemy->SetLifeTime(it_->lifeTime_);
//		newEnemy->SetHP(it_->hp_);
//		newEnemy->SetShotIntervalTime(it_->shotInterval_);
//		if (it_->movePoints_.size() > 0) {
//			it_->movePoints_.insert(it_->movePoints_.begin(), it_->pos_);
//			newEnemy->SetMaxTime(it_->moveTime_);
//			newEnemy->SetMovePoints(it_->movePoints_);
//		}
//		newEnemy->SetBulletManager(bulletManager_);
//		enemies_.push_back(std::move(newEnemy));
//	}
//
//	if (it_->waitTime_ > 0) {
//		isWait_ = true;
//		waitTimer_ = it_->waitTime_;
//	}
//
//	it_++;
//}
//
//void EnemyManager::EnemyReactions(BaseEnemy* enemy)
//{
//	const int32_t randMax = 4;
//
//	//敵座標
//	Vector3 enemyPos;
//	enemyPos = enemy->GetEnemyObj()->GetMatWorld().r[3];
//
//	//敵のHPが0ならパーティクルを発生させる
//	if (enemy->GetHP() <= 0) {
//		particles_->Add(30, enemyPos, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.02f, 0.0f }, 5.0f, 0.0f);
//	}
//
//	//ロックオン処理
//	XMVECTOR enemy3dPos = { enemy->GetEnemyObj()->GetMatWorld().r[3] }; //ワールド座標
//	XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //ビュープロジェクションビューポート行列
//	enemy3dPos = XMVector3TransformCoord(enemy3dPos, matViewProjectionViewport); //スクリーン座標
//
//	DirectX::XMFLOAT2 enemy2dPos = { enemy3dPos.m128_f32[0], enemy3dPos.m128_f32[1] };
//
//	if (IsTargetCheck(enemy2dPos)) {
//		Reticle::GetIns()->SetIsSelectReticle(true);
//		if (player_->GetIsBomb()) {
//			enemy->SetTarget(true);
//		}
//	}
//
//	//敵が死亡したらエフェクトを発生させる
//	if (enemy->GetIsDead() && enemy->GetHP() <= 0) {
//		const Vector3 explosionAcc = { 0.0f, 0.0f, 0.0f };
//		const float startScale = 10.0f;
//		const float endScale = 0.0f;
//		const Vector3 startColor = { 1.0f, 1.0f, 1.0f };
//		const Vector3 endColor = { 1.0f, 0.2f, 0.0f };
//		for (int32_t i = 0; i < 32; i++) {
//			const float rnd_vel = 2.0f;
//
//			Vector3 particlePos = enemyPos;
//			particlePos.x += (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
//			particlePos.y += (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
//			particlePos.z += (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
//
//			XMFLOAT3 vel{};
//			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
//			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
//			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
//
//			XMFLOAT3 acc{};
//			const float rnd_acc = 0.01f;
//			acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
//			acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
//			acc.z = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
//			particles_->Add(20,
//				particlePos,
//				vel,
//				acc,
//				startScale,
//				endScale,
//				startColor,
//				endColor);
//		}
//	}
//}
//
//void RailScene::AddEffect()
//{
//	//最終的な大きさ
//	const float endScale = 0.0f;
//	//デフォルト加速度
//	const Vector3 defaultAcc = { 0.0f, 0.0f, 0.0f };
//
//	//プレイヤーのHPが1以上ならエフェクトを発生させる
//	if (player_->GetHPCount() > noneHP) {
//		//乱数上限
//		const int32_t randMax = 5;
//		//パーティクル生成時間
//		int32_t particleLife = 3;
//		//初期アルファ値
//		Vector3 initAlpha = { 0.0f, 0.0f, 0.6f };
//		//最終的なアルファ値
//		Vector3 endAlpha = { 1.0f, 1.0f, 1.0f };
//
//		//プレイヤーのワールド行列からパーティクルの生成位置を求める
//		XMVECTOR playerPos = { 0.0f, 1.2f, -1.0f };
//		playerPos = XMVector3TransformCoord(playerPos, player_->GetPlayerObject()->GetMatWorld());
//		Vector3 thrusterPos = playerPos;
//
//		for (int32_t i = 0; i < 10; i++) {
//			float thrusterPower = (float)(rand() % randMax);
//			thrusterPower *= -0.1f;
//			float startScale = (float)(rand() % (randMax - 2));
//			XMVECTOR playerBack = { 0.0f, 0.0f, thrusterPower };
//			playerBack = XMVector3TransformNormal(playerBack, player_->GetPlayerObject()->GetMatWorld());
//			Vector3 thrusterDir = playerBack;
//			thrusterParticle_->Add(
//				particleLife,
//				thrusterPos,
//				thrusterDir,
//				defaultAcc,
//				startScale,
//				endScale,
//				initAlpha,
//				endAlpha
//			);
//		}
//	}
//
//	//プレイヤーのHPが0ならエフェクトを発生させる
//	if (player_->GetHPCount() <= noneHP && !isPlayerDead_) {
//		XMVECTOR playerPos = { player_->GetPlayerPos().x, player_->GetPlayerPos().y, player_->GetPlayerPos().z };
//		XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
//		playerPos = XMVector3TransformCoord(playerPos, matVPV);
//
//		XMFLOAT2 player2dPos = { playerPos.m128_f32[0] - 150, playerPos.m128_f32[1] - 140 };
//		std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
//		new2DParticle->Initialize(player2dPos, { 200, 200 }, 80, ImageManager::ImageName::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
//		particles2d_.push_back(std::move(new2DParticle));
//		isPlayerDead_ = true;
//		SoundManager::GetIns()->StopBGM(SoundManager::BGMKey::STAGE1_RAIL);
//	}
//
//	//マズルフラッシュを発生させる
//	if (player_->GetIsShot()) {
//		Vector3 gunPos = player_->GetGunObject()->GetMatWorld().r[3];
//		gunParticle_->Add(2, gunPos,
//			{ 0.0f, 0.0f, 0.0f },
//			{ 0.0f, 0.0f, 0.0f },
//			5.0f, 0.0f,
//			{ 0.5f, 0.0f, 0.0f },
//			{ 0.5f, 0.3f, 0.0f }
//		);
//	}
//
//	for (const std::unique_ptr<Bomb>& bomb : bulletManager_->GetBombs()) {
//		//ボムの軌跡にパーティクルを発生させる
//		Vector3 bombPos = bomb->GetBullet()->GetMatWorld().r[3];
//		bombParticle_->Add(20, bombPos,
//			{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
//			3.0f, 0.0f, { 1.0f, 1.0f, 1.0f },
//			{ 1.0f, 1.0f, 1.0f }, 1.0f, 0.0f);
//	}
//}
//
//void EnemyManager::LoadEnemyData()
//{
//	std::string line;
//	Vector3 pos{};
//	Vector3 rot{};
//	Vector3 scale{};
//	Vector3 movePoint{};
//	std::vector<Vector3> movePoints{};
//	std::string type;
//	float moveTime = 120.0f;//2[s]
//	int32_t lifeTime = 240;//4[s]
//	int32_t shotIntervalTime = 60;//1[s]
//	int32_t hp = 1;
//	int32_t waitTime = 0;
//	bool isPos = false;
//	bool isRot = false;
//	bool isStyle = false;
//	bool isMovePoint = false;
//
//	while (getline(enemyData_, line)) {
//		std::istringstream line_stream(line);
//		std::string word;
//		//半角区切りで文字列を取得
//		getline(line_stream, word, ' ');
//		if (word == "#") {
//			continue;
//		}
//		if (word == "Pos") {
//			line_stream >> pos.x;
//			line_stream >> pos.y;
//			line_stream >> pos.z;
//			isPos = true;
//		}
//		if (word == "Rot") {
//			line_stream >> rot.x;
//			line_stream >> rot.y;
//			line_stream >> rot.z;
//			isRot = true;
//		}
//		if (word == "Type") {
//			line_stream >> type;
//			isStyle = true;
//		}
//		if (word == "Move") {
//			line_stream >> movePoint.x;
//			line_stream >> movePoint.y;
//			line_stream >> movePoint.z;
//			movePoints.push_back(movePoint);
//		}
//		if (word == "End") {
//			isMovePoint = true;
//		}
//		if (word == "MoveTime") {
//			line_stream >> moveTime;
//			//秒数換算なので60倍する
//			moveTime *= 60.0f;
//		}
//		if (word == "LifeTime") {
//			line_stream >> lifeTime;
//			lifeTime *= 60;
//		}
//		if (word == "ShotCoolTime") {
//			line_stream >> shotIntervalTime;
//		}
//		if (word == "Hp") {
//			line_stream >> hp;
//		}
//		if (word == "Wait") {
//			line_stream >> waitTime;
//			//break;
//		}
//
//		if (isPos && isRot && isStyle) {
//			EnemyData enemyData;
//			enemyData.pos_ = pos;
//			enemyData.rot_ = rot;
//			enemyData.type_ = type;
//			if (isMovePoint) {
//				enemyData.movePoints_ = movePoints;
//				movePoints.clear();
//			}
//			enemyData.moveTime_ = moveTime;
//			enemyData.lifeTime_ = lifeTime;
//			enemyData.shotInterval_ = shotIntervalTime;
//			enemyData.hp_ = hp;
//			enemyData.waitTime_ = waitTime;
//			enemyDatas_.push_back(enemyData);
//
//			isPos = false;
//			isRot = false;
//			isStyle = false;
//			isMovePoint = false;
//		}
//	}
//
//	it_ = enemyDatas_.begin();
//}
//
//void EnemyManager::EnemyRockOnPerformance()
//{
//	for (std::unique_ptr<BaseEnemy>& enemy : enemies_) {
//		enemy->RockOnPerformance();
//	}
//}
//
//bool EnemyManager::IsTargetCheck(DirectX::XMFLOAT2 enemyPos)
//{
//	const float aimPosCorrection = 20.0f;
//	DirectX::XMFLOAT2 aimPos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
//	return (enemyPos.x >= aimPos.x - aimPosCorrection && enemyPos.x <= aimPos.x + aimPosCorrection && enemyPos.y >= aimPos.y - aimPosCorrection && enemyPos.y <= aimPos.y + aimPosCorrection);
//}
