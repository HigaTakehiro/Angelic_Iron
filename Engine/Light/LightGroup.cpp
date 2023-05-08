#include "LightGroup.h"

using namespace DirectX;

ID3D12Device* LightGroup::device_ = nullptr;

void LightGroup::StaticInitialize()
{
	assert(!LightGroup::device_);
	LightGroup::device_ = DirectXSetting::GetIns()->GetDev();
}

LightGroup* LightGroup::Create()
{
	LightGroup* instance = new LightGroup();
	instance->Initialize();
	return instance;
}

std::unique_ptr<LightGroup> LightGroup::UniquePtrCreate()
{
	std::unique_ptr<LightGroup> instance = std::make_unique<LightGroup>();
	instance->Initialize();
	return instance;
}

void LightGroup::Initialize() 
{
	assert(device_);

	DefaultLightSetting();

	HRESULT result;
	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_)
	);
	if (FAILED(result)) {
		assert(0);
	}

	TransferConstBuffer();
}

void LightGroup::Update() {
	if (isDirty_) {
		TransferConstBuffer();
		isDirty_ = false;
	}
}

void LightGroup::Draw(UINT rootParameterIndex) {
	DirectXSetting::GetIns()->GetCmdList()->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff_->GetGPUVirtualAddress());
}

void LightGroup::TransferConstBuffer()
{
	HRESULT result;
	//定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->ambientColor_ = ambientColor_;
		for (int i = 0; i < DirLightNum; i++) {
			if (dirLights_[i].GetIsActive()) {
				constMap->dirLights_[i].isActive_ = 1;
				constMap->dirLights_[i].lightVec_ = -dirLights_[i].GetLightDir();
				constMap->dirLights_[i].lightColor_ = dirLights_[i].GetLightColor();
			}
			else {
				constMap->dirLights_[i].isActive_ = 0;
			}
		}
		for (int i = 0; i < PointLightNum; i++) {
			if (pointLights_[i].GetIsActive()) {
				constMap->pointLights_[i].isActive_ = 1;
				constMap->pointLights_[i].lightPos_ = pointLights_[i].GetLightPos();
				constMap->pointLights_[i].lightColor_ = pointLights_[i].GetLightColor();
				constMap->pointLights_[i].lightAtten_ = pointLights_[i].GetLightAtten();
			}
			else {
				constMap->pointLights_[i].isActive_ = 0;
			}
		}
		for (int i = 0; i < SpotLightNum; i++) {
			if (spotLights_[i].GetIsActive()) {
				constMap->spotLights_[i].isActive_ = 1;
				constMap->spotLights_[i].lightVec_ = -spotLights_[i].GetLightVec();
				constMap->spotLights_[i].lightPos_ = spotLights_[i].GetLightPos();
				constMap->spotLights_[i].lightColor_ = spotLights_[i].GetLightColor();
				constMap->spotLights_[i].lightAtten_ = spotLights_[i].GetLightAtten();
				constMap->spotLights_[i].lightCosAngle_ = spotLights_[i].GetLightCosAngle();
			}
			else {
				constMap->spotLights_[i].isActive_ = 0;
			}
		}
		for (int i = 0; i < CircleShadowNum; i++) {
			if (circleShadows_[i].GetIsActive()) {
				constMap->circleShadow_[i].isActive_ = 1;
				constMap->circleShadow_[i].dir_ = -circleShadows_[i].GetDir();
				constMap->circleShadow_[i].casterPos_ = circleShadows_[i].GetCasterPos();
				constMap->circleShadow_[i].distanceCasterLight_ = circleShadows_[i].GetDistanceCasterLight();
				constMap->circleShadow_[i].atten_ = circleShadows_[i].GetAtten();
				constMap->circleShadow_[i].cosAngle_ = circleShadows_[i].GetAngle();
			}
			else {
				constMap->circleShadow_[i].isActive_ = 0;
			}
		}
		constBuff_->Unmap(0, nullptr);
	}
}

void LightGroup::DefaultLightSetting() {
	ambientColor_ = { 1.0f, 1.0f, 1.0f };

	dirLights_[0].SetIsActive(true);
	dirLights_[0].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights_[0].SetLightDir({ 0.0f, -1.0f, 0.0f, 0.0f });

	dirLights_[1].SetIsActive(true);
	dirLights_[1].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights_[1].SetLightDir({ 0.5f, 0.1f, 0.2f, 0.0f });

	dirLights_[2].SetIsActive(true);
	dirLights_[2].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights_[2].SetLightDir({ -0.5f, 0.1f, -0.2f, 0.0f });
}

void LightGroup::SetAmbientColor(const XMFLOAT3& ambientColor_) {
	this->ambientColor_ = ambientColor_;
	isDirty_ = true;
}

void LightGroup::SetDirLightActive(int index, bool isActive_) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetIsActive(isActive_);
}

void LightGroup::SetDirLightColor(int index, const XMFLOAT3& lightColor_) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightColor(lightColor_);
	isDirty_ = true;
}

void LightGroup::SetDirLightDirection(int index, const XMFLOAT3& lightDir) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightDir({ lightDir.x, lightDir.y, lightDir.z });
	isDirty_ = true;
}

void LightGroup::SetPointLightActive(int index, bool isActive_)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetActive(isActive_);
}

void LightGroup::SetPointLightPos(int index, const XMFLOAT3& lightPos_)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetLightPos(lightPos_);
	isDirty_ = true;
}

void LightGroup::SetPointLightColor(int index, const XMFLOAT3& lightColor_)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetLightColor(lightColor_);
	isDirty_ = true;
}

void LightGroup::SetPointLightAtten(int index, const XMFLOAT3& lightAtten_)
{
	assert(0 <= index && index < PointLightNum);

	pointLights_[index].SetLightAtten(lightAtten_);
	isDirty_ = true;
}

void LightGroup::SetSpotLightActive(int index, bool isActive_)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetIsActive(isActive_);
}

void LightGroup::SetSpotLightDirection(int index, const XMVECTOR& lightDir)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightVec(lightDir);
	isDirty_ = true;
}

void LightGroup::SetSpotLightPos(int index, const XMFLOAT3& lightPos_)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightPos(lightPos_);
	isDirty_ = true;
}

void LightGroup::SetSpotLightColor(int index, const XMFLOAT3& lightColor_)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightColor(lightColor_);
	isDirty_ = true;
}

void LightGroup::SetSpotLightAtten(int index, const XMFLOAT3& lightAtten_)
{
	assert(0 <= index && index < SpotLightNum);
	
	spotLights_[index].SetLightAtten(lightAtten_);
	isDirty_ = true;
}

void LightGroup::SetSpotLightAngle(int index, const XMFLOAT2& lightAngle)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights_[index].SetLightCosAngle(lightAngle);
	isDirty_ = true;
}

void LightGroup::SetCircleShadowActive(int index, bool isActive_)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetIsActive(isActive_);
}

void LightGroup::SetCircleShadowCasterPos(int index, const XMFLOAT3& casterPos)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetCasterPos(casterPos);
	isDirty_ = true;
}

void LightGroup::SetCircleShadowDir(int index, const XMVECTOR& lightDir)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetDir(lightDir);
	isDirty_ = true;
}

void LightGroup::SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetDistanceCasterLight(distanceCasterLight);
	isDirty_ = true;
}

void LightGroup::SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten_)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetAtten(lightAtten_);
	isDirty_ = true;
}

void LightGroup::SetCircleShadowAngle(int index, const XMFLOAT2& angle)
{
	assert(0 <= index && index < CircleShadowNum);

	circleShadows_[index].SetAngle(angle);
	isDirty_ = true;
}