#pragma once
#include "DirectXSetting.h"
#include "Vector3.h"
#include "Object3d.h"
#include "Camera.h"

class ShadowMap
{
public: //エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //構造体
	//定数バッファデータ(B0)
	struct ConstBuffDataB0 {
		DirectX::XMMATRIX wvp;
		DirectX::XMMATRIX world;
	};

	//定数バッファデータ(B1)
	struct ConstBuffDataB1 {
		DirectX::XMMATRIX lightVP;
		DirectX::XMVECTOR lightColor;
		Vector3 lightDir;
	};

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(Object3d* obj, Camera* camera);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private: //メンバ関数

	/// <summary>
	/// テクスチャ用デスクリプタヒープ作成
	/// </summary>
	bool TexHeapCreate();

	/// <summary>
	/// シャドウマップ用バッファ作成
	/// </summary>
	bool ShadowBuffCreate();

	/// <summary>
	/// シャドウマップ用デスクリプタヒープ作成
	/// </summary>
	bool ShadowHeapCreate();

	/// <summary>
	/// グラフィックスパイプライン作成
	/// </summary>
	bool GraphicsPipelineCrate();

private: //メンバ変数
	//シャドウマップ用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> shadowHeap_;
	//テクスチャ用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> texHeap_;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffB0_;
	//シャドウマップ用バッファ
	ComPtr<ID3D12Resource> shadowBuff_;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature_;
	//パイプラインステート
	ComPtr<ID3D12PipelineState> pipelinestate_;

};