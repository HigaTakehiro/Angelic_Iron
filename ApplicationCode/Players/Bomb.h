#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "ModelManager.h"
#include "safedelete.h"

class Bomb
{
public: 
	Bomb();
	~Bomb();

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="playerPos">プレイヤーの位置</param>
	/// <param name="enemyPos">ロックオンされた敵の位置</param>
	void Initialize(const Vector3& playerPos, Object3d* target);

	/// <summary>
	/// 更新
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
	/// 死亡フラグ取得
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead_; }

	/// <summary>
	/// 弾オブジェクト取得
	/// </summary>
	/// <returns>弾オブジェクト</returns>
	Object3d* GetBullet() { return bullet_; }

private: //メンバ変数
	Object3d* bullet_;
	Object3d* targetEnemy_;
	Vector3 bulletPos_;
	Vector3 enemyPos_;
	Vector3 initBulletPos_;

	bool isDead_;
	bool isUp_;
};

