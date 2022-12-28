#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "DirectXSetting.h"

class Light
{
private: // エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	Light() = default;

	~Light() = default;

public: //サブクラス
	struct ConstBufferData {
		XMVECTOR lightVec; //ライトへの方向を表すベクトル
		XMFLOAT3 lightColor; //ライトの色
	};

public: //静的メンバ関数

	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <returns>インスタンス</returns>
	static Light* Create();

	/// <summary>
	/// ライト座標をセット
	/// </summary>
	/// <param name="light"></param>
	static void SetLightPos(XMFLOAT3 pos);

	/// <summary>
	/// ライト座標を取得
	/// </summary>
	/// <returns>ライト座標</returns>
	static XMFLOAT3 GetLightPos() { return pos; }

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 定数バッファへデータ転送
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightDir">ライト方向</param>
	void SetLightDir(const XMVECTOR& lightDir);

	/// <summary>
	/// ライト色をセット
	/// </summary>
	/// <param name="lightColor">ライト色</param>
	void SetLightColor(const XMFLOAT3& lightColor);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rootParameter">指定ルートパラメータ</param>
	void Draw(UINT rootParameter);

private: //静的メンバ変数
	//デバイス
	static ID3D12Device* device;
	//ライト座標
	static XMFLOAT3 pos;

private: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//ライト光線方向
	XMVECTOR lightDir = { 1, 0, 0, 0 };
	//ライト色
	XMFLOAT3 lightColor = { 1, 1, 1 };
	//ダーティフラグ
	bool isDirty = false;
};