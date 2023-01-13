#pragma once
#include "Sound.h"
#include <map>

class SoundManager final
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SoundManager() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SoundManager() = default;
	/// <summary>
	/// コピーコンストラクタを禁止
	/// </summary>
	SoundManager(const SoundManager& obj) = delete;

	/// <summary>
	/// 代入演算子を禁止
	/// </summary>
	SoundManager& operator=(const SoundManager& obj) = delete;

public: //サブクラス
	enum BGMKey {
		TITLE,
		STAGE1_RAIL,
		STAGE1_BOSS
	};

	enum SEKey {
		SHOT,
		PLAYER_DEAD,
		ENEMY_DEAD,
		RELOAD
	};

public:  //静的メンバ関数
	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static SoundManager* GetIns();

public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="sound">サウンドクラスのインスタンス</param>
	void Initialize(Sound* sound);
	
	/// <summary>
	/// BGMを再生
	/// </summary>
	/// <param name="bgmKey">再生したいBGMマップのキー</param>
	/// <param name="isRoop">ループ再生フラグ</param>
	/// <param name="volume">BGM音量</param>
	void PlayBGM(const BGMKey bgmKey, const bool isRoop, const float volume);

	/// <summary>
	/// SEを再生
	/// </summary>
	/// <param name="seKey">再生したいSEマップのキー</param>
	/// <param name="volume">SE音量</param>
	void PlaySE(const SEKey seKey, const float volume);

	/// <summary>
	/// BGMを停止
	/// </summary>
	/// <param name="bgmKey">停止したいBGMマップのキー</param>
	void StopBGM(const BGMKey bgmKey);

	/// <summary>
	/// SEを停止
	/// </summary>
	/// <param name="seKey">停止したいSEマップのキー</param>
	void StopSE(const SEKey seKey);

private: //メンバ変数

	/// <summary>
	/// BGM追加
	/// </summary>
	/// <param name="bgmKey">追加したいBGMマップのキー</param>
	/// <param name="fileName">ファイル名</param>
	void LoadBGM(const char* fileName, BGMKey bgmKey);

	/// <summary>
	/// SE追加
	/// </summary>
	/// <param name="seKey">追加したいSEマップのキー</param>
	/// <param name="fileName">ファイル名</param>
	void LoadSE(const char* fileName, SEKey seKey);

private: //メンバ変数
	//サウンドクラスのインスタンス
	Sound* sound = nullptr;
	//BGM連想配列
	std::map<BGMKey, Sound::SoundData> bgmMap;
	//SE連想配列
	std::map<SEKey, Sound::SoundData> seMap;
};

