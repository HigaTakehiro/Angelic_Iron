#include "Model.h"
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

ID3D12Device* Model::device_ = nullptr;
UINT Model::descriptorHandleIncrementSize_ = 0;

void Model::StaticInitialize(ID3D12Device* device_) {
	//nullptr�`�F�b�N
	assert(device_);

	Model::device_ = device_;
}

Model* Model::CreateModel(const std::string& modelname, bool isSmoothing) {
	Model* instance = new Model;
	instance->InitializeDescriptorHeap();
	instance->InitializeModel(modelname, isSmoothing);

	return instance;
}

Model* Model::CreateShapeModel(const std::vector<VertexPosNormalUv>& vertices_, const std::vector<unsigned short> indices_, const std::string& textureName)
{
	Model* shape = new Model;
	shape->InitializeDescriptorHeap();
	shape->InitializeShapesModel(vertices_, indices_, textureName);
	return shape;
}

void Model::InitializeShapesModel(const std::vector<VertexPosNormalUv>& vertices, const std::vector<unsigned short> indices, const std::string& textureName)
{
	HRESULT result = S_FALSE;

	std::vector<VertexPosNormalUv> realVertices;

	vertices_ = vertices;
	indices_ = indices;

	material_.name_ = "square";
	material_.ambient_ = { 1.0f, 1.0f, 1.0f };
	material_.textureFilename_ = textureName;
	LoadTexture("Engine/Resources/Images/", material_.textureFilename_);

	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices_.size());
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices_.size());
	// ���_�o�b�t�@����
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff_));
	if (FAILED(result)) {
		assert(0);
		return;
	}

	// �C���f�b�N�X�o�b�t�@����
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff_));
	if (FAILED(result)) {
		assert(0);
		return;
	}

	// ���_�o�b�t�@�ւ̃f�[�^�]��
	VertexPosNormalUv* vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		std::copy(vertices_.begin(), vertices_.end(), vertMap);
		vertBuff_->Unmap(0, nullptr);
	}

	// �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	unsigned short* indexMap = nullptr;
	result = indexBuff_->Map(0, nullptr, (void**)&indexMap);
	if (SUCCEEDED(result)) {

		// �S�C���f�b�N�X�ɑ΂���
		std::copy(indices_.begin(), indices_.end(), indexMap);

		indexBuff_->Unmap(0, nullptr);
	}

	// ���_�o�b�t�@�r���[�̍쐬
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = sizeVB;
	vbView_.StrideInBytes = sizeof(vertices_[0]);

	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView_.BufferLocation = indexBuff_->GetGPUVirtualAddress();
	ibView_.Format = DXGI_FORMAT_R16_UINT;
	ibView_.SizeInBytes = sizeIB;
}

void Model::AddSmoothData(unsigned short indexPosition, unsigned short indexVertex)
{
	smoothData_[indexPosition].emplace_back(indexVertex);
}

void Model::CalculateSmoothedVertexNormals()
{
	auto itr = smoothData_.begin();
	for (; itr != smoothData_.end(); ++itr) {
		std::vector<unsigned short>& v = itr->second;
		XMVECTOR normal_ = {};
		for (unsigned short index : v) {
			normal_ += XMVectorSet(vertices_[index].normal_.x, vertices_[index].normal_.y, vertices_[index].normal_.z, 0);
		}
		normal_ = XMVector3Normalize(normal_ / (float)v.size());
		for (unsigned short index : v) {
			vertices_[index].normal_ = { normal_.m128_f32[0], normal_.m128_f32[1], normal_.m128_f32[2] };
		}
	}
}

void Model::Initialize() {
	HRESULT result;

	//�萔�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB1_));
}

void Model::Update(Material materials) {
	HRESULT result;

	ConstBufferDataB1* constMap = nullptr;
	result = constBuffB1_->Map(0, nullptr, (void**)&constMap);
	constMap->ambient_ = material_.ambient_;
	constMap->diffuse_ = material_.diffuse_;
	constMap->specular_ = material_.specular_;
	constMap->alpha_ = material_.alpha_;
	constBuffB1_->Unmap(0, nullptr);
}

void Model::Draw(ID3D12GraphicsCommandList* cmdList) {
	// ���_�o�b�t�@�̐ݒ�
	cmdList->IASetVertexBuffers(0, 1, &vbView_);
	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	cmdList->IASetIndexBuffer(&ibView_);

	// �f�X�N���v�^�q�[�v�̔z��
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap_.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// �萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(1, constBuffB1_->GetGPUVirtualAddress());
	// �V�F�[�_���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(2, gpuDescHandleSRV_);
	// �`��R�}���h
	cmdList->DrawIndexedInstanced((UINT)indices_.size(), 1, 0, 0, 0);
}

std::wstring Model::SeparatedExtension(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring fileExt;

	//��؂蕶��'.'���o�Ă����ԍŌ�̕���������
	pos1 = filePath.rfind('.');
	if (pos1 != std::wstring::npos) {
		//��؂蕶���̌����t�@�C���g���q�Ƃ��ĕۑ�
		fileExt = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
	}
	else {
		fileExt = L"";
	}

	return fileExt;
}

void Model::InitializeDescriptorHeap() {
	HRESULT result = S_FALSE;

	// �f�X�N���v�^�q�[�v�𐶐�	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	descHeapDesc.NumDescriptors = 1; // �V�F�[�_�[���\�[�X�r���[1��
	result = device_->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap_));//����
	if (FAILED(result)) {
		assert(0);
	}

	// �f�X�N���v�^�T�C�Y���擾
	descriptorHandleIncrementSize_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void Model::InitializeModel(const std::string& modelname, bool isSmoothing) {

	HRESULT result = S_FALSE;

	//�t�@�C���X�g���[��
	std::ifstream file;
	//obj�t�@�C�����J��
	//const string modelname = "armor";
	const string filename = modelname + ".obj";
	const string directoryPath = "Engine/Resources/3DModels/obj/" + modelname + "/";
	file.open(directoryPath + filename);
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}

	vector<XMFLOAT3> positions;
	vector<XMFLOAT3> normals;
	vector<XMFLOAT2> texcoords;
	//��s���ǂݍ���
	string line;
	while (getline(file, line)) {
		//��s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		//�擪������mtllib�Ȃ�}�e���A��
		if (key == "mtllib") {
			//�}�e���A���̃t�@�C�����ǂݍ���
			string filename;
			line_stream >> filename;
			//�}�e���A���ǂݍ���
			LoadMaterial(directoryPath, filename);
		}

		//�擪������v�Ȃ璸�_���W
		if (key == "v") {
			//X,Y,Z���W�ǂݍ���
			XMFLOAT3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//���W�f�[�^�ɒǉ�
			positions.emplace_back(position);
		}

		//�擪������vt�Ȃ�e�N�X�`��
		if (key == "vt") {
			//UV�����ǂݍ���
			XMFLOAT2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V�������]
			texcoord.y = 1.0f - texcoord.y;
			//�e�N�X�`�����W�f�[�^�ɒǉ�
			texcoords.emplace_back(texcoord);
		}

		//�擪������vn�Ȃ�@���x�N�g��
		if (key == "vn") {
			//XYZ�����ǂݍ���
			XMFLOAT3 normal_{};
			line_stream >> normal_.x;
			line_stream >> normal_.y;
			line_stream >> normal_.z;
			//�@���x�N�g���f�[�^�ɒǉ�
			normals.emplace_back(normal_);
		}

		//�擪������f�Ȃ�|���S��
		if (key == "f") {
			//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			string index_string;
			while (getline(line_stream, index_string, ' ')) {
				//���_�C���f�b�N�X����̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexTexcoord, indexNormal;
				index_stream >> indexPosition;
				index_stream.seekg(1, ios_base::cur);
				index_stream >> indexTexcoord;
				index_stream.seekg(1, ios_base::cur);
				index_stream >> indexNormal;
				//���_�f�[�^�̒ǉ�
				VertexPosNormalUv vertex{};
				vertex.pos_ = positions[indexPosition - 1];
				vertex.normal_ = normals[indexNormal - 1];
				vertex.uv_ = texcoords[indexTexcoord - 1];
				vertices_.emplace_back(vertex);
				if (isSmoothing) {
					AddSmoothData(indexPosition, (unsigned short)vertices_.size() - 1);
				}
				//���_�C���f�b�N�X�ɒǉ�
				indices_.emplace_back((unsigned short)indices_.size());
			}
		}
	}

	file.close();

	if (isSmoothing) {
		CalculateSmoothedVertexNormals();
	}

	std::vector<VertexPosNormalUv> realVertices;

	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices_.size());
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices_.size());
	// ���_�o�b�t�@����
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff_));
	if (FAILED(result)) {
		assert(0);
		return;
	}

	// �C���f�b�N�X�o�b�t�@����
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff_));
	if (FAILED(result)) {
		assert(0);
		return;
	}

	// ���_�o�b�t�@�ւ̃f�[�^�]��
	VertexPosNormalUv* vertMap = nullptr;
	result = vertBuff_->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		std::copy(vertices_.begin(), vertices_.end(), vertMap);
		vertBuff_->Unmap(0, nullptr);
	}

	// �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	unsigned short* indexMap = nullptr;
	result = indexBuff_->Map(0, nullptr, (void**)&indexMap);
	if (SUCCEEDED(result)) {

		// �S�C���f�b�N�X�ɑ΂���
		std::copy(indices_.begin(), indices_.end(), indexMap);

		indexBuff_->Unmap(0, nullptr);
	}

	// ���_�o�b�t�@�r���[�̍쐬
	vbView_.BufferLocation = vertBuff_->GetGPUVirtualAddress();
	vbView_.SizeInBytes = sizeVB;
	vbView_.StrideInBytes = sizeof(vertices_[0]);

	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView_.BufferLocation = indexBuff_->GetGPUVirtualAddress();
	ibView_.Format = DXGI_FORMAT_R16_UINT;
	ibView_.SizeInBytes = sizeIB;
}

void Model::LoadTexture(const std::string& directoryPath, const std::string& filename) {
	HRESULT result = S_FALSE;

	// WIC�e�N�X�`���̃��[�h
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	//�t�@�C���p�X������
	string filepath = directoryPath + filename;

	//���j�R�[�h������ɕϊ�����
	wchar_t wfilepath[128];
	int32_t iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wfilepath, _countof(wfilepath));

	const std::wstring fileExt = SeparatedExtension(wfilepath);

	if (fileExt == L"dds") {
		result = LoadFromDDSFile(
			wfilepath, DDS_FLAGS_NONE,
			&metadata, scratchImg);

		if (FAILED(result)) {
			assert(0);
		}
	}
	else {
		result = LoadFromWICFile(
			wfilepath, WIC_FLAGS_NONE,
			&metadata, scratchImg);

		if (FAILED(result)) {
			assert(0);
		}
	}

	//ScratchImage mipChain{};

	//�~�b�v�}�b�v����
	//result = GenerateMipMaps(
	//	scratchImg.GetImages(), scratchImg.GetImageCount(),
	//	scratchImg.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);
	//if (SUCCEEDED(result)) {
	//	scratchImg = std::move(mipChain);
	//	metadata = scratchImg.GetMetadata();
	//}
	
	//�ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
	//metadata.format = MakeSRGB(metadata.format);

	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// �e�N�X�`���p�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // �e�N�X�`���p�w��
		nullptr,
		IID_PPV_ARGS(&texbuff_));
	if (FAILED(result)) {
		assert(0);
	}

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (int32_t i = 0; i < metadata.mipLevels; i++) {
		const Image* img = scratchImg.GetImage(i, 0, 0); // ���f�[�^���o

		result = texbuff_->WriteToSubresource(
			(UINT)i,
			nullptr, // �S�̈�փR�s�[
			img->pixels,    // ���f�[�^�A�h���X
			(UINT)img->rowPitch,  // 1���C���T�C�Y
			(UINT)img->slicePitch // 1���T�C�Y
		);
		if (FAILED(result)) {
			assert(0);
		}
	}

	// �V�F�[�_���\�[�X�r���[�쐬
	cpuDescHandleSRV_ = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap_->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize_);
	gpuDescHandleSRV_ = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap_->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize_);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	D3D12_RESOURCE_DESC resDesc = texbuff_->GetDesc();

	srvDesc.Format = texresDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = texresDesc.MipLevels;

	device_->CreateShaderResourceView(texbuff_.Get(), //�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc, //�e�N�X�`���ݒ���
		cpuDescHandleSRV_
	);
}

void Model::LoadMaterial(const std::string& directoryPath, const std::string& filename) {
	//�t�@�C���X�g���[��
	std::ifstream file;
	//�}�e���A���t�@�C�����J��
	file.open(directoryPath + filename);
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}

	//��s���ǂݍ���
	string line;
	while (getline(file, line)) {
		//��s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		//�擪�̃^�u�����͖�������
		if (key[0] == '\t') {
			key.erase(key.begin());
		}

		//�擪������newmtl�Ȃ�}�e���A����
		if (key == "newmtl") {
			//�}�e���A�����ǂݍ���
			line_stream >> material_.name_;
		}

		//�擪������Ka�Ȃ�A���r�G���g�F
		if (key == "Ka") {
			line_stream >> material_.ambient_.x;
			line_stream >> material_.ambient_.y;
			line_stream >> material_.ambient_.z;
		}

		//�擪������Kd�Ȃ�f�B�t���[�Y�F
		if (key == "Kd") {
			line_stream >> material_.diffuse_.x;
			line_stream >> material_.diffuse_.y;
			line_stream >> material_.diffuse_.z;
		}

		//�擪������Ks�Ȃ�X�y�L�����[�F
		if (key == "Ks") {
			line_stream >> material_.specular_.x;
			line_stream >> material_.specular_.y;
			line_stream >> material_.specular_.z;
		}

		//�擪������map_Kd�Ȃ�e�N�X�`���t�@�C����
		if (key == "map_Kd") {
			//�e�N�X�`���̃t�@�C�����̓ǂݍ���
			line_stream >> material_.textureFilename_;
			//�e�N�X�`���ǂݍ���
			LoadTexture(directoryPath, material_.textureFilename_);
		}

	}

	file.close();
}