#include "Camera.h"

using namespace DirectX;

XMMATRIX Camera::matView{};
XMMATRIX Camera::matProjection{};
XMMATRIX Camera::matWorld{};
XMFLOAT3 Camera::eye = { 0, 200.0f, -200.0f };
XMFLOAT3 Camera::target = { 0, 0, 0 };
XMFLOAT3 Camera::up = { 0, 1, 0 };

void Camera::InitializeCamera(int window_width, int window_height)
{
	// ビュー行列の生成
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 10000.0f
	);

	//ワールド行列の生成
	matWorld = XMMatrixTranslation(eye.x, eye.y, eye.z);
}

void Camera::SetEye(XMFLOAT3 eye)
{
	Camera::eye = eye;

	UpdateViewMatrix();

	UpdateWorldMatrix();
}

void Camera::SetTarget(XMFLOAT3 target)
{
	Camera::target = target;

	UpdateViewMatrix();

	UpdateWorldMatrix();
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

void Camera::UpdateViewMatrix()
{
	// ビュー行列の更新
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::UpdateWorldMatrix()
{
	float xRot, yRot, zRot;
	XMFLOAT3 distance;
	XMMATRIX matRot, matTrans;

	distance = XMFLOAT3(eye.x - target.x, eye.y - target.y, eye.z - target.z);
	xRot = (atan2(distance.y, distance.z) * 180.0f / 3.14f);
	yRot = (atan2(distance.x, distance.z) * 180.0f / 3.14f);
	zRot = (atan2(distance.y, distance.x) * 180.0f / 3.14f);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(zRot));
	matRot *= XMMatrixRotationX(XMConvertToRadians(xRot));
	matRot *= XMMatrixRotationY(XMConvertToRadians(yRot));
	matTrans = XMMatrixTranslation(eye.x, eye.y, eye.z);

	matWorld = XMMatrixIdentity();
	matWorld *= matRot;
	matWorld *= matTrans;

}