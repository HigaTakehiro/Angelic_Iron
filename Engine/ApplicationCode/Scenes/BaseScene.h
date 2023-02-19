#pragma once
#include <DirectXMath.h>
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "SceneChangeEffect.h"
#include "Sprite.h"
#include "Easing.h"
#include "SafeDelete.h"
#include "Reticle.h"

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

protected: //���z�����o�֐�
	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	virtual void SceneChange() = 0;

public: //�����o�֐�

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

protected: //�ÓI�����o�ϐ�

};