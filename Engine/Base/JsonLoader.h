#pragma once
#include <string>
#include <json.hpp>
#include <fstream>
#include <vector>
#include <list>
#include "Vector3.h"
#include "Object3d.h"
#include "ModelManager.h"

class JsonLoader
{
public:
	struct StageData {
		struct ObjectData {
			std::string  fileName;
			Vector3 transform;
			Vector3 rotation;
			Vector3 scaling;
		};
		std::vector<ObjectData> objects;
	};

public:
	JsonLoader() = default;
	~JsonLoader();

public: //メンバ関数
	/// <summary>
	/// ステージデータjsonファイル読み込み及び生成
	/// </summary>
	/// <param name="fileName">jsonファイル</param>
	void StageDataLoadandSet(const std::string fileName);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private: //静的メンバ変数
	static const std::string baseDirectory;
	static const std::string extension;

private: //メンバ変数
	std::list<std::unique_ptr<Object3d>> allObjects;
};

