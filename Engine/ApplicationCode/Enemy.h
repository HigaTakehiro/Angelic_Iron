#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "ModelManager.h"
#include "EnemyBullet.h"
#include "GameScene.h"
#include "Sprite.h"

class GameScene;

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
	void Initialize(const std::string& modelName, const Vector3& pos, const Vector3& scale, const std::string& style);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const XMFLOAT3& playerPos);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 画像描画処理
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 弾の発射処理
	/// </summary>
	void Shot();

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

	/// <summary>
	/// 敵タイプ取得
	/// </summary>
	/// <returns>敵タイプ</returns>
	EnemyStyle GetEnemyStyle() { return type; }

	/// <summary>
	/// ゲームシーンをセットする
	/// </summary>
	/// <param name="gameScene">ゲームシーン</param>
	void SetGamaScene(GameScene* gameScene) { this->gameScene = gameScene; }

private: //メンバ関数
	/// <summary>
	/// 文字列をエネミータイプに変換する
	/// </summary>
	/// <param name="type">エネミータイプ(string)</param>
	/// <returns>エネミータイプ(enum)</returns>
	EnemyStyle stringToEnemyStyle(const std::string& type);

	/// <summary>
	/// 敵の行動
	/// </summary>
	void EnemyAction(const XMFLOAT3& playerPos);

	/// <summary>
	/// プレイヤーが射撃範囲にいるかどうか
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	/// <param name="enemyPos">エネミーの座標</param>
	/// <param name="range">射撃範囲</param>
	/// <param name="playerScale">プレイヤーの大きさ</param>
	/// <returns></returns>
	bool IsShotRangeJudge(const Vector3& playerPos, const Vector3& enemyPos, float range, float playerScale);

private: //静的メンバ変数
	static const int32_t shotIntervalTime = 60;
	static const int32_t lifeTime = 240;

private: //メンバ変数

	int32_t shotIntervalTimer = shotIntervalTime;
	int32_t lifeTimer;
	Object3d* enemy;
	Sprite* test;
	GameScene* gameScene;
	Vector3 pos;
	Vector3 oldPos;
	float moveSpeedX;
	float moveSpeedY;
	EnemyStyle type;
	bool isDead;
};

