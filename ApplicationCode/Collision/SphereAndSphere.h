#pragma once
#include "Object3d.h"

class SphereAndSphere
{
public: //メンバ関数
	/// <summary>
	/// 当たり判定チェック(球と球)
	/// </summary>
	/// <param name="obj1">判定したいオブジェクト1</param>
	/// <param name="obj2">判定したいオブジェクト2</param>
	/// <returns>当たっている</returns>
	bool HitTest(Object3d* obj1, Object3d* obj2);
};

