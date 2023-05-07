#pragma once
#include "Sprite.h"
#include "imageManager.h"
#include "safeDelete.h"
#include <DirectXMath.h>

class Particle2d
{
public: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: 
	Particle2d() = default;

	~Particle2d();

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">�������W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="time">��������</param>
	/// <param name="imageName">�摜��</param>
	/// <param name="anchorPoint">�A���J�[�|�C���g</param>
	/// <param name="imageNo">�����摜��</param>
	/// <param name="texUpperLeft">�摜����/param>
	/// <param name="texLowerRight">�摜�E��</param>
	void Initialize(XMFLOAT2 pos, XMFLOAT2 scale, int32_t time, ImageManager::ImageName imageName, XMFLOAT2 anchorPoint = {0, 0}, int32_t imageNo = 0, XMFLOAT2 texUpperLeft = {0, 0}, XMFLOAT2 texLowerRight = {0, 0});

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
    /// �G�̏�Ԃ��擾
    /// </summary>
    /// <returns>�G�̏��</returns>
	bool IsDelete() const { return isDelete_; }

private: //�����o�ϐ�

	XMFLOAT2 pos_; //�������W
	int32_t deleteTime_; //��������
	XMFLOAT2 texUpperLeft_; //�A���摜�p������W
	XMFLOAT2 texLowerRight_; //�A���摜�p�E����W
	int32_t imageNo_; //�����摜��
	Sprite* particle_; //�p�[�e�B�N��

	int32_t nowTimer_; //���ݎ���
	int32_t drawTime_; //1�̉摜�̕`�掞��
	int32_t nowImage_; //���݂̕����摜

	bool isDelete_; //���Ńt���O
};

