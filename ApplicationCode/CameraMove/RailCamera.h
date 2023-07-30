#pragma once
#include "camera.h"
#include "Vector3.h"
#include <DirectXMath.h>
#include <vector>
#include "KeyInput.h"
#include <chrono>
#include <thread>
#include <string>

class RailCamera
{
private: //エイリアス
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //構造体
	
	//移動するポイント
	struct MovePoints {
		std::vector<Vector3> points_; //スプライン補間用の各ポイント
		std::vector<Vector3> cameraRot_; //カメラ角度
		std::vector<float> moveTime_; //ポイントに移動する時間
	};

public: //メンバ関数

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="fileName">読み込むレールポイントファイル</param>
	void Initialize(const std::string& fileName);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// ダメージエフェクト発生用フラグを立てる
	/// </summary>
	void SetIsDamage() { isDamage_ = true; }

	/// <summary>
	/// ワールド行列取得
	/// </summary>
	/// <returns></returns>
	XMMATRIX GetMatWorld() { return matWorld_; }

	/// <summary>
	/// 終点フラグ取得
	/// </summary>
	/// <returns>終点フラグ</returns>
	bool GetIsEnd() { return isEnd_; }

private: //メンバ関数

	/// <summary>
	/// スプライン補間の移動
	/// </summary>
	void SplineMove();

	/// <summary>
	/// ワールド行列補間
	/// </summary>
	void UpdateMatWorld();

	/// <summary>
	/// レールポイント読み込み
	/// </summary>
	/// <param name="fileName">読み込むレールポイントファイル</param>
	void LoadRailPoint(const std::string& fileName);

private: //静的メンバ変数

private: //メンバ変数
	Vector3 eye_; //ワールド座標
	Vector3 rot_; //回転角
	Vector3 target_; //ターゲット
	XMMATRIX matWorld_; //ワールド行列
	MovePoints movePoints_; //移動する各ポイント格納コンテナ

	long long nowCount_; //現在時間
	long long elapsedCount_; //経過時間 

	float timeRate_; //移動した時間を0~1で評価
	int32_t startIndex_ = 1; //移動したポイントをカウント

	Vector3 initPos_; //初期座標
	Vector3 initRot_; //初期回転

	bool isStop_ = false; //デバッグ用カメラ停止フラグ
	bool isDamage_ = false; //ダメージを受けたかのフラグ
	bool isRoop_ = false; //ループ用フラグ
	bool isEnd_ = false; //終点フラグ
	float delayCount_ = 0;
};

