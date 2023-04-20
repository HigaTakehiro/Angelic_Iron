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
	/// テクスチャ用デスクリプタヒープ作成
	/// </summary>
	bool TexHeapCreate();

	/// <summary>
	/// テクスチャ用バッファ作成
	/// </summary>
	bool TexBuffCreate();

	/// <summary>
	/// シャドウマップ用バッファ作成
	/// </summary>
	bool ShadowBuffCreate();

	/// <summary>
	/// シャドウマップ用デスクリプタヒープ作成
	/// </summary>
	bool ShadowHeapCreate();

private: //メンバ変数
	//シャドウマップ用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> shadowHeap_;
	//テクスチャ用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> texHeap_;
	//シャドウマップ用バッファ
	ComPtr<ID3D12Resource> shadowBuff_;
	//テクスチャ用バッファ
	ComPtr<ID3D12Resource> texBuff_;
};