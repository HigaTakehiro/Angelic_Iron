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
	/// 文字描画更新処理
	/// </summary>
	void TextMessageUpdate();

	/// <summary>
	/// 薬莢を追加
	/// </summary>
	void AddBulletCase();

	/// <summary>
	/// ポーズ処理
	/// </summary>
	virtual void Pause();

	/// <summary>
	/// シーン切り替え
	/// </summary>
	virtual void SceneChange();

	/// <summary>
	/// 敵の弾を追加
	/// </summary>
	virtual void AddEnemyBullet();

	/// <summary>
	/// プレイヤーの弾を追加
	/// </summary>
	virtual void AddPlayerBullet();

	/// <summary>
	/// 当たり判定チェック
	/// </summary>
	virtual void CollisionCheck();

	/// <summary>
	/// 敵の更新処理
	/// </summary>
	virtual void EnemyUpdates();
};