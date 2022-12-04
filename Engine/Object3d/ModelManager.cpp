#include "ModelManager.h"

ModelManager::~ModelManager() {
	for (Model* model : models) {
		delete model;
	}
	models.clear();
}

ModelManager* ModelManager::GetIns()
{
	static ModelManager instance;
	return &instance;
}

void ModelManager::Initialize() {
	LoadModel("Player_Normal");
	LoadModel("Player_Stand");
	LoadModel("Player_Down");
	LoadModel("Gun");
	LoadModel("Enemy");
	LoadModel("Block");
	LoadModel("ground");
	LoadModel("CelestialSphere");
}

void ModelManager::LoadModel(const std::string modelName) {
	Model* newModel = nullptr;
	newModel = Model::CreateModel(modelName);
	models.push_back(newModel);
	newModel = nullptr;
	delete newModel;
}