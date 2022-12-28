#include "Light.h"

using namespace DirectX;

ID3D12Device* Light::device = nullptr;

XMFLOAT3 Light::pos = { 0.0f, 0.0f, 0.0f };

void Light::StaticInitialize()
{
	assert(Light::device);
	assert(device);
	Light::device = DirectXSetting::GetIns()->GetDev();
}

Light* Light::Create()
{
	Light* light = new Light;
	light->Initialize();
	return light;
}

void Light::SetLightPos(XMFLOAT3 pos) {
	Light::pos = pos;
}

void Light::Initialize()
{
	HRESULT result;
	//定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff)
	);
	if (FAILED(result)) { assert(0); }

	TransferConstBuffer();
}

void Light::TransferConstBuffer()
{
	HRESULT result;
	//定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightVec = -lightDir;
		constMap->lightColor = lightColor;
		constBuff->Unmap(0, nullptr);
	}
}

void Light::SetLightDir(const XMVECTOR& lightDir)
{
	this->lightDir = XMVector3Normalize(lightDir);
	isDirty = true;
}

void Light::SetLightColor(const XMFLOAT3& lightColor)
{
	this->lightColor = lightColor;
	isDirty = true;
}

void Light::Update()
{
	if (isDirty) {
		TransferConstBuffer();
		isDirty = false;
	}
}

void Light::Draw(UINT rootParameter)
{
	DirectXSetting::GetIns()->GetCmdList()->SetGraphicsRootConstantBufferView(
		rootParameter, constBuff->GetGPUVirtualAddress()
	);
}
