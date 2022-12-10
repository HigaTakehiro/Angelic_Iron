#include "BossScene.h"

void BossScene::Initialize()
{
	camera = new Camera;
	camera->SetEye(XMFLOAT3(0, 100, 0));
	camera->SetTarget(XMFLOAT3(0, 10, 0));

	for (int i = 0; i < 36; i++) {
		Vector3 pos = { 0, 0, 0 };
		Vector3 rot = { 0, 270, 0 };
		Vector3 scale = { 20, 20, 20 };
		float angle = 20;
		float length = 300;
		if (i > 17) {
			angle = 25;
			length = 500;
		}
		pos = MotionMath::GetIns()->CircularMotion({ 0, 0, 0 }, pos, angle * i, length, MotionMath::Y);
		rot.y -= angle * i;
		std::unique_ptr<Object3d> newBuilding;
		newBuilding = (std::unique_ptr<Object3d>)Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Building));
		newBuilding->SetPosition(pos);
		newBuilding->SetRotation(rot);
		newBuilding->SetScale(scale);
		buildings.push_back(std::move(newBuilding));
	}

	ground = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Ground));
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celetialSphere = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::CelestialSphere));
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	postEffect = new PostEffect();
	postEffect->Initialize();

	postEffectNo = PostEffect::NORMAL;

	cameraAngle = 0.0f;
	//cameraPos = MotionMath::GetIns()->CircularMotion({10, 0, 0}, cameraPos, cameracameraAngle, 30, MotionMath::Y);

	test = Object3d::Create(ModelManager::GetIns()->GetModel(ModelManager::Player_Normal));
}

void BossScene::Update()
{
	ground->Update();
	celetialSphere->Update();
	camera->SetTarget({ 0.0f, 0.0f, 0.0f });
	camera->SetEye(cameraPos);
	//test->Update();
	//Vector3 testPos;
	//testPos
	//test->SetPosition();

	for (std::unique_ptr<Object3d>& building : buildings) {
		building->Update();
	}
	if (KeyInput::GetIns()->PushKey(DIK_A)) {
		cameraAngle -= 1.0f;
		if (cameraAngle <= 0.0f) {
			cameraAngle = 360.0f;
		}
		cameraPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);

	}
	if (KeyInput::GetIns()->PushKey(DIK_D)) {
		cameraAngle += 1.0f;
		if (cameraAngle >= 360.0f) {
			cameraAngle = 0.0f;
		}
		cameraPos = MotionMath::GetIns()->CircularMotion({ 0.0f, 0.0f, 0.0f }, cameraPos, cameraAngle, 250.0f, MotionMath::Y);
	}

	if (KeyInput::GetIns()->PushKey(DIK_W)) {
		cameraPos.y += 1.0f;
	}
	if (KeyInput::GetIns()->PushKey(DIK_S)) {
		cameraPos.y -= 1.0f;
	}

	if (MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::Result);
	}
}

void BossScene::Draw()
{
	//”wŒiF
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	bool isRoop = false;

	//if (player->GetIsDamage()) {
	//	postEffectNo = PostEffect::DAMAGE;
	//}
	//else {
	postEffectNo = PostEffect::NORMAL;
	isRoop = true;
	//}

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//ƒXƒvƒ‰ƒCƒg•`‰æˆ—(”wŒi)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3DƒIƒuƒWƒFƒNƒg•`‰æˆ—
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	ground->Draw();
	celetialSphere->Draw();
	test->Draw();
	for (std::unique_ptr<Object3d>& building : buildings) {
		building->Draw();
	}
	Object3d::PostDraw();

	//ƒXƒvƒ‰ƒCƒg•`‰æˆ—(UI“™)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());

	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), 60.0f, postEffectNo, isRoop);
	DirectXSetting::GetIns()->PostDraw();
}

void BossScene::Finalize()
{
	safe_delete(ground);
	safe_delete(celetialSphere);
	safe_delete(camera);
	safe_delete(postEffect);
	safe_delete(test);
}
