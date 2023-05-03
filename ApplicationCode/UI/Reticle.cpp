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
    //レティクル中央
    const DirectX::XMFLOAT2 reticleCenter = { 0.5f, 0.5f };
    //レティクル初期座標
    reticlePos = { 0, 0 };
    //レティクル角度
    reticleRot = 0.0f;
    //レティクルサイズ
    reticleSize = { 80.0f, 80.0f };
    //レティクル生成
    reticle = Sprite::Create(ImageManager::aim, reticlePos);
    reticle->SetSize(reticleSize);
    reticle->SetAnchorPoint(reticleCenter);
}

void Reticle::Update()
{
    //デフォルト角度
    const float defaultReticleRot = 0.0f;
    //デフォルトカラー
    const DirectX::XMFLOAT3 defaultReticleColor = { 0.4f, 0.4f, 0.8f };

    //レティクル更新
    reticlePos.x = (float)MouseInput::GetIns()->GetMousePoint().x;
    reticlePos.y = (float)MouseInput::GetIns()->GetMousePoint().y;
    reticle->SetPosition(reticlePos);
    reticle->SetSize(reticleSize);
    reticle->SetRotation(reticleRot);
    reticle->SetColor(defaultReticleColor);

    //レティクルがボタンまたは敵にあっている場合
    if (isSeletctReticle) {
        const float selectReticleRot = 45.0f;
        const DirectX::XMFLOAT2 selectReticleSize = { 90.0f, 90.0f };
        const DirectX::XMFLOAT3 selectReticleColor = { 0.7f, 0.4f, 0.4f };
        //レティクル回転タイマー加算
        rotTimer++;
        if (rotTimer >= rotTime) {
            rotTimer = rotTime;
        }
        //徐々にレティクルを回転させる
        reticleRot = Easing::easeIn((float)rotTimer, (float)rotTime, selectReticleRot, reticleRot);
        //レティクル更新
        reticle->SetSize(selectReticleSize);
        reticle->SetRotation(reticleRot);
        reticle->SetColor(selectReticleColor);
    }
    else {
        //回転時間初期化
        rotTimer = 0;
        //レティクル角度
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
