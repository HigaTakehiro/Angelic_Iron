#pragma once
#include "Sprite.h"
#include "TextDraw.h"
#include "Vector2.h"
#include "ExternalFileLoader.h"
#include <sstream>

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
	void Initialize(const std::string& fileName);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// スプライト描画処理
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// テキストデータの描画
	/// </summary>
	void TextMessageDraw(bool isBomb);

private: //静的メンバ変数
	static const int32_t faceAnimeTime = 6;
	//テキストウィンドウ開放時間
	static const int32_t windowOpenTime = 120;
	//テキストウィンドウ閉鎖時間
	static const int32_t windowCloseTime = 120;


private: //メンバ変数
	//オペレータ通常顔グラフィック
	std::unique_ptr<Sprite> opeNormal_[3];
	//オペレータ笑顔顔グラフィック
	std::unique_ptr<Sprite> opeSmile_[3];
	//オペレータ驚愕顔グラフィック
	std::unique_ptr<Sprite> opeSurprise_[3];
	//顔グラフィック画像サイズ
	Vector2 faceSize_;

	//テキストウィンドウ
	std::unique_ptr<Sprite> textWindow_;
	//テキストウィンドウサイズ
	Vector2 textWindowSize_;
	//顔ウィンドウ
	std::unique_ptr<Sprite> faceWindow_;
	//顔ウィンドウサイズ
	Vector2 faceWindowSize_;
	//テキストスピード
	int32_t textSpeed_;
	//テキスト数
	int32_t textCount_;
	//テキスト追加時間
	int32_t textAddTimer_;
	//文字描画クラス
	TextDraw* textDraw_;
	//ウィンドウ開放タイマー
	int32_t windowOpenTimer_;
	//ウィンドウ閉鎖タイマー
	int32_t windowCloseTimer_;
	//メッセージデータ更新待機フラグ
	bool isMessageUpdateWait_;
	//メッセージデータ待機タイマー
	int32_t messageWaitTimer_;
	//メッセージデータ描画完了フラグ
	bool isTextDrawComplete_;
	//テキストウィンドウ開閉フラグ
	bool isTextWindowOpen_;
	//メッセージデータ格納用文字列
	std::stringstream textData_;
	//メッセージ出力用文字列
	std::wstring drawMessage_;
	//メッセージ格納用文字列
	std::wstring message_;
	//顔グラフィックアニメーションタイマー
	int32_t faceAnimeTimer_;
	//顔グラフィックアニメ
	int32_t faceAnimeCount_;
	//顔グラフィック
	FaceGraphics faceType_;
};

