#pragma once
#include "GameScene.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "ResultScene.h"
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
		Game,
		Result,
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

private: //�ÓI�����o�ϐ�
	static BaseScene* nowScene;
	static int nextScene;
};

