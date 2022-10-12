#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "Player.h"
#include "ModelManager.h"

class Enemy
{
	enum class EnemyStyle {
		STOP_PTAG,
		STOP_STR,
		UDMOVE_PTAG,
		UDMOVE_STR,
		LRMOVE_PTAG,
		LRMOVE_STR
	};

public: //コンストラクタ&デストラクタ
	Enemy();

	~Enemy();

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::string& modelName, const Vector3& pos, const Vector3& rot, const Vector3& scale, const std::string& style);

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
	/// 敵の状態を取得
	/// </summary>
	/// <returns>敵の状態</returns>
	bool IsDead() const { return isDead; }

	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns>敵オブジェクト</returns>
	Object3d* GetEnemyObj() { return enemy; }

private: //メンバ関数
	EnemyStyle stringToEnemyStyle(const std::string& type);

	/// <summary>
	/// 敵の行動
	/// </summary>
	void EnemyAction();

private: //メンバ変数

	Object3d* enemy;
	Vector3 pos;
	Vector3 oldPos;
	float moveSpeed;
	EnemyStyle type;
	bool isDead;
};

