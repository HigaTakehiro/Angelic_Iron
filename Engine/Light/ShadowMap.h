#pragma once
#include <DirectXMath.h>

class ShadowMap {
private: //�G�C���A�X
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//�萔�o�b�t�@�f�[�^
	struct ConstBufferData {
		XMMATRIX lightVP;
		XMFLOAT4 lightColor;
		XMFLOAT3 lightDir;
	};

public: //�����o�֐�

};