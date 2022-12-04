#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "ImageManager.h"
#include "KeyInput.h"
#include "PostEffect.h"
#include "SafeDelete.h"
#include "MouseInput.h"

class GameOverScene : public BaseScene
{
public: //�����o�ϐ�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
    /// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

private: //�����o�ϐ�
	PostEffect* postEffect = nullptr; //�|�X�g�G�t�F�N�g
	Sprite* gameover = nullptr; //�Q�[���I�[�o�[��ʉ摜

	PostEffect::PostEffectNo postEffectNo; //�|�X�g�G�t�F�N�g�ԍ�
};

