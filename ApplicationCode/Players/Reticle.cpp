#include "Reticle.h"
#include "MouseInput.h"
#include "SafeDelete.h"
#include "Easing.h"

Sprite* Reticle::reticle = nullptr;
DirectX::XMFLOAT2 Reticle::reticlePos = {};
DirectX::XMFLOAT2 Reticle::reticleSize = {};
float Reticle::reticleRot = 0.0f;
bool Reticle::isSeletctReticle = false;
const int32_t Reticle::rotTime = 15;

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
    reticlePos = { 0, 0 };
    //���e�B�N���p�x
    reticleRot = 0.0f;
    //���e�B�N���T�C�Y
    reticleSize = { 80.0f, 80.0f };
    //���e�B�N������
    reticle = Sprite::Create(ImageManager::aim, reticlePos);
    reticle->SetSize(reticleSize);
    reticle->SetAnchorPoint(reticleCenter);
}

void Reticle::Update()
{
    //�f�t�H���g�p�x
    const float defaultReticleRot = 0.0f;
    //�f�t�H���g�J���[
    const DirectX::XMFLOAT3 defaultReticleColor = { 0.4f, 0.4f, 0.8f };

    //���e�B�N���X�V
    reticlePos.x = (float)MouseInput::GetIns()->GetMousePoint().x;
    reticlePos.y = (float)MouseInput::GetIns()->GetMousePoint().y;
    reticle->SetPosition(reticlePos);
    reticle->SetSize(reticleSize);
    reticle->SetRotation(reticleRot);
    reticle->SetColor(defaultReticleColor);

    //���e�B�N�����{�^���܂��͓G�ɂ����Ă���ꍇ
    if (isSeletctReticle) {
        const float selectReticleRot = 45.0f;
        const DirectX::XMFLOAT2 selectReticleSize = { 90.0f, 90.0f };
        const DirectX::XMFLOAT3 selectReticleColor = { 0.7f, 0.4f, 0.4f };
        //���e�B�N����]�^�C�}�[���Z
        rotTimer++;
        if (rotTimer >= rotTime) {
            rotTimer = rotTime;
        }
        //���X�Ƀ��e�B�N������]������
        reticleRot = Easing::easeIn((float)rotTimer, (float)rotTime, selectReticleRot, reticleRot);
        //���e�B�N���X�V
        reticle->SetSize(selectReticleSize);
        reticle->SetRotation(reticleRot);
        reticle->SetColor(selectReticleColor);
    }
    else {
        //��]���ԏ�����
        rotTimer = 0;
        //���e�B�N���p�x
        reticleRot = defaultReticleRot;
    }
}

void Reticle::Draw()
{
    reticle->Draw();
}

void Reticle::Finalize()
{
    safe_delete(reticle);
}
