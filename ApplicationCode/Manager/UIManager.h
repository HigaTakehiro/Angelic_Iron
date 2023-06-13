#pragma once
#include "Sprite.h"
#include "Button.h"
#include "JsonLoader.h"
#include "SceneManager.h"

class UIManager
{
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
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

private: //メンバ変数
	std::list<std::unique_ptr<Sprite>> allUI_;
	std::list<std::unique_ptr<Button>> allButton_;
};