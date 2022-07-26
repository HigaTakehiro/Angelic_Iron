#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"

class Enemy
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

private: //メンバ関数

private: //メンバ変数

	//エネミーの位置
	Vector3 enemyPos[3];

	//エネミーの向き
	Vector3 enemyRot;

	//エネミーの大きさ
	Vector3 enemyScale = { 5, 5, 5 };

	//エネミーのモデル
	Model* enemyModel;

	//エネミーオブジェクト
	Object3d* enemy[3];
};

