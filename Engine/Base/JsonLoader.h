#pragma once
#include <string>
#include <json.hpp>
#include <fstream>
#include <vector>
#include <list>
#include "Vector2.h"
#include "Vector3.h"
#include "Object3d.h"
#include "ModelManager.h"
#include "BaseEnemy.h"
#include "ShadowMap.h"

class JsonLoader
{
public:
	//ステージオブジェクトデータ
	struct StageData {
		struct ObjectData {
			std::string fileName_;
			Vector3 transform_;
			Vector3 rotation_;
			Vector3 scaling_;
			bool isWave_;
		};
		std::vector<ObjectData> stageObjects_;
	};

	enum class EnemyType {
		STR,
		AIM
	};
	//敵データ
	struct EnemyData {
		struct EnemyStatus {
			std::string fileName_;
			Vector3 transform_;
			Vector3 rotation_;
			Vector3 scaling_;
			JsonLoader::EnemyType enemyType_;
			int32_t waitTime_;
			int32_t lifeTime_;
			int32_t shotCoolTime_;
			int32_t hp_;
		};
		std::vector<EnemyStatus> enemyObjects_;
	};
	//UIデータ
	struct UIData {
		struct SpriteData {
			std::string fileName_;
			Vector2 pos_;
			Vector2 scale_;
			float rot_;
			std::string type_;
		};
		std::vector<SpriteData> uiObjects_;
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
	/// UIデータ読み込み
	/// </summary>
	/// <param name="fileName">jsonファイル</param>
	/// <returns>UIデータ</returns>
	std::list<std::unique_ptr<UIData>> UIDataLoad(const std::string fileName);

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
	std::list<std::unique_ptr<Object3d>> allObjects_;
	//エネミーオブジェクト
	std::list<std::unique_ptr<BaseEnemy>> allEnemies_;
	//エネミーjsonデータ
	nlohmann::json enemyJsonData_;
	//ポップ待機フラグ
	bool isWait_;
	//ポップ待機タイマー
	int32_t waitTimer_;
};