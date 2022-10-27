#include "MatCalc.h"

MatCalc* MatCalc::GetIns()
{
	static MatCalc instance;
	return &instance;
}

XMVECTOR MatCalc::Wdivided(const XMVECTOR& vec, const XMMATRIX& mat) {
	float x, y, z, w;

	x = (vec.m128_f32[0] * mat.r[0].m128_f32[0]) + (vec.m128_f32[1] * mat.r[1].m128_f32[0]) + (vec.m128_f32[2] * mat.r[2].m128_f32[0]) + (1.0f * mat.r[3].m128_f32[0]);
	y = (vec.m128_f32[0] * mat.r[0].m128_f32[1]) + (vec.m128_f32[1] * mat.r[1].m128_f32[1]) + (vec.m128_f32[2] * mat.r[2].m128_f32[1]) + (1.0f * mat.r[3].m128_f32[1]);
	z = (vec.m128_f32[0] * mat.r[0].m128_f32[2]) + (vec.m128_f32[1] * mat.r[1].m128_f32[2]) + (vec.m128_f32[2] * mat.r[2].m128_f32[2]) + (1.0f * mat.r[3].m128_f32[2]);
	w = 1.0f;

	w = z;
	x = x / w;
	y = y / w;
	z = z / w;

	return XMVECTOR{ x, y, z, w };
}

XMVECTOR MatCalc::VecDivided(const XMVECTOR& vec, const XMMATRIX& mat) {
	float x, y, z, w;

	x = (vec.m128_f32[0] * mat.r[0].m128_f32[0]) + (vec.m128_f32[1] * mat.r[1].m128_f32[0]) + (vec.m128_f32[2] * mat.r[2].m128_f32[0]) + (0.0f * mat.r[3].m128_f32[0]);
	y = (vec.m128_f32[0] * mat.r[0].m128_f32[1]) + (vec.m128_f32[1] * mat.r[1].m128_f32[1]) + (vec.m128_f32[2] * mat.r[2].m128_f32[1]) + (0.0f * mat.r[3].m128_f32[1]);
	z = (vec.m128_f32[0] * mat.r[0].m128_f32[2]) + (vec.m128_f32[1] * mat.r[1].m128_f32[2]) + (vec.m128_f32[2] * mat.r[2].m128_f32[2]) + (0.0f * mat.r[3].m128_f32[2]);
	w = 0.0f;

	return XMVECTOR{ x, y, z, w };
}

XMMATRIX MatCalc::InverseMatrix(const XMMATRIX& mat) {
	XMMATRIX invMat;
	//1���1�s��
	invMat.r[0].m128_f32[0] = (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[3]) 
		+ (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1]) 
		+ (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2]) 
		- (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2]) 
		- (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1]);
	//1���2�s��
	invMat.r[0].m128_f32[1] = (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1])
		- (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[2])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1])
		- (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2]);
	//1���3�s��
	invMat.r[0].m128_f32[2] = (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[1])//��
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//1���4�s��
	invMat.r[0].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2���1�s��
	invMat.r[1].m128_f32[0] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2���2�s��
	invMat.r[1].m128_f32[1] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2���3�s��
	invMat.r[1].m128_f32[2] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2���4�s��
	invMat.r[1].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3���1�s��
	invMat.r[2].m128_f32[0] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3���2�s��
	invMat.r[2].m128_f32[1] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3���3�s��
	invMat.r[2].m128_f32[2] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3���4�s��
	invMat.r[2].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4���1�s��
	invMat.r[3].m128_f32[0] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4���2�s��
	invMat.r[3].m128_f32[1] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4���3�s��
	invMat.r[3].m128_f32[2] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4���4�s��
	invMat.r[3].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
}