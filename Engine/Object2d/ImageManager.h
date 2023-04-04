#pragma once
#include "Sprite.h"

class ImageManager final
{
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager & obj) = delete;
	ImageManager& operator=(const ImageManager & obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static ImageManager* GetIns();

public: //画像名
	enum ImageName {
		aim = 1,
		title,
		score,
		scoreNumbers,
		playerUI,
		playerHP,
		playerBullet,
		reload,
		enemyDead,
		StartButton,
		Stage1,
		Stage2,
		ManualButton,
		Manual,
		Manual_2,
		Close,
		Pause,
		TitleBack,
		Back,
		Restart,
		Boost,
		Allow,
		FaceWindow,
		TextWindow,
		OPE_NORMAL,
		OPE_SURPRISE,
		OPE_SMILE,
		SceneChangeBar,
		Bomb,
		HPBar
	};

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
};

