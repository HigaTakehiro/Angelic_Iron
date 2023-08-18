#pragma once
#include <DirectXMath.h>
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "SceneChangeEffect.h"
#include "Sprite.h"
#include "Easing.h"
#include "SafeDelete.h"
#include "Reticle.h"
#include "CollisionManager.h"
#include "PostEffect.h"
#include "ModelManager.h"

class BaseScene
{
public:
	//デストラクタ
	virtual ~BaseScene() {}

public:
	enum ScoreNumber {
		zero = 64 * 0,
		one = 64 * 1,
		two = 64 * 2,
		three = 64 * 3,
		four = 64 * 4,
		five = 64 * 5,
		six = 64 * 6,
		seven = 64 * 7,
		eight = 64 * 8,
		nine = 64 * 9
	};

	//デバックテキスト用テクスチャ番号
	static const int32_t debugTextNumber = 0;

	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

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

protected: //仮想メンバ関数
	/// <summary>
	/// シーン切り替え処理
	/// </summary>
	virtual void SceneChange() = 0;

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

	/// <summary>
	/// nの位の数字を判定する
	/// </summary>
	/// <param name="score">判定したいスコア</param>
	/// <param name="place">判定したいスコアの位</param>
	/// <returns></returns>
	ScoreNumber JudgeDigitNumber(int32_t score, int32_t digit);

	/// <summary>
	/// コリジョンマネージャーをセット
	/// </summary>
	/// <param name="colManager">コリジョンマネージャー</param>
	void SetColManager(CollisionManager* colManager) { colManager_ = colManager; }

protected: //メンバ変数
	CollisionManager* colManager_;
};