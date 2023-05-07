#pragma once

#include "RailScene.h"
#include "BaseScene.h"
#include "BossScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "GameOverScene.h"
#include "DirectXSetting.h"
#include "Sound.h"
#include "KeyInput.h"
#include "SafeDelete.h"
#include "TextDraw.h"

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

public: //�V�[���Ǘ��ԍ�
	enum class SceneName {
		Title,
		Stage1_Rail,
		Stage1_Boss,
		Stage2_Rail,
		Stage2_Boss,
		Result,
		GameOver,
		None
	};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

public: //�ÓI�����o�֐�

	/// <summary>
	/// �X�V
	/// </summary>
	static void Update();

	/// <summary>
	/// �`��
	/// </summary>
	static void Draw();

	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	static void SceneChange(SceneName scene);

	/// <summary>
	/// �X�R�A�����Z
	/// </summary>
	/// <param name="score">�X�R�A</param>
	static void AddScore(const int32_t score);

	/// <summary>
	/// �X�R�A���Z�b�g
	/// </summary>
	/// <param name="score"></param>
	static void SetScore(const int32_t score);

	/// <summary>
	/// �{�X�V�[���t���O���Z�b�g
	/// </summary>
	/// <param name="isBossScene">�{�X�V�[���t���O</param>
	static void SetIsBossScene(const bool isBossScene) { SceneManager::isBossScene_ = isBossScene; }

	/// <summary>
	/// �X�e�[�W�ԍ��擾
	/// </summary>
	/// <returns>�X�e�[�W�ԍ�</returns>
	static int32_t GetStageNo() { return stageNo_; }

	/// <summary>
	/// �X�R�A�擾
	/// </summary>
	/// <returns>�X�R�A</returns>
	static int32_t GetScore() { return score_; }

	/// <summary>
	/// �{�X�V�[���t���O���擾
	/// </summary>
	/// <returns>�{�X�V�[���t���O</returns>
	static bool GetIsBossScene() { return isBossScene_; }

private: //�ÓI�����o�ϐ�
	static BaseScene* nowScene_;
	static int32_t stageNo_;
	static int32_t score_;
	static bool isBossScene_;

private: //�����o�ϐ�
	std::unique_ptr<TextDraw> textDraw_;
};