#pragma once
#include "BaseEnemy.h"
#include "RailScene.h"

class StraightEnemy : public BaseEnemy
{
public:
	StraightEnemy() = default;

	~StraightEnemy();

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="modelName">モデル名</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& rot) override;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	/// <param name="delayTime">スロー演出用遅延時間</param>
	void Update(const int delayTime) override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 画像描画処理
	/// </summary>
	void SpriteDraw() override;

private: //メンバ関数
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move() override;
	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack() override;

private: //静的メンバ変数

private: //メンバ変数

};

