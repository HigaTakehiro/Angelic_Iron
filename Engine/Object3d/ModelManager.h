#pragma once
#include "Model.h"
#include <vector>

class ModelManager
{
private:
	ModelManager() = default;
	~ModelManager();
	ModelManager(const ModelManager & obj) = delete;
	ModelManager& operator=(const ModelManager & obj) = delete;

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static ModelManager* GetIns();

public: //���f����
	enum ModelName {
		Player_Normal,
		Player_Stand,
		Player_Down,
		Gun,
		Enemy,
		Shot,
		Ground,
		CelestialSphere,
		Building,
		BossBody,
		BossHand,
		Shadow
	};

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���f���ǉ�
	/// </summary>
	void LoadModel(const std::string modelName);

	/// <summary>
	/// ���f���擾
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <returns>���f��</returns>
	Model* GetModel(const ModelName modelName) { return models[modelName]; }

private: //�����o�ϐ�
	std::vector<Model*> models;
};

