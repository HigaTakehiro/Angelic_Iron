#pragma once
#include "Object3d.h"
#include "SphereAndSphere.h"
#include <list>

class CollisionManager
{
public: //�����o�֐�
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CollisionManager();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �I�u�W�F�N�g�ǉ�
	/// </summary>
	/// <param name="obj">�ǉ��I�u�W�F�N�g</param>
	void AddObj(Object3d* obj) { objList_.push_back(obj); }

private: //�����o�ϐ�
	//�I�u�W�F�N�g���X�g
	std::list<Object3d*> objList_;
};

