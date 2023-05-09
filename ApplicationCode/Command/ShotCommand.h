#pragma once
#include "Player.h"
#include "PlayerCommand.h"

class ShotCommand : public PlayerCommand
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ShotCommand() {}

public: //メンバ関数
	/// <summary>
	/// コマンド実行
	/// </summary>
	/// <param name="player"></param>
	void Execute(Player* player);
};