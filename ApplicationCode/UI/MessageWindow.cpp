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
		//半角区切りで文字列を取得
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
	//ウィンドウサイズ(クローズ時)
	const float closeWindowSizeY = 0.0f;
	//ウィンドウサイズ(オープン時)
	const float openWindowSizeY = 160.0f;

	//メッセージウィンドウ開閉処理
	//メッセージウィンドウ閉鎖処理
	if (!isTextWindowOpen_) {
		windowOpenTimer_ = 0;
		windowCloseTimer_++;
		if (windowCloseTimer_ >= windowCloseTime) {
			windowCloseTimer_ = windowCloseTime;
		}
		//イーズインアウトでメッセージウィンドウを閉じる
		textWindowSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, faceWindowSize_.y);
		faceSize_.y = Easing::easeInOut((float)windowCloseTimer_, (float)windowCloseTime, closeWindowSizeY, faceSize_.y);
	}
	//メッセージウィンドウ開放処理
	else if (isTextWindowOpen_) {
		windowCloseTimer_ = 0;
		windowOpenTimer_++;
		if (windowOpenTimer_ >= windowOpenTime) {
			windowOpenTimer_ = windowOpenTime;
		}
		//イーズインアウトでメッセージウィンドウを開く
		textWindowSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, textWindowSize_.y);
		faceWindowSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, faceWindowSize_.y);
		faceSize_.y = Easing::easeInOut((float)windowOpenTimer_, (float)windowOpenTime, openWindowSizeY, faceSize_.y);
	}

	//メッセージウィンドウサイズを変更
	textWindow_->SetSize(textWindowSize_);
	faceWindow_->SetSize(faceWindowSize_);
	for (int32_t i = 0; i < 3; i++) {
		opeNormal_[i]->SetSize(faceSize_);
		opeSurprise_[i]->SetSize(faceSize_);
		opeSmile_[i]->SetSize(faceSize_);
	}

	//顔グラフィックアニメーション時間加算
	faceAnimeTimer_++;
	if (faceAnimeTimer_ >= faceAnimeTime) {
		faceAnimeTimer_ = 0;
		faceAnimeCount_++;
		if (faceAnimeCount_ >= 3) {
			faceAnimeCount_ = 0;
		}
	}
	//読み込んだテキスト描画が完了していたら
	if (isTextDrawComplete_) {
		faceAnimeCount_ = 0;
		faceAnimeTimer_ = 0;
	}
	//テキストスピードが0以下にならないようにする
	if (textSpeed_ <= 0) {
		textSpeed_ = 1;
	}
	//テキスト描画範囲
	D2D1_RECT_F textDrawPos = {
		200, 560, 950, 700
	};
	D2D1_RECT_F bombMessageDrawPos = {
		400, 0, 900, 300
	};
	//テキストを1文字ずつ指定時間ごとに追加する
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
		//読み込んだテキスト描画が完了したら
		if (textCount_ >= message_.size()) {
			isTextDrawComplete_ = true;
		}
	}
	//現在追加されている文字を全て描画する
	textDraw_->Draw("meiryo", "white", drawMessage_, textDrawPos);
	if (isBomb) {
		textDraw_->Draw("meiryo", "orange", L"時間内にできるだけ多くの敵を\nロックオンしてください。\n右クリックで発射可能", bombMessageDrawPos);
	}
}
