#pragma once
#include "Object3d.h"
#include "Vector3.h"

class BaseBoss
{
public:
	virtual ~BaseBoss();

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize();
	/// <summary>
	/// 行動
	/// </summary>
	virtual void Action();

protected: //メンバ変数
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
};

