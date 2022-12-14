#pragma once
#include "BaseBoss.h"
#include "BossScene.h"
#include "BossScenePlayer.h"

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
	void Initialize(const ModelManager::ModelName model, const Vector3& pos);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const Vector3& playerPos, const int delayTime = 0);
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
	/// <summary>
	/// 行動
	/// </summary>
	void Action();
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
	bool GetIsLeftHandDead() { return isLeftHandDead; }
	/// <summary>
	/// 右手死亡フラグ取得
	/// </summary>
	/// <returns></returns>
	bool GetIsRightHandDead() { return isRightHandDead; }
	/// <summary>
	/// 左手オブジェクト取得
	/// </summary>
	/// <returns>左手オブジェクト</returns>
	Object3d* GetLeftHandObj() { return leftHand; }
	/// <summary>
	/// 右手オブジェクト取得
	/// </summary>
	/// <returns>右手オブジェクト</returns>
	Object3d* GetRightHandObj() { return rightHand; }

private: //メンバ関数
	/// <summary>
	/// 防御
	/// </summary>
	void Guard();
	/// <summary>
	/// 回転攻撃
	/// </summary>
	void RollingShot();
	/// <summary>
	/// 押しつぶし攻撃
	/// </summary>
	void Stomp();
	/// <summary>
	/// ラリアット攻撃
	/// </summary>
	void Lariat();
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

private: //静的メンバ変数
	static const int32_t rollingShotTime;
	static const int32_t leftHandDeadTime;
	static const int32_t rightHandDeadTime;
	static const int32_t guardTime;
	static const int32_t stompTime;
	static const int32_t punchTime;

private: //メンバ変数
	// 左手
	Object3d* leftHand;
	Object3d* leftHandShadow;
	//右手
	Object3d* rightHand;
	Object3d* rightHandShadow;
	//左手関連変数
	Vector3 leftHandPos;
	Vector3 leftHandScale;
	Vector3 leftHandRot;
	int leftHandHP;
	bool isLeftHandDamage;
	bool isLeftHandDead;
	int32_t leftHandDamageTimer;
	int32_t leftHandDeadTimer;
	float leftHandAngle;
	Vector3 leftHandShadowPos;
	//右手関連変数
	Vector3 rightHandPos;
	Vector3 rightHandScale;
	Vector3 rightHandRot;
	int rightHandHP;
	bool isRightHandDamage;
	bool isRightHandDead;
	int32_t rightHandDamageTimer;
	int32_t rightHandDeadTimer;
	float rightHandAngle;
	Vector3 rightHandShadowPos;

	//攻撃関連変数
	int32_t rollingShotTimer;
	int32_t guardTimer;
	int32_t stompTimer;
	int32_t punchTimer;
};

