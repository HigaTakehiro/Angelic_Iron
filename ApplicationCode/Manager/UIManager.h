#pragma once
#include "Sprite.h"
#include "Button.h"
#include "JsonLoader.h"
#include "SceneManager.h"

class UIManager
{
public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIManager() = default;
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UIManager() = default;
	
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="fileName">�ǂݍ��ރt�@�C����</param>
	void Initialize(const std::string fileName);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

private: //�����o�ϐ�
	std::list<std::unique_ptr<Sprite>> allUI_;
	std::list<std::unique_ptr<Button>> allButton_;
};