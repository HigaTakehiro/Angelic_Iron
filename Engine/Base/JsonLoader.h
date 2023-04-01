#pragma once
#include <string>
#include <json.hpp>
#include <fstream>
#include <vector>
#include <list>
#include "Vector3.h"
#include "Object3d.h"
#include "ModelManager.h"
#include "BaseEnemy.h"

class JsonLoader
{
public:
	//ステージオブジェクトデータ
	struct StageData {
		struct ObjectData {
			std::string fileName;
			Vector3 transform;
			Vector3 rotation;
			Vector3 scaling;
			bool isWave;
		};
		std::vector<ObjectData> stageObjects;
	};

	struct EnemyData {
		struct EnemyStatus {
			std::string fileName;
			Vector3 transform;
			Vector3 rotation;
			Vector3 scaling;
			int32_t waitTime;
			int32_t lifeTime;
			int32_t shotCoolTime;
			int hp;
		};
		std::vector<EnemyStatus> enemyObjects;
	};

public:
	JsonLoader() = default;
	~JsonLoader() = default;

public: //メンバ関数
	/// <summary>
	/// ステージデータjsonファイル読み込み及び生成
	/// </summary>
	/// <param name="fileName">jsonファイル</param>
	void StageDataLoadandSet(const std::string fileName);

	/// <summary>
	/// エネミーデータjsonファイル読み込み
	/// </summary>
	/// <param name="fileName"></param>
	void EnemyDataLoad(const std::string fileName);

	/// <summary>
	/// エネミーデータ更新処理
	/// </summary>
	/// <param name="isPause">ポーズフラグ</param>
	void EnemyDataUpdate(bool isPause);

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

private: //静的メンバ変数
	static const std::string baseDirectory;
	static const std::string extension;

private: //メンバ変数
	//ステージオブジェクト
	std::list<std::unique_ptr<Object3d>> allObjects;
	//エネミーオブジェクト
	std::list<std::unique_ptr<BaseEnemy>> allEnemies;
	//エネミーjsonデータ
	nlohmann::json enemyJsonData;
	//ポップ待機フラグ
	bool isWait;
	//ポップ待機タイマー
	int32_t waitTimer;
};