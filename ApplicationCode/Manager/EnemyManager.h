#pragma once
#include "BaseEnemy.h"
#include "Vector3.h"
#include <list>
#include <vector>

class EnemyManager
{
public: //構造体
	//敵ポップ用情報
	struct EnemyData {
		Vector3 pos_;
		Vector3 scale_;
		Vector3 rot_;
		std::vector<Vector3> movePoints_;
		std::string type_;
		int32_t moveTime_;
		int32_t lifeTime_;
		int32_t shotInterval_;
		int32_t hp_;
	};

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EnemyManager() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager() = default;
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
	/// 敵データ更新処理
	/// </summary>
	void LoadEnemyUpdate();

private: //メンバ変数
	// 敵オブジェクトリスト
	std::list<std::unique_ptr<BaseEnemy>> enemies_;
	//敵ポップ用情報リスト
	std::list<EnemyData> enemyDatas_;
	//ポップ待機フラグ
	bool isWait_;
	//イテレータ
	std::list<EnemyData>::iterator it_;
};

