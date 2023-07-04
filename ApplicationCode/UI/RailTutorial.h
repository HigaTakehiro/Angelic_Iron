#pragma once
#include "ImageManager.h"
#include "Sprite.h"
#include "Vector2.h"

class RailTutorial
{
public: //�����o�֐�
	/// <summary>
	/// ����������
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
	/// �㏸�����t���O�Z�b�g
	/// </summary>
	/// <param name="isUp">�㏸����</param>
	void SetIsUPMove(bool isUp) { isUpMove_ = isUp; }
	/// <summary>
	/// ���~�����t���O�Z�b�g
	/// </summary>
	/// <param name="isDown">���~����</param>
	void SetIsDownMove(bool isDown) { isDownMove_ = isDown; }
	/// <summary>
	/// ���ړ������t���O�Z�b�g
	/// </summary>
	/// <param name="isLeft">���ړ�����</param>
	void SetIsLeftMove(bool isLeft) { isLeftMove_ = isLeft; }
	/// <summary>
	/// �E�ړ������t���O�Z�b�g
	/// </summary>
	/// <param name="isRight">�E�ړ�����</param>
	void SetIsRightMove(bool isRight) { isRightMove_ = isRight; }
	/// <summary>
	/// �ˌ������t���O�Z�b�g
	/// </summary>
	/// <param name="isShot"></param>
	void SetIsShot(bool isShot) { isShot_ = isShot; }
	/// <summary>
	/// �{�������t���O�Z�b�g
	/// </summary>
	/// <param name="isBomb"></param>
	void SetIsBomb(bool isBomb) { isBomb_ = isBomb; }
	//�v���C���[2d���W�Z�b�g
	void SetPlayer2DPos(Vector2 player2DPos) { player2dPos_ = player2DPos; }

private: //�ÓI�����o�ϐ�
	//�`���[�g���A���\������
	static const int32_t tutorialTime = 180;

private: //�����o�ϐ�
	//�`���[�g���A���\���^�C�}�[
	int32_t tutorialTimer_;

	//�㏸�����t���O
	bool isUpMove_;
	//���~�����t���O
	bool isDownMove_;
	//���ړ������t���O
	bool isLeftMove_;
	//�E�ړ������t���O
	bool isRightMove_;
	//�ˌ������t���O
	bool isShot_;
	//�{���U�������t���O
	bool isBomb_;
	//�㏸�L�[�X�v���C�g
	std::unique_ptr<Sprite> how_to_up_;
	//�㏸�X�v���C�g�A���t�@�l
	float upAlpha_;
	//���~�L�[�X�v���C�g
	std::unique_ptr<Sprite> how_to_down_;
	//���~�X�v���C�g�A���t�@�l
	float downAlpha_;
	//���ړ��L�[�X�v���C�g
	std::unique_ptr<Sprite> how_to_left_;
	//���X�v���C�g�A���t�@�l
	float leftAlpha_;
	//�E�ړ��L�[�X�v���C�g
	std::unique_ptr<Sprite> how_to_right_;
	//�E�X�v���C�g�A���t�@�l
	float rightAlpha_;
	//�ˌ��L�[�X�v���C�g
	std::unique_ptr<Sprite> how_to_shot_;
	//�ˌ��X�v���C�g�A���t�@�l
	float shotAlpha_;
	//�{���L�[�X�v���C�g
	std::unique_ptr<Sprite> how_to_bomb_;
	//�{���X�v���C�g�A���t�@�l
	float bombAlpha_;
	//�v���C���[2D���W
	Vector2 player2dPos_;
};