#pragma once
#include "Sprite.h"
#include "ImageManager.h"

class Score final
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Score() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Score() = default;

	/// <summary>
	/// コピーコンストラクタを禁止
	/// </summary>
	Score(const Score& obj) = delete;

	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	Score& operator=(const Score& obj) = delete;

public:
	enum class ScoreNumber {
		zero = 64 * 0,
		one = 64 * 1,
		two = 64 * 2,
		three = 64 * 3,
		four = 64 * 4,
		five = 64 * 5,
		six = 64 * 6,
		seven = 64 * 7,
		eight = 64 * 8,
		nine = 64 * 9
	};

public: //静的メンバ関数
	/// <summary>
	/// インスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static Score* GetIns();

public: //メンバ関数
	/// <summary>
	/// 初期化
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
	/// nの位の数字を判定する
	/// </summary>
	/// <param name="score">判定したいスコア</param>
	/// <param name="place">判定したいスコアの位</param>
	/// <returns></returns>
	ScoreNumber JudgeDigitNumber(int32_t score, int32_t digit);

	/// <summary>
	/// スコアを加算
	/// </summary>
	/// <param name="score">加算するスコア</param>
	void AddScore(int32_t score);

	/// <summary>
	/// スコアをセット
	/// </summary>
	/// <param name="score">セットするスコア</param>
	void SetScore(int32_t score) { score_ = score; }
	
	/// <summary>
	/// スコアを取得
	/// </summary>
	/// <returns></returns>
	int32_t GetScore() { return score_; }

private: //メンバ関数
	/// <summary>
	/// スコア加算演出
	/// </summary>
	void AddScorePerformance();

private: //静的メンバ変数
	//スコア加算演出時間
	const static int32_t scoreAddTime = 60;
	//スコア
	static int32_t score_;

private: //メンバ変数
	//スコアロール演出用座標
	float scoreRollPosX_[6];
	//加算するスコア
	int32_t addScore_;
	//加算するスコアのアルファ値
	float addScoreAlpha_;
	//スコア加算演出タイマー
	int32_t scoreAddTimer_;
	//スコア画像
	std::unique_ptr<Sprite> scoreNumber_[6];
	//プラス画像
	std::unique_ptr<Sprite> plus_;
	//加算スコア画像
	std::unique_ptr<Sprite> addScoreNumber_[4];
	//スコア加算フラグ
	bool isAddScore_;
};