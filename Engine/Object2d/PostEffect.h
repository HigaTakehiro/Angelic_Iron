#pragma once
#include "Sprite.h"

class PostEffect : public Sprite
{
public: //構造体
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

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画コマンド
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, const float maxTime, PostEffectNo pipelineNo = PostEffectNo::NONE, bool isRoop = false);

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// パイプライン生成
	/// </summary>
	void CreateGraphicsPipelineState();

	/// <summary>
	/// ピクセルシェーダー読み込み
	/// </summary>
	void LoadPS(const wchar_t* psName, ComPtr<ID3DBlob>& psBlob);

	/// <summary>
	/// ブラーが適用されない範囲セット
	/// </summary>
	/// <param name="mask">ブラーが適用されない範囲</param>
	void SetMask(float mask) { mask_ = mask; }

	/// <summary>
	///	ブラー発生中心位置をセット
	/// </summary>
	/// <param name="blurCenter">ブラー発生中心位置</param>
	void SetBlurCenter(DirectX::XMFLOAT2 blurCenter) { blurCenter_ = blurCenter; }

private: //静的メンバ変数
	static const int32_t texSize = 8;

public: //メンバ変数
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff_[texSize];
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV_;
	//深度バッファ
	ComPtr<ID3D12Resource> depthBuff_;
	//RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV_;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV_;
	//グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> pipelineState_[texSize];
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature_;

private: //静的メンバ変数
	//画面クリアカラー
	static const float clearColor_[4];

private: //メンバ変数
	PostEffectNo nowPipelineNo_ = PostEffectNo::NONE;
	float timer_ = 0.0f;
	//ブラーが適用されない範囲
	float mask_;
	//ブラーの中心
	DirectX::XMFLOAT2 blurCenter_;
	//定数バッファ転送用
	ComPtr<ID3D12Resource> constBuffB0_;

private: //メンバ関数
	/// <summary>
	/// テクスチャ作成
	/// </summary>
	void TexCreate();

	/// <summary>
	/// SRV作成
	/// </summary>
	void SRVCreate();

	/// <summary>
	/// RTV作成
	/// </summary>
	void RTVCreate();

	/// <summary>
	/// 深度バッファ作成
	/// </summary>
	void DepthCreate();

	/// <summary>
	/// DSV作成
	/// </summary>
	void DSVCreate();

};