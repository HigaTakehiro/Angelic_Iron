#pragma once
#include "camera.h"
#include "Vector3.h"
#include "MatCalc.h"
#include <DirectXMath.h>
#include <vector>
#include "KeyInput.h"

class RailCamera
{
private: //エイリアス
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="eye">カメラのワールド座標</param>
	/// <param name="rot">回転角</param>
	/// <param name="points">スプライン補間時に通る各ポイント</param>
	void Initialize(const Vector3& eye, const Vector3& rot, const std::vector<Vector3>& points, const float& maxTime);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

private: //メンバ関数

	/// <summary>
	/// スプライン補間
	/// </summary>
	/// <param name="points">通るポイント</param>
	/// <param name="startIndex">ポイントを通った時のカウント</param>
	/// <param name="t">時間</param>
	/// <returns>座標</returns>
	Vector3 Spline(const std::vector<Vector3>& points, const int& startIndex, const float& t);

	/// <summary>
	/// スプライン補間の移動
	/// </summary>
	void SplineMove();

	/// <summary>
	/// ワールド行列補間
	/// </summary>
	void UpdateMatWorld();

private: //メンバ変数
	Vector3 eye; //ワールド座標
	Vector3 rot; //回転角
	Vector3 target; //ターゲット
	XMMATRIX matWorld; //ワールド行列
	std::vector<Vector3> points; //スプライン補間用の各ポイント

	long long startTime; //開始時間
	long long nowCount; //現在時間
	long long elapsedCount; //経過時間 

	float maxTime; //ポイント間を移動する時間
	float timeRate; //移動した時間を0~1で評価
	int startIndex; //移動したポイントをカウント

	Vector3 initPos;
	Vector3 initRot;

	bool isStop = true;
};

