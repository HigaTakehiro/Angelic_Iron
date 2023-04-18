#pragma once
#include "DirectXSetting.h"

class ShadowMap
{
public: //エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private: //メンバ関数

	/// <summary>
	/// SRV作成
	/// </summary>
	bool SRVCreate();

	/// <summary>
	/// RTV作成
	/// </summary>
	bool RTVCreate();

	/// <summary>
	/// 深度バッファ作成
	/// </summary>
	bool DepthCreate();

	/// <summary>
	/// DSV作成
	/// </summary>
	bool DSVCreate();

private: //メンバ変数
	//深度バッファ用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> depthHeap_;
	//テクスチャ用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> texHeap_;
	//シャドウマップ用バッファ
	ComPtr<ID3D12Resource> shadowBuff_;
	//深度バッファ
	ComPtr<ID3D12Resource> depthBuff_;
};