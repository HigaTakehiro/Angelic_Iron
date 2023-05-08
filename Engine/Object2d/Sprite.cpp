#include "Sprite.h"
#include <cassert>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

/// <summary>
/// �ÓI�����o�ϐ��̎���
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
	//null�`�F�b�N
	assert(device_);

	Sprite::device_ = device_;

	//�f�X�N���v�^�T�C�Y���擾
	descriptorHandleIncrementSize_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	HRESULT result;

	ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob = nullptr; // �G���[�I�u�W�F�N�g

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object2d/SpriteVS.hlsl",  // �V�F�[�_�t�@�C����
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
		exit(1);
	}

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Engine/Resources/shaders/Object2d/SpritePS.hlsl",   // �V�F�[�_�t�@�C����
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
		exit(1);
	}

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,      0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};

	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
	//�T���v���}�X�N
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
	//���X�^���C�U�X�e�[�g
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;              // �w�ʃJ�����O�����Ȃ�

	// �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = gpipeline.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // �W���ݒ�
	blenddesc.BlendEnable = true;                   // �u�����h��L���ɂ���
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;    // ���Z
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;      // �\�[�X�̒l��100% �g��
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;    // �f�X�g�̒l��   0% �g��
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;             // ���Z
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;         // �\�[�X�̃A���t�@�l
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;    // 1.0f-�\�[�X�̃A���t�@�l

	// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthEnable = false;    // �[�x�e�X�g�����Ȃ�
	//gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;       // ��ɏ㏑�����[��
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	//���_���C�A�E�g�̐ݒ�
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);
	//�`��ݒ�(�O�p�`)
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1; // �`��Ώۂ�1��
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0�`255�w���RGBA
	gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// �f�X�N���v�^�����W
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 ���W�X�^

	// ���[�g�p�����[�^
	CD3DX12_ROOT_PARAMETER rootparams[2];
	rootparams[0].InitAsConstantBufferView(0); // �萔�o�b�t�@�r���[�Ƃ��ď�����(b0���W�X�^)
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV);

	// �X�^�e�B�b�N�T���v���[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ���[�g�V�O�l�`���̐ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// �o�[�W������������ł̃V���A���C�Y
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	if (FAILED(result)) {
		assert(0);
		return false;
	}
	// ���[�g�V�O�l�`���̐���
	result = device_->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	gpipeline.pRootSignature = rootSignature_.Get();
	//�O���t�B�b�N�X�p�C�v���C���̐���
	result = device_->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineState_));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//�ˉe�s��v�Z
	matProjection_ = XMMatrixOrthographicOffCenterLH(
		0.0f, (float)window_width,
		(float)window_height, 0.0f,
		0.0f, 1.0f
	);

	//�f�X�N���v�^�q�[�v�𐶐� 
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
	//null�`�F�b�N
	assert(device_);

	HRESULT result;
	//WIC�e�N�X�`���̃��[�h
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);

	const Image* img = scratchImg.GetImage(0, 0, 0); // ���f�[�^���o

	//���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	//�e�N�X�`���p�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // �e�N�X�`���p�w��
		nullptr,
		IID_PPV_ARGS(&texBuff_[texnumber]));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	result = texBuff_[texnumber]->WriteToSubresource(
		0,
		nullptr, // �S�̈�փR�s�[
		img->pixels,    // ���f�[�^�A�h���X
		(UINT)img->rowPitch,    // 1���C���T�C�Y
		(UINT)img->slicePitch   // 1���T�C�Y
	);

	//�V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	//�q�[�v��texnumber�ԖڂɃV�F�[�_�[���\�[�X�r���[�쐬
	device_->CreateShaderResourceView(
		texBuff_[texnumber].Get(), //�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc, //�e�N�X�`���ݒ���
		CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap_->GetCPUDescriptorHandleForHeapStart(), texnumber, device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	return true;
}

void Sprite::PreDraw(ID3D12GraphicsCommandList* cmdList_) {
	//PreDraw��PostDraw���y�A�ŌĂ΂�Ă��Ȃ���΃G���[
	assert(Sprite::cmdList_ == nullptr);
	//�R�}���h���X�g���Z�b�g
	Sprite::cmdList_ = cmdList_;
	//�p�C�v���C���X�e�[�g�̐ݒ�
	cmdList_->SetPipelineState(pipelineState_.Get());
	//���[�g�V�O�l�`���̐ݒ�
	cmdList_->SetGraphicsRootSignature(rootSignature_.Get());
	//�v���~�e�B�u�`���ݒ�
	cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Sprite::PostDraw() {
	//�R�}���h���X�g������
	Sprite::cmdList_ = nullptr;
}

Sprite* Sprite::Create(UINT texNumber_, XMFLOAT2 position_, XMFLOAT4 color_, XMFLOAT2 anchorpoint_, bool isFlipX_, bool isFlipY_) {
	XMFLOAT2 size_ = { 100.0f, 100.0f };

	if (texBuff_[texNumber_]) {
		//�e�N�X�`�����擾
		D3D12_RESOURCE_DESC resDesc = texBuff_[texNumber_]->GetDesc();
		//�X�v���C�g�̃T�C�Y���e�N�X�`���̃T�C�Y�ɐݒ�
		size_ = { (float)resDesc.Width, (float)resDesc.Height };
	}

	//Sprite�̃C���X�^���X�𐶐�
	Sprite* sprite = new Sprite(texNumber_, position_, size_, color_, anchorpoint_, isFlipX_, isFlipY_);
	if (sprite == nullptr) {
		return nullptr;
	}

	//������
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
		//�e�N�X�`�����擾
		D3D12_RESOURCE_DESC resDesc = texBuff_[texNumber_]->GetDesc();
		//�X�v���C�g�̃T�C�Y���e�N�X�`���̃T�C�Y�ɐݒ�
		size_ = { (float)resDesc.Width, (float)resDesc.Height };
	}

	//Sprite�̃C���X�^���X�𐶐�
	std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>(texNumber_, position_, size_, color_, anchorpoint_, isFlipX_, isFlipY_);
	if (sprite == nullptr) {
		return nullptr;
	}

	//������
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
	//null�`�F�b�N
	assert(device_);

	HRESULT result = S_FALSE;

	// ���_�o�b�t�@����
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

	// ���_�o�b�t�@�f�[�^�]��
	TransferVertices();

	// ���_�o�b�t�@�r���[�̍쐬
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = sizeof(VertexPosUv) * 4;
	vbView_.StrideInBytes = sizeof(VertexPosUv);

	// �萔�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff_));

	// �萔�o�b�t�@�Ƀf�[�^�]��
	ConstBufferData* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);
	constMap->color_ = XMFLOAT4(1, 1, 1, 1); // �F�w��iRGBA�j
	if (SUCCEEDED(result)) {
		constMap->color_ = color_;
		constMap->mat_ = matProjection_;
		constBuff_->Unmap(0, nullptr);
	}

	return true;
}

void Sprite::SetRotation(float rotation) {
	rotation_ = rotation;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	TransferVertices();
}

void Sprite::SetPosition(XMFLOAT2 position) {
	position_ = position;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	TransferVertices();
}

void Sprite::SetSize(XMFLOAT2 size) {
	size_ = size;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	TransferVertices();
}

void Sprite::SetAnchorPoint(XMFLOAT2 anchorpoint) {
	anchorpoint_ = anchorpoint;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	TransferVertices();
}

void Sprite::SetIsFlipX(bool isFlipX) {
	isFlipX_ = isFlipX;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	TransferVertices();
}

void Sprite::SetIsFlipY(bool isFlipY) {
	isFlipY_ = isFlipY;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	TransferVertices();
}

void Sprite::SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize) {
	texBase_ = texBase;
	texSize_ = texSize;

	//���_�o�b�t�@�ւ̃f�[�^�]��
	TransferVertices();
}

void Sprite::Draw() {
	// ���[���h�s��̍X�V
	this->matWorld_ = XMMatrixIdentity();
	// Z����]
	this->matWorld_ *= XMMatrixRotationZ(XMConvertToRadians(rotation_));
	// ���s�ړ�
	this->matWorld_ *= XMMatrixTranslation(position_.x, position_.y, 0.0f);

	// �萔�o�b�t�@�ɓ]��
	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap);
	color_.w = alpha_;
	if (SUCCEEDED(result)) {
		constMap->mat_ = matWorld_ * matProjection_;
		constMap->color_ = color_;
		this->constBuff_->Unmap(0, nullptr);
	}

	//���_�o�b�t�@�̐ݒ�
	cmdList_->IASetVertexBuffers(0, 1, &this->vbView_);
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap_.Get() };
	//�f�X�N���v�^�q�[�v���Z�b�g
	cmdList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	// �萔�o�b�t�@���Z�b�g
	cmdList_->SetGraphicsRootConstantBufferView(0, this->constBuff_->GetGPUVirtualAddress());
	// �V�F�[�_���\�[�X�r���[���Z�b�g
	cmdList_->SetGraphicsRootDescriptorTable(
		1,
		CD3DX12_GPU_DESCRIPTOR_HANDLE(
			descHeap_->GetGPUDescriptorHandleForHeapStart(),
			this->texNumber_,
			descriptorHandleIncrementSize_
		)
	);
	//�`��
	cmdList_->DrawInstanced(4, 1, 0, 0);

}

void Sprite::TransferVertices() {
	HRESULT result = S_FALSE;

	//   �����A����A�E���A�E��
	enum { LB, LT, RB, RT };

	//���E���]
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
	//�㉺���]
	if (isFlipY_) {
		top = -top;
		bottom = -bottom;
	}

	//���_�f�[�^
	VertexPosUv vertices[vertNum];

	vertices[LB].pos_ = { left, bottom, 0.0f }; //����
	vertices[LT].pos_ = { left, top, 0.0f }; //����
	vertices[RB].pos_ = { right, bottom, 0.0f }; //�E��
	vertices[RT].pos_ = { right, top, 0.0f }; //�E��

	//�e�N�X�`�����擾
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

	//���_�o�b�t�@�ւ̃f�[�^�]��
	VertexPosUv* vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff_->Unmap(0, nullptr);
	}
}