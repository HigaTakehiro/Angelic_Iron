﻿#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <forward_list>
#include <memory>

#include "Camera.h"

/// <summary>
/// パーティクルマネージャ
/// </summary>
class ParticleManager
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 頂点データ構造体
	struct VertexPos
	{
		XMFLOAT3 pos_; // xyz座標
		float scale_; // スケール
		XMFLOAT4 color_; //色
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMMATRIX mat_;	// ビュープロジェクション行列
		XMMATRIX matBillboard_;	// ビルボード行列
	};

	// パーティクル1粒
	class Particle
	{
		// Microsoft::WRL::を省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		// DirectX::を省略
		using XMFLOAT2 = DirectX::XMFLOAT2;
		using XMFLOAT3 = DirectX::XMFLOAT3;
		using XMFLOAT4 = DirectX::XMFLOAT4;
		using XMMATRIX = DirectX::XMMATRIX;
	public:
		// 座標
		XMFLOAT3 position_ = {};
		// 速度
		XMFLOAT3 velocity_ = {};
		// 加速度
		XMFLOAT3 accel_ = {};
		// 色
		XMFLOAT3 color_ = {};
		// スケール
		float scale_ = 1.0f;
		// 回転
		float rotation_ = 0.0f;
		//アルファ値
		float alpha_ = 1.0f;
		// 初期値
		XMFLOAT3 s_color_ = {};
		float s_scale_ = 1.0f;
		float s_rotation_ = 0.0f;
		float s_alpha_ = 1.0f;
		// 最終値
		XMFLOAT3 e_color_ = {};
		float e_scale_ = 0.0f;
		float e_rotation_ = 0.0f;
		float e_alpha_ = 0.0f;
		// 現在フレーム
		int32_t frame_ = 0;
		// 終了フレーム
		int32_t num_frame_ = 0;
	};

private: // 定数
	static const int32_t vertexCount = 65536;		// 頂点数

public: // 静的メンバ関数
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static ParticleManager* Create(ID3D12Device* device, Camera* camera, bool isSubBlend = false);

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="camera">カメラ</param>
	/// <param name="isSubBlend">減算合成フラグ</param>
	/// <returns>インスタンス</returns>
	static std::unique_ptr<ParticleManager> UniquePtrCreate(ID3D12Device* device, Camera* camera, bool isSubBlend = false);

public: // メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="camera">カメラ</param>
	ParticleManager(ID3D12Device* device, Camera* camera);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	void Initialize(bool isSubBlend);
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList * cmdList);

	/// <summary>
	/// パーティクルの追加
	/// </summary>
	/// <param name="life">生存時間</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">速度</param>
	/// <param name="accel">加速度</param>
	/// <param name="start_scale">開始時スケール</param>
	/// <param name="end_scale">終了時スケール</param>
	/// <param name="start_color">開始時カラー</param>
	/// <param name="end_color">終了時カラー</param>
	/// <param name="start_alpha">開始時アルファ値</param>
	/// <param name="end_alpha">終了時アルファ値</param>
	void Add(int32_t life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale = 1.0f, float end_scale = 0.0f, XMFLOAT3 start_color = {1.0f, 1.0f, 1.0f}, XMFLOAT3 end_color = {0.0f, 0.0f, 0.0f}, float start_alpha = 1.0f, float end_alpha = 0.0f);

	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	/// <returns></returns>
	void InitializeDescriptorHeap();

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	void InitializeGraphicsPipeline(bool isSubBlend);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>
	void LoadTexture(const std::string& textureName = "defaultEffect");

	/// <summary>
	/// モデル作成
	/// </summary>
	void CreateModel();

private: // メンバ変数
	// デバイス
	ID3D12Device* device_ = nullptr;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize_ = 0u;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature_;
	// パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate_;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap_;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff_;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff_;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV_;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV_;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView_;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	// パーティクル配列
	std::forward_list<Particle> particles_;
	// カメラ
	Camera* camera_ = nullptr;

};