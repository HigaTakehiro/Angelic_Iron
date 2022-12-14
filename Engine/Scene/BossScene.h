#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "MotionMath.h"
#include "BossScenePlayer.h"
#include "PlayerBullet.h"
#include "Sound.h"
#include "BaseBoss.h"
#include "FirstBoss.h"
#include "Particle2d.h"

class BossScenePlayer;
class BaseBoss;
class FirstBoss;

class BossScene : public BaseScene
{
public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// プレイヤー弾を追加
	/// </summary>
	void AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet);
	/// <summary>
	/// ボス弾を追加
	/// </summary>
	/// <param name="bossEnemy"></param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> bosBullet);

private: //メンバ変数

	//ビルリスト
	std::list<std::unique_ptr<Object3d>> buildings;
	//プレイヤー弾リスト
	std::list<std::unique_ptr<PlayerBullet>> playerBullets;
	//ボス弾リスト
	std::list<std::unique_ptr<EnemyBullet>> bossBullets;
	//2Dパーティクルリスト
	std::list<std::unique_ptr<Particle2d>> particles2d;
	//カメラ
	Camera* camera = nullptr;
	//サウンド
	Sound* sound = nullptr;
	//プレイヤー
	BossScenePlayer* player = nullptr;
	//地面
	Object3d* ground = nullptr;
	//天球
	Object3d* celetialSphere = nullptr;
	//ポストエフェクト
	PostEffect* postEffect = nullptr;
	PostEffect::PostEffectNo postEffectNo;

	Vector3 groundPos = { 0, 0, 0 }; //地面座標
	Vector3 groundScale = { 1, 1, 1 }; //地面の大きさ
	Vector3 spherePos = { 0, 0, 0 }; //天球座標
	Vector3 sphereScale = { 10, 10, 10 };  //天球の大きさ

	Sprite* pause = nullptr;
	Sprite* titleBack = nullptr;
	Sprite* back = nullptr;

	//BaseBoss* boss;
	FirstBoss* firstBoss;

	XMFLOAT2 titleBackSize;
	XMFLOAT2 backSize;
	//スコア
	int score;

	//ポーズフラグ
	bool isPause;
	//タイトルバックフラグ
	bool isTitleBack;
	//死亡フラグ
	bool isDead;
};

