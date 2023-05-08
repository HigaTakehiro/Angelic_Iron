#pragma once

#include <DirectXMath.h>

class SpotLight {
private: //エイリアス
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //サブクラス
	struct ConstBufferData {
		XMVECTOR lightVec_;
		XMFLOAT3 lightPos_;
		float pad1_;
		XMFLOAT3 lightColor_;
		float pad2_;
		XMFLOAT3 lightAtten_;
		float pad3_;
		XMFLOAT2 lightCosAngle_;
		unsigned int isActive_;
		float pad4_;
	};

public: //メンバ関数

	/// <summary>
	/// ライト方向を取得
	/// </summary>
	/// <returns>ライト方向</returns>
	const XMVECTOR& GetLightVec() { return lightVec_; }

	/// <summary>
	/// ライト座標を取得
	/// </summary>
	/// <returns>ライト座標</returns>
	const XMFLOAT3& GetLightPos() { return lightPos_; }

	/// <summary>
	/// ライト色を取得
	/// </summary>
	/// <returns>ライト色</returns>
	const XMFLOAT3& GetLightColor() { return lightColor_; }

	/// <summary>
	/// ライト距離減衰係数を取得
	/// </summary>
	/// <returns>ライト距離減衰係数</returns>
	const XMFLOAT3& GetLightAtten() { return lightAtten_; }

	/// <summary>
	/// ライト減衰角度(開始角度、終了角度)
	/// </summary>
	/// <returns>ライト減衰角度</returns>
	const XMFLOAT2& GetLightCosAngle() { return lightCosAngle_; }

	/// <summary>
	/// 有効化フラグを取得
	/// </summary>
	/// <returns>有効化フラグ</returns>
	bool GetIsActive() { return isActive_; }

	/// <summary>
	/// スポットライト有効化
	/// </summary>
	/// <param name="isActive">有効化フラグ</param>
	void SetIsActive(bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightVec">ライト方向</param>
	void SetLightVec(const XMVECTOR& lightVec) { lightVec_ = DirectX::XMVector3Normalize(lightVec); }

	/// <summary>
	/// ライト座標をセット
	/// </summary>
	/// <param name="lightPos">ライト座標</param>
	void SetLightPos(const XMFLOAT3& lightPos) { lightPos_ = lightPos; }

	/// <summary>
	/// ライト色をセット
	/// </summary>
	/// <param name="lightColor">ライト色</param>
	void SetLightColor(const XMFLOAT3& lightColor) { lightColor_ = lightColor; }

	/// <summary>
	/// ライト距離減衰係数をセット
	/// </summary>
	/// <param name="lightAtten">ライト距離減衰係数</param>
	void SetLightAtten(const XMFLOAT3& lightAtten) { lightAtten_ = lightAtten; }

	/// <summary>
	/// ライト減衰角度をセット
	/// </summary>
	/// <param name="lightCosAngle">ライト減衰角度</param>
	void SetLightCosAngle(const XMFLOAT2& lightCosAngle) { 
		this->lightCosAngle_.x = cosf(DirectX::XMConvertToRadians(lightCosAngle.x));
		this->lightCosAngle_.y = cosf(DirectX::XMConvertToRadians(lightCosAngle.y));
	}

private: //メンバ変数
	XMVECTOR lightVec_ = { 1, 0, 0, 0 };
	XMFLOAT3 lightPos_ = { 0, 0, 0 };
	XMFLOAT3 lightColor_ = { 1, 1, 1 };
	XMFLOAT3 lightAtten_ = { 1.0f, 1.0f, 1.0f };
	XMFLOAT2 lightCosAngle_ = { 0.5f, 0.2f };
	bool isActive_ = false;
};