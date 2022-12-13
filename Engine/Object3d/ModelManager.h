#pragma once
#include "Model.h"
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
		Enemy,
		Shot,
		Ground,
		CelestialSphere,
		Building,
		BossBody,
		BossHand,
		Shadow
	};

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// モデル追加
	/// </summary>
	void LoadModel(const std::string modelName);

	/// <summary>
	/// モデル取得
	/// </summary>
	/// <param name="modelName">モデル名</param>
	/// <returns>モデル</returns>
	Model* GetModel(const ModelName modelName) { return models[modelName]; }

private: //メンバ変数
	std::vector<Model*> models;
};

