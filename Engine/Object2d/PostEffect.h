#pragma once
#include "Sprite.h"

class PostEffect : public Sprite
{
public: //構造体
	struct ConstBuffDataB0 {
		float time;
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
	void Draw(ID3D12GraphicsCommandList* cmdList, int pipelineNo = 0);

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

public: //メンバ変数
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff[2];
	//SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	//RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> pipelineState[2];
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;

private: //静的メンバ変数
	//画面クリアカラー
	static const float clearColor[4];

private: //メンバ変数
	int nowPipelineNo = 0;
	//定数バッファ転送用
	ComPtr<ID3D12Resource> constBuffB0;

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

