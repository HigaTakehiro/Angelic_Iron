#pragma once
#include <stdint.h>
#include "Sprite.h"
#include "Vector2.h"
#include "Vector3.h"

class BaseBattleScene
{
public: //�T�u�N���X
	enum class FaceGraphics {
		OPE_NORMALFACE,
		OPE_SURPRISEFACE,
		OPE_SMILEFACE
	};

public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BaseBattleScene() {};

public: //�����o�֐�
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
	/// <summary>
	/// �X�e�[�W�ԍ����Z�b�g����
	/// </summary>
	/// <param name="stageNo">�X�e�[�W�ԍ�</param>
	void SetStageNo(int32_t stageNo) { stageNo_ = stageNo; }

protected: //�����o�֐�
	/// <summary>
	/// �����`��X�V����
	/// </summary>
	void TextMessageUpdate();

	/// <summary>
	/// ���ʏ���������
	/// </summary>
	void CommonInitialize();

	/// <summary>
	/// �|�[�Y����
	/// </summary>
	virtual void Pause() = 0;

	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	virtual void SceneChange() = 0;

	/// <summary>
	/// �G�̍X�V����
	/// </summary>
	virtual void EnemyUpdates() = 0;

protected: //�����o�ϐ�
	//�X�e�[�W�ԍ�
	int32_t stageNo_;
	//�ʏ펞�I�y���[�^��O���t�B�b�N
	std::unique_ptr<Sprite> opeNormal_[3];
	//�Ί�I�y���[�^��O���t�B�b�N
	std::unique_ptr<Sprite> opeSmile_[3];
	//�����I�y���[�^��O���t�B�b�N
	std::unique_ptr<Sprite> opeSurprise_[3];
	//�e�L�X�g�E�B���h�E�T�C�Y
	Vector2 textWindowSize_;
	//�t�F�C�X�E�B���h�E�T�C�Y
	Vector2 faceWindow_;
	//
};