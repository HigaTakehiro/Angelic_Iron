#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"

class PlayerBullet
{
public: //ƒƒ“ƒoŠÖ”

	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Vector3 pos);

	/// <summary>
	/// XVˆ—
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æˆ—
	/// </summary>
	void Draw();

	/// <summary>
	/// ’e‚Ìó‘Ô‚ğ“n‚·
	/// </summary>
	/// <returns>’e‚Ìó‘Ô</returns>
	bool IsDead() const { return isDead; }

private: //ƒƒ“ƒo•Ï”
	Model* bulletModel;
	Object3d* bullet;
	Vector3 pos;
	Vector3 initPos;
	bool isDead;
};

