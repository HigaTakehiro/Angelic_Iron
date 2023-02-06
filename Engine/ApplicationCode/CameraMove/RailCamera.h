#pragma once
#include "camera.h"
#include "Vector3.h"
#include <DirectXMath.h>
#include <vector>
#include "KeyInput.h"
#include <chrono>
#include <thread>

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
	void Initialize(const Vector3& eye, const Vector3& rot, const std::vector<Vector3>& points, float maxTime, bool isRoop = false);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(float delayCount = 60.0f);

	/// <summary>
	/// リセット
	/// </summary>
	void Reset(std::vector<Vector3>& points);

	/// <summary>
	/// 開始時間のセット
	/// </summary>
	void SetStartTime(long long startTime) { this->startTime = startTime; }

	/// <summary>
	/// ダメージエフェクト発生用フラグを立てる
	/// </summary>
	void SetIsDamage() { isDamage = true; }

	/// <summary>
	/// ワールド行列取得
	/// </summary>
	/// <returns></returns>
	XMMATRIX GetMatWorld() { return matWorld; }

	/// <summary>
	/// 終点フラグ取得
	/// </summary>
	/// <returns>終点フラグ</returns>
	bool GetIsEnd() { return isEnd; }

private: //メンバ関数

	/// <summary>
	/// スプライン補間
	/// </summary>
	/// <param name="points">通るポイント</param>
	/// <param name="startIndex">ポイントを通った時のカウント</param>
	/// <param name="t">時間</param>
	/// <returns>座標</returns>
	Vector3 Spline(const std::vector<Vector3>& points, int startIndex, float t);

	/// <summary>
	/// スプライン補間の移動
	/// </summary>
	void SplineMove();

	/// <summary>
	/// ワールド行列補間
	/// </summary>
	void UpdateMatWorld();

	/// <summary>
    /// ダメージを受けた時のカメラ演出
    /// </summary>
	void DamageCameraEffect();

private: //静的メンバ変数
	//ダメージエフェクト発生時間
	static const int damageEffectTime = 20;

private: //メンバ変数
	Vector3 eye; //ワールド座標
	Vector3 rot; //回転角
	Vector3 target; //ターゲット
	XMMATRIX matWorld; //ワールド行列
	std::vector<Vector3> points; //スプライン補間用の各ポイント

	long long startTime; //開始時間
	long long nowCount; //現在時間
	long long elapsedCount; //経過時間 
	std::chrono::steady_clock::time_point reference;

	float maxTime; //ポイント間を移動する時間
	float timeRate; //移動した時間を0~1で評価
	int startIndex = 1; //移動したポイントをカウント

	Vector3 initPos; //初期座標
	Vector3 initRot; //初期回転

	bool isStop = false; //デバッグ用カメラ停止フラグ
	bool isDamage = false; //ダメージを受けたかのフラグ
	bool isRoop = false; //ループ用フラグ
	bool isEnd = false; //終点フラグ
	float delayCount = 0;

	int  damageEffectTimer; //ダメージ演出用タイマー
};

