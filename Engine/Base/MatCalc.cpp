#include "MatCalc.h"

MatCalc* MatCalc::GetIns()
{
	static MatCalc instance;
	return &instance;
}

XMVECTOR MatCalc::WDivided(const XMVECTOR& pos, const XMMATRIX& mat, const bool isWSlide) {
	float x, y, z, w;

	x = (pos.m128_f32[0] * mat.r[0].m128_f32[0]) + (pos.m128_f32[1] * mat.r[1].m128_f32[0]) + (pos.m128_f32[2] * mat.r[2].m128_f32[0]) + (1.0f * mat.r[3].m128_f32[0]);
	y = (pos.m128_f32[0] * mat.r[0].m128_f32[1]) + (pos.m128_f32[1] * mat.r[1].m128_f32[1]) + (pos.m128_f32[2] * mat.r[2].m128_f32[1]) + (1.0f * mat.r[3].m128_f32[1]);
	z = (pos.m128_f32[0] * mat.r[0].m128_f32[2]) + (pos.m128_f32[1] * mat.r[1].m128_f32[2]) + (pos.m128_f32[2] * mat.r[2].m128_f32[2]) + (1.0f * mat.r[3].m128_f32[2]);

	w = pos.m128_f32[3];
	if (isWSlide) {
		w = z;
	}

	x = x / w;
	y = y / w;
	z = z / w;
	w = w / w;

	return XMVECTOR{ x, y, z, w };
}

XMVECTOR MatCalc::WDivision(const XMVECTOR& pos, const bool isWSlide) {
	float x, y, z, w;
	x = pos.m128_f32[0];
	y = pos.m128_f32[1];
	z = pos.m128_f32[2];
	w = pos.m128_f32[3];

	if (isWSlide) {
		w = z;
	}

	x = x / w;
	y = y / w;
	z = z / w;
	w = w / w;

	return XMVECTOR{ x, y, z, w };
}

XMVECTOR MatCalc::VecDivided(const XMVECTOR& pos, const XMMATRIX& mat) {
	float x, y, z, w;

	x = (pos.m128_f32[0] * mat.r[0].m128_f32[0]) + (pos.m128_f32[1] * mat.r[1].m128_f32[0]) + (pos.m128_f32[2] * mat.r[2].m128_f32[0]) + (0.0f * mat.r[3].m128_f32[0]);
	y = (pos.m128_f32[0] * mat.r[0].m128_f32[1]) + (pos.m128_f32[1] * mat.r[1].m128_f32[1]) + (pos.m128_f32[2] * mat.r[2].m128_f32[1]) + (0.0f * mat.r[3].m128_f32[1]);
	z = (pos.m128_f32[0] * mat.r[0].m128_f32[2]) + (pos.m128_f32[1] * mat.r[1].m128_f32[2]) + (pos.m128_f32[2] * mat.r[2].m128_f32[2]) + (0.0f * mat.r[3].m128_f32[2]);
	w = 0.0f;

	return XMVECTOR{ x, y, z, w };
}

XMVECTOR MatCalc::PosDivided(const XMVECTOR& pos, const XMMATRIX& mat, const bool isWSlide) {
	float x, y, z, w;

	x = (pos.m128_f32[0] * mat.r[0].m128_f32[0]) + (pos.m128_f32[1] * mat.r[1].m128_f32[0]) + (pos.m128_f32[2] * mat.r[2].m128_f32[0]) + (1.0f * mat.r[3].m128_f32[0]);
	y = (pos.m128_f32[0] * mat.r[0].m128_f32[1]) + (pos.m128_f32[1] * mat.r[1].m128_f32[1]) + (pos.m128_f32[2] * mat.r[2].m128_f32[1]) + (1.0f * mat.r[3].m128_f32[1]);
	z = (pos.m128_f32[0] * mat.r[0].m128_f32[2]) + (pos.m128_f32[1] * mat.r[1].m128_f32[2]) + (pos.m128_f32[2] * mat.r[2].m128_f32[2]) + (1.0f * mat.r[3].m128_f32[2]);

	w = 1.0f;

	if (isWSlide == true) {
		w = z;
	}

	return XMVECTOR{ x, y, z, w };
}

XMMATRIX MatCalc::InverseMatrix(const XMMATRIX& mat) {
	float matJudge;
	XMMATRIX invMat;
	invMat = mat;
	//matJudge = (mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[1].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	+ mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	- mat.r[0].m128_f32[0] * mat.r[0].m128_f32[1] * mat.r[0].m128_f32[2] * mat.r[0].m128_f32[3]
	//	);
	//if (matJudge != 0) return invMat;

	//1列目1行目
	invMat.r[0].m128_f32[0] = -1 / ((mat.r[1].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[3]) //a22 * a33 * a44
		+ (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1]) //a23 * a34 * a42
		+ (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2]) //a24 * a32 * a43
		- (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2]) //a22 * a34 * a43
		- (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]) //a23 * a32 * a44
		- (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1])); //a24 * a33 * a42
	//1列目2行目
	invMat.r[0].m128_f32[1] = -1 / ((mat.r[0].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2]) //a12 * a34 * a43
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]) //a13 * a32 * a44
		+ (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1]) //a14 * a33 * a42
		- (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[3]) //a12 * a33 * a44
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1]) //a13 * a34 * a42
		- (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2])); //a14 * a32 * a43
	//1列目3行目
	invMat.r[0].m128_f32[2] = -1 / ((mat.r[0].m128_f32[1] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[3]) //a12 * a23 * a44
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[1]) //a13 * a24 * a42
		+ (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[1] * mat.r[3].m128_f32[2]) //a14 * a22 * a43
		- (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[2]) //a12 * a24 * a43
		- (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[1] * mat.r[3].m128_f32[3]) //a13 * a22 * a44
		- (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[1])); //a14 * a23 * a42
	//1列目4行目
	invMat.r[0].m128_f32[3] = -1 / ((mat.r[0].m128_f32[1] * mat.r[1].m128_f32[3] * mat.r[2].m128_f32[2]) //a12 * a24 * a33
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[1] * mat.r[2].m128_f32[3]) //a13 * a22 * a34
		+ (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[2] * mat.r[2].m128_f32[1]) //a14 * a23 * a32
		- (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[2] * mat.r[2].m128_f32[3]) //a12 * a23 * a34
		- (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[3] * mat.r[2].m128_f32[1]) //a13 * a24 * a32
		- (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[1] * mat.r[2].m128_f32[2])); //a14 * a22 * a33
	//2列目1行目
	invMat.r[1].m128_f32[0] = -1 / ((mat.r[1].m128_f32[0] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2]) //a21 * a34 * a43
		+ (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[3]) //a23 * a31 * a44
		+ (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[0]) //a24 * a33 * a41
		- (mat.r[1].m128_f32[0] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[3]) //a21 * a33 * a44
		- (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[0]) //a23 * a34 * a41
		- (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[2])); //a24 * a31 * a43
	//2列目2行目
	invMat.r[1].m128_f32[1] = -1 / ((mat.r[0].m128_f32[0] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[3]) //a11 * a33 * a44
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[0]) //a13 * a34 * a41
		+ (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[2]) //a14 * a31 * a43
		- (mat.r[0].m128_f32[0] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[2]) //a11 * a34 * a43
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[3]) //a13 * a31 * a44
		- (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[0])); //a14 * a33 * a41
	//2列目3行目
	invMat.r[1].m128_f32[2] = -1 / ((mat.r[0].m128_f32[0] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[2]) //a11 * a24 * a43
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[0] * mat.r[3].m128_f32[3]) //a13 * a21 * a44
		+ (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[0]) //a14 * a23 * a41
		- (mat.r[0].m128_f32[0] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[3]) //a11 * a23 * a44
		- (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[0]) //a13 * a24 * a41
		- (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[0] * mat.r[3].m128_f32[2])); //a14 * a21 * a43
	//2列目4行目
	invMat.r[1].m128_f32[3] = -1 / ((mat.r[0].m128_f32[0] * mat.r[1].m128_f32[2] * mat.r[2].m128_f32[3]) //a11 * a23 * a34
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[3] * mat.r[2].m128_f32[0]) // a13 * a24 * a31
		+ (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[0] * mat.r[2].m128_f32[2]) // a14 * a21 * a33
		- (mat.r[0].m128_f32[0] * mat.r[1].m128_f32[3] * mat.r[2].m128_f32[2]) // a11 * a24 * a33
		- (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[0] * mat.r[2].m128_f32[3]) // a13 * a21 * a34
		- (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[2] * mat.r[2].m128_f32[0])); // a14 * a23 * a31
	//3列目1行目
	invMat.r[2].m128_f32[0] = -1 / ((mat.r[1].m128_f32[0] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]) // a21 * a32 * a44
		+ (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[0]) // a22 * a34 * a41
		+ (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[1]) // a24 * a31 * a42
		- (mat.r[1].m128_f32[0] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1]) // a21 * a34 * a42
		- (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[3]) // a22 * a31 * a44
		- (mat.r[1].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[0])); // a24 * a32 * a41
	//3列目2行目
	invMat.r[2].m128_f32[1] = -1 / ((mat.r[0].m128_f32[0] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[1]) // a11 * a34 * a41
		+ (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[3]) // a12 * a31 * a44
		+ (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[0]) // a14 * a32 * a41
		- (mat.r[0].m128_f32[0] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[3]) // a11 * a32 * a44
		- (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[3] * mat.r[3].m128_f32[0]) // a12 * a34 * a41
		- (mat.r[0].m128_f32[3] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[1])); // a14 * a31 * a42
	//3列目3行目
	invMat.r[2].m128_f32[2] = -1 / ((mat.r[0].m128_f32[0] * mat.r[1].m128_f32[1] * mat.r[3].m128_f32[3]) // a11 * a22 * a44
		+ (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[0]) // a12 * a24 * a41
		+ (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[0] * mat.r[3].m128_f32[1]) // a14 * a21 * a42
		- (mat.r[0].m128_f32[0] * mat.r[1].m128_f32[3] * mat.r[3].m128_f32[1]) // a11 * a24 * a42
		- (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[0] * mat.r[3].m128_f32[3]) // a12 * a21 * a44
		- (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[1] * mat.r[3].m128_f32[0])); // a14 * a22 * a41
	//3列目4行目
	invMat.r[2].m128_f32[3] = -1 / ((mat.r[0].m128_f32[0] * mat.r[1].m128_f32[3] * mat.r[2].m128_f32[1]) // a11 * a24 * a32
		+ (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[0] * mat.r[2].m128_f32[3]) // a12 * a21 * a34
		+ (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[1] * mat.r[2].m128_f32[0]) // a14 * a22 * a31
		- (mat.r[0].m128_f32[0] * mat.r[1].m128_f32[1] * mat.r[2].m128_f32[3]) // a11 * a22 * a34
		- (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[3] * mat.r[2].m128_f32[0]) // a12 * a24 * a31
		- (mat.r[0].m128_f32[3] * mat.r[1].m128_f32[0] * mat.r[2].m128_f32[1])); // a14 * a21 * a32
	//4列目1行目
	invMat.r[3].m128_f32[0] = -1 / ((mat.r[1].m128_f32[0] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1]) //a21 * a33 * a42
		+ (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[2]) // a22 * a31 * a43
		+ (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[0]) // a23 * a32 * a41
		- (mat.r[1].m128_f32[0] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2]) // a21 * a32 * a43
		- (mat.r[1].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[0]) // a22 * a33 * a41
		- (mat.r[1].m128_f32[2] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[1])); // a23 * a31 * a42
	//4列目2行目
	invMat.r[3].m128_f32[1] = -1 / ((mat.r[0].m128_f32[0] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[2]) // a11 * a32 * a43
		+ (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[0]) // a12 * a33 * a41
		+ (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[1]) // a13 * a31 * a42
		- (mat.r[0].m128_f32[0] * mat.r[2].m128_f32[2] * mat.r[3].m128_f32[1]) // a11 * a33 * a42
		- (mat.r[0].m128_f32[1] * mat.r[2].m128_f32[0] * mat.r[3].m128_f32[2]) // a12 * a31 * a43
		- (mat.r[0].m128_f32[2] * mat.r[2].m128_f32[1] * mat.r[3].m128_f32[0])); // a13 * a32 * a41
	//4列目3行目
	invMat.r[3].m128_f32[2] = -1 / ((mat.r[0].m128_f32[0] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[1]) // a11 * a23 * a42
		+ (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[0] * mat.r[3].m128_f32[2]) // a12 * a21 * a43
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[1] * mat.r[3].m128_f32[0]) // a13 * a22 * a41
		- (mat.r[0].m128_f32[0] * mat.r[1].m128_f32[1] * mat.r[3].m128_f32[2]) // a11 * a22 * a43
		- (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[2] * mat.r[3].m128_f32[0]) // a12 * a23 * a41
		- (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[0] * mat.r[3].m128_f32[1])); // a13 * a21 * a42
	//4列目4行目
	invMat.r[3].m128_f32[3] = -1 / ((mat.r[0].m128_f32[0] * mat.r[1].m128_f32[1] * mat.r[2].m128_f32[2]) // a11 * a22 * a33
		+ (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[2] * mat.r[2].m128_f32[0]) // a12 * a23 * a31
		+ (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[0] * mat.r[2].m128_f32[1]) // a13 * a21 * a32
		- (mat.r[0].m128_f32[0] * mat.r[1].m128_f32[2] * mat.r[2].m128_f32[1]) // a11 * a23 * a32
		- (mat.r[0].m128_f32[1] * mat.r[1].m128_f32[0] * mat.r[2].m128_f32[2]) // a12 * a21 * a33
		- (mat.r[0].m128_f32[2] * mat.r[1].m128_f32[1] * mat.r[2].m128_f32[0])); // a13 * a22 * a31

	return invMat;
}