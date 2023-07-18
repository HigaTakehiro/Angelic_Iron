#pragma once
#include "Object3d.h"
#include "SphereAndSphere.h"
#include <list>

class CollisionManager
{
public: //メンバ関数
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CollisionManager();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// オブジェクト追加
	/// </summary>
	/// <param name="obj">追加オブジェクト</param>
	void AddObj(Object3d* obj) { objList_.push_back(obj); }

private: //メンバ変数
	//オブジェクトリスト
	std::list<Object3d*> objList_;
};

