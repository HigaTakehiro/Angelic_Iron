#include "ResultScene.h"

void ResultScene::Initialize()
{
	cameraPos = { -50, 0, 100 };
	cameraTargetPos = { 0, 0, 0 };

	camera = new Camera;
	camera->SetEye(cameraPos);
	camera->SetTarget(cameraTargetPos);

	score = Sprite::Create(ImageManager::ImageName::score, { 300, 100 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i] = Sprite::Create(ImageManager::scoreNumbers, { 450 - ((float)i * 60), 250 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
		scoreNumbers[i]->SetTextureRect({ nine, 0 }, { 64, 64 });
		scoreNumbers[i]->SetSize({ 64, 64 });
	}

	scoreRollTimer = 0;
	for (int i = 0; i < 6; i++) {
		scoreRollPos[i] = { -640, 0 };
	}

	resultPlayer = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player_Normal));
	playerScale = { 20, 20, 20 };
	playerPos = { -30, 0, -500 };
	playerRot = { 0, 0, 0 };
	resultPlayer->SetScale(playerScale);
	resultPlayer->SetPosition(playerPos);
	resultPlayer->SetRotation(playerRot);

	gun = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Gun));
	gun->SetPosition(Vector3(0.9, 0.6, 1.2));
	gun->SetParent(resultPlayer);

	ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetScale({ 15, 15, 15 });

	//PostEffect�̏�����
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffectNo = PostEffect::NORMAL;
}

void ResultScene::Update()
{
	const float scoreRollTime = 240.0f;
	const float fallTime = 120.0f;
	const XMFLOAT2 scoreSize = { 64, 64 };
	const float endPoint = 0;

	scoreRollTimer++;
	if (scoreRollTimer >= scoreRollTime) {
		scoreRollTimer = scoreRollTime;
	}

	//cameraTargetPos.y = Easing::GetIns()->easeOut(scoreRollTimer, fallTime, lastY, cameraTargetPos.y);
	playerPos.z = Easing::GetIns()->easeOut(scoreRollTimer, fallTime, endPoint, playerPos.z);

	camera->SetTarget(cameraTargetPos);
	resultPlayer->SetPosition(playerPos);

	for (int i = 0; i < 6; i++) {
		scoreRollPos[i].x = Easing::GetIns()->easeOut(scoreRollTimer, scoreRollTime, (float)JudgeDigitNumber(SceneManager::GetScore(), i), scoreRollPos[i].x);
	}
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i]->SetTextureRect(scoreRollPos[i], scoreSize);
	}

	resultPlayer->Update();
	celetialSphere->Update();
	ground->Update();
	gun->Update();

	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::Title);
	}
}

void ResultScene::Draw()
{
	//�w�i�F
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//�X�v���C�g�`�揈��(�w�i)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3D�I�u�W�F�N�g�`�揈��
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	resultPlayer->Draw();
	celetialSphere->Draw();
	ground->Draw();
	gun->Draw();
	Object3d::PostDraw();

	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	score->Draw();
	for (int i = 0; i < 6; i++) {
		scoreNumbers[i]->Draw();
	}
	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 60, postEffectNo, true);
	DirectXSetting::GetIns()->PostDraw();
}

void ResultScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(score);
	safe_delete(resultPlayer);
	safe_delete(celetialSphere);
	safe_delete(ground);
	safe_delete(gun);
	for (int i = 0; i < 6; i++) {
		safe_delete(scoreNumbers[i]);
	}
}

ResultScene::ScoreNumber ResultScene::JudgeDigitNumber(int score, int digit)
{
	if (score >= 1000000) {
		return nine;
	}

	int num = (score / (int)pow(10, digit)) % 10;

	return (ScoreNumber)(64 * num);
}