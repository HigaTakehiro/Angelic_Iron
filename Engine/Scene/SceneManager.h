#pragma once
#include "GameScene.h"
#include "DirectXCommon.h"

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
		Result,
		None
	};

public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	void SceneChange(SceneName sceneName);

private: //�����o�ϐ�
	DirectXCommon* dxCommon;
	GameScene* gameScene;

	int nowSceneNo = Title;
	int nextSceneNo = None;
};

