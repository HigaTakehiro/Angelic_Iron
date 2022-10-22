#pragma once
#include "Model.h"
#include <vector>

class ModelManager
{
private:
	ModelManager() = default;
	~ModelManager() = default;
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
		Player,
		Enemy,
		Shot
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

	/// <summary>
	/// ���f���ǉ�
	/// </summary>
	void LoadModel(const std::string modelName);

	/// <summary>
	/// ���f���擾
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <returns>���f��</returns>
	Model* GetModel(const ModelName modelName) { return model[modelName]; }

private: //�����o�ϐ�
	std::vector<Model*> model;
};

