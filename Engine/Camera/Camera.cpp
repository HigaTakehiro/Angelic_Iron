#include "Camera.h"

using namespace DirectX;

XMMATRIX Camera::matView_{};
XMMATRIX Camera::matProjection_{};
XMMATRIX Camera::matWorld_{};
XMMATRIX Camera::matViewPort_{};
XMFLOAT3 Camera::eye_ = { 0, 200.0f, -200.0f };
XMFLOAT3 Camera::target_ = { 0, 0, 0 };
XMFLOAT3 Camera::up_ = { 0, 1, 0 };
XMMATRIX Camera::matBillboard_ = XMMatrixIdentity();
XMMATRIX Camera::matBillboardY_ = XMMatrixIdentity();
bool Camera::isMatWorldCalc_ = false;

void Camera::InitializeCamera(int32_t window_width, int32_t window_height)
{
	// ビュー行列の生成
	UpdateViewMatrix();

	// 透視投影による射影行列の生成
	matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 10000.0f
	);

	//ワールド行列の生成
	matWorld_ = XMMatrixTranslation(eye_.x, eye_.y, eye_.z);

	//ビューポート行列の生成
	matViewPort_ = XMMatrixIdentity();
	matViewPort_.r[0].m128_f32[0] = (float)window_width / 2.0f;
	matViewPort_.r[1].m128_f32[1] = -1.0f * (float)(window_height / 2.0f);
	matViewPort_.r[2].m128_f32[2] = 1.0f;
	matViewPort_.r[3].m128_f32[0] = (float)window_width / 2.0f;
	matViewPort_.r[3].m128_f32[1] = (float)window_height / 2.0f;
	matViewPort_.r[3].m128_f32[3] = 1.0f;
}

void Camera::SetEye(XMFLOAT3 eye_)
{
	Camera::eye_ = eye_;

	UpdateViewMatrix();

	if (isMatWorldCalc_) {
		UpdateWorldMatrix();
	}
}

void Camera::SetTarget(XMFLOAT3 target_)
{
	Camera::target_ = target_;

	UpdateViewMatrix();

	if (isMatWorldCalc_) {
		UpdateWorldMatrix();
	}
}

void Camera::CameraMoveVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::CameraMoveEyeVector(XMFLOAT3 move)
{
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera::CameraMoveTargetVector(XMFLOAT3 move) {
	XMFLOAT3  target_moved = GetTarget();

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetTarget(target_moved);
}

void Camera::UpdateViewMatrix() {

	XMVECTOR eyePosition = XMLoadFloat3(&eye_);
	XMVECTOR targetPosition = XMLoadFloat3(&target_);
	XMVECTOR upVector = XMLoadFloat3(&up_);

	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));

	cameraAxisZ = XMVector3Normalize(cameraAxisZ);
	XMVECTOR  cameraAxisX;
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	cameraAxisX = XMVector3Normalize(cameraAxisX);

	XMVECTOR cameraAxisY;
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);

	XMMATRIX matCameraRot;
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);

	matBillboard_.r[0] = cameraAxisX;
	matBillboard_.r[1] = cameraAxisY;
	matBillboard_.r[2] = cameraAxisZ;
	matBillboard_.r[3] = XMVectorSet(0, 0, 0, 1);

	XMVECTOR ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;
	ybillCameraAxisX = cameraAxisX;
	ybillCameraAxisY = XMVector3Normalize(upVector);
	ybillCameraAxisZ = XMVector3Cross(ybillCameraAxisX, ybillCameraAxisY);

	matBillboardY_.r[0] = ybillCameraAxisX;
	matBillboardY_.r[1] = ybillCameraAxisY;
	matBillboardY_.r[2] = ybillCameraAxisZ;
	matBillboardY_.r[3] = XMVectorSet(0, 0, 0, 1);

	matView_ = XMMatrixTranspose(matCameraRot);

	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);

	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	matView_.r[3] = translation;
}

void Camera::UpdateWorldMatrix()
{
	float xRot, yRot, zRot;
	XMFLOAT3 distance;
	XMMATRIX matRot, matTrans;

	distance = XMFLOAT3(eye_.x - target_.x, eye_.y - target_.y, eye_.z - target_.z);
	xRot = -(atan2(distance.y, sqrtf((float)pow(distance.z, 2)) + (float)pow(distance.x, 2)) * 180.0f / 3.14f);
	yRot = (atan2(distance.x, distance.z) * 180.0f / 3.14f);
	zRot = 0;
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(zRot));
	matRot *= XMMatrixRotationX(XMConvertToRadians(xRot));
	matRot *= XMMatrixRotationY(XMConvertToRadians(yRot));
	matTrans = XMMatrixTranslation(eye_.x, eye_.y, eye_.z);

	up_ = XMFLOAT3{ matRot.r[1].m128_f32[0], matRot.r[1].m128_f32[1], matRot.r[1].m128_f32[2] };

	matWorld_ = XMMatrixIdentity();
	matWorld_ *= matRot;
	matWorld_ *= matTrans;

}

void Camera::SetUp(XMFLOAT3 up_) {
	Camera::up_ = up_;

	UpdateViewMatrix();
}

void Camera::SetMatWorld(XMMATRIX matWorld_) {
	Camera::matWorld_ = matWorld_;
	Camera::isMatWorldCalc_ = true;
}