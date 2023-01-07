#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <d3d11.h>
#include <d3d11on12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include <DirectXMath.h>
#include <chrono>
#include <thread>

#include "WinApp.h"

class DirectXSetting final
{
private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DirectXSetting() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DirectXSetting() = default;
	/// <summary>
    /// �R�s�[�R���X�g���N�^���֎~
    /// </summary>
	DirectXSetting(const DirectXSetting& obj) = delete;

	/// <summary>
	/// ������Z�q���֎~
	/// </summary>
	DirectXSetting& operator=(const DirectXSetting& obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X���擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static DirectXSetting* GetIns();

private: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* win);
	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="color">�w�i�F</param>
	void PreDraw(XMFLOAT4 color);
	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();
	/// <summary>
	/// �f�o�C�X�̎擾
	/// </summary>
	/// <returns></returns>
	ID3D12Device* GetDev() { return dev.Get(); }
	/// <summary>
	/// �R�}���h���X�g�̎擾
	/// </summary>
	/// <returns></returns>
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
private: //�����o�ϐ�
	//�E�B���h�E�Y�A�v���P�[�V�����Ǘ�
	WinApp* winApp;

	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D11Device> dev11;
	ComPtr<ID3D11DeviceContext> devContext11;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	//FPS�Œ�p�L�^����
	std::chrono::steady_clock::time_point reference;

private: //�����o�֐�
	/// <summary>
	/// �f�o�C�X�̏�����
	/// </summary>
	void InitializeDev();
	/// <summary>
	/// �R�}���h�֘A�̏�����
	/// </summary>
	void InitializeCmd();
	/// <summary>
	/// DirectX11�̃f�o�C�X�̏�����
	/// </summary>
	void InitializeDev11();
	/// <summary>
	/// �X���b�v�`�F�[���̏�����
	/// </summary>
	void InitializeSwapChain();
	/// <summary>
	/// �����_�[�^�[�Q�b�g�̏�����
	/// </summary>
	void InitializeRenderTarget();
	/// <summary>
	/// �[�x�o�b�t�@�̏�����
	/// </summary>
	void InitializeDepthBuffer();
	/// <summary>
	/// �t�F���X�̏�����
	/// </summary>
	void InitializeFence();
	/// <summary>
	/// FPS�Œ菉����
	/// </summary>
	void InitializeFixFPS();
	/// <summary>
	/// FPS�Œ�X�V
	/// </summary>
	void UpdateFixFPS();
};

