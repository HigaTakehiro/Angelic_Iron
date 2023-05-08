#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "DirectXSetting.h"

class DirectionalLight
{
private: // エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: //サブクラス
	struct ConstBufferData {
		XMVECTOR lightVec_; //ライトへの方向を表すベクトル
		XMFLOAT3 lightColor_; //ライトの色
		unsigned int isActive_;
	};

public: //メンバ関数

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightDir">ライト方向</param>
	inline void SetLightDir(const XMVECTOR& lightDir) { lightDir_ = DirectX::XMVector3Normalize(lightDir); }

	/// <summary>
	/// ライト色をセット
	/// </summary>
	/// <param name="lightColor">ライト色</param>
	inline void SetLightColor(const XMFLOAT3& lightColor) { lightColor_ = lightColor; }

	/// <summary>
	/// 平行光源を有効化
	/// </summary>
	/// <param name="isActive">有効化フラグ</param>
	inline void SetIsActive(bool isActive) { isActive_ = isActive; }

	/// <summary>
	/// 有効化フラグ取得
	/// </summary>
	inline bool GetIsActive() { return isActive_; }

	/// <summary>
	/// ライト方向を取得
	/// </summary>
	/// <returns>ライト方向</returns>
	inline const XMVECTOR& GetLightDir() { return lightDir_; }

	/// <summary>
	/// ライト色を取得
	/// </summary>
	/// <returns>ライト色</returns>
	inline const XMFLOAT3& GetLightColor() { return lightColor_; }

private: //メンバ変数
	//ライト光線方向
	XMVECTOR lightDir_ = { 1, 0, 0, 0 };
	//ライト色
	XMFLOAT3 lightColor_ = { 1, 1, 1 };
	//有効化フラグ
	bool isActive_ = false;
};