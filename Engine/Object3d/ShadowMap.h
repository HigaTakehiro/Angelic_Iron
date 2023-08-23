#pragma once
#include "DirectXSetting.h"
#include "Vector3.h"
#include "Camera.h"

class ShadowMap
{
public: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //�\����
	//�萔�o�b�t�@�f�[�^(B0)
	struct ShadowBuffData {
		DirectX::XMMATRIX wvp;
		DirectX::XMMATRIX world;
	};

	//�萔�o�b�t�@�f�[�^(B1)
	struct LightBuffData {
		DirectX::XMMATRIX lightVP;
		DirectX::XMVECTOR lightColor;
		Vector3 lightDir;
	};

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ShadowMap* Create();

	/// <summary>
	/// �C���X�^���X����(���j�[�N�|�C���^)
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static std::unique_ptr<ShadowMap> UniquePtrCreate();

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(DirectX::XMMATRIX world);

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
	ComPtr<ID3D12Resource> shadowBuff_;
	//�V���h�E�}�b�v�p�o�b�t�@
	ComPtr<ID3D12Resource> lightBuff_;
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature_;
	//�p�C�v���C���X�e�[�g
	ComPtr<ID3D12PipelineState> pipelinestate_;

};