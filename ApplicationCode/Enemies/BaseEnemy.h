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
	/// <param name="modelKey">モデルのキー</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	virtual void Initialize(const std::string modelKey, const Vector3& pos, const Vector3& rot) = 0;
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
	/// ボム攻撃ヒット時コールバック関数
	/// </summary>
	void BombHitCollision();
	/// <summary>
	/// ロックオンフラグをセット
	/// </summary>
	/// <param name="isTarget"></param>
	void SetIsTarget(bool isTarget) { isTarget_ = isTarget; }
	/// <summary>
	/// 死亡フラグを取得
	/// </summary>
	/// <param name="isDead"></param>
	bool GetIsDead() { return isDead_; }
	/// <summary>
	/// HP取得
	/// </summary>
	/// <returns>HP</returns>
	int32_t GetHP() { return hp_; }
	/// <summary>
	/// レールシーンをセット
	/// </summary>
	/// <param name="railScene"></param>
	void SetRailScene(RailScene* railScene) { railScene_ = railScene; }
	/// <summary>
	/// プレイヤーをセット
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void SetPlayer(Player* player) { player_ = player; }
	/// <summary>
	/// ロックオンフラグをセット
	/// </summary>
	/// <param name="isTarget">ロックオンフラグ</param>
	void SetTarget(bool isTarget) { isTarget_ = isTarget; }
	/// <summary>
	/// 移動時間をセット
	/// </summary>
	/// <param name="maxTime">移動時間</param>
	void SetMaxTime(float maxTime) { maxTime_ = maxTime; }
	/// <summary>
	/// 最大生存時間をセット
	/// </summary>
	/// <param name="lifeTime">生存時間</param>
	void SetLifeTime(int32_t lifeTime) { lifeTime_ = lifeTime; }
	/// <summary>
	/// 弾発射間隔をセット
	/// </summary>
	/// <param name="shotIntervalTime">弾発射間隔</param>
	void SetShotIntervalTime(int32_t shotIntervalTime) { shotIntervalTime_ = shotIntervalTime; }
	/// <summary>
	/// HPをセット
	/// </summary>
	/// <param name="hp">HP</param>
	void SetHP(int32_t hp) { hp_ = hp; }
	/// <summary>
	/// 移動するポイントをセット
	/// </summary>
	/// <param name="movePoints">移動ポイント</param>
	void SetMovePoints(const std::vector<Vector3>& movePoints) { movePoints_ = movePoints; }
	/// <summary>
	/// ロックオンフラグを取得
	/// </summary>
	/// <returns>ロックオンフラグ</returns>
	bool GetIsTarget() { return isTarget_; }
	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns>敵オブジェクト</returns>
	Object3d* GetEnemyObj() { return enemy_; }
	/// <summary>
	/// ロックオン演出
	/// </summary>
	void RockOnPerformance();

protected: //メンバ関数
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// ダメージ処理
	/// </summary>
	void Damage();
	/// <summary>
	/// 攻撃処理
	/// </summary>
	virtual void Attack() = 0;

protected: //静的メンバ変数
	//ロックオン演出用時間
	static const float targetReactionTime;
	//死亡時演出用時間
	static const int32_t deadTime = 30;
	//ダメージ演出用時間
	static const int32_t damageTime = 12;

protected: //メンバ変数
	//敵オブジェクト
	Object3d* enemy_;
	//ロックオン画像
	Sprite* target_;
	//座標
	Vector3 pos_;
	//初期座標
	Vector3 oldPos_;
	//大きさ
	Vector3 scale_ = { 5.0f, 5.0f, 5.0f };
	//回転角
	Vector3 rot_ = {5.0f, 5.0f, 5.0f};
	//死亡フラグ
	bool isDead_;
	//ロックオンフラグ
	bool isTarget_;
	//ダメージフラグ
	bool isDamage_;
	//ゲームシーンのポインタ
	RailScene* railScene_;
	//移動するポイント
	std::vector<Vector3> movePoints_;
	//現在時間
	float nowTimer_;
	//経過時間
	float elapsedTimer_;
	//移動時間
	float maxTime_ = 1.0f;
	//評価時間
	float timeRate_;
	//移動完了したポイント
	int32_t movedPoint_ = 0;
	//プレイヤーのポインタ
	Player* player_;
	//体力
	int32_t hp_;
	//プレイヤーの座標
	Vector3 playerPos_;
	//生存時間
	int32_t lifeTimer_;
	//最大生存時間
	int32_t lifeTime_;
	//弾発射間隔時間
	int32_t shotIntervalTimer_;
	//弾発射間隔
	int32_t shotIntervalTime_;
	//死亡時演出用時間
	int32_t deadTimer_;
	//ダメージ演出用時間
	int32_t damageTimer_;
	//ロックオン演出用時間
	float targetReactionTimer_;
};