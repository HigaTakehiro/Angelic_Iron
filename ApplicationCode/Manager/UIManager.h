#pragma once
#include "Sprite.h"
#include "Button.h"
#include "JsonLoader.h"
#include "SceneManager.h"
#include "Vector2.h"

class UIManager
{
public: //構造体

	enum class UIType {
		Back,
		HP,
		Bullet,
		Anime
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
	void Initialize(const std::string fileName);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(bool isPause);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(bool isPause);

private: //定数
	//アニメーション時間
	static const int32_t animeTime = 20;

private: //メンバ変数
	//全てのUI
	std::list<std::unique_ptr<UIData>> allUI_;
	//全てのボタン
	std::list<std::unique_ptr<ButtonData>> allButton_;
};