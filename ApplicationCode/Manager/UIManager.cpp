#include "UIManager.h"
#include "JsonLoader.h"

void UIManager::Initialize(const std::string fileName)
{

}

void UIManager::Update()
{

	for (std::unique_ptr<Button>& button : allButton_) {
		button->Update();
	}
}

void UIManager::Draw()
{
	for (std::unique_ptr<Sprite>& ui : allUI_) {
		ui->Draw();
	}
	for (std::unique_ptr<Button>& button : allButton_) {
		button->Draw();
	}
}
