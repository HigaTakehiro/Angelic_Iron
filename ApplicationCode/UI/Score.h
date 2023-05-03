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
	/// スコアを加算
	/// </summary>
	/// <param name="score">加算するスコア</param>
	void AddScore(int32_t score) { score += score; }

private: //メンバ変数
	//スコア
	int32_t score_;
	//以前のスコア
	int32_t preScore_;

	std::unique_ptr<Sprite> scoreNumber_[6];
};