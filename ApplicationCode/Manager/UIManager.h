#pragma once
#include "Sprite.h"
#include "Button.h"
#include "JsonLoader.h"
#include "SceneManager.h"
#include "Vector2.h"
#include "Player.h"

class Player;

class UIManager
{
public: //構造体

	enum class UIType {
		Back,
		HP,
		Bullet,
		Anime
	};

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

	struct HPUI {
		bool isHp_ = false;
		int32_t hp_ = 0;
		bool isRight_ = false;
	};

	struct BulletUI {
		bool isBullet_ = false;
		int32_t bulletCount_ = 0;
		bool isRight_ = false;
	};

	struct AnimeUI {
		bool isAnime_ = false;
		float animeSize_ = 0.0f;
		int32_t animeSpeed_ = 0;
		int32_t animeCount_ = 0;
	};

	struct UIData {
		Vector2 pos_;
		Vector2 size_;
		float rot_;
		std::unique_ptr<Sprite> uiSprite_;
		UIType type_;
		bool isPauseView_;
		struct HPUI hpType_;
		struct BulletUI bulletType_;
		struct AnimeUI animeType_;
	};

	struct ButtonData {
		Vector2 pos_;
		Vector2 size_;
		float rot_;
		std::unique_ptr<Button> button_;
		bool isPauseView_;
	};

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIManager() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~UIManager() = default;
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="fileName">読み込むファイル名</param>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(bool isPause, Player* player);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(bool isPause, Player* player);

	/// <summary>
	/// スコアをセット
	/// </summary>
	/// <param name="score">スコア</param>
	void SetScore(int32_t score) { score_ = score; }

private: //メンバ関数
	/// <summary>
	/// nの位の数字を判定する
	/// </summary>
	/// <param name="score">判定したいスコア</param>
	/// <param name="place">判定したいスコアの位</param>
	/// <returns></returns>
	ScoreNumber JudgeDigitNumber(int32_t score, int32_t digit);

private: //定数
	//アニメーション時間
	static const int32_t animeTime = 20;

	//ボム攻撃時間
	static const int32_t bombTime = 60 * 5;

private: //メンバ変数
	//全てのUI
	std::list<UIData> allUI_;
	//全てのボタン
	std::list<ButtonData> allButton_;

	//UI
	//スコアテキスト
	std::unique_ptr<Sprite> scoreSprite_ = nullptr;
	//スコア数字
	std::unique_ptr<Sprite> scoreNumber_[6] = {};
	//ボム攻撃タイマー数字
	std::unique_ptr<Sprite> bombTimerNumber_[3] = {};

	//スコア
	int32_t score_;
};