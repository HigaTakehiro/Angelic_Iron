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
	/// �����`��X�V����
	/// </summary>
	void TextMessageUpdate();

	/// <summary>
	/// ��䰂�ǉ�
	/// </summary>
	void AddBulletCase();

	/// <summary>
	/// �|�[�Y����
	/// </summary>
	virtual void Pause();

	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	virtual void SceneChange();

	/// <summary>
	/// �G�̒e��ǉ�
	/// </summary>
	virtual void AddEnemyBullet();

	/// <summary>
	/// �v���C���[�̒e��ǉ�
	/// </summary>
	virtual void AddPlayerBullet();

	/// <summary>
	/// �����蔻��`�F�b�N
	/// </summary>
	virtual void CollisionCheck();

	/// <summary>
	/// �G�̍X�V����
	/// </summary>
	virtual void EnemyUpdates();
};