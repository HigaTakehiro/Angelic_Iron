#include "ModelManager.h"

ModelManager::~ModelManager() {
	for (auto model : models_) {
		delete model.second;
	}
	for (auto model : fbxModels_) {
		delete model.second;
	}
	models_.clear();
	fbxModels_.clear();
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
	LoadModel("Mountain", "mountain", true);
	LoadModel("GlassGround", "grass_ground");
	LoadModel("DirtRoad", "dirt_road");
	LoadModel("ScoreItem", "scoreItem");
	LoadModel("Tower", "tower");
	//LoadFBXModel("Player_Attack");
}

void ModelManager::LoadModel(const std::string modelName, const std::string modelKey, bool isSmoothing) {
	Model* newModel = nullptr;
	newModel = Model::CreateModel(modelName, isSmoothing);
	models_[modelKey] = newModel;
	newModel = nullptr;
	delete newModel;
}

void ModelManager::LoadFBXModel(const std::string modelName, const std::string modelKey)
{
	FBXModel* newModel = nullptr;
	newModel = FbxLoader::GetInstance()->LoadModelFromFile(modelName);
	fbxModels_[modelKey] = newModel;
	newModel = nullptr;
	delete newModel;
}
