#pragma once
#include "BaseShape.h"
#include "Vector3.h"

class SphereShape : public BaseShape
{
public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="radius">半径</param>
	SphereShape(const Vector3& pos, float radius);

	/// <summary>
	/// 形状タイプ取得
	/// </summary>
	/// <returns>球タイプ</returns>
	ShapeType GetShapeType() { return ShapeType::Sphere; }

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <returns>座標</returns>
	Vector3 GetPos() const { return pos_; }

	/// <summary>
	/// 半径取得
	/// </summary>
	/// <returns>半径</returns>
	float GetRadius() const { return radius_; }

private: //メンバ変数
	//座標
	Vector3 pos_;
	//半径
	float radius_;
};

