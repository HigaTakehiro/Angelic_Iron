#include "DebugText.h"

DebugText::DebugText() {

}

DebugText::~DebugText() {
	for (int32_t i = 0; i < _countof(spriteDatas_); i++) {
		delete spriteDatas_[i];
	}
}

void DebugText::Initialize(UINT texnumber) {
	//全てのスプライトデータについて
	for (int32_t i = 0; i < _countof(spriteDatas_); i++) {
		//スプライトを生成する
		spriteDatas_[i] = Sprite::Create(texnumber, { 0, 0 });
	}
}

void DebugText::Print(const std::string& text, float x, float y, float scale = 1.0f) {
	//全ての文字について
	for (int32_t i = 0; i < text.size(); i++) {
		//最大文字数超過
		if (spriteIndex_ >= maxCharCount) {
			break;
		}

		//1文字取り出す(ASCIIコードでしか成り立たない)
		const unsigned char& character = text[i];

		int32_t fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int32_t fontIndexY = fontIndex / fontLineCount;
		int32_t fontIndexX = fontIndex % fontLineCount;

		//座標計算
		spriteDatas_[spriteIndex_]->SetPosition({ x + fontWidth * scale * i, y });
		spriteDatas_[spriteIndex_]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }, { (float)fontWidth, (float)fontHeight });
		spriteDatas_[spriteIndex_]->SetSize({ fontWidth * scale, fontHeight * scale });

		//文字を1つ進める
		spriteIndex_++;
	}
}

void DebugText::DrawAll(ID3D12GraphicsCommandList* cmdList) {
	//全ての文字のスプライトについて
	for (int32_t i = 0; i < spriteIndex_; i++) {
		//スプライト描画
		spriteDatas_[i]->Draw();
	}

	spriteIndex_ = 0;
}