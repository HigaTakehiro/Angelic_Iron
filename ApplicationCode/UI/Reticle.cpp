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
    //���e�B�N������
    const DirectX::XMFLOAT2 reticleCenter = { 0.5f, 0.5f };
    //���e�B�N���������W
    reticlePos_ = { 0, 0 };
    //���e�B�N���p�x
    reticleRot_ = 0.0f;
    //���e�B�N���T�C�Y
    reticleSize_ = { 80.0f, 80.0f };
    //���e�B�N������
    reticle_ = Sprite::Create((UINT)ImageManager::ImageName::aim, reticlePos_);
    reticle_->SetSize(reticleSize_);
    reticle_->SetAnchorPoint(reticleCenter);
}

void Reticle::Update()
{
    //�f�t�H���g�p�x
    const float defaultReticleRot = 0.0f;
    //�f�t�H���g�J���[
    const DirectX::XMFLOAT3 defaultReticleColor = { 0.4f, 0.4f, 0.8f };

    //���e�B�N���X�V
    reticlePos_.x = (float)MouseInput::GetIns()->GetMousePoint().x;
    reticlePos_.y = (float)MouseInput::GetIns()->GetMousePoint().y;
    reticle_->SetPosition(reticlePos_);
    reticle_->SetSize(reticleSize_);
    reticle_->SetRotation(reticleRot_);
    reticle_->SetColor(defaultReticleColor);

    //���e�B�N�����{�^���܂��͓G�ɂ����Ă���ꍇ
    if (isSeletctReticle_) {
        const float selectReticleRot = 45.0f;
        const DirectX::XMFLOAT2 selectReticleSize = { 90.0f, 90.0f };
        const DirectX::XMFLOAT3 selectReticleColor = { 0.7f, 0.4f, 0.4f };
        //���e�B�N����]�^�C�}�[���Z
        rotTimer_++;
        if (rotTimer_ >= rotTime_) {
            rotTimer_ = rotTime_;
        }
        //���X�Ƀ��e�B�N������]������
        reticleRot_ = Easing::easeIn((float)rotTimer_, (float)rotTime_, selectReticleRot, reticleRot_);
        //���e�B�N���X�V
        reticle_->SetSize(selectReticleSize);
        reticle_->SetRotation(reticleRot_);
        reticle_->SetColor(selectReticleColor);
    }
    else {
        //��]���ԏ�����
        rotTimer_ = 0;
        //���e�B�N���p�x
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