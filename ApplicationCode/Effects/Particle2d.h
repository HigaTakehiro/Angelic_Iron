#pragma once
#include "Sprite.h"
#include "imageManager.h"
#include "safeDelete.h"
#include <DirectXMath.h>

class Particle2d
{
public: //エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: 
	Particle2d() = default;

	~Particle2d();

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">発生座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="time">発生時間</param>
	/// <param name="imageName">画像名</param>
	/// <param name="anchorPoint">アンカーポイント</param>
	/// <param name="imageNo">分割画像数</param>
	/// <param name="texUpperLeft">画像左上/param>
	/// <param name="texLowerRight">画像右下</param>
	void Initialize(XMFLOAT2 pos, XMFLOAT2 scale, int32_t time, ImageManager::ImageName imageName, XMFLOAT2 anchorPoint = {0, 0}, int32_t imageNo = 0, XMFLOAT2 texUpperLeft = {0, 0}, XMFLOAT2 texLowerRight = {0, 0});

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
    /// 敵の状態を取得
    /// </summary>
    /// <returns>敵の状態</returns>
	bool IsDelete() const { return isDelete_; }

private: //メンバ変数

	XMFLOAT2 pos_; //発生座標
	int32_t deleteTime_; //発生時間
	XMFLOAT2 texUpperLeft_; //連続画像用左上座標
	XMFLOAT2 texLowerRight_; //連続画像用右上座標
	int32_t imageNo_; //分割画像数
	Sprite* particle_; //パーティクル

	int32_t nowTimer_; //現在時間
	int32_t drawTime_; //1つの画像の描画時間
	int32_t nowImage_; //現在の分割画像

	bool isDelete_; //消滅フラグ
};

