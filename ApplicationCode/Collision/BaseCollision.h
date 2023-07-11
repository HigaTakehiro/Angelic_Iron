#pragma once
#include "BaseShape.h"
#include "Vector3.h"

class BaseCollision {
public: //メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseCollision() {};

	/// <summary>
	/// 当たっているかチェック
	/// </summary>
	/// <param name="shape1">判定したいオブジェクト1</param>
	/// <param name="shape2">判定したいオブジェクト2</param>
	/// <returns>当たっている</returns>
	virtual bool CollisionCheck(const BaseShape& shape1, const BaseShape& shape2) = 0;
};