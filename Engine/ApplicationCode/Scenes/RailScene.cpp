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
	isSceneChangeComplete = true;
	SceneChangeInitialize();

	//�J����������
	camera = new Camera;
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));
	railCamera = new RailCamera;

	//�f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextNumber);

	//�X�v���C�g�摜������
	background = Sprite::Create(ImageManager::ImageName::background, { 0, 0 });
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
	for (int i = 0; i < 3; i++) {
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
	}
	for (int i = 0; i < 6; i++) {
		scoreNumber[i] = Sprite::Create(ImageManager::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber[i]->SetTextureRect({ nine, 0.0f }, { 64, 64 });
		scoreNumber[i]->SetSize({ 32, 32 });
	}

	//���C�g������
	light = LightGroup::Create();
	for (int i = 0; i < 3; i++) {
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
	if (SceneManager::GetStageNo() == 1) {
		ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	}
	else if (SceneManager::GetStageNo() == 2) {
		ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Wave));
	}
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);
	ground->SetAmbient({ 1, 1, 1 });

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	int stageNo;
	stageNo = SceneManager::GetStageNo();

	//�X�e�[�W�w�i�I�u�W�F�N�g������
	if (stageNo == 1) {
		for (int i = 0; i < 90; i++) {
			Vector3 pos = { 0, 20, 0 };
			Vector3 rot = { 0, 270, 0 };
			Vector3 scale = { 5, 5, 5 };
			float angle = 20;
			float length = 100;
			if (i > 17) {
				angle = 25;
				length = 200;
			}
			if (i > 35) {
				angle = 20;
				length = 300;
			}
			if (i > 53) {
				angle = 22;
				length = 400;
			}
			if (i > 71) {
				angle = 20;
				length = 500;
			}
			pos = MotionMath::CircularMotion({ 0, 0, 0 }, pos, angle * i, length, MotionMath::Y);
			pos.y = (float)(rand() % 20 - 40);
			rot.y -= angle * i;
			std::unique_ptr<Object3d> newBuilding;
			newBuilding = (std::unique_ptr<Object3d>)Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Building));
			newBuilding->SetPosition(pos);
			newBuilding->SetRotation(rot);
			newBuilding->SetScale(scale);
			buildings.push_back(std::move(newBuilding));
		}
	}

	//�v���C���[������
	player = new Player;
	player->Initialize(camera, clearTime);
	player->SetRailScene(this);

	//�p�[�e�B�N��������
	bombParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	enemyParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);
	gunParticle = ParticleManager::Create(DirectXSetting::GetIns()->GetDev(), camera);

	//�X�e�[�W�f�[�^�ǂݍ���
	if (stageNo == 1) {
		LoadRailPoint("Stage1RailPoints.aid");
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
	if (KeyInput::GetIns()->TriggerKey(DIK_ESCAPE) && player->GetHPCount() != noneHP) {
		isPause = !isPause;
	}
	//�v���C���[�����S���Ă��邩
	if (player->GetIsDead()) {
		isDead = true;
		isSceneChangeStart = true;
	}

	//�X���[���o�p�^�C�}�[
	float delayCount = 0.0f;
	if (player->GetIsBomb()) {
		delayCount = 3.0f;
	}

	//�X�R�A�\��
	for (int i = 0; i < 6; i++) {
		scoreNumber[i]->SetTextureRect({ (float)JudgeDigitNumber(score, i), 0 }, { 64, 64 });
	}

	//�G�t�F�N�g��������
	AddEffect();

	if (!isPause) {
		//�G�o������
		EnemyDataUpdate();
		//�e�L�X�g�X�V����
		TextMessageUpdate();
		//�����蔻��`�F�b�N
		CollisionCheck();

		//�I�u�W�F�N�g�X�V����
		celetialSphere->Update();
		ground->Update();
		for (std::unique_ptr<Object3d>& building : buildings) {
			building->Update();
		}
		//�v���C���[�������Ă���ꍇ�ɍX�V
		if (player->GetHPCount() > 0) {
			if (!railCamera->GetIsEnd()) {
				railCamera->Update(delayCount);
			}
			for (std::unique_ptr<BaseEnemy>& enemy : enemies) {
				enemy->Update((int)delayCount);
				EnemyReactions(enemy.get());
			}
			for (std::unique_ptr<Bomb>& bomb : bombs) {
				bomb->Update();
				//�{���̋O�ՂɃp�[�e�B�N���𔭐�������
				Vector3 bombPos = bomb->GetBullet()->GetMatWorld().r[3];
				bombParticle->Add(20, bombPos,
					{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
					3.0f, 0.0f, { 1.0f, 1.0f, 1.0f },
					{ 1.0f, 1.0f, 1.0f }, 1.0f, 0.0f);
			}

			if (player->GetIsShot()) {
				Vector3 gunPos = player->GetGunObject()->GetMatWorld().r[3];
				//�}�Y���t���b�V���𔭐�������
				gunParticle->Add(2, gunPos,
					{ 0.0f, 0.0f, 0.0f },
					{ 0.0f, 0.0f, 0.0f },
					5.0f, 0.0f,
					{ 0.5f, 0.0f, 0.0f },
					{ 0.5f, 0.3f, 0.0f }
				);
			}
		}

		enemyParticle->Update();
		bombParticle->Update();
		gunParticle->Update();

		for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets) {
			enemyBullet->Update(delayCount);
		}
		for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets) {
			playerBullet->Update(delayCount);
		}
		for (std::unique_ptr<Particle2d>& particle2d : particles2d) {
			particle2d->Update();
		}
		for (std::unique_ptr<BulletCase>& bulletCase : bulletCases) {
			bulletCase->Update(delayCount);
		}

		player->Update(railCamera->GetIsEnd());
	}
	else {
		Pause();
	}

	light->Update();

	//�V�[���؂�ւ�����
	if (isSceneChangeComplete) {
		SceneChangeCompleteEffect();
	}
	if (isSceneChangeStart) {
		SceneChangeEffect();
	}

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
	ground->Draw();
	celetialSphere->Draw();

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
	for (std::unique_ptr<Object3d>& building : buildings) {
		building->Draw();
	}
	for (std::unique_ptr<BulletCase>& bulletCase : bulletCases) {
		bulletCase->Draw();
	}
	enemyParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	bombParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	gunParticle->Draw(DirectXSetting::GetIns()->GetCmdList());
	Object3d::PostDraw();

	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	scoreSprite->Draw();
	for (int i = 0; i < 6; i++) {
		scoreNumber[i]->Draw();
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
	SceneChangeEffectDraw();
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
	safe_delete(ground);
	safe_delete(background);
	safe_delete(celetialSphere);
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
	safe_delete(enemyParticle);
	safe_delete(textDraw);
	safe_delete(textWindow);
	safe_delete(faceWindow);
	for (int i = 0; i < 3; i++) {
		safe_delete(opeNormal[i]);
		safe_delete(opeSurprise[i]);
		safe_delete(opeSmile[i]);
	}
	for (int i = 0; i < 6; i++) {
		safe_delete(scoreNumber[i]);
	}
}

void RailScene::EnemyDataUpdate() {
	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	Vector3 scale{};
	std::string type;
	bool isPos = false;
	bool isRot = false;
	bool isStyle = false;

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
		if (word == "Wait") {
			isWait = true;
			line_stream >> waitTimer;

			break;
		}

		if (isPos && isRot && isStyle) {

			if (type == "STR") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<StraightEnemy>();
				newEnemy->Initialize(ModelManager::Enemy, pos, rot);
				newEnemy->SetRailScene(this);
				enemies.push_back(std::move(newEnemy));
			}
			if (type == "HOM") {
				std::unique_ptr<BaseEnemy> newEnemy = std::make_unique<HomingEnemy>();
				newEnemy->Initialize(ModelManager::Enemy, pos, rot);
				newEnemy->SetRailScene(this);
				newEnemy->SetPlayer(player);
				enemies.push_back(std::move(newEnemy));
			}

			isPos = false;
			isRot = false;
			isStyle = false;
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
	int stringCount = 0;

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
			isStart = false;
		}
		else if (isEnd) {
			points.push_back(pos);
			points.push_back(pos);
			isEnd = false;
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
			isTime = false;
		}
		else if (isPoint) {
			points.push_back(pos);
		}

		stringCount++;
	}

	assert(splineTime != 0);
	railCamera->Initialize(startPos, rot, points, splineTime, isCameraRoop);

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
	for (int i = 0; i < 3; i++) {
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
}

bool RailScene::IsTargetCheck(XMFLOAT2 enemyPos, XMFLOAT2 aimPos) {
	const float aimPosCorrection = 20.0f;
	return (enemyPos.x >= aimPos.x - aimPosCorrection && enemyPos.x <= aimPos.x + aimPosCorrection && enemyPos.y >= aimPos.y - aimPosCorrection && enemyPos.y <= aimPos.y + aimPosCorrection);
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
		isSceneChangeStart = true;
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
				enemy->OnCollision();
				for (int i = 0; i < 10; i++) {
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
	//�G��HP��0�Ȃ�p�[�e�B�N���𔭐�������
	if (enemy->GetHP() <= 0) {
		Vector3 enemyPos;
		enemyPos = enemy->GetEnemyObj()->GetMatWorld().r[3];
		enemyParticle->Add(30, enemyPos, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.02f, 0.0f }, 5.0f, 0.0f);
	}

	//���b�N�I������
	XMVECTOR raticle2D = { enemy->GetEnemyObj()->GetMatWorld().r[3] }; //���[���h���W
	XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort(); //�r���[�v���W�F�N�V�����r���[�|�[�g�s��
	raticle2D = XMVector3TransformCoord(raticle2D, matViewProjectionViewport); //�X�N���[�����W

	DirectX::XMFLOAT2 spritePos = { raticle2D.m128_f32[0], raticle2D.m128_f32[1] };

	XMFLOAT2 targetCheckHitPos = { spritePos.x - player->GetAimPos().x, spritePos.y - player->GetAimPos().y };

	if (IsTargetCheck(spritePos, player->GetAimPos()) && player->GetIsBomb()) {
		enemy->SetTarget(true);
	}

	//�G�����S������G�t�F�N�g�𔭐�������
	if (enemy->GetIsDead() && enemy->GetHP() <= 0) {
		std::unique_ptr<Particle2d> new2DParticle = std::make_unique<Particle2d>();
		new2DParticle->Initialize(spritePos, { 50, 50 }, 24, ImageManager::enemyDead, { 0.5f, 0.5f }, 8, { 0, 0 }, { 32, 32 });
		particles2d.push_back(std::move(new2DParticle));
	}
}

void RailScene::AddEffect()
{
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
			isSceneChangeStart = true;
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
			isSceneChangeStart = true;
		}
	}
	else {
		restart->SetSize(restartSize);
		restart->SetAlpha(normalAlpha);
	}
}

void RailScene::SceneChange()
{
	//�V�[���؂�ւ�
	if (isSceneChange) {
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
