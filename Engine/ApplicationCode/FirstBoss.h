#pragma once
#include "BaseBoss.h"

class FirstBoss : public BaseBoss
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FirstBoss() = default;
	/// <summary>
	///	デストラクタ
	/// </summary>
	~FirstBoss() = default;

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const ModelManager::ModelName model, const Vector3& pos);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const Vector3& playerPos, const int delayTime = 0);
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// 行動
	/// </summary>
	void Action();

private: //静的メンバ変数

private: //メンバ変数
	
};

