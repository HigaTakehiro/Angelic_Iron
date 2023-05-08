#pragma once
#include <DirectXMath.h>

class PointLight
{
private: //エイリアス
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //サブクラス
	struct ConstBufferData {
		XMFLOAT3 lightPos_;
		float pad1_;
		XMFLOAT3 lightColor_;
		float pad2_;
		XMFLOAT3 lightAtten_;
		unsigned int isActive_;
	};

public: //メンバ関数
	/// <summary>
	/// ライト座標をセット
	/// </summary>
	/// <param name="lightPos">ライト座標</param>
	inline void SetLightPos(const XMFLOAT3& lightPos) { lightPos_ = lightPos; }

	/// <summary>
	/// ライト座標を取得
	/// </summary>
	/// <returns>ライト座標</returns>
	inline const XMFLOAT3& GetLightPos() { return lightPos_; }

	/// <summary>
	/// ライト色をセット
	/// </summary>
	/// <param name="lightColor">ライト色</param>
	inline void SetLightColor(const XMFLOAT3& lightColor) { lightColor_ = lightColor; }

	/// <summary>
	/// ライト色を取得
	/// </summary>
	/// <returns>ライト色</returns>
	inline const XMFLOAT3& GetLightColor() { return lightColor_; }

	/// <summary>
	/// ライト距離減衰係数をセット
	/// </summary>
	/// <param name="lightAtten">ライト距離減衰係数</param>
	inline void SetLightAtten(const XMFLOAT3& lightAtten) { lightAtten_ = lightAtten; }

	/// <summary>
	/// ライト距離減衰係数を取得
	/// </summary>
	/// <returns>ライト距離減衰係数</returns>
	inline const XMFLOAT3& GetLightAtten() { return lightAtten_; }

	/// <summary>
	/// 点光源有効化
	/// </summary>
	/// <param name="isActive">有効化フラグ</param>
	inline void SetActive(bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// 点光源有効化フラグを取得
	/// </summary>
	/// <returns>有効化フラグ</returns>
	inline bool GetIsActive() { return isActive_; }

private: //メンバ変数
	//ライト座標
	XMFLOAT3 lightPos_ = { 0, 0, 0 };
	//ライト色
	XMFLOAT3 lightColor_ = { 1, 1, 1 };
	//ライト距離減衰係数
	XMFLOAT3 lightAtten_ = { 1.0f, 1.0f, 1.0f };
	//有効化フラグ
	bool isActive_ = false;
};