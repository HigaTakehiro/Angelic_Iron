#include "UIManager.h"
#include "JsonLoader.h"

void UIManager::Initialize(const std::string fileName)
{

}

void UIManager::Update(bool isPause)
{

	for (std::unique_ptr<UIData>& ui : allUI_) {
		if (ui.get()->isPauseView_ && !isPause) continue;
		
	}

	for (std::unique_ptr<ButtonData>& button : allButton_) {
		if (button.get()->isPauseView_ && !isPause) continue;
		button.get()->button_->Update();
	}
}

void UIManager::Draw(bool isPause)
{
	for (std::unique_ptr<UIData>& ui : allUI_) {
		if (ui.get()->isPauseView_ == true && !isPause) continue;
		ui.get()->uiSprite_->Draw();
	}
	for (std::unique_ptr<ButtonData>& button : allButton_) {
		if (button.get()->isPauseView_ == true && !isPause) continue;
		button.get()->button_->Draw();
	}
}
