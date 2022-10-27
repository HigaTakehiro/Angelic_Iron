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
	//1列目1行目
	invMat.r[0].m128_f32[0] = (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[3]) 
		+ (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1]) 
		+ (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2]) 
		- (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2]) 
		- (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1]);
	//1列目2行目
	invMat.r[0].m128_f32[1] = (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1])
		- (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[2])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1])
		- (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2]);
	//1列目3行目
	invMat.r[0].m128_f32[2] = (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[1])//←
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//1列目4行目
	invMat.r[0].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2列目1行目
	invMat.r[1].m128_f32[0] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2列目2行目
	invMat.r[1].m128_f32[1] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2列目3行目
	invMat.r[1].m128_f32[2] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//2列目4行目
	invMat.r[1].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3列目1行目
	invMat.r[2].m128_f32[0] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3列目2行目
	invMat.r[2].m128_f32[1] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3列目3行目
	invMat.r[2].m128_f32[2] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//3列目4行目
	invMat.r[2].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4列目1行目
	invMat.r[3].m128_f32[0] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4列目2行目
	invMat.r[3].m128_f32[1] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4列目3行目
	invMat.r[3].m128_f32[2] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
	//4列目4行目
	invMat.r[3].m128_f32[3] = (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3])
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]);
}