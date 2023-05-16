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

void ShadowMap::Update(Object3d* obj, Camera* camera)
{
	// �萔�o�b�t�@�փf�[�^�]��
	ConstBuffDataB0* constMap0 = nullptr;
	if (SUCCEEDED(constBuffB0_->Map(0, nullptr, (void**)&constMap0))) {
		constMap0->wvp = obj->GetMatWorld() * camera->GetMatView() * camera->GetMatProjection();
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
		constMap1->lightDir = { 0, -1, 0 };
		constBuffB0_->Unmap(1, nullptr);
	}
}

void ShadowMap::Draw()
{
	DirectXSetting::GetIns()->GetCmdList()->SetGraphicsRootSignature(rootsignature_.Get());
	//DirectXSetting::GetIns()->GetCmdList()->SetPipelineState(pipelinestate_.Get());
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

	//�V�F�[�_�[���\�[�X�r���[�쐬
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
	descHeapDesc.NumDescriptors = 1; //1��
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
	ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob;	// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g

	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object3d/obj/ShadowMapVS.hlsl",   // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		return result;
	}

	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object3d/obj/ShadowMapPS.hlsl",   // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		return result;
	}

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ // xy���W(1�s�ŏ������ق������₷��)
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ // �@���x�N�g��(1�s�ŏ������ق������₷��)
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ // uv���W(1�s�ŏ������ق������₷��)
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	// �O���t�B�b�N�X�p�C�v���C���̗����ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// �T���v���}�X�N
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
	// ���X�^���C�U�X�e�[�g
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	/*gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	gpipeline.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;*/
	// �f�v�X�X�e���V���X�e�[�g
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	// �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RBGA�S�Ẵ`�����l����`��
	blenddesc.BlendEnable = true;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	// �u�����h�X�e�[�g�̐ݒ�
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	// �[�x�o�b�t�@�̃t�H�[�}�b�g
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// ���_���C�A�E�g�̐ݒ�
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// �}�`�̌`��ݒ�i�O�p�`�j
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;	// �`��Ώۂ�1��
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0�`255�w���RGBA
	gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �f�X�N���v�^�����W
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 ���W�X�^

	// ���[�g�p�����[�^
	CD3DX12_ROOT_PARAMETER rootparams[4];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[3].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);

	// �X�^�e�B�b�N�T���v���[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ���[�g�V�O�l�`���̐ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// �o�[�W������������̃V���A���C�Y
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ���[�g�V�O�l�`���̐���
	result = DirectXSetting::GetIns()->GetDev()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootsignature_));
	if (FAILED(result)) {
		return result;
	}

	gpipeline.pRootSignature = rootsignature_.Get();

	// �O���t�B�b�N�X�p�C�v���C���̐���
	result = DirectXSetting::GetIns()->GetDev()->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelinestate_));

	if (FAILED(result)) {
		return result;
	}

	return true;
}

