#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include <memory>
#include "Model.h"
#include "Camera.h"
#include "LightGroup.h"

/// <summary>
/// 3D�I�u�W�F�N�g
/// </summary>
class Object3d
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj_;	// �r���[�ϊ��s��
		XMMATRIX world_; //���[���h�s��
		XMFLOAT4 color_; // �F
		XMFLOAT3 cameraPos_; //�J�������W
		float time_; //����
	};

	// ���_�V�F�[�_�ԍ�
	enum class VSPipelineNo {
		Normal,
		Wave,
	};

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	/// <returns>����</returns>
	static bool StaticInitialize(ID3D12Device* device, int32_t window_width, int32_t window_height);

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Object3d* Create(Model* model);

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns></returns>
	static std::unique_ptr<Object3d> UniquePtrCreate(Model* model);

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device_;
	//���_�V�F�[�_�[��
	static const int32_t vsSize = 2;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList_;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature_;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate_[vsSize];
	//���C�g
	static LightGroup* light_;

private:// �ÓI�����o�֐�
	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	static bool InitializeGraphicsPipeline();

	/// <summary>
	/// ���_�V�F�[�_�[�ǂݍ���
	/// </summary>
	/// <param name="vsName">���_�V�F�[�_�[��</param>
	/// <param name="vsBlob">���_�V�F�[�_�[�I�u�W�F�N�g</param>
	static void LoadVS(const wchar_t* vsName, ComPtr<ID3DBlob>& vsBlob);

	/// <summary>
	/// �s�N�Z���V�F�[�_�[�ǂݍ���
	/// </summary>
	/// <param name="psName">�s�N�Z���V�F�[�_�[��</param>
	/// <param name="psBlob">�s�N�Z���V�F�[�_�[�I�u�W�F�N�g</param>
	static void LoadPS(const wchar_t* psName, ComPtr<ID3DBlob>& psBlob);

public: //�ÓI�����o�֐�
	/// <summary>
	/// ���C�g���Z�b�g
	/// </summary>
	/// <param name="light">���C�g</param>
	static void SetLight(LightGroup* light) { Object3d::light_ = light; }

public: // �����o�֐�
	bool Initialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	/// <param name="maxTime">�萔�o�b�t�@�ɑ���ő厞��</param>
	void Update(const float maxTime = 0.0f);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const XMFLOAT3& GetPosition() { return position_; }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT3 position) { position_ = position; }

	/// <summary>
	/// �傫���̎擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetScale() { return scale_; }

	/// <summary>
	/// �傫���̐ݒ�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(XMFLOAT3 scale) { scale_ = scale; }

	/// <summary>
	/// ��]�p�̎擾
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetRotation() { return rotation_; }

	/// <summary>
	/// ��]�p�̐ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(XMFLOAT3 rotation) { rotation_ = rotation; }

	//���f���̃Z�b�g
	void SetModel(Model* model) { model_ = model; }

	/// <summary>
	/// ���[���h�ϊ��s��̎擾
	/// </summary>
	/// <returns>���[���h�ϊ��s��</returns>
	const XMMATRIX& GetMatWorld() { return matWorld_; }

	/// <summary>
	/// �e�I�u�W�F�N�g�ݒ�(�J����)
	/// </summary>
	void SetCameraParent(Camera* cameraParent) { cameraParent_ = cameraParent; }

	/// <summary>
	/// �e�I�u�W�F�N�g�ݒ�(obj)
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(Object3d* parent) { parent_ = parent; }

	/// <summary>
	/// �A���r�G���g���Z�b�g
	/// </summary>
	/// <param name="ambient">�A���r�G���g</param>
	void SetAmbient(const XMFLOAT3& ambient) { model_->SetAmbient(ambient); }

	/// <summary>
	/// �F���Z�b�g
	/// </summary>
	/// <param name="color"></param>
	void SetColor(XMFLOAT4 color) { this->color_ = color; }

	/// <summary>
	/// �r���{�[�h�s����|����
	/// </summary>
	/// <param name="isBillboard">�r���{�[�h�t���O</param>
	void SetIsBillboard(bool isBillboard) { this->isBillboard_ = isBillboard; }

	/// <summary>
	/// Y���r���{�[�h�s����|����
	/// </summary>
	/// <param name="isBillboardY">Y���r���{�[�h�t���O</param>
	void SetIsBillboardY(bool isBillboardY) { this->isBillboardY_ = isBillboardY; }

	/// <summary>
	/// �g�p�V�F�[�_�[�K�p�t���O���Z�b�g
	/// </summary>
	void SetIsWave(bool isWave) { this->isWave_ = isWave; }

	/// <summary>
	/// �e�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g</returns>
	Object3d* GetParent() { return parent_; }

	/// <summary>
	/// �e�I�u�W�F�N�g(�J����)�擾
	/// </summary>
	/// <returns>�e�I�u�W�F�N�g(�J����)</returns>
	Camera* GetCameraParent() { return cameraParent_; }

private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuffB0_; // �萔�o�b�t�@
	// �F
	XMFLOAT4 color_ = { 1,1,1,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale_ = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation_ = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position_ = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld_;
	// �e�I�u�W�F�N�g
	Object3d* parent_ = nullptr;
	//�e�I�u�W�F�N�g(�J����)
	Camera* cameraParent_ = nullptr;
	//���f���f�[�^
	Model* model_ = nullptr;
	//�J����
	Camera* camera_ = nullptr;
	//�r���{�[�h�s��t���O
	bool isBillboard_;
	//Y���r���{�[�h�s��t���O
	bool isBillboardY_;
	//�g�p�V�F�[�_�[�K�p�t���O
	bool isWave_;
	//�V�F�[�_�[�p�^�C�}�[
	float timer_ = 0.0f;
};

