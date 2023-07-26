#pragma once
#include "Object3d.h"
#include "Model.h"

class CollisionObject3d
{
public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>�C���X�^���X</returns>
	static CollisionObject3d* Create(Model* model);
	/// <summary>
	/// �C���X�^���X����(unique_ptr)
	/// </summary>
	/// <param name="model">���f��</param>
	/// <returns>�C���X�^���X</returns>
	static std::unique_ptr<CollisionManager> UniqueCreate(Model* model);

public: //�\����
	enum class CollisionType {
		Sphere,
		None
	};

	enum class OBJType {
		Player,
		PlayerBullet,
		Bomb,
		Enemy,
		EnemyBullet,
		Boss,
		ScoreItem,
		Wall,
		None
	};

public: //�����o�֐�
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CollisionObject3d() {};

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// ���f�����Z�b�g
	/// </summary>
	/// <param name="model">���f��</param>
	void SetModel(Model* model) { model_ = model; }

	/// <summary>
	/// �����蔻��^�C�v�Z�b�g
	/// </summary>
	/// <param name="colType">�����蔻��^�C�v</param>
	void SetCollisionType(CollisionType colType) { colType_ = colType; }

	/// <summary>
	/// �I�u�W�F�N�g�^�C�v���Z�b�g
	/// </summary>
	/// <param name="objType">�I�u�W�F�N�g�^�C�v</param>
	void SetOBJType(OBJType objType) { objType_ = objType; }

private: //�����o�ϐ�
	//�I�u�W�F�N�g
	std::unique_ptr<Object3d> object_;
	//���f��
	Model* model_;
	//�I�u�W�F�N�g�^�C�v
	OBJType objType_;
	//�R���W�����^�C�v
	CollisionType colType_;
};

