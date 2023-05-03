#pragma once
#include "Sprite.h"
#include "ImageManager.h"
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

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// レティクル座標を取得
	/// </summary>
	/// <returns>レティクル座標</returns>
	DirectX::XMFLOAT2 GetPos() { return reticlePos; }

	/// <summary>
	/// レティクルがボタンまたは敵にあっているフラグを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsSelectReticle() { return isSeletctReticle; }

	/// <summary>
	/// レティクルがボタンまたは敵にあっているフラグを立てる
	/// </summary>
	/// <param name="isSelectReticle">レティクルがボタンまたは敵にあっているフラグ</param>
	void SetIsSelectReticle(bool isSelectReticle) { this->isSeletctReticle = isSelectReticle; }

private: //静的メンバ変数
	//レティクル回転時間
	const static int32_t rotTime;

	//レティクル
	static Sprite* reticle;
	//レティクル座標
	static DirectX::XMFLOAT2 reticlePos;
	//レティクルサイズ
	static DirectX::XMFLOAT2 reticleSize;
	//レティクル角度
	static float reticleRot;
	//レティクルがボタンまたは敵にあっているフラグ
	static bool isSeletctReticle;

private: //メンバ変数
	//レティクル回転タイマー
	int32_t rotTimer;
};
