#include "ModelManager.h"

ModelManager::~ModelManager() {
	for (auto model : models) {
		delete model.second;
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
	LoadModel("Player_Normal", "player_Normal");
	LoadModel("Player_Stand", "player_Stand");
	LoadModel("Player_Down", "player_Down");
	LoadModel("Gun", "gun");
	LoadModel("Bullet", "bullet");
	LoadModel("BulletCase", "bulletCase");
	LoadModel("Enemy", "enemy1", true);
	LoadModel("Block", "block");
	LoadModel("ground", "ground");
	LoadModel("CelestialSphere", "celetialSphere", true);
	LoadModel("Building", "building");
	LoadModel("BossBody", "boss1_Body");
	LoadModel("BossHand", "boss1_Hand");
	LoadModel("Aircraft_Carrier", "aircraft_Carrier", true);
	LoadModel("Wave", "wave");
	LoadModel("Shadow", "shadow");
	LoadFBXModel("Player_Attack");
}

void ModelManager::LoadModel(const std::string modelName, const std::string modelKey, bool isSmoothing) {
	Model* newModel = nullptr;
	newModel = Model::CreateModel(modelName, isSmoothing);
	models[modelKey] = newModel;
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
