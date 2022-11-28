#include "TitleScene.h"

void TitleScene::Initialize()
{
	title = Sprite::Create(ImageManager::ImageName::title, { 0, 0 });

	postEffect = new PostEffect();
	postEffect->Initialize();
}

void TitleScene::Update()
{
	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) || MouseInput::GetIns()->TriggerClick(MouseInput::LEFT_CLICK)) {
		SceneManager::SceneChange(SceneManager::Stage1_Rail);
	}
}

void TitleScene::Draw()
{
	//�w�i�F
	const XMFLOAT4 backColor = { 0.1f,0.25f, 0.5f, 0.0f };
	static int postEffectNo = 0;

	postEffect->PreDrawScene(DirectXSetting::GetIns()->GetCmdList());

	//�X�v���C�g�`�揈��(�w�i)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3D�I�u�W�F�N�g�`�揈��
	Object3d::PreDraw(DirectXSetting::GetIns()->GetCmdList());

	Object3d::PostDraw();

	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(DirectXSetting::GetIns()->GetCmdList());
	title->Draw();

	Sprite::PostDraw();

	postEffect->PostDrawScene(DirectXSetting::GetIns()->GetCmdList());

	DirectXSetting::GetIns()->PreDraw(backColor);
	postEffect->Draw(DirectXSetting::GetIns()->GetCmdList(), postEffectNo);
	DirectXSetting::GetIns()->PostDraw();

}

void TitleScene::Finalize()
{
	safe_delete(postEffect);
	safe_delete(title);
}
