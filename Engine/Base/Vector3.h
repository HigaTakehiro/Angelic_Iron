#pragma once
#include <DirectXMath.h>
#include <cmath>

using namespace DirectX;

class Vector3 : public XMFLOAT3
{

public:
	//�R���X�g���N�^
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const XMVECTOR& vec);

	//�����o�֐�
	float length() const;
	Vector3& normalize();
	float dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;

	//�P�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const Vector3& v);
	Vector3& operator/=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

//2�����Z�q�I�[�o�[���[�h
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

//��Ԋ֐�
//���`���(1���֐����)
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);