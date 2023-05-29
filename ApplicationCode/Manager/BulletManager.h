#pragma once
#include "PlayerBullet.h"
#include "Bomb.h"
#include "EnemyBullet.h"
#include "BulletCase.h"

class BulletManager
{
public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	BulletManager() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~BulletManager() = default;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤー弾追加
	/// </summary>
	/// <param name="playerBullet">プレイヤー弾</param>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);

	/// <summary>
	/// 薬莢追加
	/// </summary>
	/// <param name="bulletCase">薬莢</param>
	void AddBulletCase(std::unique_ptr<BulletCase> bulletCase);

	/// <summary>
	/// 敵弾追加
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	/// <summary>
	/// ボム追加
	/// </summary>
	/// <param name="bomb">ボム</param>
	void AddBomb(std::unique_ptr<Bomb> bomb);

	/// <summary>
	/// プレイヤー弾リスト取得
	/// </summary>
	/// <returns>プレイヤー弾リスト</returns>
	const std::list<std::unique_ptr<PlayerBullet>>& GetPlayerBullets() { return playerBullets_; }

	/// <summary>
	/// 敵弾リスト取得
	/// </summary>
	/// <returns>敵弾リスト</returns>
	const std::list<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() { return enemyBullets_; }

	/// <summary>
	/// ボムリスト取得
	/// </summary>
	/// <returns>ボムリスト</returns>
	const std::list<std::unique_ptr<Bomb>>& GetBombs() { return bombs_; }

private: //メンバ変数
	//プレイヤー弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets_;
	//敵弾リスト
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//ボムリスト
	std::list<std::unique_ptr<Bomb>> bombs_;

	std::list<std::unique_ptr<BulletCase>> bulletCases_;
};