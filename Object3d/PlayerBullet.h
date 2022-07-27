#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"

class PlayerBullet
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

private: //メンバ変数
	Model* bulletModel;
	Object3d* bullet;
};

