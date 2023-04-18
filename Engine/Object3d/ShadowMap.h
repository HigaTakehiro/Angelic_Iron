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
	/// SRV�쐬
	/// </summary>
	bool SRVCreate();

	/// <summary>
	/// RTV�쐬
	/// </summary>
	bool RTVCreate();

	/// <summary>
	/// �[�x�o�b�t�@�쐬
	/// </summary>
	bool DepthCreate();

	/// <summary>
	/// DSV�쐬
	/// </summary>
	bool DSVCreate();

private: //�����o�ϐ�
	//�[�x�o�b�t�@�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> depthHeap_;
	//�e�N�X�`���p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> texHeap_;
	//�V���h�E�}�b�v�p�o�b�t�@
	ComPtr<ID3D12Resource> shadowBuff_;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource> depthBuff_;
};