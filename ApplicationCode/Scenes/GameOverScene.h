#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "Button.h"
#include "LightGroup.h"

class GameOverScene : public BaseScene
{
public:

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
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
	///// <summary>
	///// n�̈ʂ̐����𔻒肷��
	///// </summary>
	///// <param name="score">���肵�����X�R�A</param>
	///// <param name="place">���肵�����X�R�A�̈�</param>
	///// <returns></returns>
	//ScoreNumber JudgeDigitNumber(int32_t score, int32_t digit);

	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange();

private: //�ÓI�����o�ϐ�
	static const int32_t waitTime = 60;

private: //�����o�ϐ�

	PostEffect* postEffect_ = nullptr; //�|�X�g�G�t�F�N�g�N���X
	Sprite* score_ = nullptr; //�X�R�A�摜
	Sprite* scoreNumbers_[6] = {}; ///�X�R�A�p�A�Ԑ����摜
	Button* titleBack_ = nullptr;
	Button* restart_ = nullptr;

	PostEffect::PostEffectNo postEffectNo_; //�|�X�g�G�t�F�N�g�ԍ�
	//���C�g
	LightGroup* light_ = nullptr;

	float scoreRollTimer_;
	DirectX::XMFLOAT2 scoreRollPos_[6] = {};
	DirectX::XMFLOAT2 mousePos_;

	Object3d* resultPlayer_ = nullptr;
	Object3d* ground_ = nullptr;
	Object3d* celetialSphere_ = nullptr;
	Camera* camera_ = nullptr;

	Vector3 playerRot_;
	Vector3 playerPos_;
	Vector3 playerScale_;

	Vector3 groundPos_;
	Vector3 groundScale_;

	Vector3 cameraPos_;
	Vector3 cameraTargetPos_;

	bool isTitleBack_;
	bool isRestart_;
	bool isSelectedButton_;
	bool isButtonSelectTiming_;

	int32_t waitTimer_;
};

