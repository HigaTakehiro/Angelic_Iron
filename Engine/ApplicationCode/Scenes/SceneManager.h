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

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

public: //�V�[���Ǘ��ԍ�
	enum SceneName {
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
	static void AddScore(const int score);

	/// <summary>
	/// �X�R�A���Z�b�g
	/// </summary>
	/// <param name="score"></param>
	static void SetScore(const int score);

	/// <summary>
	/// �X�e�[�W�ԍ��擾
	/// </summary>
	/// <returns>�X�e�[�W�ԍ�</returns>
	static int GetStageNo() { return stageNo; }

	/// <summary>
	/// �X�R�A�擾
	/// </summary>
	/// <returns>�X�R�A</returns>
	static int GetScore() { return score; }

private: //�ÓI�����o�ϐ�
	static BaseScene* nowScene;
	static int stageNo;
	static int score;
};