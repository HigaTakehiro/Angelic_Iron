#include "ShadowMap.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

void ShadowMap::Initialize()
{
	if (!ShadowHeapCreate()) {
		assert(0);
		return;
	}
	if (!ShadowBuffCreate()) {
		assert(0);
		return;
	}
	if (!TexHeapCreate()) {
		assert(0);
		return;
	}
	if (!GraphicsPipelineCrate()) {
		assert(0);
		return;
	}
}

void ShadowMap::Update(Object3d* obj)
{
	// 定数バッファへデータ転送
	ConstBuffDataB0* constMap0 = nullptr;
	if (SUCCEEDED(constBuffB0_->Map(0, nullptr, (void**)&constMap0))) {
		constMap0->wvp = obj->GetMatWorld() * Camera::GetMatView() * Camera::GetMatProjection();
		constMap0->world = obj->GetMatWorld();
		constBuffB0_->Unmap(0, nullptr);
	}

	ConstBuffDataB1* constMap1 = nullptr;
	if (SUCCEEDED(constBuffB0_->Map(0, nullptr, (void**)&constMap1))) {
		constMap1->lightColor = { 1, 1, 1, 1 };
		constMap1->lightVP.r[0] = { 0, 0, 0, 0 };
		constMap1->lightVP.r[1] = { 0, 0, 0, 0 };
		constMap1->lightVP.r[2] = { 0, 0, 0, 0 };
		constMap1->lightVP.r[3] = { 0, 5, 0, 0 };
		constMap1->lightDir = { 0, 1, 0 };
		constBuffB0_->Unmap(1, nullptr);
	}
}

void ShadowMap::Draw()
{
	DirectXSetting::GetIns()->GetCmdList()->SetPipelineState(pipelinestate_.Get());
	DirectXSetting::GetIns()->GetCmdList()->SetGraphicsRootSignature(rootsignature_.Get());
	DirectXSetting::GetIns()->GetCmdList()->SetGraphicsRootConstantBufferView(0, constBuffB0_->GetGPUVirtualAddress());
}

bool ShadowMap::TexHeapCreate()
{
	HRESULT result;

	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.NumDescriptors = 2;
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NodeMask = 0;
	result = DirectXSetting::GetIns()->GetDev()->CreateDescriptorHeap(
		&descHeapDesc, IID_PPV_ARGS(&texHeap_)
	);

	//シェーダーリソースビュー作成
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle{};
	D3D12_SHADER_RESOURCE_VIEW_DESC rvDesc{};

	rvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	rvDesc.Texture2D.MipLevels = 1;
	rvDesc.Texture2D.MostDetailedMip = 0;
	rvDesc.Texture2D.PlaneSlice = 0;
	rvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	rvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	srvHandle = texHeap_->GetCPUDescriptorHandleForHeapStart();
	DirectXSetting::GetIns()->GetDev()->CreateShaderResourceView(
		shadowBuff_.Get(), &rvDesc, srvHandle
	);

	rvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvHandle.ptr += DirectXSetting::GetIns()->GetDev()->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
	);
	DirectXSetting::GetIns()->GetDev()->CreateShaderResourceView(shadowBuff_.Get(), &rvDesc, srvHandle);

	return true;
}

bool ShadowMap::ShadowBuffCreate()
{
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.Texture2D.MipSlice = 0;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	DirectXSetting::GetIns()->GetDev()->CreateDepthStencilView(
		shadowBuff_.Get(), &dsvDesc,
		shadowHeap_->GetCPUDescriptorHandleForHeapStart()
	);

	D3D12_SHADER_RESOURCE_VIEW_DESC resourceViewDesc{};
	resourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
	resourceViewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	resourceViewDesc.Texture2D.MipLevels = 1;
	resourceViewDesc.Texture2D.MostDetailedMip = 0;
	resourceViewDesc.Texture2D.PlaneSlice = 0;
	resourceViewDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	resourceViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	DirectXSetting::GetIns()->GetDev()->CreateShaderResourceView(
		shadowBuff_.Get(), &resourceViewDesc,
		texHeap_->GetCPUDescriptorHandleForHeapStart()
	);

	return true;
}

bool ShadowMap::ShadowHeapCreate()
{
	HRESULT result;

	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.NumDescriptors = 1; //1つ
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	descHeapDesc.NodeMask = 0;
	result = DirectXSetting::GetIns()->GetDev()->CreateDescriptorHeap(
		&descHeapDesc, IID_PPV_ARGS(&shadowHeap_));
	if (FAILED(result)) {
		return false;
	}

	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	result = DirectXSetting::GetIns()->GetDev()->CreateDescriptorHeap(
		&descHeapDesc, IID_PPV_ARGS(&texHeap_)
	);

	D3D12_HEAP_PROPERTIES heapProp{};
	D3D12_RESOURCE_DESC resourceDesc{};
	D3D12_CLEAR_VALUE clearValue{};
	heapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProp.CreationNodeMask = 0;
	heapProp.VisibleNodeMask = 0;

	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Width = 1024;
	resourceDesc.Height = 1024;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 0;
	resourceDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.SampleDesc.Quality = 0;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	clearValue.Format = DXGI_FORMAT_D32_FLOAT;
	clearValue.DepthStencil.Depth = 1.0f;
	clearValue.DepthStencil.Stencil = 0;

	result = DirectXSetting::GetIns()->GetDev()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBuffDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuffB0_)
	);
	if (FAILED(result)) {
		return false;
	}

	return true;
}

bool ShadowMap::GraphicsPipelineCrate()
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object3d/obj/ShadowMapVS.hlsl",   // シェーダファイル名
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
		return result;
	}

	D3D12_DESCRIPTOR_RANGE		range[2]{};
	D3D12_ROOT_PARAMETER		root_parameters[4]{};
	D3D12_ROOT_SIGNATURE_DESC	root_signature_desc{};
	D3D12_STATIC_SAMPLER_DESC	sampler_desc[2]{};
	ComPtr<ID3DBlob> blob{};

	//変換行列用の定数バッファ	
	root_parameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	root_parameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	root_parameters[0].Descriptor.ShaderRegister = 0;
	root_parameters[0].Descriptor.RegisterSpace = 0;

	//ライト用の定数バッファ
	root_parameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	root_parameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	root_parameters[1].Descriptor.ShaderRegister = 1;
	root_parameters[1].Descriptor.RegisterSpace = 0;


	//テクスチャ
	range[0].NumDescriptors = 2;
	range[0].BaseShaderRegister = 0;
	range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	root_parameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	root_parameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	root_parameters[2].DescriptorTable.NumDescriptorRanges = 1;
	root_parameters[2].DescriptorTable.pDescriptorRanges = &range[0];


	//サンプラ
	sampler_desc[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	sampler_desc[0].MipLODBias = 0.0f;
	sampler_desc[0].MaxAnisotropy = 16;
	sampler_desc[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	sampler_desc[0].BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	sampler_desc[0].MinLOD = 0.0f;
	sampler_desc[0].MaxLOD = D3D12_FLOAT32_MAX;
	sampler_desc[0].ShaderRegister = 0;
	sampler_desc[0].RegisterSpace = 0;
	sampler_desc[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	sampler_desc[1].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	sampler_desc[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	sampler_desc[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	sampler_desc[1].MipLODBias = 0.0f;
	sampler_desc[1].MaxAnisotropy = 16;
	sampler_desc[1].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	sampler_desc[1].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
	sampler_desc[1].MinLOD = 0.0f;
	sampler_desc[1].MaxLOD = D3D12_FLOAT32_MAX;
	sampler_desc[1].ShaderRegister = 1;
	sampler_desc[1].RegisterSpace = 0;
	sampler_desc[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;


	root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	root_signature_desc.NumParameters = _countof(root_parameters);
	root_signature_desc.pParameters = root_parameters;
	root_signature_desc.NumStaticSamplers = _countof(sampler_desc);
	root_signature_desc.pStaticSamplers = sampler_desc;

	result = D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &blob, nullptr);
	if (FAILED(result)) {
		return result;
	}
	result = DirectXSetting::GetIns()->GetDev()->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&rootsignature_));

	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object3d/obj/ShadowMapPS.hlsl",   // シェーダファイル名
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
		return result;
	}

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
	gpipeline.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	gpipeline.VS.BytecodeLength = vsBlob->GetBufferSize();

	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	gpipeline.SampleDesc.Count = 1;
	gpipeline.SampleDesc.Quality = 0;
	gpipeline.SampleMask = UINT_MAX;

	gpipeline.NumRenderTargets = 1;
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;

	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.pRootSignature = rootsignature_.Get();

	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
	gpipeline.RasterizerState.FrontCounterClockwise = FALSE;
	gpipeline.RasterizerState.DepthBias = 0;
	gpipeline.RasterizerState.DepthBiasClamp = 0;
	gpipeline.RasterizerState.SlopeScaledDepthBias = 0;
	gpipeline.RasterizerState.DepthClipEnable = TRUE;
	gpipeline.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	gpipeline.RasterizerState.AntialiasedLineEnable = FALSE;
	gpipeline.RasterizerState.MultisampleEnable = FALSE;


	//ブレンドステートの設定
	for (int i = 0; i < _countof(gpipeline.BlendState.RenderTarget); ++i) {
		gpipeline.BlendState.RenderTarget[i].BlendEnable = FALSE;
		gpipeline.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_ONE;
		gpipeline.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_ZERO;
		gpipeline.BlendState.RenderTarget[i].BlendOp = D3D12_BLEND_OP_ADD;
		gpipeline.BlendState.RenderTarget[i].SrcBlendAlpha = D3D12_BLEND_ONE;
		gpipeline.BlendState.RenderTarget[i].DestBlendAlpha = D3D12_BLEND_ZERO;
		gpipeline.BlendState.RenderTarget[i].BlendOpAlpha = D3D12_BLEND_OP_ADD;
		gpipeline.BlendState.RenderTarget[i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		gpipeline.BlendState.RenderTarget[i].LogicOpEnable = FALSE;
		gpipeline.BlendState.RenderTarget[i].LogicOp = D3D12_LOGIC_OP_CLEAR;
	}
	gpipeline.BlendState.AlphaToCoverageEnable = FALSE;
	gpipeline.BlendState.IndependentBlendEnable = FALSE;


	//デプスステンシルステートの設定
	gpipeline.DepthStencilState.DepthEnable = TRUE;								//深度テストあり
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	gpipeline.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	gpipeline.DepthStencilState.StencilEnable = FALSE;							//ステンシルテストなし
	gpipeline.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
	gpipeline.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

	gpipeline.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	gpipeline.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	gpipeline.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	gpipeline.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	gpipeline.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	gpipeline.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	gpipeline.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	gpipeline.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	result = DirectXSetting::GetIns()->GetDev()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate_));

	if (FAILED(result)) {
		return result;
	}

	return true;
}

