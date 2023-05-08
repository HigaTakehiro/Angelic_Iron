#pragma once
#include "Sprite.h"

class PostEffect : public Sprite
{
public: //�\����
	struct ConstBuffDataB0 {
		float time_;
		float maxTime_;
		float mask_;
		float blurCenterX_;
		float blurCenterY_;
	};

	enum class PostEffectNo {
		NONE,
		FADEOUT,
		NORMAL,
		DAMAGE,
		SLOW,
		DASH,
		SHOUT,
		POSTSHOUT,
	};

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PostEffect();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��R�}���h
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, const float maxTime, PostEffectNo pipelineNo = PostEffectNo::NONE, bool isRoop = false);

	/// <summary>
	/// �V�[���`��O����
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �V�[���`��㏈��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �p�C�v���C������
	/// </summary>
	void CreateGraphicsPipelineState();

	/// <summary>
	/// �s�N�Z���V�F�[�_�[�ǂݍ���
	/// </summary>
	void LoadPS(const wchar_t* psName, ComPtr<ID3DBlob>& psBlob);

	/// <summary>
	/// �u���[���K�p����Ȃ��͈̓Z�b�g
	/// </summary>
	/// <param name="mask">�u���[���K�p����Ȃ��͈�</param>
	void SetMask(float mask) { mask_ = mask; }

	/// <summary>
	///	�u���[�������S�ʒu���Z�b�g
	/// </summary>
	/// <param name="blurCenter">�u���[�������S�ʒu</param>
	void SetBlurCenter(DirectX::XMFLOAT2 blurCenter) { blurCenter_ = blurCenter; }

private: //�ÓI�����o�ϐ�
	static const int32_t texSize = 8;

public: //�����o�ϐ�
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff_[texSize];
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV_;
	//�[�x�o�b�t�@
	ComPtr<ID3D12Resource> depthBuff_;
	//RTV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapRTV_;
	//DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapDSV_;
	//�O���t�B�b�N�X�p�C�v���C��
	ComPtr<ID3D12PipelineState> pipelineState_[texSize];
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature_;

private: //�ÓI�����o�ϐ�
	//��ʃN���A�J���[
	static const float clearColor_[4];

private: //�����o�ϐ�
	PostEffectNo nowPipelineNo_ = PostEffectNo::NONE;
	float timer_ = 0.0f;
	//�u���[���K�p����Ȃ��͈�
	float mask_;
	//�u���[�̒��S
	DirectX::XMFLOAT2 blurCenter_;
	//�萔�o�b�t�@�]���p
	ComPtr<ID3D12Resource> constBuffB0_;

private: //�����o�֐�
	/// <summary>
	/// �e�N�X�`���쐬
	/// </summary>
	void TexCreate();

	/// <summary>
	/// SRV�쐬
	/// </summary>
	void SRVCreate();

	/// <summary>
	/// RTV�쐬
	/// </summary>
	void RTVCreate();

	/// <summary>
	/// �[�x�o�b�t�@�쐬
	/// </summary>
	void DepthCreate();

	/// <summary>
	/// DSV�쐬
	/// </summary>
	void DSVCreate();

};