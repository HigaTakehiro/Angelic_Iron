#pragma once
#include "Object3d.h"
#include "Model.h"
#include "ModelManager.h"
#include "Vector3.h"
#include "MouseInput.h"
#include "SafeDelete.h"

class BaseBoss
{
public:
	virtual ~BaseBoss() {}

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize(const ModelManager::ModelName model, const Vector3& pos) = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(const Vector3& playerPos, const int delayTime = 0) = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// 行動
	/// </summary>
	virtual void Action() = 0;

protected: //静的メンバ変数
	//行動クールタイム
	static const int32_t actionCoolTime;

protected: //メンバ変数
	//ボスオブジェクト
	Object3d* boss;
	//プレイヤー座標
	Vector3 playerPos;
	//座標
	Vector3 pos;
	//回転角
	Vector3 rot;
	//大きさ
	Vector3 scale;
	//攻撃力
	float attackPower;
	//体力
	float hp;
	//行動クールタイマー
	int32_t actionCoolTimer;
	//スロー演出用タイマー
	int delayTimer;
};