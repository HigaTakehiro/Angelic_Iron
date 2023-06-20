//#pragma once
//#include "BaseEnemy.h"
//#include "Vector3.h"
//#include "BulletManager.h"
//#include "RailScene.h"
//#include "ParticleManager.h"
//#include <list>
//#include <vector>
//#include <sstream>
//
//class EnemyManager
//{
//public: //構造体
//	//敵ポップ用情報
//	struct EnemyData {
//		Vector3 pos_;
//		Vector3 scale_;
//		Vector3 rot_;
//		std::vector<Vector3> movePoints_;
//		std::string type_;
//		float moveTime_;
//		int32_t lifeTime_;
//		int32_t shotInterval_;
//		int32_t hp_;
//		int32_t waitTime_;
//	};
//
//public: //メンバ関数
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	EnemyManager() = default;
//	/// <summary>
//	/// デストラクタ
//	/// </summary>
//	~EnemyManager() = default;
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	void Initialize(const std::string& fileName);
//	/// <summary>
//	/// 更新処理
//	/// </summary>
//	void Update(bool isPause);
//	/// <summary>
//	/// 描画処理
//	/// </summary>
//	void Draw();
//	/// <summary>
//	/// スプライト描画処理
//	/// </summary>
//	void SpriteDraw();
//	/// <summary>
//	/// 敵データ更新処理
//	/// </summary>
//	void EnemyDataUpdate(bool isPause);
//	/// <summary>
//	/// 敵演出処理
//	/// </summary>
//	void EnemyReactions(BaseEnemy* enmey);
//	/// <summary>
//	/// 敵データ読み込み処理
//	/// </summary>
//	void LoadEnemyData();
//	/// <summary>
//	/// ロックオン処理
//	/// </summary>
//	void EnemyRockOnPerformance();
//	/// <summary>
//	/// 敵リスト取得
//	/// </summary>
//	/// <returns></returns>
//	std::list<std::unique_ptr<BaseEnemy>>& GetEnemies() { return enemies_; }
//	/// <summary>
//	/// 弾管理マネージャーセット
//	/// </summary>
//	/// <param name="bulletManager">弾管理マネージャ>
//	void SetBulletManager(BulletManager* bulletManager) { bulletManager_ = bulletManager; }
//	/// <summary>
//	/// レールシーンをセット
//	/// </summary>
//	/// <param name="railScene">レールシーン</param>
//	void SetRailScene(RailScene* railScene) { railScene_ = railScene; }
//	/// <summary>
//	/// プレイヤーをセット
//	/// </summary>
//	/// <param name="player">プレイヤー</param>
//	void SetPlayer(Player* player) { player_ = player; }
//	/// <summary>
//	/// パーティクルマネージャーをセット
//	/// </summary>
//	/// <param name="particleManager">パーティクルマネージャー</param>
//	void SetParticleManager(ParticleManager* particleManager) { particles_ = particleManager; }
//	/// <summary>
//	/// マウスカーソルがあっているかチェック
//	/// </summary>
//	/// <param name="enemy">敵</param>
//	/// <returns>マウスカーソルがあたっている</returns>
//	bool IsTargetCheck(DirectX::XMFLOAT2 enemyPos);
//
//private: //メンバ変数
//	// 敵オブジェクトリスト
//	std::list<std::unique_ptr<BaseEnemy>> enemies_;
//	//敵ポップ用情報リスト
//	std::list<EnemyData> enemyDatas_;
//	//敵外部ファイル格納用文字列
//	std::stringstream enemyData_;
//	/// <summary>
//	/// 弾管理マネージャー
//	/// </summary>
//	BulletManager* bulletManager_;
//	/// <summary>
//	/// レールシーン
//	/// </summary>
//	RailScene* railScene_;
//	/// <summary>
//	/// プレイヤー
//	/// </summary>
//	Player* player_;
//	//ポップ待機フラグ
//	bool isWait_;
//	//待機時間
//	int32_t waitTimer_;
//	//パーティクル
//	ParticleManager* particles_;
//	//イテレータ
//	std::list<EnemyData>::iterator it_;
//};
//
