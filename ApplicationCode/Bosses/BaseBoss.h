#pragma once
#include "Object3d.h"
#include "Model.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "MouseInput.h"
#include "SafeDelete.h"
#include "EnemyBullet.h"
#include "MotionMath.h"
#include "ImageManager.h"
#include "BulletManager.h"
#include "Sprite.h"

class BossScene;
class BossScenePlayer;

class BaseBoss
{
public:
	virtual ~BaseBoss() {}

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize(const std::string modelKey, const Vector3& pos) = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(const Vector3& playerPos, const int32_t delayTime = 0) = 0;
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
	/// 行動
	/// </summary>
	virtual void Action() = 0;
	/// <summary>
	/// ムービー演出行動
	/// </summary>
	virtual void MovieAction() = 0;
	/// <summary>
	/// 攻撃ヒット時コールバック関数
	/// </summary>
	void OnCollision();
	/// <summary>
	/// ダメージリアクション
	/// </summary>
	void DamageReaction();
	/// <summary>
	/// ボスオブジェクト取得
	/// </summary>
	/// <returns></returns>
	Object3d* GetBossObj() { return boss_; }
	/// <summary>
	/// ボス本体HPを取得
	/// </summary>
	/// <returns>ボスHP</returns>
	float GetBossHp() { return hp_; }
	/// <summary>
	/// 死亡フラグ取得
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead_; }
	/// <summary>
	/// ムービーフラグ取得
	/// </summary>
	/// <returns>ムービーフラグ</returns>
	bool GetIsMovie() { return isMovie_; }
	/// <summary>
	/// ボスシーンをセット
	/// </summary>
	/// <param name="bossScene">ボスシーン</param>
	void SetBossScene(BossScene* bossScene) { bossScene_ = bossScene; }
	/// <summary>
	/// プレイヤーをセット
	/// </summary>
	/// <param name="player">プレイヤー</param>
	void SetPlayer(BossScenePlayer* player) { player_ = player; }
	/// <summary>
	/// 弾管理クラスをセット
	/// </summary>
	/// <param name="bulletManager">弾管理クラス</param>
	void SetBulletManager(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
	/// <summary>
	/// カメラ移動タイミングフラグ取得
	/// </summary>
	/// <returns></returns>
	bool GetIsCameraMoveTiming() { return isCameraMoveTiming_; }
	/// <summary>
	/// ムービーエフェクトタイミング取得
	/// </summary>
	/// <returns></returns>
	virtual bool GetIsMovieEffectTiming() = 0;

protected: //静的メンバ変数
	//行動クールタイム
	static const int32_t actionCoolTime;
	//ダメージタイム
	static const int32_t damageTime;
	//回転時間
	static const int32_t rotationTime;
	//死亡時間
	static const int32_t deadTime;
	//ダメージカラー
	static const DirectX::XMFLOAT4 damageColor;
	//死亡HP
	static const int32_t deadHP;

protected: //メンバ変数
	//ボスオブジェクト
	Object3d* boss_;
	//ボスシーン
	BossScene* bossScene_;
	//プレイヤー
	BossScenePlayer* player_;
	//プレイヤー座標
	Vector3 playerPos_;
	//座標
	Vector3 pos_;
	//回転角
	Vector3 rot_;
	//大きさ
	Vector3 scale_;
	//攻撃力
	float attackPower_;
	//体力
	float hp_;
	//行動クールタイマー
	int32_t actionCoolTimer_;
	//ダメージタイマー
	int32_t damageTimer_;
	//回転時間
	int32_t rotationTimer_;
	//スロー演出用タイマー
	int32_t delayTimer_;
	//攻撃パターン
	int32_t actionPattern_;
	//ダメージフラグ
	bool isDamage_ = false;
	//死亡フラグ
	bool isDead_ = false;
	//ムービーフラグ
	bool isMovie_ = false;
	bool isCameraMoveTiming_ = false;
	//死亡タイマー
	int32_t deadTimer_;
	//HPバー
	Sprite* hpBar_;
	Sprite* hpRedBar_;
	BulletManager* bulletManager_;

};