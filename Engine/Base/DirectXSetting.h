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
	/// コンストラクタ
	/// </summary>
	DirectXSetting() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~DirectXSetting() = default;
	/// <summary>
    /// コピーコンストラクタを禁止
    /// </summary>
	DirectXSetting(const DirectXSetting& obj) = delete;

	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	DirectXSetting& operator=(const DirectXSetting& obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static DirectXSetting* GetIns();

private: //エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* win);
	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="color">背景色</param>
	void PreDraw(XMFLOAT4 color);
	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();
	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <returns></returns>
	ID3D12Device* GetDev() { return dev.Get(); }
	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	/// <returns></returns>
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
private: //メンバ変数
	//ウィンドウズアプリケーション管理
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
	//FPS固定用記録時間
	std::chrono::steady_clock::time_point reference;

private: //メンバ関数
	/// <summary>
	/// デバイスの初期化
	/// </summary>
	void InitializeDev();
	/// <summary>
	/// コマンド関連の初期化
	/// </summary>
	void InitializeCmd();
	/// <summary>
	/// DirectX11のデバイスの初期化
	/// </summary>
	void InitializeDev11();
	/// <summary>
	/// スワップチェーンの初期化
	/// </summary>
	void InitializeSwapChain();
	/// <summary>
	/// レンダーターゲットの初期化
	/// </summary>
	void InitializeRenderTarget();
	/// <summary>
	/// 深度バッファの初期化
	/// </summary>
	void InitializeDepthBuffer();
	/// <summary>
	/// フェンスの初期化
	/// </summary>
	void InitializeFence();
	/// <summary>
	/// FPS固定初期化
	/// </summary>
	void InitializeFixFPS();
	/// <summary>
	/// FPS固定更新
	/// </summary>
	void UpdateFixFPS();
};

