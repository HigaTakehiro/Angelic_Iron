#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "ModelManager.h"
#include "safedelete.h"

class PlayerBullet
{
public: //コンストラクタ&デストラクタ
	PlayerBullet();

	~PlayerBullet();

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& pos, const Vector3& velocity, Object3d* target = nullptr);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 弾の状態を取得
	/// </summary>
	/// <returns>弾の状態</returns>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// 弾オブジェクト取得
	/// </summary>
	/// <returns>弾オブジェクト</returns>
	Object3d* GetBulletObj() { return bullet_; }

private: //静的メンバ変数
	static const int32_t lifeTime = 60 * 2;
	static const float bulletSpeed;

private: //メンバ変数
	Object3d* bullet_;
	Object3d* target_ = nullptr;
	Vector3 pos_;
	bool isDead_;
	bool isHoming_;
	int32_t lifeTimer_ = lifeTime;
	Vector3 velocity_;
};

