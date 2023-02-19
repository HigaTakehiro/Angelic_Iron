#pragma once

class BaseBattleScene
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~BaseBattleScene() = default;
	
public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() = 0;

protected: //�����o�֐�
	/// <summary>
	/// 
	/// </summary>
	virtual void TextMessageUpdate();
};

