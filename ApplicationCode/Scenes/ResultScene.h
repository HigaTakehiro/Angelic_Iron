#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "KeyInput.h"
#include "MouseInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "Easing.h"
#include "LightGroup.h"

class ResultScene : public BaseScene
{
public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon"></param>
	void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�֐�
	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange();

private: //�����o�ϐ�

	PostEffect* postEffect_ = nullptr; //�|�X�g�G�t�F�N�g�N���X
	Sprite* score_ = nullptr; //�X�R�A�摜
	Sprite* scoreNumbers_[6] = {}; ///�X�R�A�p�A�Ԑ����摜
	Sprite* titleBack_ = nullptr;

	LightGroup* light_ = nullptr;

	DirectX::XMFLOAT2 mousePos_;
	DirectX::XMFLOAT2 titleBackSize_;
	float titleBackAlpha_;

	PostEffect::PostEffectNo postEffectNo_; //�|�X�g�G�t�F�N�g�ԍ�

	float scoreRollTimer_;
	DirectX::XMFLOAT2 scoreRollPos_[6] = {};

	Object3d* resultPlayer_ = nullptr;
	Object3d* ground_ = nullptr;
	Object3d* celetialSphere_ = nullptr;
	Object3d* gun_ = nullptr;
	Camera* camera_ = nullptr;

	Vector3 playerRot_;
	Vector3 playerPos_;
	Vector3 playerScale_;

	Vector3 groundPos_;
	Vector3 groundScale_;

	Vector3 cameraPos_;
	Vector3 cameraTargetPos_;
};

