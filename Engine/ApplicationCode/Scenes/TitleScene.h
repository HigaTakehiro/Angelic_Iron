#pragma once

#include "BaseScene.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"
#include "Object3d.h"
#include "Vector3.h"
#include "Camera.h"
#include "MouseInput.h"
#include "Easing.h"
#include "Shapes.h"
#include "ParticleManager.h"
#include "LightGroup.h"
#include "DebugText.h"
#include "MotionMath.h"
#include "JsonLoader.h"

class TitleScene : public BaseScene
{
public: //�����o�֐�
	/// <summary>
	/// �������֐�
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
	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	void SceneChange();

private: //�ÓI�����o�ϐ�
	//�^�C�g������ʊO�ɏo�鎞��
	static const int32_t titleOutTime = 40;
	//�X�e�[�W1�{�^���\������
	static const int32_t stage1ComeTime = 150;
	//�}�j���A���{�^���\������
	static const int32_t manualComeTime = 170;
	//�}�j���A���J������
	static const int32_t manualOpenTime = 60;
	//�X�e�[�W�J�n����
	static const int32_t startTime = 60;
	//�}�j���A���X���C�h����
	static const int32_t manualSlideTime = 60;

private: //�����o�ϐ�
	//�{�^�����I������Ă���Ƃ��̃A���t�@�l
	const float selectAlpha = 0.5f;
	//�{�^�������A���t�@�l
	const float initAlpha = 1.0f;

	//�X�v���C�g
	//�^�C�g��
	std::unique_ptr<Sprite> title = nullptr;
	//�X�^�[�g�{�^��
	std::unique_ptr<Sprite> startButton = nullptr;
	//�X�e�[�W1�{�^��
	std::unique_ptr<Sprite> stage1 = nullptr;
	//�}�j���A���{�^��
	std::unique_ptr<Sprite> manualButton = nullptr;
	//�������1
	std::unique_ptr<Sprite> manual = nullptr;
	//�������2
	std::unique_ptr<Sprite> manual2 = nullptr;
	//�}�j���A�����{�^��
	std::unique_ptr<Sprite> close = nullptr;
	//�}�j���A���y�[�W�ύX�{�^��
	std::unique_ptr<Sprite> allow = nullptr;
	//�f�o�b�O�e�L�X�g�\���p�N���X
	DebugText debugText;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo;

	//�X�v���C�g�p�ϐ�
	//�^�C�g�����W
	DirectX::XMFLOAT2 titlePos;
	//�X�^�[�g�{�^�����W
	DirectX::XMFLOAT2 startButtonPos;
	//�X�^�[�g�{�^���T�C�Y
	DirectX::XMFLOAT2 startButtonSize;
	//�X�e�[�W1���W
	DirectX::XMFLOAT2 stage1Pos;
	//�X�e�[�W1�T�C�Y
	DirectX::XMFLOAT2 stage1Size;
	//�}�j���A���{�^�����W
	DirectX::XMFLOAT2 manualButtonPos;
	//�}�j���A���{�^���T�C�Y
	DirectX::XMFLOAT2 manualButtonSize;
	//��������T�C�Y
	DirectX::XMFLOAT2 manualSize;
	//��������ő�T�C�Y
	DirectX::XMFLOAT2 manualMaxSize;
	//����������W
	DirectX::XMFLOAT2 manualPos;
	//�}�j���A���y�[�W�ύX�{�^�����W
	DirectX::XMFLOAT2 allowPos;
	//�}�j���A���y�[�W�ύX�{�^���T�C�Y
	DirectX::XMFLOAT2 allowSize;
	//�}�j���A������{�^�����W
	DirectX::XMFLOAT2 closePos;
	//�}�j���A������{�^���T�C�Y
	DirectX::XMFLOAT2 closeSize;
	//�}�E�X���W
	DirectX::XMFLOAT2 mousePos;
	//�X�e�[�W�I�����o�p�^�C�}�[
	int32_t stageSelectTimer;
	//�}�j���A���J���o�p�^�C�}�[
	int32_t manualTimer;
	//�X�e�[�W�J�n���o����
	int32_t startTimer;
	//�}�j���A���y�[�W�ύX����
	int32_t manualSlideTimer;

	//�|�X�g�G�t�F�N�g
	std::unique_ptr<PostEffect> postEffect = nullptr;
	//�^�C�g����ʃv���C���[
	std::unique_ptr<Object3d> titlePlayer = nullptr;
	//�J����
	std::unique_ptr<Camera> camera = nullptr;
	//���C�g
	std::unique_ptr<LightGroup> light = nullptr;
	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> particle = nullptr;
	//json���[�_�[
	std::unique_ptr<JsonLoader> jsonLoader = nullptr;
	//�v���C���[��]�p
	Vector3 playerRot;
	//�v���C���[���W
	Vector3 playerPos;
	//�v���C���[�T�C�Y
	Vector3 playerScale;
	//�J�������W
	Vector3 cameraPos;
	//�J���������_
	Vector3 cameraTargetPos;
	//�y�[�W�ԍ�
	int pageNumber;
	//�O�y�[�W�ԍ�
	int prePageNumber;
	//�X�e�[�W�I����ʃt���O
	bool isStageSelectMenu;
	//�X�e�[�W�I���t���O
	bool isStageChoice;
	//�}�j���A���\���t���O
	bool isManual;
	//�X�e�[�W1�I���t���O
	bool isStage1;
	//�y�[�W�ύX�t���O(���̃y�[�W)
	bool isNextPage;
	//�y�[�W�ύX�t���O(�O�̃y�[�W)
	bool isPrevPage;
};