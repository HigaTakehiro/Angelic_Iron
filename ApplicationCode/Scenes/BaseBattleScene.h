#pragma once
#include <stdint.h>
#include "Sprite.h"
#include "Vector2.h"
#include "Vector3.h"

class BaseBattleScene
{
public: //サブクラス
	enum class FaceGraphics {
		OPE_NORMALFACE,
		OPE_SURPRISEFACE,
		OPE_SMILEFACE
	};

public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseBattleScene() {};

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// ステージ番号をセットする
	/// </summary>
	/// <param name="stageNo">ステージ番号</param>
	void SetStageNo(int32_t stageNo) { stageNo_ = stageNo; }

protected: //メンバ関数
	/// <summary>
	/// 文字描画更新処理
	/// </summary>
	void TextMessageUpdate();

	/// <summary>
	/// 共通初期化処理
	/// </summary>
	void CommonInitialize();

	/// <summary>
	/// ポーズ処理
	/// </summary>
	virtual void Pause() = 0;

	/// <summary>
	/// シーン切り替え
	/// </summary>
	virtual void SceneChange() = 0;

	/// <summary>
	/// 敵の更新処理
	/// </summary>
	virtual void EnemyUpdates() = 0;

protected: //メンバ変数
	//ステージ番号
	int32_t stageNo_;
	//通常時オペレータ顔グラフィック
	std::unique_ptr<Sprite> opeNormal_[3];
	//笑顔オペレータ顔グラフィック
	std::unique_ptr<Sprite> opeSmile_[3];
	//驚愕オペレータ顔グラフィック
	std::unique_ptr<Sprite> opeSurprise_[3];
	//テキストウィンドウサイズ
	Vector2 textWindowSize_;
	//フェイスウィンドウサイズ
	Vector2 faceWindow_;
	//
};