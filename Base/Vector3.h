#pragma once
#include <DirectXMath.h>
#include <cmath>

using namespace DirectX;

class Vector3 : public XMFLOAT3
{

public:
	//コンストラクタ
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const XMVECTOR& vec);

	//メンバ関数
	float length() const;
	Vector3& normalize();
	float dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;

	//単項演算子オーバーロード
	Vector3 operator+() const;
	Vector3 operator-() const;

	//代入演算子オーバーロード
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

//2項演算子オーバーロード
//※いろんな引数のパターンに対応(引数の順序)するため、以下のように準備している
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

//補間関数
//線形補間(1次関数補間)
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);