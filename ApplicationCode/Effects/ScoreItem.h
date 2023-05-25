#pragma once
#include "Player.h"
#include "Object3d.h"
#include "Vector3.h"
#include "ParticleManager.h"
#include "Camera.h"

class Player;

class ScoreItem
{
public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ScoreItem() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ScoreItem();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">発生位置</param>
	/// <param name="player">プレイヤー</param>
	/// <param name="camera">カメラ</param>
	void Initialize(const Vector3& pos, Player* player, Camera* camera);

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
	/// 死亡フラグ取得
	/// </summary>
	/// <returns>死亡フラグ</returns>
	bool GetIsDead() { return isDead_; }

	/// <summary>
	/// スコアアイテム取得
	/// </summary>
	/// <returns>スコアアイテム</returns>
	Object3d* GetScoreItemObj() { return scoreItem_; }

private: //静的メンバ変数
	//待機時間
	static const int32_t standByTime = 60;

	//移動時間
	static const float moveTime;

private: //メンバ変数
	//スコアアイテムオブジェクト
	Object3d* scoreItem_;
	//パーティクル
	ParticleManager* particle_;
	//プレイヤー
	Player* player_;
	//死亡フラグ
	bool isDead_;
	//座標
	Vector3 pos_;
	//回転角度
	Vector3 rot_;
	//大きさ
	Vector3 scale_;
	//待機タイマー
	int32_t standByTimer_;
	//移動タイマー
	float moveTimer_;
};

