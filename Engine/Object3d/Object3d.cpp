#include "Object3d.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device* Object3d::device_ = nullptr;
ID3D12GraphicsCommandList* Object3d::cmdList_ = nullptr;
ComPtr<ID3D12RootSignature> Object3d::rootsignature_;
//ComPtr<ID3D12RootSignature> Object3d::shadowRootSignature_;
ComPtr<ID3D12PipelineState> Object3d::pipelinestate_[] = {};
LightGroup* Object3d::light_ = nullptr;
CollisionManager* Object3d::colManager_ = nullptr;

bool Object3d::StaticInitialize(ID3D12Device* device, int32_t window_width, int32_t window_height)
{
	// nullptrチェック
	assert(device);

	Object3d::device_ = device;

	Model::StaticInitialize(device_);

	// カメラ初期化
	Camera::InitializeCamera(window_width, window_height);

	// パイプライン初期化
	InitializeGraphicsPipeline();
	//InitializeShadowBuff();

	return true;
}

void Object3d::PreDraw(ID3D12GraphicsCommandList* cmdList_)
{
	// PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(Object3d::cmdList_ == nullptr);

	// コマンドリストをセット
	Object3d::cmdList_ = cmdList_;

	// プリミティブ形状を設定
	cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3d::PostDraw()
{
	// コマンドリストを解除
	Object3d::cmdList_ = nullptr;
}

Object3d* Object3d::Create(Model* model_)
{
	// 3Dオブジェクトのインスタンスを生成
	Object3d* object3d = new Object3d();
	if (object3d == nullptr) {
		return nullptr;
	}

	object3d->SetModel(model_);

	// 初期化
	if (!object3d->Initialize()) {
		delete object3d;
		assert(0);
		return nullptr;
	}

	return object3d;
}

std::unique_ptr<Object3d> Object3d::UniquePtrCreate(Model* model_)
{
	// 3Dオブジェクトのインスタンスを生成
	std::unique_ptr<Object3d> object3d = std::make_unique<Object3d>();
	if (object3d == nullptr) {
		return nullptr;
	}

	object3d->SetModel(model_);

	// 初期化
	if (!object3d->Initialize()) {
		assert(0);
		return nullptr;
	}

	return object3d;
}

bool Object3d::InitializeGraphicsPipeline()
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	for (int32_t i = 0; i < vsSize; i++) {
		//頂点シェーダーの読み込み
		if ((VSPipelineNo)i == VSPipelineNo::Normal) {
			LoadVS(L"Engine/Resources/shaders/Object3d/obj/OBJVertexShader.hlsl", vsBlob);
		}
		else if ((VSPipelineNo)i == VSPipelineNo::Wave) {
			LoadVS(L"Engine/Resources/shaders/Object3d/obj/WaveVS.hlsl", vsBlob);
		}
		//ピクセルシェーダーの読み込み
		LoadPS(L"Engine/Resources/shaders/Object3d/obj/OBJPixelShader.hlsl", psBlob);

		// 頂点レイアウト
		D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
			{ // xy座標(1行で書いたほうが見やすい)
				"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			},
			{ // 法線ベクトル(1行で書いたほうが見やすい)
				"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			},
			{ // uv座標(1行で書いたほうが見やすい)
				"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
			},
		};

		// グラフィックスパイプラインの流れを設定
		D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
		gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
		gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

		// サンプルマスク
		gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
		// ラスタライザステート
		gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		/*gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;*/
		// デプスステンシルステート
		gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

		// レンダーターゲットのブレンド設定
		D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
		blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RBGA全てのチャンネルを描画
		blenddesc.BlendEnable = true;
		blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

		blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

		// ブレンドステートの設定
		gpipeline.BlendState.RenderTarget[0] = blenddesc;

		// 深度バッファのフォーマット
		gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

		// 頂点レイアウトの設定
		gpipeline.InputLayout.pInputElementDescs = inputLayout;
		gpipeline.InputLayout.NumElements = _countof(inputLayout);

		// 図形の形状設定（三角形）
		gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

		gpipeline.NumRenderTargets = 1;	// 描画対象は1つ
		gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0～255指定のRGBA
		gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

		// デスクリプタレンジ
		CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
		descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

		// ルートパラメータ
		CD3DX12_ROOT_PARAMETER rootparams[4];
		rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
		rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
		rootparams[2].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
		rootparams[3].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);

		// スタティックサンプラー
		CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

		// ルートシグネチャの設定
		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		ComPtr<ID3DBlob> rootSigBlob;
		// バージョン自動判定のシリアライズ
		result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
		// ルートシグネチャの生成
		result = device_->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature_));
		if (FAILED(result)) {
			return result;
		}

		gpipeline.pRootSignature = rootsignature_.Get();

		// グラフィックスパイプラインの生成
		result = device_->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate_[i]));

		if (FAILED(result)) {
			return result;
		}
	}
	
	if (FAILED(result)) {
		return result;
	}

	return true;
}

bool Object3d::Initialize()
{
	// nullptrチェック
	assert(device_);

	HRESULT result;
	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0_));

	//result = device_->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&shadowBuff_));

	//result = device_->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&lightBuff_));

	model_->Initialize();
	colManager_->AddObj(*this);

	return true;
}

void Object3d::Update(const float maxTime)
{
	timer_++;
	if (timer_ >= maxTime) {
		timer_ = 0.0f;
	}
	isHit_ = false;

	XMMATRIX matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation_.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation_.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation_.y));
	matTrans = XMMatrixTranslation(position_.x, position_.y, position_.z);

	// ワールド行列の合成
	matWorld_ = XMMatrixIdentity(); // 変形をリセット

	matWorld_ *= matScale; // ワールド行列にスケーリングを反映
	matWorld_ *= matRot; // ワールド行列に回転を反映
	if (isBillboard_) {
		matWorld_ *= Camera::GetMatBillboard(); //ワールド行列にビルボード行列を掛ける
	}
	if (isBillboardY_) {
		matWorld_ *= Camera::GetMatBillboardY();
	}
	matWorld_ *= matTrans; // ワールド行列に平行移動を反映

	// 親オブジェクトがあれば
	if (parent_ != nullptr) {
		// 親オブジェクトのワールド行列を掛ける
		matWorld_ *= parent_->GetMatWorld();
	}

	if (cameraParent_ != nullptr) {
		matWorld_ *= cameraParent_->GetMatWorld();
	}

	// 定数バッファへデータ転送
	ConstBufferDataB0* constMap0 = nullptr;
	if (SUCCEEDED(constBuffB0_->Map(0, nullptr, (void**)&constMap0))) {
		constMap0->viewproj_ = camera_->GetMatView() * camera_->GetMatProjection();
		constMap0->world_ = matWorld_;
		constMap0->color_ = color_;
		constMap0->cameraPos_ = camera_->GetEye();
		constMap0->time_ = timer_ / maxTime;
		constBuffB0_->Unmap(0, nullptr);
	}

	//ShadowConstBuff* shadowMap = nullptr;
	//if (SUCCEEDED(shadowBuff_->Map(0, nullptr, (void**)&shadowMap))) {
	//	shadowMap->world_ = matWorld_;
	//	shadowMap->wvp_ = matWorld_ * Camera::GetMatView() * Camera::GetMatProjection();
	//	shadowBuff_->Unmap(0, nullptr);
	//}

	//LightConstBuff* lightMap = nullptr;
	//if (SUCCEEDED(lightBuff_->Map(0, nullptr, (void**)&lightMap))) {
	//	lightMap->lightVP.r[0] = { 0, 0, 0, 0 };
	//	lightMap->lightVP.r[1] = { 0, 0, 0, 0 };
	//	lightMap->lightVP.r[2] = { 0, 0, 0, 0 };
	//	lightMap->lightVP.r[3] = { -10, 5, 0, 0 };
	//	lightBuff_->Unmap(0, nullptr);
	//}

	model_->Update(model_->GetMaterial());
}

void Object3d::Draw()
{
	// nullptrチェック
	assert(device_);
	assert(Object3d::cmdList_);

	//パイプラインステートの設定
	if (isWave_) {
		cmdList_->SetPipelineState(pipelinestate_[(int32_t)VSPipelineNo::Wave].Get());
	}
	else {
		cmdList_->SetPipelineState(pipelinestate_[(int32_t)VSPipelineNo::Normal].Get());
	}
	//ルートシグネチャの設定
	cmdList_->SetGraphicsRootSignature(rootsignature_.Get());
	//定数バッファビューをセット
	cmdList_->SetGraphicsRootConstantBufferView(0, constBuffB0_->GetGPUVirtualAddress());
	
	//cmdList_->SetPipelineState(pipelinestate_[2].Get());
	//cmdList_->SetGraphicsRootSignature(shadowRootSignature_.Get());
	//cmdList_->SetGraphicsRootConstantBufferView(0, shadowBuff_->GetGPUVirtualAddress());

	light_->Draw(3);
	model_->Draw(cmdList_);

}

void Object3d::LoadVS(const wchar_t* vsName, ComPtr<ID3DBlob>& vsBlob) {
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

	result = D3DCompileFromFile(
		vsName,   // シェーダファイル名
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
		assert(0);
	}
}

void Object3d::LoadPS(const wchar_t* psName, ComPtr<ID3DBlob>& psBlob) {
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

	result = D3DCompileFromFile(
		psName,   // シェーダファイル名
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
		assert(0);
	}
}

//bool Object3d::InitializeShadowBuff()
//{
//	HRESULT result = S_FALSE;
//	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
//	ComPtr<ID3DBlob> psBlob;	// ピクセルシェーダオブジェクト
//	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト
//
//	LoadVS(L"Engine/Resources/shaders/Object3d/obj/ShadowMapVS.hlsl", vsBlob);
//	//ピクセルシェーダーの読み込み
//	LoadPS(L"Engine/Resources/shaders/Object3d/obj/ShadowMapPS.hlsl", psBlob);
//
//	// 頂点レイアウト
//	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
//		{ // xy座標(1行で書いたほうが見やすい)
//			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//		{ // 法線ベクトル(1行で書いたほうが見やすい)
//			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//		{ // uv座標(1行で書いたほうが見やすい)
//			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
//			D3D12_APPEND_ALIGNED_ELEMENT,
//			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
//		},
//	};
//
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
//
//	D3D12_DESCRIPTOR_RANGE		range[2]{};
//	D3D12_ROOT_PARAMETER		root_parameters[4]{};
//	D3D12_ROOT_SIGNATURE_DESC	root_signature_desc{};
//	D3D12_STATIC_SAMPLER_DESC	sampler_desc[2]{};
//	ComPtr<ID3DBlob> blob{};
//
//	//変換行列用の定数バッファ	
//	root_parameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//	root_parameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//	root_parameters[0].Descriptor.ShaderRegister = 0;
//	root_parameters[0].Descriptor.RegisterSpace = 0;
//
//	//ライト用の定数バッファ
//	root_parameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
//	root_parameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//	root_parameters[1].Descriptor.ShaderRegister = 1;
//	root_parameters[1].Descriptor.RegisterSpace = 0;
//
//	//テクスチャ
//	range[0].NumDescriptors = 2;
//	range[0].BaseShaderRegister = 0;
//	range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
//	range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//
//	root_parameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
//	root_parameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//	root_parameters[2].DescriptorTable.NumDescriptorRanges = 1;
//	root_parameters[2].DescriptorTable.pDescriptorRanges = &range[0];
//
//	//サンプラ
//	sampler_desc[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
//	sampler_desc[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	sampler_desc[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	sampler_desc[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
//	sampler_desc[0].MipLODBias = 0.0f;
//	sampler_desc[0].MaxAnisotropy = 16;
//	sampler_desc[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
//	sampler_desc[0].BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
//	sampler_desc[0].MinLOD = 0.0f;
//	sampler_desc[0].MaxLOD = D3D12_FLOAT32_MAX;
//	sampler_desc[0].ShaderRegister = 0;
//	sampler_desc[0].RegisterSpace = 0;
//	sampler_desc[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//
//	sampler_desc[1].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
//	sampler_desc[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
//	sampler_desc[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
//	sampler_desc[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
//	sampler_desc[1].MipLODBias = 0.0f;
//	sampler_desc[1].MaxAnisotropy = 16;
//	sampler_desc[1].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
//	sampler_desc[1].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
//	sampler_desc[1].MinLOD = 0.0f;
//	sampler_desc[1].MaxLOD = D3D12_FLOAT32_MAX;
//	sampler_desc[1].ShaderRegister = 1;
//	sampler_desc[1].RegisterSpace = 0;
//	sampler_desc[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
//
//	root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
//	root_signature_desc.NumParameters = _countof(root_parameters);
//	root_signature_desc.pParameters = root_parameters;
//	root_signature_desc.NumStaticSamplers = _countof(sampler_desc);
//	root_signature_desc.pStaticSamplers = sampler_desc;
//
//	result = D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &blob, nullptr);
//	if (FAILED(result)) {
// 		return result;
//	}
//	result = DirectXSetting::GetIns()->GetDev()->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&shadowRootSignature_));
//
//	// グラフィックスパイプラインの流れを設定
//	gpipeline.VS.pShaderBytecode = vsBlob->GetBufferPointer();
//	gpipeline.VS.BytecodeLength = vsBlob->GetBufferSize();
//
//	gpipeline.InputLayout.pInputElementDescs = inputLayout;
//	gpipeline.InputLayout.NumElements = _countof(inputLayout);
//
//	gpipeline.SampleDesc.Count = 1;
//	gpipeline.SampleDesc.Quality = 0;
//	gpipeline.SampleMask = UINT_MAX;
//
//	gpipeline.NumRenderTargets = 1;
//	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//
//	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//
//	gpipeline.pRootSignature = shadowRootSignature_.Get();
//
//	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
//	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
//	gpipeline.RasterizerState.FrontCounterClockwise = FALSE;
//	gpipeline.RasterizerState.DepthBias = 0;
//	gpipeline.RasterizerState.DepthBiasClamp = 0;
//	gpipeline.RasterizerState.SlopeScaledDepthBias = 0;
//	gpipeline.RasterizerState.DepthClipEnable = TRUE;
//	gpipeline.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
//	gpipeline.RasterizerState.AntialiasedLineEnable = FALSE;
//	gpipeline.RasterizerState.MultisampleEnable = FALSE;
//
//
//	//ブレンドステートの設定
//	for (int i = 0; i < _countof(gpipeline.BlendState.RenderTarget); ++i) {
//		gpipeline.BlendState.RenderTarget[i].BlendEnable = FALSE;
//		gpipeline.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_ONE;
//		gpipeline.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_ZERO;
//		gpipeline.BlendState.RenderTarget[i].BlendOp = D3D12_BLEND_OP_ADD;
//		gpipeline.BlendState.RenderTarget[i].SrcBlendAlpha = D3D12_BLEND_ONE;
//		gpipeline.BlendState.RenderTarget[i].DestBlendAlpha = D3D12_BLEND_ZERO;
//		gpipeline.BlendState.RenderTarget[i].BlendOpAlpha = D3D12_BLEND_OP_ADD;
//		gpipeline.BlendState.RenderTarget[i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
//		gpipeline.BlendState.RenderTarget[i].LogicOpEnable = FALSE;
//		gpipeline.BlendState.RenderTarget[i].LogicOp = D3D12_LOGIC_OP_CLEAR;
//	}
//	gpipeline.BlendState.AlphaToCoverageEnable = FALSE;
//	gpipeline.BlendState.IndependentBlendEnable = FALSE;
//
//	//デプスステンシルステートの設定
//	gpipeline.DepthStencilState.DepthEnable = TRUE;								//深度テストあり
//	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
//	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
//	gpipeline.DepthStencilState.StencilEnable = FALSE;							//ステンシルテストなし
//	gpipeline.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
//	gpipeline.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
//
//	gpipeline.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
//	gpipeline.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
//	gpipeline.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
//	gpipeline.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
//
//	gpipeline.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
//	gpipeline.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
//	gpipeline.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
//	gpipeline.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
//
//	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;
//
//	result = DirectXSetting::GetIns()->GetDev()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate_[2]));
//	return false;
//}
