#pragma once
#include "Model.h"
#include "ModelManager.h"
#include "Object3d.h"
#include "SafeDelete.h"
#include "Vector3.h"

class BulletCase
{
public: //コンストラクタ&デストラクタ
	BulletCase() = default;
	~BulletCase();

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">初期座標</param>
	/// <param name="velocity">速度ベクトル</param>
	/// <param name="rot">向き</param>
	void Initialize(const Vector3& pos, const Vector3& velocity, const Vector3& rot);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 薬莢の状態を取得
	/// </summary>
	/// <returns>弾の状態</returns>
	bool IsDead() const { return isDead; }

private: //静的メンバ変数
	static const int32_t lifeTime = 60 * 2;

private: //メンバ変数
	Object3d* bulletCase;
	Vector3 pos;
	bool isDead;
	int32_t lifeTimer = lifeTime;
	Vector3 velocity;
};
