#pragma once
#include "BaseBoss.h"
#include "BossScene.h"
#include "BossScenePlayer.h"
#include "BulletManager.h"

class FirstBoss : public BaseBoss
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FirstBoss() = default;
	/// <summary>
	///	デストラクタ
	/// </summary>
	~FirstBoss() = default;

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(const std::string modelKey, const Vector3& pos);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const Vector3& playerPos, const int32_t delayTime = 0);
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 画像描画処理
	/// </summary>
	void SpriteDraw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// 行動
	/// </summary>
	void Action();
	/// <summary>
	/// ムービー演出行動
	/// </summary>
	void MovieAction();
	/// <summary>
	/// 左手ヒット時コールバック関数
	/// </summary>
	void LeftHandOnCollision();
	/// <summary>
	/// 右手ヒット時コールバック関数
	/// </summary>
	void RightHandOnCollision();
	/// <summary>
	/// 左手ダメージリアクション
	/// </summary>
	void LeftHandDamageReaction();
	/// <summary>
	/// 右手ダメージリアクション
	/// </summary>
	void RightHandDamageReaction();
	/// <summary>
	/// 左手死亡フラグ取得
	/// </summary>
	/// <returns></returns>
	bool GetIsLeftHandDead() { return isLeftHandDead_; }
	/// <summary>
	/// 右手死亡フラグ取得
	/// </summary>
	/// <returns></returns>
	bool GetIsRightHandDead() { return isRightHandDead_; }
	/// <summary>
	/// エフェクトタイミングフラグ取得
	/// </summary>
	/// <returns></returns>
	bool GetIsMovieEffectTiming() override { return isMoviePoint_2_; }
	/// <summary>
	/// 左手オブジェクト取得
	/// </summary>
	/// <returns>左手オブジェクト</returns>
	Object3d* GetLeftHandObj() { return leftHand_; }
	/// <summary>
	/// 右手オブジェクト取得
	/// </summary>
	/// <returns>右手オブジェクト</returns>
	Object3d* GetRightHandObj() { return rightHand_; }

private: //メンバ関数
	/// <summary>
	/// 防御
	/// </summary>
	void Guard(const int32_t actionPreTime);
	/// <summary>
	/// 回転攻撃
	/// </summary>
	void RollingShot(const int32_t actionPreTime);
	/// <summary>
	/// 死亡演出
	/// </summary>
	void DeadReaction();
	/// <summary>
	/// 左手死亡演出
	/// </summary>
	void LeftHandDeadReaction();
	/// <summary>
	/// 右手死亡演出
	/// </summary>
	void RightHandDeadReaction();
	/// <summary>
	/// HPバー座標更新
	/// </summary>
	void HPBarUpdate();

private: //静的メンバ変数

	const int32_t FirstBoss::rotationTime = 15;
	const int32_t FirstBoss::actionCoolTime = 60;
	const int32_t FirstBoss::rollingShotTime = 180;
	const int32_t FirstBoss::deadTime = 180;
	const int32_t FirstBoss::leftHandDeadTime = 180;
	const int32_t FirstBoss::rightHandDeadTime = 180;
	const int32_t FirstBoss::guardTime = 90;
	const int32_t FirstBoss::stompTime = 100;
	const int32_t FirstBoss::punchTime = 180;

private: //メンバ変数
	// 左手
	Object3d* leftHand_;
	Object3d* leftHandShadow_;
	Sprite* leftHpBar_;
	Sprite* leftHpRedBar_;
	//右手
	Object3d* rightHand_;
	Object3d* rightHandShadow_;
	Sprite* rightHpBar_;
	Sprite* rightHpRedBar_;
	//左手関連変数
	Vector3 leftHandPos_;
	Vector3 leftHandScale_;
	Vector3 leftHandRot_;
	int32_t leftHandHP_;
	bool isLeftHandDamage_;
	bool isLeftHandDead_;
	int32_t leftHandDamageTimer_;
	int32_t leftHandDeadTimer_;
	float leftHandAngle_;
	Vector3 leftHandShadowPos_;
	//右手関連変数
	Vector3 rightHandPos_;
	Vector3 rightHandScale_;
	Vector3 rightHandRot_;
	int32_t rightHandHP_;
	bool isRightHandDamage_;
	bool isRightHandDead_;
	int32_t rightHandDamageTimer_;
	int32_t rightHandDeadTimer_;
	float rightHandAngle_;
	Vector3 rightHandShadowPos_;

	//ムービー関連変数
	int32_t movieTimer_;
	bool isMoviePoint_1_ = false;
	bool isMoviePoint_2_ = false;
	bool isMoviePoint_3_ = false;

	//攻撃関連変数
	int32_t rollingShotTimer_;
	int32_t guardTimer_;
	int32_t stompTimer_;
	int32_t punchTimer_;
	int32_t actionPreTimer_;
	int32_t actionPostTimer_;
	bool isActionPos_;
	bool isActionPost_;
};

