#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"

class Enemy
{
public: //メンバ関数

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
	void Draw(bool isEnemyDead[]);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Shot();

	/// <summary>
	/// エネミーを取得
	/// </summary>
	/// <param name="i">エネミー配列の番号</param>
	/// <returns>エネミーオブジェクト</returns>
	Object3d* GetEnemy(int enemyNo) { return enemy[enemyNo]; }

	/// <summary>
	/// エネミーの弾を取得
	/// </summary>
	/// <param name="enemyNo">エネミー配列の番号</param>
	/// <returns>指定したエネミーの弾</returns>
	Object3d* GetEnemyShot(int enemyNo) { return shot[enemyNo]; }

	/// <summary>
	/// 発射可能範囲にいるか判定
	/// </summary>
	/// <param name="player">プレイヤーオブジェクト</param>
	/// <returns>発射可能かどうか</returns>
	bool ShotRangeJudge(Object3d* player);

private: //メンバ関数

private: //メンバ変数

	//エネミーの位置
	std::vector<Vector3> enemyPos;

	//エネミーの向き
	Vector3 enemyRot;

	//エネミーの大きさ
	Vector3 enemyScale = { 5, 5, 5 };

	//弾の位置
	Vector3 shotPos[3];

	//弾の大きさ
	Vector3 shotScale[3];

	//モデル
	Model* enemyModel;
	Model* shotModel;

	//3dオブジェクト
	Object3d* enemy[3];
	Object3d* shot[3];

	//ゲームに使用する変数
	bool isShotRange[3];
};

