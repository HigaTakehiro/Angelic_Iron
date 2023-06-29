#pragma once
#include "Sprite.h"
#include "TextDraw.h"

class MessageWindow
{
public: //列挙型
	//顔グラフィック
	enum class FaceGraphics {
		OPE_NORMALFACE,
		OPE_SMILEFACE,
		OPE_SURPRISEFACE
	};

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MessageWindow() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~MessageWindow() = default;

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
	/// 終了処理
	/// </summary>
	void Finalize();

private: //メンバ変数
	//オペレータ通常顔グラフィック
	std::unique_ptr<Sprite> opeNormalFace_[3];
	//オペレータ笑顔顔グラフィック
	std::unique_ptr<Sprite> opeSmileFace_[3];
	//オペレータ驚愕顔グラフィック
	std::unique_ptr<Sprite> opeSurpriseFace_[3];
	//テキストウィンドウ
	std::unique_ptr<Sprite> textWindow_;
	//顔ウィンドウ
	std::unique_ptr<Sprite> faceWindow_;

};

