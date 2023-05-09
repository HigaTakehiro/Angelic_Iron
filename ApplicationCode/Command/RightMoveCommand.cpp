#include "RightMoveCommand.h"
#include "Vector3.h"

void RightMoveCommand::Execute(Player* player)
{
	//右方向への移動ベクトル
	const Vector3 moveVec = { 1.0f, 0.0f, 0.0f };
	player->AddPlayerVector(moveVec);
}
