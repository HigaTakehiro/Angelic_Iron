#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "LightGroup.h"

class GameOverScene : public BaseScene
{
public:
	enum ScoreNumber {
		zero = 64 * 0,
		one = 64 * 1,
		two = 64 * 2,
		three = 64 * 3,
		four = 64 * 4,
		five = 64 * 5,
		six = 64 * 6,
		seven = 64 * 7,
		eight = 64 * 8,
		nine = 64 * 9
	};

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
	//ScoreNumber JudgeDigitNumber(int score, int digit);

	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange();

private: //�����o�ϐ�

	PostEffect* postEffect = nullptr; //�|�X�g�G�t�F�N�g�N���X
	Sprite* score = nullptr; //�X�R�A�摜
	Sprite* scoreNumbers[6] = {}; ///�X�R�A�p�A�Ԑ����摜
	Sprite* titleBack = nullptr;
	Sprite* restart = nullptr;

	PostEffect::PostEffectNo postEffectNo; //�|�X�g�G�t�F�N�g�ԍ�
	//���C�g
	LightGroup* light = nullptr;

	float scoreRollTimer;
	DirectX::XMFLOAT2 scoreRollPos[6] = {};
	DirectX::XMFLOAT2 titleBackSize;
	DirectX::XMFLOAT2 restartSize;
	DirectX::XMFLOAT2 mousePos;
	float titleBackAlpha;
	float restartAlpha;

	Object3d* resultPlayer = nullptr;
	Object3d* ground = nullptr;
	Object3d* celetialSphere = nullptr;
	Camera* camera = nullptr;

	Vector3 playerRot;
	Vector3 playerPos;
	Vector3 playerScale;

	Vector3 groundPos;
	Vector3 groundScale;

	Vector3 cameraPos;
	Vector3 cameraTargetPos;

	bool isTitleBack;
	bool isRestart;
	bool isSelectedButton;
};

