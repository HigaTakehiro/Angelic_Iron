#pragma once
#include "DirectXSetting.h"

class ShadowMap
{
public: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

private: //�����o�֐�

	/// <summary>
	/// �e�N�X�`���p�f�X�N���v�^�q�[�v�쐬
	/// </summary>
	bool TexHeapCreate();

	/// <summary>
	/// �e�N�X�`���p�o�b�t�@�쐬
	/// </summary>
	bool TexBuffCreate();

	/// <summary>
	/// �V���h�E�}�b�v�p�o�b�t�@�쐬
	/// </summary>
	bool ShadowBuffCreate();

	/// <summary>
	/// �V���h�E�}�b�v�p�f�X�N���v�^�q�[�v�쐬
	/// </summary>
	bool ShadowHeapCreate();

private: //�����o�ϐ�
	//�V���h�E�}�b�v�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> shadowHeap_;
	//�e�N�X�`���p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> texHeap_;
	//�V���h�E�}�b�v�p�o�b�t�@
	ComPtr<ID3D12Resource> shadowBuff_;
	//�e�N�X�`���p�o�b�t�@
	ComPtr<ID3D12Resource> texBuff_;
};