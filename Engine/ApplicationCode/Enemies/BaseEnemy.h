#pragma once

#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "EnemyBullet.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "Easing.h"

class RailScene;
class Player;

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
	/// <param name="rot">回転</param>
	virtual void Initialize(const ModelManager::ModelName modelName, const Vector3& pos, const Vector3& rot) = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	/// <param name="delayTime">スロー演出用遅延時間</param>
	virtual void Update() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 画像描画処理
	/// </summary>
	virtual void SpriteDraw() = 0;
	/// <summary>
	/// 死亡時演出
	/// </summary>
	virtual void DeadPerformance() = 0;
	/// <summary>
	/// 攻撃ヒット時コールバック関数
	/// </summary>
	void OnCollision();
	/// <summary>
	/// ロックオンフラグをセット
	/// </summary>
	/// <param name="isTarget"></param>
	void SetIsTarget(bool isTarget) { this->isTarget = isTarget; }
	/// <summary>
	/// 死亡フラグを取得
	/// </summary>
	/// <param name="isDead"></param>
	bool GetIsDead() { return isDead; }
	/// <summary>
	/// HP取得
	/// </summary>
	/// <returns>HP</returns>
	int GetHP() { return hp; }
	/// <summary>
	/// レールシーンをセット
	/// </summary>
	/// <param name="railScene"></param>
	void SetRailScene(RailScene* railScene) { this->railScene = railScene; }
	/// <summary>
	/// プレイヤーをセット
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void SetPlayer(Player* player) { this->player = player; }
	/// <summary>
	/// ロックオンフラグをセット
	/// </summary>
	/// <param name="isTarget">ロックオンフラグ</param>
	void SetTarget(bool isTarget) { this->isTarget = isTarget; }
	/// <summary>
	/// ロックオンフラグを取得
	/// </summary>
	/// <returns>ロックオンフラグ</returns>
	bool GetIsTarget() { return isTarget; }
	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns>敵オブジェクト</returns>
	Object3d* GetEnemyObj() { return enemy; }

protected: //メンバ関数
	/// <summary>
	/// 移動処理
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// 攻撃処理
	/// </summary>
	virtual void Attack() = 0;

	/// <summary>
	/// ロックオン演出
	/// </summary>
	void RockOnPerformance();

protected: //静的メンバ変数
	//ロックオン演出用時間
	static const float targetReactionTime;
	//死亡時演出用時間
	static const int32_t deadTime = 30;

protected: //メンバ変数
	//敵オブジェクト
	Object3d* enemy;
	//ロックオン画像
	Sprite* target;
	//座標
	Vector3 pos;
	//初期座標
	Vector3 oldPos;
	//大きさ
	Vector3 scale = { 5.0f, 5.0f, 5.0f };
	//回転角
	Vector3 rot = {5.0f, 5.0f, 5.0f};
	//死亡フラグ
	bool isDead;
	//ロックオンフラグ
	bool isTarget;
	//ゲームシーンのポインタ
	RailScene* railScene;
	//プレイヤーのポインタ
	Player* player;
	//体力
	int hp;
	//プレイヤーの座標
	Vector3 playerPos;
	//生存時間
	int32_t lifeTimer;
	//最大生存時間
	int32_t lifeTime;
	//弾発射間隔時間
	int32_t shotIntervalTimer;
	//弾発射間隔
	int32_t shotIntervalTime;
	//死亡時演出用時間
	int32_t deadTimer;
	//ロックオン演出用時間
	float targetReactionTimer;
};