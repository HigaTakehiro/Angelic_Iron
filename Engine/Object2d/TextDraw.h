#pragma once
#include "DirectXSetting.h"

class TextDraw
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

private: //メンバ関数
	void FontHandleCreate();

private: //静的メンバ変数
	//デフォルトフォントサイズ
	static const int defaultFontSize = 64;
	//デフォルトフォント横幅
	static const int defaultFontWeight = 1000;
	//デフォルトフォント
	static const char* defaultFont;

private: //メンバ変数
	//フォントサイズ
	int fontSize;
	//フォント横幅
	int fontWeight;
	//フォントハンドル
	LOGFONT lf;
};

