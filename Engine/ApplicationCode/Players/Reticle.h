#pragma once
#include "Sprite.h"
#include "DirectXMath.h"

class Reticle final
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Reticle() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Reticle() = default;

	/// <summary>
	/// コピーコンストラクタを禁止
	/// </summary>
	Reticle(const Reticle& obj) = delete;

	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	Reticle& operator=(const Reticle& obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Reticle* GetIns();

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private: //メンバ変数
	//レティクル
	Sprite* reticle;
	//レティクル座標
	DirectX::XMFLOAT2 reticlePos;
	//レティクルサイズ
	DirectX::XMFLOAT2 reticleSize;

};
