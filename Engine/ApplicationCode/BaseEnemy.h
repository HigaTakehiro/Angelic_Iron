#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "EnemyBullet.h"
#include "RailScene.h"
#include "Sprite.h"
#include "Easing.h"

class BaseEnemy
{
public:
	virtual ~BaseEnemy() {};

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="modelName">モデル名</param>
	/// <param name="pos">座標</param>
	/// <param name="scale">大きさ</param>
	virtual void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& scale) = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	/// <param name="delayTime">スロー演出用遅延時間</param>
	virtual void Update(Vector3 playerPos, int delayTime) = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 画像描画処理
	/// </summary>
	virtual void SpriteDraw() = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// 攻撃ヒット時コールバック関数
	/// </summary>
	void OnCollision();
	/// <summary>
	/// ロックオンフラグを立てる
	/// </summary>
	/// <param name="isTarget"></param>
	void SetIsTarget(bool isTarget) { this->isTarget = isTarget; }
	/// <summary>
	/// 死亡フラグをセット
	/// </summary>
	/// <param name="isDead"></param>
	bool GetIsDead() { return isDead; }
	/// <summary>
	/// レールシーンをセット
	/// </summary>
	/// <param name="railScene"></param>
	void SetRailScene(RailScene* railScene) { this->railScene = railScene; }

protected: //メンバ変数
	//座標
	Vector3 pos;
	//大きさ
	Vector3 scale;
	//回転角
	Vector3 rot;
	//死亡フラグ
	bool isDead;
	//ロックオンフラグ
	bool isTarget;
	//ゲームシーンのポインタ
	RailScene* railScene;
};

