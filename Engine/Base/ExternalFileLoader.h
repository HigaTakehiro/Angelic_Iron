#pragma once

#include <string>
#include <sstream>
#include "BaseEnemy.h"

class ExternalFileLoader
{
public:
	ExternalFileLoader() = default;
	~ExternalFileLoader() = default;

private: //静的メンバ変数
	//デフォルトファイルパス
	const static std::string defaultDirectory;

private: //メンバ関数
	/// <summary>
	/// 外部ファイル読み込み
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns>ファイルデータ</returns>
	std::stringstream ExternalFileOpen(const std::string& fileName);

	/*/// <summary>
	/// 敵データ更新処理
	/// </summary>
	/// <param name="enemyData">敵データ</param>
	void EnemyDataUpdate(const std::stringstream& enemyData);

	/// <summary>
	/// メッセージデータ更新処理
	/// </summary>
	/// <param name="textMessageData">メッセージデータ</param>
	void TextMessageDataUpdate(const std::stringstream& textMessageData);*/
};

