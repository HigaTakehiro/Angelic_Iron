#pragma once
#include "Object3d.h"
#include "Model.h"

class Shapes
{
public:

public: //静的メンバ関数
	/// <summary>
	/// インスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Shapes* GetIns();

	/// <summary>
	/// 平面の三角形を生成
	/// </summary>
	/// <param name="vertices_1">頂点1</param>
	/// <param name="vertices_2">頂点2</param>
	/// <param name="vertices_3">頂点3</param>
	/// <returns>平面の三角形</returns>
	static Object3d* CreateTriangle(XMFLOAT3 vertices_1, XMFLOAT3 vertices_2, XMFLOAT3 vertices_3);

	/// <summary>
	/// 平面の四角形を生成
	/// </summary>
	/// <param name="upperLeft">左上座標</param>
	/// <param name="lowerBottom">右下座標</param>
	/// <returns>平面の四角形</returns>
	static Object3d* CreateSquare(XMFLOAT2 upperLeft, XMFLOAT2 lowerBottom);

public: //メンバ関数
};

