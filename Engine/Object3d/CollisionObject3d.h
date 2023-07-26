#pragma once
#include "Object3d.h"
#include "Model.h"

class CollisionObject3d
{
public: //静的メンバ関数
	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>インスタンス</returns>
	static CollisionObject3d* Create(Model* model);
	/// <summary>
	/// インスタンス生成(unique_ptr)
	/// </summary>
	/// <param name="model">モデル</param>
	/// <returns>インスタンス</returns>
	static std::unique_ptr<CollisionManager> UniqueCreate(Model* model);

public: //構造体
	enum class CollisionType {
		Sphere,
		None
	};

	enum class OBJType {
		Player,
		PlayerBullet,
		Bomb,
		Enemy,
		EnemyBullet,
		Boss,
		ScoreItem,
		Wall,
		None
	};

public: //メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CollisionObject3d() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// モデルをセット
	/// </summary>
	/// <param name="model">モデル</param>
	void SetModel(Model* model) { model_ = model; }

	/// <summary>
	/// 当たり判定タイプセット
	/// </summary>
	/// <param name="colType">当たり判定タイプ</param>
	void SetCollisionType(CollisionType colType) { colType_ = colType; }

	/// <summary>
	/// オブジェクトタイプをセット
	/// </summary>
	/// <param name="objType">オブジェクトタイプ</param>
	void SetOBJType(OBJType objType) { objType_ = objType; }

private: //メンバ変数
	//オブジェクト
	std::unique_ptr<Object3d> object_;
	//モデル
	Model* model_;
	//オブジェクトタイプ
	OBJType objType_;
	//コリジョンタイプ
	CollisionType colType_;
};

