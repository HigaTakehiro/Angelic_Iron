#include "Score.h"
#include "Easing.h"

int32_t Score::score_ = 0;

Score* Score::GetIns()
{
    static Score instance;
    return &instance;
}

void Score::Initialize()
{
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::scoreNumbers, { 1252 - ((float)i * 30), 100 });
		scoreNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		scoreNumber_[i]->SetTextureRect({ (float)Score::ScoreNumber::nine, 0.0f }, { 64, 64 });
		scoreNumber_[i]->SetSize({ 32, 32 });
	}
	for (int32_t i = 0; i < 4; i++) {
		addScoreNumber_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::scoreNumbers, { 1252 - ((float)i * 30), 200 });
		addScoreNumber_[i]->SetAnchorPoint({ 0.5f, 0.5f });
		addScoreNumber_[i]->SetTextureRect({ (float)Score::ScoreNumber::zero, 0.0f }, { 64, 64 });
		addScoreNumber_[i]->SetSize({ 16, 16 });
	}
	plus_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::Plus, { 1228, 200 });
	plus_->SetAnchorPoint({ 0.5f, 0.5f });
	plus_->SetSize({ 16, 16 });
	score_ = 0;
	addScore_ = 0;
	addScoreAlpha_ = 1.0f;
}

void Score::Update()
{
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i]->SetTextureRect({ (float)JudgeDigitNumber(score_, i), 0.0f}, {64.0f, 64.0f});
	}
	AddScorePerformance();
}

void Score::Draw()
{
	for (int32_t i = 0; i < 6; i++) {
		scoreNumber_[i]->Draw();
	}
	if (!isAddScore_) return;
	for (int32_t i = 0; i < 4; i++) {
		addScoreNumber_[i]->Draw();
	}
	plus_->Draw();
}

Score::ScoreNumber Score::JudgeDigitNumber(int32_t score, int32_t digit)
{
	if (score >= 1000000) {
		return Score::ScoreNumber::nine;
	}

	int32_t num = (score / (int32_t)pow(10, digit)) % 10;

	return (ScoreNumber)(64 * num);
}

void Score::AddScorePerformance()
{
	const float addScoreLastPos = 100.0f;
	const float addScoreFirstPos = 200.0f;
	
	if (!isAddScore_) return;
	if (++scoreAddTimer_ < scoreAddTime) {
		for (int32_t i = 0; i < 4; i++) {
			addScoreNumber_[i]->SetTextureRect({ (float)JudgeDigitNumber(addScore_, i), 0.0f }, {64, 64});
			addScoreNumber_[i]->SetPosition({ addScoreNumber_[i]->GetPosition().x, (float)Easing::easeIn((float)scoreAddTimer_, (float)scoreAddTime, addScoreLastPos, addScoreNumber_[i].get()->GetPosition().y) });
		}
		plus_->SetPosition({ addScoreNumber_[0]->GetPosition().x - 20.0f, addScoreNumber_[0]->GetPosition().y });
		for (int32_t i = 0; i < 6; i++) {
			scoreRollPosX_[i] = Easing::easeOut((float)scoreAddTimer_, (float)scoreAddTime, (float)JudgeDigitNumber(score_ + addScore_, i), scoreRollPosX_[i]);
			scoreNumber_[i]->SetTextureRect({ scoreRollPosX_[i], 0.0f }, { 64.0f, 64.0f });
		}
	}
	else {
		for (int32_t i = 0; i < 4; i++) {
			addScoreNumber_[i]->SetPosition({addScoreNumber_[i]->GetPosition().x, addScoreFirstPos});
		}
		score_ += addScore_;
		isAddScore_ = false;
	}
}

void Score::AddScore(int32_t score)
{
	addScore_ = score;
	isAddScore_ = true;
}


