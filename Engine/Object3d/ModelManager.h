#pragma once
#include "Model.h"
#include <vector>

class ModelManager
{
private:
	ModelManager() = default;
	~ModelManager() = default;
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
		Player,
		Enemy,
		Shot
	};

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// モデル追加
	/// </summary>
	void LoadModel(const std::string modelName);

	/// <summary>
	/// モデル取得
	/// </summary>
	/// <param name="modelName">モデル名</param>
	/// <returns>モデル</returns>
	Model* GetModel(const ModelName modelName) { return model[modelName]; }

private: //メンバ変数
	std::vector<Model*> model;
};

