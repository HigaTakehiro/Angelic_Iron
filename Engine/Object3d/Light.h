#pragma once
#include "DirectXMath.h"

class Light
{
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Light() = default;

	~Light() = default;

public: //静的メンバ関数

	/// <summary>
	/// ライト座標をセット
	/// </summary>
	/// <param name="light"></param>
	static void SetLightPos(XMFLOAT3 pos);

	/// <summary>
	/// ライト座標を取得
	/// </summary>
	/// <returns>ライト座標</returns>
	static XMFLOAT3 GetLightPos() { return pos; }

private: //メンバ変数
	//ライト座標
	static XMFLOAT3 pos;
};