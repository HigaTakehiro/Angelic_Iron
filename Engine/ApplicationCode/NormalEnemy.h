#pragma once
#include "BaseEnemy.h"

class RailScene;

class NormalEnemy : public BaseEnemy
{
public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="modelName">モデル名</param>
	/// <param name="pos">座標</param>
	/// <param name="scale">大きさ</param>
	void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& scale);
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	/// <param name="delayTime">スロー演出用遅延時間</param>
	void Update(const Vector3& playerPos, const int delayTime);
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 画像描画処理
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

private: //メンバ関数
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();

private: //静的メンバ変数

private: //メンバ変数

};

