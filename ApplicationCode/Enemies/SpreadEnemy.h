#pragma once
#include "BaseEnemy.h"
#include "RailScene.h"

class SpreadEnemy : public BaseEnemy
{
public:
	SpreadEnemy() = default;

	~SpreadEnemy();

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="modelKey">モデルのキー</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot) override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 画像描画処理
	/// </summary>
	void SpriteDraw() override;
	/// <summary>
	/// 死亡処理
	/// </summary>
	void DeadPerformance() override;

private: //メンバ関数

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack() override;
};

