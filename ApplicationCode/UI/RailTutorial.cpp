#include "RailTutorial.h"
#include "MouseInput.h"
#include "KeyInput.h"

void RailTutorial::Initialize()
{
	//アンカーポイント
	const Vector2 anchorPoint = { 0.5f, 0.5f };
	//サイズ
	const Vector2 iconSize = { 64.0f, 64.0f };

	how_to_bomb_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::How_to_Bomb, { 0.0f, 0.0f });
	how_to_bomb_->SetAnchorPoint(anchorPoint);
	how_to_bomb_->SetSize(iconSize);
	how_to_shot_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::How_to_Shot, { 0.0f, 0.0f });
	how_to_shot_->SetAnchorPoint(anchorPoint);
	how_to_shot_->SetSize(iconSize);
	how_to_left_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::How_to_Left, { 0.0f, 0.0f });
	how_to_left_->SetAnchorPoint(anchorPoint);
	how_to_left_->SetSize(iconSize);
	how_to_right_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::How_to_Right, { 0.0f, 0.0f });
	how_to_right_->SetAnchorPoint(anchorPoint);
	how_to_right_->SetSize(iconSize);
	how_to_up_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::How_to_Up, { 0.0f, 0.0f });
	how_to_up_->SetAnchorPoint(anchorPoint);
	how_to_up_->SetSize(iconSize);
	how_to_down_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::How_to_Down, { 0.0f, 0.0f });
	how_to_down_->SetAnchorPoint(anchorPoint);
	how_to_down_->SetSize(iconSize);

	shotAlpha_ = 1.0f;
	leftAlpha_ = 1.0f;
	rightAlpha_ = 1.0f;
	upAlpha_ = 1.0f;
	downAlpha_ = 1.0f;
	bombAlpha_ = 1.0f;

	player2dPos_ = { 0.0f, 0.0f };
}

void RailTutorial::Update()
{
	//アイコンをずらす距離
	const float iconSlidePos = 100.0f;

	if (++tutorialTimer_ > tutorialTime) {
		isUpMove_ = true;
		isDownMove_ = true;
		isLeftMove_ = true;
		isRightMove_ = true;
		isShot_ = true;
	}

	//チュートリアルアイコンの座標を求める
	how_to_up_->SetPosition({ player2dPos_.x, player2dPos_.y - iconSlidePos });
	how_to_down_->SetPosition({ player2dPos_.x, player2dPos_.y + iconSlidePos });
	how_to_left_->SetPosition({ player2dPos_.x - iconSlidePos, player2dPos_.y });
	how_to_right_->SetPosition({ player2dPos_.x + iconSlidePos, player2dPos_.y });
	how_to_shot_->SetPosition({ (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y - iconSlidePos});
	how_to_bomb_->SetPosition({ (float)MouseInput::GetIns()->GetMousePoint().x, (float)MouseInput::GetIns()->GetMousePoint().y - iconSlidePos });

	//チュートリル完了したら透明にする
	if (KeyInput::GetIns()->TriggerKey(DIK_W)) {
		isUpMove_ = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_S)) {
		isDownMove_ = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_A)) {
		isLeftMove_ = true;
	}
	if (KeyInput::GetIns()->TriggerKey(DIK_D)) {
		isRightMove_ = true;
	}
	if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::LEFT_CLICK)) {
		isShot_ = true;
	}
	if (MouseInput::GetIns()->TriggerClick(MouseInput::MouseState::RIGHT_CLICK)) {
		isBomb_ = true;
	}

	if (isUpMove_ && upAlpha_ > 0) {
		upAlpha_ -= 0.05f;
		how_to_up_->SetAlpha(upAlpha_);
	}
	if (isDownMove_ && downAlpha_ > 0) {
		downAlpha_ -= 0.05f;
		how_to_down_->SetAlpha(downAlpha_);
	}
	if (isLeftMove_ && leftAlpha_ > 0) {
		leftAlpha_ -= 0.05f;
		how_to_left_->SetAlpha(leftAlpha_);
	}
	if (isRightMove_ && rightAlpha_ > 0) {
		rightAlpha_ -= 0.05f;
		how_to_right_->SetAlpha(rightAlpha_);
	}
	if (isShot_ && shotAlpha_ > 0) {
		shotAlpha_ -= 0.05f;
		how_to_shot_->SetAlpha(shotAlpha_);
	}
	if (isBomb_ && bombAlpha_ > 0) {
		bombAlpha_ -= 0.1f;
		how_to_bomb_->SetAlpha(bombAlpha_);
	}
}

void RailTutorial::Draw()
{
	how_to_bomb_->Draw();
	how_to_shot_->Draw();
	how_to_down_->Draw();
	how_to_up_->Draw();
	how_to_left_->Draw();
	how_to_right_->Draw();
}
