#include "ModelManager.h"

ModelManager::~ModelManager() {
	for (Model* model : models) {
		delete model;
	}
	for (FBXModel* model : fbxModels) {
		delete model;
	}
	models.clear();
	fbxModels.clear();
}

ModelManager* ModelManager::GetIns()
{
	static ModelManager instance;
	return &instance;
}

void ModelManager::Initialize() {
	LoadModel("Player_Normal");
	LoadModel("Player_Stand", true);
	LoadModel("Player_Down");
	LoadModel("Gun");
	LoadModel("Enemy", true);
	LoadModel("Block");
	LoadModel("ground");
	LoadModel("CelestialSphere");
	LoadModel("Building");
	LoadModel("BossBody");
	LoadModel("BossHand");
	LoadModel("Shadow");
	LoadFBXModel("Player_Attack");
}

void ModelManager::LoadModel(const std::string modelName, bool isSmoothing) {
	Model* newModel = nullptr;
	newModel = Model::CreateModel(modelName, isSmoothing);
	models.push_back(newModel);
	newModel = nullptr;
	delete newModel;
}

void ModelManager::LoadFBXModel(const std::string modelName)
{
	FBXModel* newModel = nullptr;
	newModel = FbxLoader::GetInstance()->LoadModelFromFile(modelName);
	fbxModels.push_back(newModel);
	newModel = nullptr;
	delete newModel;
}
