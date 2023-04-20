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
#include "HomingEnemy.h"
#include "DirectXSetting.h"
#include "ExternalFileLoader.h"
#include <algorithm>
#include <fstream>

using namespace DirectX;
using namespace Microsoft::WRL;

void RailScene::Initialize() {

	//SoundManager::GetIns()->PlayBGM(SoundManager::STAGE1_RAIL, true, 0.2f);

	//�J����������
	camera = new Camera;
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));
	railCamera = new RailCamera;

	//�f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextNumber);

	//�X�v���C�g�摜������
	pause = Sprite::Create(ImageManager::ImageName::Pause, { 640, 100 });
	pause->SetAnchorPoint({ 0.5f, 0.5f });
	titleBack = Sprite::Create(ImageManager::ImageName::TitleBack, { 640, 300 });
	titleBack->SetAnchorPoint({ 0.5f, 0.5f });
	titleBackSize = titleBack->GetSize();
	back = Sprite::Create(ImageManager::ImageName::Back, { 640, 450 });
	back->SetAnchorPoint({ 0.5f, 0.5f });
	backSize = back->GetSize();
	restart = Sprite::Create(ImageManager::Restart, { 640, 600 });
	restart->SetAnchorPoint({ 0.5f, 0.5f });
	restartSize = restart->GetSize();
	restartSize.x /= 2;
	restartSize.y /= 2;
	scoreSprite = Sprite::Create(ImageManager::score, { 1180, 50 });
	scoreSprite->SetAnchorPoint({ 0.5f, 0.5f });
	scoreSprite->SetSize({ scoreSprite->GetSize().x / 2.0f, scoreSprite->GetSize().y / 2.0f });
	textWindow = Sprite::Create(ImageManager::TextWindow, { 580, 630 });
	textWindow->SetAlpha(0.4f);
	textWindowSize = textWindow->GetSize();
	textWindowSize.y = 0;
	textWindow->SetAnchorPoint({ 0.5f, 0.5f });
	faceWindow = Sprite::Create(ImageManager::FaceWindow, { 90, 630 });
	faceWindowSize = faceWindow->GetSize();
	faceWindowSize.y = 0;
	faceWindow->SetAlpha(0.4f);
	faceWindow->SetAnchorPoint({ 0.5f, 0.5f });
	faceGraphicSize = { 160, 0 };
	for (int32_t i = 0; i < 3; i++) {
		opeNormal[i] = Sprite::Create(ImageManager::OPE_NORMAL, { 90, 630 });
		opeNormal[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeNormal[i]->SetSize({ 160, 160 });
		opeNormal[i]->SetColor({ 2, 2, 2 });
		opeNormal[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSurprise[i] = Sprite::Create(ImageManager::OPE_SURPRISE, { 90, 630 });
		opeSurprise[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSurprise[i]->SetSize({ 160, 160 });
		opeSurprise[i]->SetColor({ 2, 2, 2 });
		opeSurprise[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSmile[i] = Sprite::Create(ImageManager::OPE_SMILE, { 90, 630 });
		opeSmile[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSmile[i]->SetSize({ 160, 160 });
		opeSmile[i]->SetColor({ 2, 2, 2 });
		opeSmile[i]->SetAnchorPoint({ 0.5f, 0.5f });

		bombTimerNumber[i] = Sprite::Create(ImageManager::scoreNumbers, { 0.0f, 0.0f });
		bombTimerNumber[i]->SetAnchorPoint({ 0.5f, 0.5f });
		bombTimerNumber[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		bombTimerNumber[i]->SetSize({ 32, 32 });
	}
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber[i] = Sprite::Create(ImageManager::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		scoreNumber[i]->SetSize({ 32, 32 });
	}
	how_to_up_ = Sprite::Create(ImageManager::How_to_Up, { 0, 0 });
	how_to_up_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_up_->SetSize({ 64.0f, 64.0f });
	how_to_up_alpha_ = 1.0f;
	how_to_down_ = Sprite::Create(ImageManager::How_to_Down, { 0, 0 });
	how_to_down_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_down_->SetSize({ 64.0f, 64.0f });
	how_to_down_alpha_ = 1.0f;
	how_to_left_ = Sprite::Create(ImageManager::How_to_Left, { 0, 0 });
	how_to_left_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_left_->SetSize({ 64.0f, 64.0f });
	how_to_left_alpha_ = 1.0f;
	how_to_right_ = Sprite::Create(ImageManager::How_to_Right, { 0, 0 });
	how_to_right_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_right_->SetSize({ 64.0f, 64.0f });
	how_to_right_alpha_ = 1.0f;
	how_to_shot_ = Sprite::Create(ImageManager::How_to_Shot, { 0, 0 });
	how_to_shot_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_shot_->SetSize({ 64.0f, 64.0f });
	how_to_shot_alpha_ = 1.0f;
	how_to_bomb_ = Sprite::Create(ImageManager::How_to_Bomb, { 0, 0 });
	how_to_bomb_->SetAnchorPoint({ 0.5f, 0.5f });
	how_to_bomb_->SetSize({ 64.0f, 64.0f });
	how_to_bomb_alpha_ = 1.0f;

	//���C�g������
	light = LightGroup::Create();
	for (int32_t i = 0; i < 3; i++) {
		light->SetDirLightActive(0, true);
		light->SetPointLightActive(i, false);
		light->SetSpotLightActive(i, false);
	}
	light->SetCircleShadowActive(0, true);
	light->SetDirLightDirection(0, { 0, -1, 0 });
	light->SetCircleShadowDir(0, { 0, -1, 0 });
	light->SetCircleShadowAtten(0, { 0.0f, 0.01f, 0.0f });
	light->SetCircleShadowDistanceCasterLight(0, 1000.0f);
	light->SetCircleShadowAngle(0, { 0.0f, 0.5f });
	Object3d::SetLight(light);

	//3d�I�u�W�F�N�g������
	int32_t stageNo;
	stageNo = SceneManager::GetStageNo();

	//�X�e�[�W�w�i�I�u�W�F�N�g������
	jsonLoader = std::make_unique<JsonLoader>();

	//�v���C���[������
	player = new Player;
	player->Initialize(camera, clearTime);
	player->SetRailScene(this);

	//�p�[�e�B�N��������
	bombParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	enemyParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	gunParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	thrusterParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);

	//�X�e�[�W�f�[�^�ǂݍ���
	if (stageNo == 1) {
		player->SetClearPos({ 130.0f, 20.0f, 55.0f });
		LoadRailPoint("Stage1RailPoints.aid");
		jsonLoader->StageDataLoadandSet("stage1");
		enemyData = ExternalFileLoader::GetIns()->ExternalFileOpen("Stage1EnemyData.aid");
		textData = ExternalFileLoader::GetIns()->ExternalFileOpen("Stage1RailText.aid");
	}
	else if (stageNo == 2) {
		LoadRailPoint("Stage2RailPoints.aid");
		enemyData = ExternalFileLoader::GetIns()->ExternalFileOpen("Stage2EnemyData.aid");;
	}

	//�|�X�g�G�t�F�N�g�̏�����
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffectNo = PostEffect::NORMAL;

	//�Q�[���V�[���p�ϐ��̏�����
	textAddTimer = 0;
	textSpeed = 1;
	textCount = 0;
	isTextDrawComplete = false;
	score = 0;
	clearTimer = clearTime;
	faceType = FaceGraphics::OPE_NORMALFACE;
	Reticle::GetIns()->SetIsSelectReticle(false);

	SceneChangeEffect::GetIns()->SetIsSceneChangeComplete(true);

}

void RailScene::Update() {
	//�I�u�W�F�N�g���X�g�������
	enemies.remove_if([](std::unique_ptr<BaseEnemy>& enemy) {return enemy->GetIsDead(); });
	enemyBullets.remove_if([](std::unique_ptr<EnemyBullet>& enemyBullet) { return enemyBullet->IsDead(); });
	playerBullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	particles2d.remove_if([](std::unique_ptr<Particle2d>& particle) {return particle->IsDelete(); });
	bulletCases.remove_if([](std::unique_ptr<BulletCase>& bulletCase) {return bulletCase->IsDead(); });
	bombs.remove_if([](std::unique_ptr<Bomb>& bomb) {return bomb->GetIsDead(); });
	//�ۉe�p�v���C���[���W�Z�b�g
	light->SetCircleShadowCasterPos(0, { player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[0], player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[1], player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[2] });
	//�|�[�Y�؂�ւ�
	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE) && player->GetHPCount() != noneHP && !railCamera->GetIsEnd()) {
		isPause = !isPause;
	}
	//���[���̍Ō�܂ł�������N���A
	ClearPaformance();
	//�v���C���[�����S���Ă��邩
	if (player->GetIsDead()) {
		isDead = true;
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}

	//�X�R�A�\��
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber[i]->SetTextureRect({ (float)JudgeDigitNumber(score, i), 0 }, { 64, 64 });
	}
	//�G�t�F�N�g��������
	AddEffect();
	//���e�B�N���X�V����
	Reticle::GetIns()->Update();
	Reticle::GetIns()->SetIsSelectReticle(false);

	if (!isPause) {
		//�����蔻��`�F�b�N
		CollisionCheck();
		//�I�u�W�F�N�g�X�V����
		for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
			enemy->RockOnPerformance();
		}
		//�{���U�����ɃX���[�ɂ���X�V����
		DelayUpdates();
		BombPerformance();
		//�`���[�g���A���X�V����
		Tutorial();

		enemyParticle->Update();
		bombParticle->Update();
		gunParticle->Update();
		thrusterParticle->Update();

		player->Update(railCamera->GetIsEnd());
	}
	else {
		Pause();
	}

	light->Update();
	jsonLoader->Update();

	//�V�[���؂�ւ�����
	SceneChangeEffect::GetIns()->Update();
	SceneChange();
}

void RailScene::Draw() {
	//�w�i�F
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	bool isRoop = false;

	if (player->GetIsDamage()) {
		postEffectNo = PostEffect::DAMAGE;
	}
	else {
		postEffectNo = PostEffect::NORMAL;
		isRoop = true;
	}

	if (player->GetIsBomb()) {
		postEffectNo = PostEffect::SLOW;
		isRoop = false;
	}

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//�X�v���C�g�`�揈��(�w�i)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3D�I�u�W�F�N�g�`�揈��
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	jsonLoader->Draw();
	if (!isDead) {
		player->ObjectDraw();
	}
	for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
		enemy->Draw();
	}
	for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
		enemyBullet->Draw();
	}
	for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
		playerBullet->Draw();
	}
	for (std::unique_ptr<Bomb>& bomb : bombs) {
		bomb->Draw();
	}
	for (std::unique_ptr<BulletCase>& bulletCase : bulletCases) {
		bulletCase->Draw();
	}
	enemyParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	bombParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	gunParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	thrusterParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	scoreSprite->Draw();
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber[i]->Draw();
	}
	for (int32_t i = 0; i < 3; i++) {
		if (player->GetIsBomb()) {
			bombTimerNumber[i]->Draw();
		}
	}
	if (!isPause) {
		textWindow->Draw();
		faceWindow->Draw();
		switch (faceType) {
		case FaceGraphics::OPE_NORMALFACE:
			opeNormal[faceAnimeCount]->Draw();
			break;
		case FaceGraphics::OPE_SURPRISEFACE:
			opeSurprise[faceAnimeCount]->Draw();
			break;
		case FaceGraphics::OPE_SMILEFACE:
			opeSmile[faceAnimeCount]->Draw();
			break;
		}
	}
	how_to_up_->Draw();
	how_to_down_->Draw();
	how_to_left_->Draw();
	how_to_right_->Draw();
	if (enemies.size() > 0) {
		how_to_bomb_->Draw();
	}
	how_to_shot_->Draw();
	player->SpriteDraw();
	for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
		enemy->SpriteDraw();
	}
	for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
		particle2d->Draw();
	}
	if (isPause) {
		pause->Draw();
		titleBack->Draw();
		back->Draw();
		restart->Draw();
	}
	Reticle::GetIns()->Draw();
	SceneChangeEffect::GetIns()->Draw();
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->beginDrawWithDirect2D();
	if (!isPause) {
		TextMessageDraw();
	}
	DirectXSetting::GetIns()->endDrawWithDirect2D();

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo, isRoop);
	DirectXSetting::GetIns()->PostDraw();
}

void RailScene::Finalize() {
	player->Finalize();
	safe_delete(player);
	safe_delete(camera);
	safe_delete(railCamera);
	safe_delete(postEffect);
	safe_delete(pause);
	safe_delete(titleBack);
	safe_delete(back);
	safe_delete(restart);
	safe_delete(scoreSprite);
	safe_delete(light);
	safe_delete(bombParticle);
	safe_delete(gunParticle);
	safe_delete(thrusterParticle);
	safe_delete(enemyParticle);
	safe_delete(textDraw);
	safe_delete(textWindow);
	safe_delete(faceWindow);
	for (int32_t i = 0; i < 3; i++) {
		safe_delete(opeNormal[i]);
		safe_delete(opeSurprise[i]);
		safe_delete(opeSmile[i]);
		safe_delete(bombTimerNumber[i]);
	}
	for (int32_t i = 0; i < 6; i++) {
		safe_delete(scoreNumber[i]);
	}
	safe_delete(how_to_up_);
	safe_delete(how_to_down_);
	safe_delete(how_to_left_);
	safe_delete(how_to_right_);
	safe_delete(how_to_shot_);
	safe_delete(how_to_bomb_);
	jsonLoader->Finalize();
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

	if (isWait) {
		if (!isPause) {
			waitTimer--;
		}
		if (waitTimer <= 0) {
			isWait = false;
		}
		return;
	}

	while (getline(enemyData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//���p��؂�ŕ�������擾
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
			//�b�����Z�Ȃ̂�60�{����
			moveTime *= 60.0f;
		}
		if (word == "LifeTime") {
			line_stream >> lifeTime;
			lifeTime *= 60;
		}
		if (word == "ShotCoolTime") {
			line_stream >> shotIntervalTime;
			shotIntervalTime *= 60;
		}
		if (word == "Hp") {
			line_stream >> hp;
		}
		if (word == "Wait") {
			isWait = true;
			line_stream >> waitTimer;

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
				enemies.push_back(std::move(newEnemy));
			}
			if (type == "HOM") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<HomingEnemy>();
				newEnemy->Initialize("enemy1", pos, rot);
				newEnemy->SetRailScene(this);
				newEnemy->SetPlayer(player);
				newEnemy->SetLifeTime(lifeTime);
				newEnemy->SetHP(hp);
				newEnemy->SetShotIntervalTime(shotIntervalTime);
				if (isMovePoint) {
					movePoints.insert(movePoints.begin(), pos);
					newEnemy->SetMaxTime(moveTime);
					newEnemy->SetMovePoints(movePoints);
				}
				enemies.push_back(std::move(newEnemy));
			}

			isPos = false;
			isRot = false;
			isStyle = false;
			isMovePoint = false;
		}
	}
}

void RailScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
	enemyBullets.push_back(std::move(enemyBullet));
}

void RailScene::AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet) {
	playerBullets.push_back(std::move(playerBullet));
}

void RailScene::AddBulletCase(std::unique_ptr<BulletCase> bulletCase)
{
	bulletCases.push_back(std::move(bulletCase));
}

void RailScene::AddBomb(std::unique_ptr<Bomb> bomb) {
	bombs.push_back(std::move(bomb));
}

void RailScene::LoadRailPoint(const std::string& filename) {
	//�t�@�C���X�g���[��
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
		//���p��؂�ŕ�������擾
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
			points.push_back(startPos);
			points.push_back(startPos);
			cameraMoveTimes_.push_back(0);
			isStart = false;
		}
		else if (isEnd) {
			points.push_back(pos);
			points.push_back(pos);
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
			points.push_back(pos);
			points.push_back(startPos);
			points.push_back(startPos);
			isRoop = false;
			isCameraRoop = true;
		}
		else if (isTime) {
			splineTime *= 60;
			cameraMoveTimes_.push_back(splineTime);
			isTime = false;
		}
		else if (isPoint) {
			points.push_back(pos);
		}

		stringCount++;
	}

	movePoints.points_ = points;
	movePoints.cameraRot_ = cameraRots_;
	movePoints.moveTime_ = cameraMoveTimes_;

	assert(splineTime != 0);
	railCamera->Initialize(startPos, cameraRots_.front(), movePoints, isCameraRoop);

}

void RailScene::TextMessageUpdate()
{
	std::string line;
	std::string face;
	std::string messageData;
	std::wstring messageDataW;

	if (isMessageWait) {
		if (isTextDrawComplete) {
			waitMessageTimer--;
		}
		if (waitMessageTimer <= 0) {
			isMessageWait = false;
			textCount = 0;
			message.clear();
			drawMessage.clear();
		}
		return;
	}

	while (getline(textData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//���p��؂�ŕ�������擾
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "OPEN") {
			isTextWindowOpen = true;
		}
		if (word == "FACE") {
			line_stream >> face;
			if (face == "OPE_NORMAL") {
				faceType = FaceGraphics::OPE_NORMALFACE;
			}
			else if (face == "OPE_SURPRISE") {
				faceType = FaceGraphics::OPE_SURPRISEFACE;
			}
			else if (face == "OPE_SMILE") {
				faceType = FaceGraphics::OPE_SMILEFACE;
			}
		}
		if (word == "TEXT") {
			line_stream >> messageData;
			messageDataW = ExternalFileLoader::GetIns()->StringToWstring(messageData);
			message = messageDataW;
		}
		if (word == "SPEED") {
			line_stream >> textSpeed;
		}
		if (word == "WAIT") {
			isMessageWait = true;
			line_stream >> waitMessageTimer;
			break;
		}
		if (word == "CLOSE") {
			isTextWindowOpen = false;
		}
	}
}

void RailScene::TextMessageDraw()
{
	//�E�B���h�E�T�C�Y(�N���[�Y��)
	const float closeWindowSizeY = 0.0f;
	//�E�B���h�E�T�C�Y(�I�[�v����)
	const float openWindowSizeY = 160.0f;

	//���b�Z�[�W�E�B���h�E�J����
	//���b�Z�[�W�E�B���h�E������
	if (!isTextWindowOpen) {
		openWindowTimer = 0;
		closeWindowTimer++;
		if (closeWindowTimer >= closeWindowTime) {
			closeWindowTimer = closeWindowTime;
		}
		//�C�[�Y�C���A�E�g�Ń��b�Z�[�W�E�B���h�E�����
		textWindowSize.y = Easing::easeInOut((float)closeWindowTimer, (float)closeWindowTime, closeWindowSizeY, textWindowSize.y);
		faceWindowSize.y = Easing::easeInOut((float)closeWindowTimer, (float)closeWindowTime, closeWindowSizeY, faceWindowSize.y);
		faceGraphicSize.y = Easing::easeInOut((float)closeWindowTimer, (float)closeWindowTime, closeWindowSizeY, faceGraphicSize.y);
	}
	//���b�Z�[�W�E�B���h�E�J������
	else if (isTextWindowOpen) {
		closeWindowTimer = 0;
		openWindowTimer++;
		if (openWindowTimer >= openWindowTime) {
			openWindowTimer = openWindowTime;
		}
		//�C�[�Y�C���A�E�g�Ń��b�Z�[�W�E�B���h�E���J��
		textWindowSize.y = Easing::easeInOut((float)openWindowTimer, (float)openWindowTime, openWindowSizeY, textWindowSize.y);
		faceWindowSize.y = Easing::easeInOut((float)openWindowTimer, (float)openWindowTime, openWindowSizeY, faceWindowSize.y);
		faceGraphicSize.y = Easing::easeInOut((float)openWindowTimer, (float)openWindowTime, openWindowSizeY, faceGraphicSize.y);
	}

	//���b�Z�[�W�E�B���h�E�T�C�Y��ύX
	textWindow->SetSize(textWindowSize);
	faceWindow->SetSize(faceWindowSize);
	for (int32_t i = 0; i < 3; i++) {
		opeNormal[i]->SetSize(faceGraphicSize);
		opeSurprise[i]->SetSize(faceGraphicSize);
		opeSmile[i]->SetSize(faceGraphicSize);
	}

	//��O���t�B�b�N�A�j���[�V�������ԉ��Z
	faceAnimeTimer++;
	if (faceAnimeTimer >= faceAnimeTime) {
		faceAnimeTimer = 0;
		faceAnimeCount++;
		if (faceAnimeCount >= 3) {
			faceAnimeCount = 0;
		}
	}
	//�ǂݍ��񂾃e�L�X�g�`�悪�������Ă�����
	if (isTextDrawComplete) {
		faceAnimeCount = 0;
		faceAnimeTimer = 0;
	}
	//�e�L�X�g�X�s�[�h��0�ȉ��ɂȂ�Ȃ��悤�ɂ���
	if (textSpeed <= 0) {
		textSpeed = 1;
	}
	//�e�L�X�g�`��͈�
	D2D1_RECT_F textDrawPos = {
		200, 560, 950, 700
	};
	D2D1_RECT_F bombMessageDrawPos = {
		400, 0, 900, 300
	};
	//�e�L�X�g��1�������w�莞�Ԃ��Ƃɒǉ�����
	textAddTimer++;
	isTextDrawComplete = false;
	if (textAddTimer >= textSpeed) {
		textAddTimer = 0;
		if (textCount < message.size()) {
			if (message.substr(textCount, 1) != L"/") {
				drawMessage += message.substr(textCount, 1);
			}
			else {
				drawMessage += L"\n";
			}
			textCount++;
		}
		//�ǂݍ��񂾃e�L�X�g�`�悪����������
		if (textCount >= message.size()) {
			isTextDrawComplete = true;
		}
	}
	//���ݒǉ�����Ă��镶����S�ĕ`�悷��
	textDraw->Draw("meiryo", "white", drawMessage, textDrawPos);
	if (player->GetIsBomb()) {
		textDraw->Draw("meiryo", "orange", L"���ԓ��ɂł��邾�������̓G��\n���b�N�I�����Ă��������B\n���N���b�N�Ŕ��ˉ\", bombMessageDrawPos);
	}
}

bool RailScene::IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos) {
	const float aimPosCorrection = 20.0f;
	return (enemyPos.x >= aimPos.x - aimPosCorrection && enemyPos.x <= aimPos.x + aimPosCorrection && enemyPos.y >= aimPos.y - aimPosCorrection && enemyPos.y <= aimPos.y + aimPosCorrection);
}

void RailScene::DelayUpdates()
{
	//�X���[���o�p�^�C�}�[
	float delayTime = 0.0f;
	if (player->GetIsBomb()) {
		delayTime = 3.0f;
	}
	delayTimer++;

	//�X���[���o
	if (delayTimer >= delayTime) {
		//�G�o������
		EnemyDataUpdate();
		//�e�L�X�g�X�V����
		TextMessageUpdate();

		//�v���C���[�������Ă���ꍇ�ɍX�V
		if (player->GetHPCount() > 0) {
			if (!railCamera->GetIsEnd()) {
				railCamera->Update();
			}
			for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
				enemy->Update();
				EnemyReactions(enemy.get());
			}
			for (std::unique_ptr<Bomb>& bomb : bombs) {
				bomb->Update();
			}
		}

		for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
			enemyBullet->Update();
		}
		for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
			playerBullet->Update();
		}
		for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
			particle2d->Update();
		}
		for (std::unique_ptr<BulletCase>& bulletCase : bulletCases) {
			bulletCase->Update();
		}

		delayTimer = 0;
	}


}

void RailScene::ClearPaformance()
{
	//���[���J�������ŏI�n�_�ɓ��B�����Ƃ�
	if (railCamera->GetIsEnd()) {
		clearTimer--;
	}
	//�N���A���o��V�[����؂�ւ���
	if (clearTimer <= 0) {
		isClear = true;
		SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
	}
}

void RailScene::CollisionCheck()
{
	for (const std::unique_ptr<BaseEnemy>& enemy : enemies) {
		for (const std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
			if (Collision::GetIns()->OBJSphereCollision(playerBullet->GetBulletObj(), enemy->GetEnemyObj(), 1.0f, 5.0f)) {
				score += 100;
				enemy->OnCollision();
				playerBullet->OnCollision();
			}
		}
	}

	for (const std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
		if (Collision::GetIns()->OBJSphereCollision(enemyBullet->GetEnemyBulletObj(), player->GetPlayerObject(), 1.0f, 2.0f)) {
			if (!player->GetIsDamage() && player->GetHPCount() > noneHP) {
				player->OnCollision();
			}
			enemyBullet->OnCollision();
			railCamera->SetIsDamage();
		}
	}

	for (const std::unique_ptr<BaseEnemy>& enemy : enemies) {
		for (const std::unique_ptr<Bomb>& bomb : bombs) {
			if (Collision::GetIns()->OBJSphereCollision(enemy->GetEnemyObj(), bomb->GetBullet(), 5.0f, 1.0f)) {
				score += 100;
				enemy->BombHitCollision();
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

					bombParticle->Add(30, pos, vel, acc, 8.0f, 0.0f, { 0.6f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
				}
				bomb->OnCollision();

			}
		}
	}
}

void RailScene::EnemyReactions(BaseEnemy* enemy)
{
	const int32_t randMax = 4;

	//�G���W
	Vector3 enemyPos;
	enemyPos = enemy->GetEnemyObj()->GetMatWorld().r[3];

	//�G��HP��0�Ȃ�p�[�e�B�N���𔭐�������
	if (enemy->GetHP() <= 0) {
		enemyParticle->Add(30, enemyPos, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.02f, 0.0f }, 5.0f, 0.0f);
	}

	//���b�N�I������
	XMVECTOR enemy3dPos = { enemy->GetEnemyObj()->GetMatWorld().r[3] }; //���[���h���W
	XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //�r���[�v���W�F�N�V�����r���[�|�[�g�s��
	enemy3dPos = XMVector3TransformCoord(enemy3dPos, matViewProjectionViewport); //�X�N���[�����W

	DirectX::XMFLOAT2 enemy2dPos = { enemy3dPos.m128_f32[0], enemy3dPos.m128_f32[1] };

	if (IsTargetCheck(enemy2dPos, Reticle::GetIns()->GetPos())) {
		Reticle::GetIns()->SetIsSelectReticle(true);
		if (player->GetIsBomb()) {
			enemy->SetTarget(true);
		}
	}

	//�G�����S������G�t�F�N�g�𔭐�������
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
			enemyParticle->Add(20,
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
	//�ŏI�I�ȑ傫��
	const float endScale = 0.0f;
	//�f�t�H���g�����x
	const Vector3 defaultAcc = { 0.0f, 0.0f, 0.0f };

	//�v���C���[��HP��1�ȏ�Ȃ�G�t�F�N�g�𔭐�������
	if (player->GetHPCount() > noneHP) {
		//�������
		const int32_t randMax = 5;
		//�p�[�e�B�N����������
		int32_t particleLife = 3;
		//�����A���t�@�l
		Vector3 initAlpha = { 0.0f, 0.0f, 0.6f };
		//�ŏI�I�ȃA���t�@�l
		Vector3 endAlpha = { 1.0f, 1.0f, 1.0f };

		//�v���C���[�̃��[���h�s�񂩂�p�[�e�B�N���̐����ʒu�����߂�
		XMVECTOR playerPos = { 0.0f, 1.2f, -1.0f };
		playerPos = XMVector3TransformCoord(playerPos, player->GetPlayerObject()->GetMatWorld());
		Vector3 thrusterPos = playerPos;

		for (int32_t i = 0; i < 10; i++) {
			float thrusterPower = (float)(rand() % randMax);
			thrusterPower *= -0.1f;
			float startScale = (float)(rand() % (randMax - 2));
			XMVECTOR playerBack = { 0.0f, 0.0f, thrusterPower };
			playerBack = XMVector3TransformNormal(playerBack, player->GetPlayerObject()->GetMatWorld());
			Vector3 thrusterDir = playerBack;
			thrusterParticle->Add(
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

	//�v���C���[��HP��0�Ȃ�G�t�F�N�g�𔭐�������
	if (player->GetHPCount() <= noneHP && !isPlayerDead) {
		XMVECTOR playerPos = { player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z };
		XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
		playerPos = XMVector3TransformCoord(playerPos, matVPV);

		XMFLOAT2 player2dPos = { playerPos.m128_f32[0] - 150, playerPos.m128_f32[1] - 140 };
		std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
		new2DParticle->Initialize(player2dPos, { 200, 200 }, 80, ImageManager::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
		particles2d.push_back(std::move(new2DParticle));
		isPlayerDead = true;
		SoundManager::GetIns()->StopBGM(SoundManager::STAGE1_RAIL);
	}

	//�}�Y���t���b�V���𔭐�������
	if (player->GetIsShot()) {
		Vector3 gunPos = player->GetGunObject()->GetMatWorld().r[3];
		gunParticle->Add(2, gunPos,
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			5.0f, 0.0f,
			{ 0.5f, 0.0f, 0.0f },
			{ 0.5f, 0.3f, 0.0f }
		);
	}

	for (std::unique_ptr<Bomb>& bomb : bombs) {
		//�{���̋O�ՂɃp�[�e�B�N���𔭐�������
		Vector3 bombPos = bomb->GetBullet()->GetMatWorld().r[3];
		bombParticle->Add(20, bombPos,
			{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
			3.0f, 0.0f, { 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f }, 1.0f, 0.0f);
	}
}

void RailScene::Pause()
{
	SoundManager::GetIns()->StopBGM(SoundManager::STAGE1_RAIL);
	XMFLOAT2 mousePos = { (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y };
	//�{�^���I�𒆃A���t�@�l
	const float selectAlpha = 0.5f;
	//�{�^���ʏ펞�A���t�@�l
	const float normalAlpha = 1.0f;
	//�I�𒆃{�^���T�C�Y
	XMFLOAT2 selectSize;
	//�^�C�g���o�b�N�{�^����I��
	if (IsMouseHitSprite(mousePos, titleBack->GetPosition(), titleBackSize.x, titleBackSize.y)) {
		selectSize = { titleBackSize.x * 0.9f, titleBackSize.y * 0.9f };
		titleBack->SetSize(selectSize);
		titleBack->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isTitleBack = true;
			SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
		}
	}
	else {
		titleBack->SetSize(titleBackSize);
		titleBack->SetAlpha(normalAlpha);
	}
	//�|�[�Y�����{�^����I��
	if (IsMouseHitSprite(mousePos, back->GetPosition(), backSize.x, backSize.y)) {
		selectSize = { backSize.x * 0.9f, backSize.y * 0.9f };
		back->SetSize(selectSize);
		back->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isPause = !isPause;
		}
	}
	else {
		back->SetSize(backSize);
		back->SetAlpha(normalAlpha);
	}
	//���X�^�[�g�{�^����I��
	if (IsMouseHitSprite(mousePos, restart->GetPosition(), restartSize.x, restartSize.y)) {
		selectSize = { restartSize.x * 0.9f, restartSize.y * 0.9f };
		restart->SetSize(selectSize);
		restart->SetAlpha(selectAlpha);
		if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
			isRestart = true;
			SceneChangeEffect::GetIns()->SetIsSceneChangeStart(true);
		}
	}
	else {
		restart->SetSize(restartSize);
		restart->SetAlpha(normalAlpha);
	}
}

void RailScene::Tutorial()
{
	//�萔
	const float iconSlidePos = 100.0f;

	if (enemies.size() > 0) {
		isMoveUp_ = true;
		isMoveDown_ = true;
		isMoveLeft_ = true;
		isMoveRight_ = true;
		isShot_ = true;
	}

	//�v���C���[�L�����̉�ʏ�̈ʒu�����߂�
	XMVECTOR playerPos = { player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[0], player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[1], player->GetPlayerObject()->GetMatWorld().r[3].m128_f32[2] };
	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	playerPos = XMVector3TransformCoord(playerPos, matVPV);
	XMFLOAT2 player2dPos = { playerPos.m128_f32[0], playerPos.m128_f32[1] };

	//�`���[�g���A���A�C�R���̍��W�����߂�
	how_to_up_->SetPosition({ player2dPos.x, player2dPos.y - iconSlidePos });
	how_to_down_->SetPosition({ player2dPos.x, player2dPos.y + iconSlidePos });
	how_to_left_->SetPosition({ player2dPos.x - iconSlidePos, player2dPos.y });
	how_to_right_->SetPosition({ player2dPos.x + iconSlidePos, player2dPos.y });
	how_to_shot_->SetPosition({ Reticle::GetIns()->GetPos().x, Reticle::GetIns()->GetPos().y - iconSlidePos });
	how_to_bomb_->SetPosition({ Reticle::GetIns()->GetPos().x, Reticle::GetIns()->GetPos().y - iconSlidePos });

	//�`���[�g�������������瓧���ɂ���
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
	if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		isShot_ = true;
	}
	if (MouseInput::GetIns()->TriggerClick(MouseInput::RIGHT_CLICK)) {
		isBomb_ = true;
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
	if (isBomb_ && how_to_bomb_alpha_ > 0) {
		how_to_bomb_alpha_ -= 0.1f;
		how_to_bomb_->SetAlpha(how_to_bomb_alpha_);
	}
}

void RailScene::BombPerformance()
{
	for (int32_t i = 0; i < 3; i++) {
		bombTimerNumber[i]->SetTextureRect({ (float)JudgeDigitNumber((player->GetBombTimer() * 100 / 60), i), 0.0f}, {64.0f, 64.0f});
		bombTimerNumber[i]->SetPosition({ Reticle::GetIns()->GetPos().x - (30.0f * i) + 30.0f, Reticle::GetIns()->GetPos().y - 100.0f});
	}
}

void RailScene::SceneChange()
{
	//�V�[���؂�ւ�
	if (SceneChangeEffect::GetIns()->GetIsSceneChange()) {
		//���S�t���O�������Ă���ꍇ
		if (isDead && !isClear) {
			SceneManager::AddScore(score);
			SceneManager::SceneChange(SceneManager::GameOver);
		}
		//�N���A�t���O�������Ă���ꍇ
		else if (isClear && !isDead) {
			SceneManager::AddScore(score);
			//�X�e�[�W�ԍ��ɂ��h��
			if (SceneManager::GetStageNo() == 1) {
				SceneManager::SceneChange(SceneManager::Stage1_Boss);
			}
			else if (SceneManager::GetStageNo() == 2) {
				SceneManager::SceneChange(SceneManager::Stage2_Boss);
			}
			SoundManager::GetIns()->StopBGM(SoundManager::STAGE1_RAIL);
		}
		//�^�C�g���o�b�N�{�^���������ꂽ�ꍇ
		else if (isTitleBack) {
			SceneManager::SceneChange(SceneManager::Title);
		}
		//���X�^�[�g�{�^���������ꂽ�ꍇ
		else if (isRestart) {
			//�X�e�[�W�ԍ��ɂ��h��
			if (SceneManager::GetStageNo() == 1) {
				SceneManager::SceneChange(SceneManager::Stage1_Rail);
			}
			else if (SceneManager::GetStageNo() == 2) {
				SceneManager::SceneChange(SceneManager::Stage2_Rail);
			}
		}
	}

	if (KeyInput::GetIns()->TriggerKey(DIK_N)) {
		SceneManager::AddScore(score);
		SceneManager::SceneChange(SceneManager::Stage1_Boss);
	}
}
