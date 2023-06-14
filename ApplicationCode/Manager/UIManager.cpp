#include "UIManager.h"
#include "JsonLoader.h"
#include "ImageManager.h"

void UIManager::Initialize()
{
	//std::list<ButtonData> allButtonData;
	//ButtonData titleBack;
	//titleBack.isPauseView_ = true;
	//titleBack.button_ = Button::CreateUniqueButton(ImageManager::ImageName::TitleBack, { 640, 150 }, { 256, 128 }, 0.0f);
	//allButtonData.push_back(titleBack);

	scoreSprite_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::score, { 1180, 50 });
	scoreSprite_->SetAnchorPoint({ 0.5f, 0.5f });
	scoreSprite_->SetSize({ scoreSprite_->GetSize().x / 2.0f, scoreSprite_->GetSize().y / 2.0f });

	for (int32_t i = 0; i < 3; i++) {
		bombTimerNumber_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::scoreNumbers, { 0.0f, 0.0f });
		bombTimerNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		bombTimerNumber_[i]->SetTextureRect({ (float)UIManager::ScoreNumber::nine, 0.0f }, { 64, 64 });
		bombTimerNumber_[i]->SetSize({ 32, 32 });
	}
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber_[i]->SetTextureRect({ (float)UIManager::ScoreNumber::nine, 0.0f }, { 64, 64 });
		scoreNumber_[i]->SetSize({ 32, 32 });
	}
}

void UIManager::Update(bool isPause, Player* player)
{

	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i]->SetTextureRect({ (float)JudgeDigitNumber(score_, i), 0 }, { 64, 64 });
	}

	for (int32_t i = 0; i < 3; i++) {
		bombTimerNumber_[i]->SetTextureRect({ (float)JudgeDigitNumber((player->GetBombTimer() * 100 / 60), i), 0.0f }, { 64.0f, 64.0f });
		bombTimerNumber_[i]->SetPosition({ Reticle::GetIns()->GetPos().x - (30.0f * i) + 30.0f, Reticle::GetIns()->GetPos().y - 100.0f });
	}

	//for (UIData& ui : allUI_) {
	//	if (ui.isPauseView_ && !isPause) continue;
	//	if (ui.type_ == UIType::HP) {

	//	}
	//	else if (ui.type_ == UIType::Bullet) {

	//	}
	//	else if (ui.type_ == UIType::Anime) {

	//	}
	//}

	//for (ButtonData& button : allButton_) {
	//	if (button.isPauseView_ && !isPause) continue;
	//	button.button_->Update();
	//}

}

void UIManager::Draw(bool isPause, Player* player)
{
	/*for (UIData& ui : allUI_) {
		if (ui.isPauseView_ == true && !isPause) continue;
		ui.uiSprite_->Draw();
	}
	for (ButtonData& button : allButton_) {
		if (button.isPauseView_ == true && !isPause) continue;
		button.button_->Draw();
	}*/

	scoreSprite_->Draw();
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i]->Draw();
	}
	for (int32_t i = 0; i < 3; i++) {
		if (player->GetIsBomb()) {
			bombTimerNumber_[i]->Draw();
		}
	}
}

UIManager::ScoreNumber UIManager::JudgeDigitNumber(int32_t score, int32_t digit)
{
	if (score >= 1000000) {
		return UIManager::ScoreNumber::nine;
	}

	int32_t num = (score / (int32_t)pow(10, digit)) % 10;

	return (ScoreNumber)(64 * num);
}
