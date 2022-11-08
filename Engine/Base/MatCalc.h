#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class MatCalc final
{
private:
	/// <summary>
    /// コンストラクタ
    /// </summary>
	MatCalc() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MatCalc() = default;

	/// <summary>
	/// コピーコンストラクタを禁止
	/// </summary>
	MatCalc(const MatCalc & obj) = delete;

	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	MatCalc& operator=(const MatCalc & obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static MatCalc* GetIns();

public: //メンバ関数

	/// <summary>
	/// 座標に行列を掛けて最後にw除算する
	/// </summary>
	/// <param name="vec">座標</param>
	/// <param name="mat">行列</param>
	/// <returns>計算結果</returns>
	XMVECTOR WDivided(const XMVECTOR& pos, const XMMATRIX& mat);

	/// <summary>
	/// 座標をw除算する
	/// </summary>
	/// <param name="pos">座標</param>
	/// <returns>計算結果</returns>
	XMVECTOR WDivision(const XMVECTOR& pos);

	/// <summary>
	/// ベクトルと行列の掛け算
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="mat">行列</param>
	/// <returns>計算結果</returns>
	XMVECTOR VecDivided(const XMVECTOR& vec, const XMMATRIX& mat);

	/// <summary>
	/// 座標と行列の掛け算
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="mat">行列</param>
	/// <param name="isWSlide">zの値をwにずらすか</param>
	/// <returns>計算結果</returns>
	XMVECTOR PosDivided(const XMVECTOR& pos, const XMMATRIX& mat, const bool isWSlide = false);

	/// <summary>
	/// 行列から逆行列を求める
	/// </summary>
	/// <param name="mat">行列</param>
	/// <returns>逆行列</returns>
	XMMATRIX InverseMatrix(const XMMATRIX& mat);

};

