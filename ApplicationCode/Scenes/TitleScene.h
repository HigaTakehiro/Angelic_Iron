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
#include "ShadowMap.h"

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
	std::unique_ptr<Sprite> title_ = nullptr;
	//�X�^�[�g�{�^��
	std::unique_ptr<Sprite> startButton_ = nullptr;
	//�X�e�[�W1�{�^��
	std::unique_ptr<Sprite> stage1_ = nullptr;
	//�}�j���A���{�^��
	std::unique_ptr<Sprite> manualButton_ = nullptr;
	//�������1
	std::unique_ptr<Sprite> manual_ = nullptr;
	//�������2
	std::unique_ptr<Sprite> manual2_ = nullptr;
	//�}�j���A�����{�^��
	std::unique_ptr<Sprite> close_ = nullptr;
	//�}�j���A���y�[�W�ύX�{�^��
	std::unique_ptr<Sprite> allow_ = nullptr;
	//�f�o�b�O�e�L�X�g�\���p�N���X
	DebugText debugText_;
	//�|�X�g�G�t�F�N�g�ԍ�
	PostEffect::PostEffectNo postEffectNo_;

	//�X�v���C�g�p�ϐ�
	//�^�C�g�����W
	DirectX::XMFLOAT2 titlePos_;
	//�X�^�[�g�{�^�����W
	DirectX::XMFLOAT2 startButtonPos_;
	//�X�^�[�g�{�^���T�C�Y
	DirectX::XMFLOAT2 startButtonSize_;
	//�X�e�[�W1���W
	DirectX::XMFLOAT2 stage1Pos_;
	//�X�e�[�W1�T�C�Y
	DirectX::XMFLOAT2 stage1Size_;
	//�}�j���A���{�^�����W
	DirectX::XMFLOAT2 manualButtonPos_;
	//�}�j���A���{�^���T�C�Y
	DirectX::XMFLOAT2 manualButtonSize_;
	//��������T�C�Y
	DirectX::XMFLOAT2 manualSize_;
	//��������ő�T�C�Y
	DirectX::XMFLOAT2 manualMaxSize_;
	//����������W
	DirectX::XMFLOAT2 manualPos_;
	//�}�j���A���y�[�W�ύX�{�^�����W
	DirectX::XMFLOAT2 allowPos_;
	//�}�j���A���y�[�W�ύX�{�^���T�C�Y
	DirectX::XMFLOAT2 allowSize_;
	//�}�j���A������{�^�����W
	DirectX::XMFLOAT2 closePos_;
	//�}�j���A������{�^���T�C�Y
	DirectX::XMFLOAT2 closeSize_;
	//�}�E�X���W
	DirectX::XMFLOAT2 mousePos_;
	//�X�e�[�W�I�����o�p�^�C�}�[
	int32_t stageSelectTimer_;
	//�}�j���A���J���o�p�^�C�}�[
	int32_t manualTimer_;
	//�X�e�[�W�J�n���o����
	int32_t startTimer_;
	//�}�j���A���y�[�W�ύX����
	int32_t manualSlideTimer_;

	//�|�X�g�G�t�F�N�g
	std::unique_ptr<PostEffect> postEffect_ = nullptr;
	//�^�C�g����ʃv���C���[
	std::unique_ptr<Object3d> titlePlayer_ = nullptr;
	//�J����
	std::unique_ptr<Camera> camera_ = nullptr;
	//���C�g
	std::unique_ptr<LightGroup> light_ = nullptr;
	//�p�[�e�B�N��
	std::unique_ptr<ParticleManager> particle_ = nullptr;
	//json���[�_�[
	std::unique_ptr<JsonLoader> jsonLoader_ = nullptr;
	//�v���C���[��]�p
	Vector3 playerRot_;
	//�v���C���[���W
	Vector3 playerPos_;
	//�v���C���[�T�C�Y
	Vector3 playerScale_;
	//�J�������W
	Vector3 cameraPos_;
	//�J���������_
	Vector3 cameraTargetPos_;
	//�y�[�W�ԍ�
	int32_t pageNumber_;
	//�O�y�[�W�ԍ�
	int32_t prePageNumber_;
	//�X�e�[�W�I����ʃt���O
	bool isStageSelectMenu_;
	//�X�e�[�W�I���t���O
	bool isStageChoice_;
	//�}�j���A���\���t���O
	bool isManual_;
	//�X�e�[�W1�I���t���O
	bool isStage1_;
	//�y�[�W�ύX�t���O(���̃y�[�W)
	bool isNextPage_;
	//�y�[�W�ύX�t���O(�O�̃y�[�W)
	bool isPrevPage_;

	ShadowMap* shadow_;

};