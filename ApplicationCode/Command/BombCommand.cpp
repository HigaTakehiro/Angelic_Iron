#include "BombCommand.h"

void BombCommand::Execute(Player* player)
{
	if (!player->GetIsBomb()) player->SetBombMode();
	else if (player->GetIsBomb()) player->BombShot();
}
