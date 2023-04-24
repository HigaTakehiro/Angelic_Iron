#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "safedelete.h"
#include "ModelManager.h"

class EnemyBullet
{
public: //コンストラクタ&デストラクタ
	EnemyBullet();
	~EnemyBullet();

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& pos, const Vector3& velocity, Object3d* playerObj = nullptr);

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
	/// 敵弾オブジェクト取得
	/// </summary>
	/// <returns>敵弾オブジェクト</returns>
	Object3d* GetEnemyBulletObj() { return enemyBullet_; }

private: //静的メンバ変数
	static const int32_t lifeTime = 60 * 2;
	static const int32_t homingTime = 30;

private: //メンバ変数
	Object3d* enemyBullet_;
	Object3d* playerObj_;
	Vector3 pos_;
	Vector3 velocity_;
	Vector3 initVelocity_;
	bool isDead_;
	bool isHoming_;
	int32_t lifeTimer_ = lifeTime;
	int32_t homingTimer_ = homingTime;
};

