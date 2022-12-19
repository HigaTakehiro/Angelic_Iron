#pragma once
#include "Model.h"
#include "FBXLoader.h"
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

	enum FBXModelName {
		Test
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
	/// FBX���f���ǉ�
	/// </summary>
	/// <param name="modelName">���f����</param>
	void LoadFBXModel(const std::string modelName);

	/// <summary>
	/// ���f���擾
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <returns>���f��</returns>
	Model* GetModel(const ModelName modelName) { return models[modelName]; }

	/// <summary>
	/// FBX���f���擾
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <returns>FBX���f��</returns>
	FBXModel* GetFBXModel(const FBXModelName modelName) { return fbxModels[modelName]; }

private: //�����o�ϐ�
	std::vector<Model*> models;
	std::vector<FBXModel*> fbxModels;
};

