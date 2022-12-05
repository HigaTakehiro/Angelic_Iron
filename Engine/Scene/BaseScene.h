#pragma once
#include <DirectXMath.h>

class BaseScene
{
public:
	//デストラクタ
	virtual ~BaseScene() {}

public: //仮想関数
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize() = 0;

public: //メンバ関数

	/// <summary>
	/// マウスがスプライトに触れているか(画像の中心が基準)
	/// </summary>
	/// <param name="mousePos">マウスの位置</param>
	/// <param name="spritePos">スプライトの位置</param>
	/// <param name="spriteWidth">スプライト横幅</param>
	/// <param name="spriteHeight">スプライト縦幅</param>
	/// <returns>マウスがスプライトを触れている</returns>
	bool IsMouseHitSprite(DirectX::XMFLOAT2 mousePos, DirectX::XMFLOAT2 spritePos, float spriteWidth, float spriteHeight);
};