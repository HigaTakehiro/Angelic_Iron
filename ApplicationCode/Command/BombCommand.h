#pragma once
#include "Player.h"
#include "PlayerCommand.h"

class BombCommand : public PlayerCommand
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BombCommand() {}

public: //�����o�֐�
	/// <summary>
	/// �R�}���h���s
	/// </summary>
	/// <param name="player"></param>
	void Execute(Player* player);
};

