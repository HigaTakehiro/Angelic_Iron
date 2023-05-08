#include "Reticle.h"
#include "MouseInput.h"
#include "SafeDelete.h"
#include "Easing.h"

Sprite* Reticle::reticle_ = nullptr;
DirectX::XMFLOAT2 Reticle::reticlePos_ = {};
DirectX::XMFLOAT2 Reticle::reticleSize_ = {};
float Reticle::reticleRot_ = 0.0f;
bool Reticle::isSeletctReticle_ = false;
const int32_t Reticle::rotTime_ = 15;

Reticle* Reticle::GetIns()
{
    static Reticle instance;
    return &instance;
}

void Reticle::Initialize()
{
    //レティクル中央
    const DirectX::XMFLOAT2 reticleCenter = { 0.5f, 0.5f };
    //レティクル初期座標
    reticlePos_ = { 0, 0 };
    //レティクル角度
    reticleRot_ = 0.0f;
    //レティクルサイズ
    reticleSize_ = { 80.0f, 80.0f };
    //レティクル生成
    reticle_ = Sprite::Create((UINT)ImageManager::ImageName::aim, reticlePos_);
    reticle_->SetSize(reticleSize_);
    reticle_->SetAnchorPoint(reticleCenter);
}

void Reticle::Update()
{
    //デフォルト角度
    const float defaultReticleRot = 0.0f;
    //デフォルトカラー
    const DirectX::XMFLOAT3 defaultReticleColor = { 0.4f, 0.4f, 0.8f };

    //レティクル更新
    reticlePos_.x = (float)MouseInput::GetIns()->GetMousePoint().x;
    reticlePos_.y = (float)MouseInput::GetIns()->GetMousePoint().y;
    reticle_->SetPosition(reticlePos_);
    reticle_->SetSize(reticleSize_);
    reticle_->SetRotation(reticleRot_);
    reticle_->SetColor(defaultReticleColor);

    //レティクルがボタンまたは敵にあっている場合
    if (isSeletctReticle_) {
        const float selectReticleRot = 45.0f;
        const DirectX::XMFLOAT2 selectReticleSize = { 90.0f, 90.0f };
        const DirectX::XMFLOAT3 selectReticleColor = { 0.7f, 0.4f, 0.4f };
        //レティクル回転タイマー加算
        rotTimer_++;
        if (rotTimer_ >= rotTime_) {
            rotTimer_ = rotTime_;
        }
        //徐々にレティクルを回転させる
        reticleRot_ = Easing::easeIn((float)rotTimer_, (float)rotTime_, selectReticleRot, reticleRot_);
        //レティクル更新
        reticle_->SetSize(selectReticleSize);
        reticle_->SetRotation(reticleRot_);
        reticle_->SetColor(selectReticleColor);
    }
    else {
        //回転時間初期化
        rotTimer_ = 0;
        //レティクル角度
        reticleRot_ = defaultReticleRot;
    }
}

void Reticle::Draw()
{
    reticle_->Draw();
}

void Reticle::Finalize()
{
    safe_delete(reticle_);
}