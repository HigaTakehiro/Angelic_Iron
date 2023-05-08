#include "Sprite.h"
#include <cassert>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device* Sprite::device_ = nullptr;
UINT Sprite::descriptorHandleIncrementSize_;
ID3D12GraphicsCommandList* Sprite::cmdList_ = nullptr;
ComPtr<ID3D12RootSignature> Sprite::rootSignature_;
ComPtr<ID3D12PipelineState> Sprite::pipelineState_;
XMMATRIX Sprite::matProjection_;
ComPtr<ID3D12DescriptorHeap> Sprite::descHeap_;
ComPtr<ID3D12Resource> Sprite::texBuff_[srvCount];

bool Sprite::StaticInitialize(ID3D12Device* device_, int32_t window_width, int32_t window_height) {
	//nullチェック
	assert(device_);

	Sprite::device_ = device_;

	//デスクリプタサイズを取得
	descriptorHandleIncrementSize_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	HRESULT result;

	ComPtr<ID3DBlob> vsBlob = nullptr; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob = nullptr; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object2d/SpriteVS.hlsl",  // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object2d/SpritePS.hlsl",   // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,      0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};

	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
	//サンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	//ラスタライザステート
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;              // 背面カリングをしない

	// レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = gpipeline.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // 標準設定
	blenddesc.BlendEnable = true;                   // ブレンドを有効にする
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;    // 加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;      // ソースの値を100% 使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;    // デストの値を   0% 使う
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;             // 加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;         // ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;    // 1.0f-ソースのアルファ値

	// デプスステンシルステートの設定
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthEnable = false;    // 深度テストをしない
	//gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;       // 常に上書きルール
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	//頂点レイアウトの設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);
	//形状設定(三角形)
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1; // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0～255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

	// ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[2];
	rootparams[0].InitAsConstantBufferView(0); // 定数バッファビューとして初期化(b0レジスタ)
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV);

	// スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定でのシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	if (FAILED(result)) {
		assert(0);
		return false;
	}
	// ルートシグネチャの生成
	result = device_->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	gpipeline.pRootSignature = rootSignature_.Get();
	//グラフィックスパイプラインの生成
	result = device_->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineState_));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//射影行列計算
	matProjection_ = XMMatrixOrthographicOffCenterLH(
		0.0f, (float)window_width,
		(float)window_height, 0.0f,
		0.0f, 1.0f
	);

	//デスクリプタヒープを生成 
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NumDescriptors = srvCount;
	result = device_->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap_));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	return true;
}

bool Sprite::LoadTexture(UINT texnumber, const wchar_t* filename) {
	//nullチェック
	assert(device_);

	HRESULT result;
	//WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);

	const Image* img = scratchImg.GetImage(0, 0, 0); // 生データ抽出

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//テクスチャ用バッファの生成
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&texBuff_[texnumber]));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//テクスチャバッファにデータ転送
	result = texBuff_[texnumber]->WriteToSubresource(
		0,
		nullptr, // 全領域へコピー
		img->pixels,    // 元データアドレス
		(UINT)img->rowPitch,    // 1ラインサイズ
		(UINT)img->slicePitch   // 1枚サイズ
	);

	//シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	//ヒープのtexnumber番目にシェーダーリソースビュー作成
	device_->CreateShaderResourceView(
		texBuff_[texnumber].Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap_->GetCPUDescriptorHandleForHeapStart(), texnumber, device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	return true;
}

void Sprite::PreDraw(ID3D12GraphicsCommandList* cmdList_) {
	//PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(Sprite::cmdList_ == nullptr);
	//コマンドリストをセット
	Sprite::cmdList_ = cmdList_;
	//パイプラインステートの設定
	cmdList_->SetPipelineState(pipelineState_.Get());
	//ルートシグネチャの設定
	cmdList_->SetGraphicsRootSignature(rootSignature_.Get());
	//プリミティブ形状を設定
	cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Sprite::PostDraw() {
	//コマンドリストを解除
	Sprite::cmdList_ = nullptr;
}

Sprite* Sprite::Create(UINT texNumber_, XMFLOAT2 position_, XMFLOAT4 color_, XMFLOAT2 anchorpoint_, bool isFlipX_, bool isFlipY_) {
	XMFLOAT2 size_ = { 100.0f, 100.0f };

	if (texBuff_[texNumber_]) {
		//テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = texBuff_[texNumber_]->GetDesc();
		//スプライトのサイズをテクスチャのサイズに設定
		size_ = { (float)resDesc.Width, (float)resDesc.Height };
	}

	//Spriteのインスタンスを生成
	Sprite* sprite = new Sprite(texNumber_, position_, size_, color_, anchorpoint_, isFlipX_, isFlipY_);
	if (sprite == nullptr) {
		return nullptr;
	}

	//初期化
	if (!sprite->Initialize()) {
		delete sprite;
		assert(0);
		return nullptr;
	}

	return sprite;
}

std::unique_ptr<Sprite> Sprite::UniquePtrCreate(UINT texNumber_, XMFLOAT2 position_, XMFLOAT4 color_, XMFLOAT2 anchorpoint_, bool isFlipX_, bool isFlipY_)
{
	XMFLOAT2 size_ = { 100.0f, 100.0f };

	if (texBuff_[texNumber_]) {
		//テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = texBuff_[texNumber_]->GetDesc();
		//スプライトのサイズをテクスチャのサイズに設定
		size_ = { (float)resDesc.Width, (float)resDesc.Height };
	}

	//Spriteのインスタンスを生成
	std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>(texNumber_, position_, size_, color_, anchorpoint_, isFlipX_, isFlipY_);
	if (sprite == nullptr) {
		return nullptr;
	}

	//初期化
	if (!sprite->Initialize()) {
		assert(0);
		return nullptr;
	}

	return sprite;
}

Sprite::Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY) {
	position_ = position;
	size_ = size;
	anchorpoint_ = anchorpoint;
	matWorld_ = XMMatrixIdentity();
	color_ = color;
	texNumber_ = texNumber;
	isFlipX_ = isFlipX;
	isFlipY_ = isFlipY;
	texSize_ = size_;
}

bool Sprite::Initialize() {
	//nullチェック
	assert(device_);

	HRESULT result = S_FALSE;

	// 頂点バッファ生成
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) * vertNum),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff_));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	// 頂点バッファデータ転送
	TransferVertices();

	// 頂点バッファビューの作成
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = sizeof(VertexPosUv) * 4;
	vbView_.StrideInBytes = sizeof(VertexPosUv);

	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));

	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);
	constMap->color_ = XMFLOAT4(1, 1, 1, 1); // 色指定（RGBA）
	if (SUCCEEDED(result)) {
		constMap->color_ = color_;
		constMap->mat_ = matProjection_;
		constBuff_->Unmap(0, nullptr);
	}

	return true;
}

void Sprite::SetRotation(float rotation) {
	rotation_ = rotation;

	//頂点バッファへのデータ転送
	TransferVertices();
}

void Sprite::SetPosition(XMFLOAT2 position) {
	position_ = position;

	//頂点バッファへのデータ転送
	TransferVertices();
}

void Sprite::SetSize(XMFLOAT2 size) {
	size_ = size;

	//頂点バッファへのデータ転送
	TransferVertices();
}

void Sprite::SetAnchorPoint(XMFLOAT2 anchorpoint) {
	anchorpoint_ = anchorpoint;

	//頂点バッファへのデータ転送
	TransferVertices();
}

void Sprite::SetIsFlipX(bool isFlipX) {
	isFlipX_ = isFlipX;

	//頂点バッファへのデータ転送
	TransferVertices();
}

void Sprite::SetIsFlipY(bool isFlipY) {
	isFlipY_ = isFlipY;

	//頂点バッファへのデータ転送
	TransferVertices();
}

void Sprite::SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize) {
	texBase_ = texBase;
	texSize_ = texSize;

	//頂点バッファへのデータ転送
	TransferVertices();
}

void Sprite::Draw() {
	// ワールド行列の更新
	this->matWorld_ = XMMatrixIdentity();
	// Z軸回転
	this->matWorld_ *= XMMatrixRotationZ(XMConvertToRadians(rotation_));
	// 平行移動
	this->matWorld_ *= XMMatrixTranslation(position_.x, position_.y, 0.0f);

	// 定数バッファに転送
	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap);
	color_.w = alpha_;
	if (SUCCEEDED(result)) {
		constMap->mat_ = matWorld_ * matProjection_;
		constMap->color_ = color_;
		this->constBuff_->Unmap(0, nullptr);
	}

	//頂点バッファの設定
	cmdList_->IASetVertexBuffers(0, 1, &this->vbView_);
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap_.Get() };
	//デスクリプタヒープをセット
	cmdList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	// 定数バッファをセット
	cmdList_->SetGraphicsRootConstantBufferView(0, this->constBuff_->GetGPUVirtualAddress());
	// シェーダリソースビューをセット
	cmdList_->SetGraphicsRootDescriptorTable(
		1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(
			descHeap_->GetGPUDescriptorHandleForHeapStart(),
			this->texNumber_,
			descriptorHandleIncrementSize_
		)
	);
	//描画
	cmdList_->DrawInstanced(4, 1, 0, 0);

}

void Sprite::TransferVertices() {
	HRESULT result = S_FALSE;

	//   左下、左上、右下、右上
	enum { LB, LT, RB, RT };

	//左右反転
	float left = (0.0f - anchorpoint_.x);
	if (isLeftSizeCorrection_) {
		left *= size_.x;
	}
	float right = (1.0f - anchorpoint_.x);
	if (isRightSizeCorrection_) {
		right *= size_.x;
	}
	float top = (0.0f - anchorpoint_.y) * size_.y;
	float bottom = (1.0f - anchorpoint_.y) * size_.y;
	if (isFlipX_) {
		left = -left;
		right = -right;
	}
	//上下反転
	if (isFlipY_) {
		top = -top;
		bottom = -bottom;
	}

	//頂点データ
	VertexPosUv vertices[vertNum];

	vertices[LB].pos_ = { left, bottom, 0.0f }; //左下
	vertices[LT].pos_ = { left, top, 0.0f }; //左上
	vertices[RB].pos_ = { right, bottom, 0.0f }; //右下
	vertices[RT].pos_ = { right, top, 0.0f }; //右上

	//テクスチャ情報取得
	if (texBuff_[texNumber_]) {
		D3D12_RESOURCE_DESC resDesc = texBuff_[texNumber_]->GetDesc();

		float tex_left = texBase_.x / resDesc.Width;
		float tex_right = (texBase_.x + texSize_.x) / resDesc.Width;
		float tex_top = texBase_.y / resDesc.Height;
		float tex_bottom = (texBase_.y + texSize_.y) / resDesc.Height;

		vertices[LB].uv_ = { tex_left, tex_bottom };
		vertices[LT].uv_ = { tex_left, tex_top };
		vertices[RB].uv_ = { tex_right, tex_bottom };
		vertices[RT].uv_ = { tex_right, tex_top };
	}

	//頂点バッファへのデータ転送
	VertexPosUv* vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff_->Unmap(0, nullptr);
	}
}