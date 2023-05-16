#pragma once
#include "DirectXSetting.h"
#include "Vector3.h"
#include "Object3d.h"
#include "Camera.h"

class ShadowMap
{
public: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //�\����
	//�萔�o�b�t�@�f�[�^(B0)
	struct ConstBuffDataB0 {
		DirectX::XMMATRIX wvp;
		DirectX::XMMATRIX world;
	};

	//�萔�o�b�t�@�f�[�^(B1)
	struct ConstBuffDataB1 {
		DirectX::XMMATRIX lightVP;
		DirectX::XMVECTOR lightColor;
		Vector3 lightDir;
	};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(Object3d* obj, Camera* camera);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private: //�����o�֐�

	/// <summary>
	/// �e�N�X�`���p�f�X�N���v�^�q�[�v�쐬
	/// </summary>
	bool TexHeapCreate();

	/// <summary>
	/// �V���h�E�}�b�v�p�o�b�t�@�쐬
	/// </summary>
	bool ShadowBuffCreate();

	/// <summary>
	/// �V���h�E�}�b�v�p�f�X�N���v�^�q�[�v�쐬
	/// </summary>
	bool ShadowHeapCreate();

	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���쐬
	/// </summary>
	bool GraphicsPipelineCrate();

private: //�����o�ϐ�
	//�V���h�E�}�b�v�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> shadowHeap_;
	//�e�N�X�`���p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> texHeap_;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB0_;
	//�V���h�E�}�b�v�p�o�b�t�@
	ComPtr<ID3D12Resource> shadowBuff_;
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature_;
	//�p�C�v���C���X�e�[�g
	ComPtr<ID3D12PipelineState> pipelinestate_;

};