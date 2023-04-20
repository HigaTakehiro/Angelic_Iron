#include "ShadowMap.h"

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
}

void ShadowMap::Update()
{
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
		texBuff_.Get(), &rvDesc, srvHandle
	);

	rvDesc.Format = DXGI_FORMAT_R32_FLOAT;
	srvHandle.ptr += DirectXSetting::GetIns()->GetDev()->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV
	);
	//DirectXSetting::GetIns()->GetDev()->CreateShaderResourceView()

	return true;
}

bool ShadowMap::TexBuffCreate()
{
	return false;
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
		texHeap_->GetCPUDescriptorHandleForHeapStart()
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
		&descHeapDesc, IID_PPV_ARGS(&shadowBuff_));
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
		&heapProp, D3D12_HEAP_FLAG_NONE, &resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, &clearValue,
		IID_PPV_ARGS(&shadowBuff_)
	);
	if (FAILED(result)) {
		return false;
	}

	return true;
}