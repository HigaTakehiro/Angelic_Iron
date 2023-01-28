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
	void Initialize(XMFLOAT2 pos, XMFLOAT2 scale, int32_t time, ImageManager::ImageName imageName, XMFLOAT2 anchorPoint = {0, 0}, int imageNo = 0, XMFLOAT2 texUpperLeft = {0, 0}, XMFLOAT2 texLowerRight = {0, 0});

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
	bool IsDelete() const { return isDelete; }

private: //�����o�ϐ�

	XMFLOAT2 pos; //�������W
	int32_t deleteTime; //��������
	XMFLOAT2 texUpperLeft; //�A���摜�p������W
	XMFLOAT2 texLowerRight; //�A���摜�p�E����W
	int imageNo; //�����摜��
	Sprite* particle; //�p�[�e�B�N��

	int32_t nowTime; //���ݎ���
	int32_t drawTime; //1�̉摜�̕`�掞��
	int nowImage; //���݂̕����摜


	bool isDelete; //���Ńt���O
};

