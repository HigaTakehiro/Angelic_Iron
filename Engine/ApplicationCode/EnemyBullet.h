#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "MatCalc.h"
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
	void Initialize(const Vector3& pos, const Vector3& velocity, bool isHoming = false);

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
	bool IsDead() const { return isDead; }

	/// <summary>
	/// 敵弾オブジェクト取得
	/// </summary>
	/// <returns>敵弾オブジェクト</returns>
	Object3d* GetEnemyBulletObj() { return enemyBullet; }

private: //静的メンバ変数
	static const int32_t lifeTime = 60 * 2;
	static const int32_t homingTime = 10;

private: //メンバ変数
	Model* bulletModel;
	Object3d* enemyBullet;
	Vector3 pos;
	Vector3 velocity;
	bool isDead;
	bool isHoming;
	int32_t lifeTimer = lifeTime;
	int32_t homingTimer = homingTime;
};

