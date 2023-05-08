#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <unordered_map>

class Model
{
private: // �G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos_; // xyz���W
		XMFLOAT3 normal_; // �@���x�N�g��
		XMFLOAT2 uv_;  // uv���W
	};
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient_;
		float pad1_;
		XMFLOAT3 diffuse_;
		float pad2_;
		XMFLOAT3 specular_;
		float alpha_;
	};
	//�}�e���A��
	struct Material
	{
		std::string name_;
		XMFLOAT3 ambient_;
		XMFLOAT3 diffuse_;
		XMFLOAT3 specular_;
		float alpha_;
		std::string textureFilename_;

		Material() {
			ambient_ = { 0.3f, 0.3f, 0.3f };
			diffuse_ = { 0.0f, 0.0f, 0.0f };
			specular_ = { 0.0f, 0.0f, 0.0f };
			alpha_ = 1.0f;
		}
	};

private: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device_;
	//�f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize_;

private: //�����o�ϐ�
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff_;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff_;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView_ = {};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView_ = {};
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices_;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices_;
	//���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData_;
	//�}�e���A��
	Material material_;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff_;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB1_;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV_;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV_;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap_;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// ����
	/// </summary>
	static Model* CreateModel(const std::string& modelname, bool isSmoothing = false);

	/// <summary>
	/// �}�`���f������
	/// </summary>
	/// <param name="vertices_">���_</param>
	/// <param name="indices_">���_�C���f�b�N�X</param>
	/// <param name="textureName">�e�N�X�`����</param>
	/// <returns></returns>
	static Model* CreateShapeModel(const std::vector<VertexPosNormalUv>& vertices_, const std::vector<unsigned short> indices_, const std::string& textureName);

public: //�����o�֐�
	/// <summary>
	/// �}�e���A���̎擾
	/// </summary>
	/// <returns></returns>
	Material GetMaterial() { return material_; }

	/// <summary>
	/// �A���r�G���g���Z�b�g
	/// </summary>
	/// <param name="ambient"></param>
	void SetAmbient(const XMFLOAT3& ambient) { material_.ambient_ = ambient; }

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �}�e���A���̓ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// ���f��������
	/// </summary>
	void InitializeModel(const std::string& modelname, bool isSmoothing);

	/// <summary>
	/// �}�`���f��������
	/// </summary>
	/// <param name="vertices_">���_�f�[�^</param>
	/// <param name="indices_">���_�C���f�b�N�X</param>
	/// <param name="textureName">�e�N�X�`����</param>
	void InitializeShapesModel(const std::vector<VertexPosNormalUv>& vertices_, const std::vector<unsigned short> indices_, const std::string& textureName);

	/// <summary>
	/// �G�b�W�������p�f�[�^��ǉ�
	/// </summary>
	/// <param name="indexPosition">���W�C���f�b�N�X</param>
	/// <param name="indexVertex">���_�C���f�b�N�X</param>
	void AddSmoothData(unsigned short indexPosition, unsigned short indexVertex);

	/// <summary>
	/// �������������_�@���̌v�Z
	/// </summary>
	void CalculateSmoothedVertexNormals();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(Material material);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

private: //�����o�֐�
	/// <summary>
	/// �g���q�𕪗�����
	/// </summary>
	/// <param name="filePath">�g���q�𕪗��������t�@�C���p�X</param>
	/// <returns>�g���q</returns>
	std::wstring SeparatedExtension(const std::wstring& filePath);

};