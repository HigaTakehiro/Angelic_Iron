#include "MessageWindow.h"
#include "safeDelete.h"

void MessageWindow::Initialize(const std::string& fileName)
{
	textData_ = ExternalFileLoader::GetIns()->ExternalFileOpen(fileName);
	textWindow_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::TextWindow, { 580, 630 });
	textWindow_->SetAlpha(0.4f);
	textWindowSize_ = textWindow_->GetSize();
	textWindowSize_.y = 0;
	textWindow_->SetAnchorPoint({ 0.5f, 0.5f });
	faceWindow_ = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::FaceWindow, { 90, 630 });
	faceWindowSize_ = faceWindow_->GetSize();
	faceWindowSize_.y = 0;
	faceWindow_->SetAlpha(0.4f);
	faceWindow_->SetAnchorPoint({ 0.5f, 0.5f });
	faceSize_ = { 160, 0 };
	for (int32_t i = 0; i < 3; i++) {
		opeNormal_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::OPE_NORMAL, { 90, 630 });
		opeNormal_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeNormal_[i]->SetSize({ 160, 160 });
		opeNormal_[i]->SetColor({ 2, 2, 2 });
		opeNormal_[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSurprise_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::OPE_SURPRISE, { 90, 630 });
		opeSurprise_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSurprise_[i]->SetSize({ 160, 160 });
		opeSurprise_[i]->SetColor({ 2, 2, 2 });
		opeSurprise_[i]->SetAnchorPoint({ 0.5f, 0.5f });

		opeSmile_[i] = Sprite::UniquePtrCreate((UINT)ImageManager::ImageName::OPE_SMILE, { 90, 630 });
		opeSmile_[i]->SetTextureRect({ 160.0f * (float)i, 0.0f }, { 160.0f, 160.0f });
		opeSmile_[i]->SetSize({ 160, 160 });
		opeSmile_[i]->SetColor({ 2, 2, 2 });
		opeSmile_[i]->SetAnchorPoint({ 0.5f, 0.5f });

	}

	textAddTimer_ = 0;
	textSpeed_ = 1;
	textCount_ = 0;
	isTextDrawComplete_ = false;
	faceType_ = FaceGraphics::OPE_NORMALFACE;
}

void MessageWindow::Update()
{
	std::string line;
	std::string face;
	std::string messageData;
	std::wstring messageDataW;

	if (isMessageUpdateWait_) {
		if (isTextDrawComplete_) {
			messageWaitTimer_--;
		}
		if (messageWaitTimer_ <= 0) {
			isMessageUpdateWait_ = false;
			textCount_ = 0;
			message_.clear();
			drawMessage_.clear();
		}
		return;
	}

	while (getline(textData_, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//���p��؂�ŕ�������擾
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "OPEN") {
			isTextWindowOpen_ = true;
		}
		if (word == "FACE") {
			line_stream >> face;
			if (face == "OPE_NORMAL") {
				faceType_ = FaceGraphics::OPE_NORMALFACE;
			}
			else if (face == "OPE_SURPRISE") {
				faceType_ = FaceGraphics::OPE_SURPRISEFACE;
			}
			else if (face == "OPE_SMILE") {
				faceType_ = FaceGraphics::OPE_SMILEFACE;
			}
		}
		if (word == "TEXT") {
			line_stream >> messageData;
			messageDataW = ExternalFileLoader::GetIns()->StringToWstring(messageData);
			message_ = messageDataW;
		}
		if (word == "SPEED") {
			line_stream >> textSpeed_;
		}
		if (word == "WAIT") {
			isMessageUpdateWait_ = true;
			line_stream >> messageWaitTimer_;
			break;
		}
		if (word == "CLOSE") {
			isTextWindowOpen_ = false;
		}
	}
}

void MessageWindow::SpriteDraw()
{
	textWindow_->Draw();
	faceWindow_->Draw();
	switch (faceType_) {
	case FaceGraphics::OPE_NORMALFACE:
		opeNormal_[faceAnimeCount_]->Draw();
		break;
	case FaceGraphics::OPE_SURPRISEFACE:
		opeSurprise_[faceAnimeCount_]->Draw();
		break;
	case FaceGraphics::OPE_SMILEFACE:
		opeSmile_[faceAnimeCount_]->Draw();
		break;
	}
}

void MessageWindow::TextMessageDraw(bool isBomb)
{
	//�E�B���h�E�T�C�Y(�N���[�Y��)
	const float closeWindowSizeY = 0.0f;
	//�E�B���h�E�T�C�Y(�I�[�v����)
	const float openWindowSizeY = 160.0f;

	//���b�Z�[�W�E�B���h�E�J����
	//���b�Z�[�W�E�B���h�E������
	if (!isTextWindowOpen_) {
		windowOpenTimer_ = 0;
		windowCloseTimer_++;
		if (windowCloseTimer_ >= windowCloseTime) {
			windowCloseTimer_ = windowCloseTime;
		}
		//�C�[�Y�C���A�E�g�Ń��b�Z�[�W�E�B���h�E�����
		textWindowSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, faceWindowSize_.y);
		faceSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, faceSize_.y);
	}
	//���b�Z�[�W�E�B���h�E�J������
	else if (isTextWindowOpen_) {
		windowCloseTimer_ = 0;
		windowOpenTimer_++;
		if (windowOpenTimer_ >= windowOpenTime) {
			windowOpenTimer_ = windowOpenTime;
		}
		//�C�[�Y�C���A�E�g�Ń��b�Z�[�W�E�B���h�E���J��
		textWindowSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, faceWindowSize_.y);
		faceSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, faceSize_.y);
	}

	//���b�Z�[�W�E�B���h�E�T�C�Y��ύX
	textWindow_->SetSize(textWindowSize_);
	faceWindow_->SetSize(faceWindowSize_);
	for (int32_t i = 0; i < 3; i++) {
		opeNormal_[i]->SetSize(faceSize_);
		opeSurprise_[i]->SetSize(faceSize_);
		opeSmile_[i]->SetSize(faceSize_);
	}

	//��O���t�B�b�N�A�j���[�V�������ԉ��Z
	faceAnimeTimer_++;
	if (faceAnimeTimer_ >= faceAnimeTime) {
		faceAnimeTimer_ = 0;
		faceAnimeCount_++;
		if (faceAnimeCount_ >= 3) {
			faceAnimeCount_ = 0;
		}
	}
	//�ǂݍ��񂾃e�L�X�g�`�悪�������Ă�����
	if (isTextDrawComplete_) {
		faceAnimeCount_ = 0;
		faceAnimeTimer_ = 0;
	}
	//�e�L�X�g�X�s�[�h��0�ȉ��ɂȂ�Ȃ��悤�ɂ���
	if (textSpeed_ <= 0) {
		textSpeed_ = 1;
	}
	//�e�L�X�g�`��͈�
	D2D1_RECT_F textDrawPos = {
		200, 560, 950, 700
	};
	D2D1_RECT_F bombMessageDrawPos = {
		400, 0, 900, 300
	};
	//�e�L�X�g��1�������w�莞�Ԃ��Ƃɒǉ�����
	textAddTimer_++;
	isTextDrawComplete_ = false;
	if (textAddTimer_ >= textSpeed_) {
		textAddTimer_ = 0;
		if (textCount_ < message_.size()) {
			if (message_.substr(textCount_, 1) != L"/") {
				drawMessage_ += message_.substr(textCount_, 1);
			}
			else {
				drawMessage_ += L"\n";
			}
			textCount_++;
		}
		//�ǂݍ��񂾃e�L�X�g�`�悪����������
		if (textCount_ >= message_.size()) {
			isTextDrawComplete_ = true;
		}
	}
	//���ݒǉ�����Ă��镶����S�ĕ`�悷��
	textDraw_->Draw("meiryo", "white", drawMessage_, textDrawPos);
	if (isBomb) {
		textDraw_->Draw("meiryo", "orange", L"���ԓ��ɂł��邾�������̓G��\n���b�N�I�����Ă��������B\n�E�N���b�N�Ŕ��ˉ\", bombMessageDrawPos);
	}
}
