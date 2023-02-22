#pragma once
#include "Model.h"
#include "FBXLoader.h"
#include <map>
#include <vector>

class ModelManager
{
private:
	ModelManager() = default;
	~ModelManager();
	ModelManager(const ModelManager & obj) = delete;
	ModelManager& operator=(const ModelManager & obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static ModelManager* GetIns();

public: //モデル名
	enum ModelName {
		Player_Normal,
		Player_Stand,
		Player_Down,
		Gun,
		Bullet,
		BulletCase,
		Enemy,
		Shot,
		Ground,
		CelestialSphere,
		Building,
		BossBody,
		BossHand,
		Aircraft_Carrier,
		Wave,
		Shadow
	};

	enum FBXModelName {
		Test
	};

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// モデル追加
	/// </summary>
	/// <param name="modelName">読み込みたいモデル名</param>
	/// <param name="modelKey">アクセスするモデルのキー</param>
	/// <param name="isSmoothing">スムージング処理するかどうか</param>
	void LoadModel(const std::string modelName, const std::string modelKey, bool isSmoothing = false);

	/// <summary>
	/// FBXモデル追加
	/// </summary>
	/// <param name="modelName">モデル名</param>
	void LoadFBXModel(const std::string modelName);

	/// <summary>
	/// モデル取得
	/// </summary>
	/// <param name="modelKey">モデルキー</param>
	/// <returns>モデル</returns>
	Model* GetModel(const std::string modelKey) { return models[modelKey]; }

	/// <summary>
	/// FBXモデル取得
	/// </summary>
	/// <param name="modelName">モデル名</param>
	/// <returns>FBXモデル</returns>
	FBXModel* GetFBXModel(const FBXModelName modelName) { return fbxModels[modelName]; }

private: //メンバ変数
	//std::vector<Model*> models;
	std::map<std::string, Model*> models;
	std::vector<FBXModel*> fbxModels;
};

