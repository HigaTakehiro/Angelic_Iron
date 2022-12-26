#include "Light.h"

using namespace DirectX;

XMFLOAT3 Light::pos = { 0.0f, 0.0f, 0.0f };

void Light::SetLightPos(XMFLOAT3 pos) {
	Light::pos = pos;
}