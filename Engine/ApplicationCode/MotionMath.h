#pragma once
#include "Vector3.h"
#include <DirectXMath.h>

class MotionMath
{
private:
	MotionMath() = default;
	~MotionMath() = default;
	MotionMath(const MotionMath& obj) = delete;
	MotionMath& operator=(const MotionMath& obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static MotionMath* GetIns();

public: //軸指定用列挙型
	enum Axis {
		X,
		Y,
		Z
	};

public: //メンバ関数
	/// <summary>
	/// 円運動
	/// </summary>
	/// <param name="centerPos">中心座標</param>
	/// <param name="rotPos">回転させる座標</param>
	/// <param name="angle">角度</param>
	/// <param name="length">中心座標との距離</param>
	/// <param name="axis">どの軸を中心に回転させるか</param>
	/// <returns>座標</returns>
	Vector3 CircularMotion(const Vector3& centerPos, const Vector3& rotPos, float angle, const float length, const Axis axis);
};

