#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <d3d11.h>
#include <d3d11on12.h>
#include <dxgi1_6.h>
#include <dwrite.h>
#include <d2d1_1.h>
#include <d2d1_3.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include <DirectXMath.h>
#include <chrono>
#include <thread>
#include <map>
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
	ID3D12Device* GetDev() { return dev_.Get(); }
	/// <summary>
	/// �R�}���h���X�g�̎擾
	/// </summary>
	/// <returns></returns>
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList_.Get(); }
	/// <summary>
	/// D2D�f�o�C�X���̎擾
	/// </summary>
	/// <returns>D2D�f�o�C�X��</returns>
	ID2D1DeviceContext* GetD2DDeviceContext() { return d2dDeviceContext_.Get(); }
	/// <summary>
	/// directWriteFactory�̎擾
	/// </summary>
	/// <returns>directWriteFactory</returns>
	IDWriteFactory* GetDWriteFactory() { return directWriteFactory_.Get(); }
	/// <summary>
	/// SolidColorBrush�̎擾
	/// </summary>
	/// <returns>SolidColorBrush�A�z�z��</returns>
	std::map<std::string, ComPtr<ID2D1SolidColorBrush>> GetColorBrushes() { return solidColorBlushes_; }
	/// <summary>
	/// �e�L�X�g�t�H�[�}�b�g�̎擾
	/// </summary>
	/// <returns>�e�L�X�g�t�H�[�}�b�g�A�z�z��</returns>
	std::map<std::string, ComPtr<IDWriteTextFormat>> GetTextFormats() { return textFormats_; }
	/// <summary>
	/// SolidColorBlush��o�^����
	/// </summary>
	/// <param name="key">�A�z�z��̃L�[</param>
	/// <param name="color">�u���V�F</param>
	void registerSolidColorBrush(const std::string& key, const D2D1::ColorF color);
	/// <summary>
	/// �e�L�X�g�t�H�[�}�b�g��o�^����
	/// </summary>
	/// <param name="key">�A�z�z��̃L�[</param>
	/// <param name="fontName">�t�H���g��</param>
	/// <param name="fontSize">�t�H���g�T�C�Y</param>
	void registerTextFormat(const std::string& key, const std::wstring& fontName, const float fontSize);
	/// <summary>
	/// Direct2D�`��J�n
	/// </summary>
	void beginDrawWithDirect2D();
	/// <summary>
	/// Direct2D�`��I��
	/// </summary>
	void endDrawWithDirect2D();

private: //�����o�ϐ�
	//�E�B���h�E�Y�A�v���P�[�V�����Ǘ�
	WinApp* winApp_;

	ComPtr<ID3D12Device> dev_;
	ComPtr<ID3D11On12Device> id3d11On12Device_;
	ComPtr<ID3D11DeviceContext> devContext11_;
	ComPtr<ID2D1DeviceContext> d2dDeviceContext_;
	ComPtr<IDXGIFactory6> dxgiFactory_;
	ComPtr<IDXGISwapChain4> swapchain_;
	ComPtr<ID3D12GraphicsCommandList> cmdList_;
	ComPtr<ID3D12CommandAllocator> cmdAllocator_;
	ComPtr<ID3D12CommandQueue> cmdQueue_;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps_;
	ComPtr<IDWriteFactory> directWriteFactory_;
	std::vector<ComPtr<ID3D12Resource>> backBuffers_;
	std::vector<ComPtr<ID3D11Resource>> wrappedBackBuffers_;
	std::vector<ComPtr<ID2D1Bitmap1>> d2dRenderTargets_;
	ComPtr<ID3D12Resource> depthBuffer_;
	ComPtr<ID3D12DescriptorHeap> dsvHeap_;
	ComPtr<ID3D12Fence> fence_;
	UINT64 fenceVal_ = 0;
	//�\���b�h�J���[�u���V
	std::map<std::string, ComPtr<ID2D1SolidColorBrush>> solidColorBlushes_;
	//�e�L�X�g�t�H�[�}�b�g
	std::map<std::string, ComPtr<IDWriteTextFormat>> textFormats_;
	//FPS�Œ�p�L�^����
	std::chrono::steady_clock::time_point reference_;

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
	/// ID2D�f�o�C�X�R���e�L�X�g�̏�����
	/// </summary>
	void InitializeID2DDeviceContext();
	/// <summary>
	/// DirectWrite�̕`���𐶐�
	/// </summary>
	void CreateD2DRenderdTarget();
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

