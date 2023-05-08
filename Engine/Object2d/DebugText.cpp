#include "DebugText.h"

DebugText::DebugText() {

}

DebugText::~DebugText() {
	for (int32_t i = 0; i < _countof(spriteDatas_); i++) {
		delete spriteDatas_[i];
	}
}

void DebugText::Initialize(UINT texnumber) {
	//�S�ẴX�v���C�g�f�[�^�ɂ���
	for (int32_t i = 0; i < _countof(spriteDatas_); i++) {
		//�X�v���C�g�𐶐�����
		spriteDatas_[i] = Sprite::Create(texnumber, { 0, 0 });
	}
}

void DebugText::Print(const std::string& text, float x, float y, float scale = 1.0f) {
	//�S�Ă̕����ɂ���
	for (int32_t i = 0; i < text.size(); i++) {
		//�ő啶��������
		if (spriteIndex_ >= maxCharCount) {
			break;
		}

		//1�������o��(ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text[i];

		int32_t fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int32_t fontIndexY = fontIndex / fontLineCount;
		int32_t fontIndexX = fontIndex % fontLineCount;

		//���W�v�Z
		spriteDatas_[spriteIndex_]->SetPosition({ x + fontWidth * scale * i, y });
		spriteDatas_[spriteIndex_]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }, { (float)fontWidth, (float)fontHeight });
		spriteDatas_[spriteIndex_]->SetSize({ fontWidth * scale, fontHeight * scale });

		//������1�i�߂�
		spriteIndex_++;
	}
}

void DebugText::DrawAll(ID3D12GraphicsCommandList* cmdList) {
	//�S�Ă̕����̃X�v���C�g�ɂ���
	for (int32_t i = 0; i < spriteIndex_; i++) {
		//�X�v���C�g�`��
		spriteDatas_[i]->Draw();
	}

	spriteIndex_ = 0;
}