#pragma once

class BaseBattleScene
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseBattleScene() = default;
	
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

protected: //メンバ関数
	/// <summary>
	/// 
	/// </summary>
	virtual void TextMessageUpdate();
};

