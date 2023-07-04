#pragma once
#include "ImageManager.h"
#include "Sprite.h"
#include "Vector2.h"

class RailTutorial
{
public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 上昇完了フラグセット
	/// </summary>
	/// <param name="isUp">上昇完了</param>
	void SetIsUPMove(bool isUp) { isUpMove_ = isUp; }
	/// <summary>
	/// 下降完了フラグセット
	/// </summary>
	/// <param name="isDown">下降完了</param>
	void SetIsDownMove(bool isDown) { isDownMove_ = isDown; }
	/// <summary>
	/// 左移動完了フラグセット
	/// </summary>
	/// <param name="isLeft">左移動完了</param>
	void SetIsLeftMove(bool isLeft) { isLeftMove_ = isLeft; }
	/// <summary>
	/// 右移動完了フラグセット
	/// </summary>
	/// <param name="isRight">右移動完了</param>
	void SetIsRightMove(bool isRight) { isRightMove_ = isRight; }
	/// <summary>
	/// 射撃完了フラグセット
	/// </summary>
	/// <param name="isShot"></param>
	void SetIsShot(bool isShot) { isShot_ = isShot; }
	/// <summary>
	/// ボム完了フラグセット
	/// </summary>
	/// <param name="isBomb"></param>
	void SetIsBomb(bool isBomb) { isBomb_ = isBomb; }
	//プレイヤー2d座標セット
	void SetPlayer2DPos(Vector2 player2DPos) { player2dPos_ = player2DPos; }

private: //静的メンバ変数
	//チュートリアル表示時間
	static const int32_t tutorialTime = 180;

private: //メンバ変数
	//チュートリアル表示タイマー
	int32_t tutorialTimer_;

	//上昇完了フラグ
	bool isUpMove_;
	//下降完了フラグ
	bool isDownMove_;
	//左移動完了フラグ
	bool isLeftMove_;
	//右移動完了フラグ
	bool isRightMove_;
	//射撃完了フラグ
	bool isShot_;
	//ボム攻撃完了フラグ
	bool isBomb_;
	//上昇キースプライト
	std::unique_ptr<Sprite> how_to_up_;
	//上昇スプライトアルファ値
	float upAlpha_;
	//下降キースプライト
	std::unique_ptr<Sprite> how_to_down_;
	//下降スプライトアルファ値
	float downAlpha_;
	//左移動キースプライト
	std::unique_ptr<Sprite> how_to_left_;
	//左スプライトアルファ値
	float leftAlpha_;
	//右移動キースプライト
	std::unique_ptr<Sprite> how_to_right_;
	//右スプライトアルファ値
	float rightAlpha_;
	//射撃キースプライト
	std::unique_ptr<Sprite> how_to_shot_;
	//射撃スプライトアルファ値
	float shotAlpha_;
	//ボムキースプライト
	std::unique_ptr<Sprite> how_to_bomb_;
	//ボムスプライトアルファ値
	float bombAlpha_;
	//プレイヤー2D座標
	Vector2 player2dPos_;
};