#pragma once

//形状
enum class ShapeType {
	Sphere,

	Num
};

class BaseShape
{
public: //メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseShape() {}

	/// <summary>
	/// 当たり判定形状取得
	/// </summary>
	/// <returns>当たり判定形状</returns>
	virtual ShapeType GetShapeType() = 0;
};

