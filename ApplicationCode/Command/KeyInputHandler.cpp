#include "KeyInputHandler.h"
#include "SafeDelete.h"

KeyInputHandler::~KeyInputHandler()
{
	safe_delete(wKey_);
	safe_delete(aKey_);
	safe_delete(sKey_);
	safe_delete(dKey_);
	safe_delete(leftClick_);
	safe_delete(rightClick_);
}

void KeyInputHandler::Initialize(Player* player)
{
	player_ = player;
	KeyBindChange_W(Commands::UpMove);
	KeyBindChange_A(Commands::LeftMove);
	KeyBindChange_S(Commands::DownMove);
	KeyBindChange_D(Commands::RightMove);
	KeyBindChange_LeftClick(Commands::Shot);
	KeyBindChange_RightClick(Commands::Bomb);
}

void KeyInputHandler::PlayerHandleInput()
{
	if (KeyInput::GetIns()->PushKey(DIK_W)) wKey_->Execute(player_);
	if (KeyInput::GetIns()->PushKey(DIK_A)) aKey_->Execute(player_);
	if (KeyInput::GetIns()->PushKey(DIK_S)) sKey_->Execute(player_);
	if (KeyInput::GetIns()->PushKey(DIK_D)) dKey_->Execute(player_);
	//if (MouseInput::GetIns()->PushClick(MouseInput::MouseState::LEFT_CLICK)) leftClick_->Execute(player_);
	//if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::RIGHT_CLICK)) rightClick_->Execute(player_);
}

void KeyInputHandler::KeyBindChange(PlayerCommand* key, Commands command)
{
	if (key != nullptr) {
		safe_delete(key);
	}

	switch (command) {
	case Commands::LeftMove:
		key = new LeftMoveCommand();
		break;
	case Commands::RightMove:
		key = new RightMoveCommand();
		break;
	case Commands::UpMove:
		key = new UpMoveCommand();
		break;
	case Commands::DownMove:
		key = new DownMoveCommand();
		break;
	case Commands::Shot:
		return;
		break;
	case Commands::Bomb:
		return;
		break;
	}
}

PlayerCommand* KeyInputHandler::KeyBindChangeW(Commands command)
{
	switch (command) {
	case Commands::LeftMove:
		return new LeftMoveCommand();
		break;
	case Commands::RightMove:
		return new RightMoveCommand();
		break;
	case Commands::UpMove:
		return new UpMoveCommand();
		break;
	case Commands::DownMove:
		return new DownMoveCommand();
		break;
	case Commands::Shot:
		return nullptr;
		break;
	case Commands::Bomb:
		return nullptr;
		break;
	}
}

void KeyInputHandler::KeyBindChange_W(Commands command)
{
	KeyBindChange(wKey_, command);
	wKey_ = KeyBindChangeW(command);
}

void KeyInputHandler::KeyBindChange_A(Commands command)
{
	KeyBindChange(aKey_, command);
	aKey_ = KeyBindChangeW(command);
}

void KeyInputHandler::KeyBindChange_S(Commands command)
{
	KeyBindChange(sKey_, command);
	sKey_ = KeyBindChangeW(command);
}

void KeyInputHandler::KeyBindChange_D(Commands command)
{
	KeyBindChange(dKey_, command);
	dKey_ = KeyBindChangeW(command);
}

void KeyInputHandler::KeyBindChange_LeftClick(Commands command)
{
	KeyBindChange(leftClick_, command);
}

void KeyInputHandler::KeyBindChange_RightClick(Commands command)
{
	KeyBindChange(rightClick_, command);
}
