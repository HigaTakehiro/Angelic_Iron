#pragma once
#include "Player.h"
#include "PlayerCommand.h"

class ReloadCommand : public PlayerCommand
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ReloadCommand() {}

public: //�����o�֐�
	/// <summary>
	/// �R�}���h���s
	/// </summary>
	/// <param name="player"></param>
	void Execute(Player* player);
};

