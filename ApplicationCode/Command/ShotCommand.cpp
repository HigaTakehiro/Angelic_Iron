#include "ShotCommand.h"

void ShotCommand::Execute(Player* player)
{
	player->Shot();
}
