#pragma once
#include "Vector3.h"
#include <DirectXMath.h>

using namespace DirectX;

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;
};

//クォータニオンを作成
Quaternion quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
Quaternion quaternion(const Vector3& v, float angle);

//内積を求める
float dot(const Quaternion& q1, const Quaternion& q2);

//ノルムを求める
float length(const Quaternion& q);

//正規化する
Quaternion Qnormalize(const Quaternion& q);

//共役四元数を求める
Quaternion conjugate(const Quaternion& q);

//単項演算子オーバーロード
Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);

//代入演算子オーバーロード
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

//2項演算子オーバーロード
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);

Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t);
XMMATRIX rotate(const Quaternion& q);
Quaternion quaternion(const XMMATRIX& m);
Vector3 getAxis(const Quaternion& q);