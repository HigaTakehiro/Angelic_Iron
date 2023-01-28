#pragma once
#include <DirectXMath.h>
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "Easing.h"
#include "SafeDelete.h"

class BaseScene
{
public:
	//�f�X�g���N�^
	virtual ~BaseScene() {}

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

public: //���z�֐�
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() = 0;

public: //�����o�֐�

	/// <summary>
	/// �V�[���؂�ւ��p�ϐ��̏�����
	/// </summary>
	void SceneChangeInitialize();

	/// <summary>
	/// �}�E�X���X�v���C�g�ɐG��Ă��邩(�摜�̒��S���)
	/// </summary>
	/// <param name="mousePos">�}�E�X�̈ʒu</param>
	/// <param name="spritePos">�X�v���C�g�̈ʒu</param>
	/// <param name="spriteWidth">�X�v���C�g����</param>
	/// <param name="spriteHeight">�X�v���C�g�c��</param>
	/// <returns>�}�E�X���X�v���C�g��G��Ă���</returns>
	bool IsMouseHitSprite(DirectX::XMFLOAT2 mousePos, DirectX::XMFLOAT2 spritePos, float spriteWidth, float spriteHeight);

	/// <summary>
	/// n�̈ʂ̐����𔻒肷��
	/// </summary>
	/// <param name="score">���肵�����X�R�A</param>
	/// <param name="place">���肵�����X�R�A�̈�</param>
	/// <returns></returns>
	ScoreNumber JudgeDigitNumber(int score, int digit);

	/// <summary>
	/// �V�[���؂�ւ��p���o
	/// </summary>
	void SceneChangeEffect();

	/// <summary>
	/// �V�[���؂�ւ��������o
	/// </summary>
	void SceneChangeCompleteEffect();

	/// <summary>
	/// �V�[���؂�ւ����o�`��
	/// </summary>
	void SceneChangeEffectDraw();

	/// <summary>
	/// �V�[���؂�ւ������t���O
	/// </summary>
	/// <param name="isSceneChangeComplete">�V�[���؂�ւ������t���O</param>
	void SetSceneChangeComplete(const bool isSceneChangeComplete) { this->isSceneChangeComplete = isSceneChangeComplete; }

	/// <summary>
	/// �V�[���؂�ւ��I������
	/// </summary>
	void SceneChangeFinalize();

protected: //�ÓI�����o�ϐ�
	//�V�[���؂�ւ����o�p����
	static int32_t sceneChangeTime;

	//�V�[���؂�ւ��p�X�v���C�g
	static Sprite* sceneChangeEffects[10];
	//�V�[���؂�ւ��p�X�v���C�g���W
	static XMFLOAT2 sceneChangeEffectsPos[10];
	//�V�[���؂�ւ����o�p�^�C�}�[
	static int32_t sceneChangeTimer;
	//�V�[���؂�ւ��J�n�t���O
	static bool isSceneChangeStart;
	//�V�[���؂�ւ��t���O
	static bool isSceneChange;
	//�V�[���؂�ւ������t���O
	static bool isSceneChangeComplete;
};