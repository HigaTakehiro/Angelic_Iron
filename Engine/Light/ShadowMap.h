#pragma once
#include <DirectXMath.h>

class ShadowMap {
private: //エイリアス
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//定数バッファデータ
	struct ConstBufferData {
		XMVECTOR lightDir;
		bool isActive;
	};

public: //メンバ関数
	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightDir"></param>
	void SetDir(XMVECTOR lightDir) { this->lightDir = lightDir; }
	/// <summary>
	/// シャドウマップを有効化
	/// </summary>
	/// <param name="isActive"></param>
	void SetIsActive(bool isActive) { this->isActive = isActive; }

	/// <summary>
	/// ライト方向を取得
	/// </summary>
	XMVECTOR GetDir() { return lightDir; }
	/// <summary>
	/// 有効化フラグを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsActive() { return isActive; }

private: //メンバ変数
	//ライト方向
	XMVECTOR lightDir = { 1, 0, 0, 0 };
	//有効化フラグ
	bool isActive = false;
};