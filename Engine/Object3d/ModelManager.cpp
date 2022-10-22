#include "ModelManager.h"

ModelManager* ModelManager::GetIns()
{
	static ModelManager instance;
	return &instance;
}

void ModelManager::Initialize() {
	LoadModel("Player");
	LoadModel("Enemy");
	LoadModel("Block");
}

void ModelManager::Finalize() {
	model.clear();
	model.shrink_to_fit();
}

void ModelManager::LoadModel(const std::string modelName) {
	Model* newModel = nullptr;
	newModel = Model::CreateModel(modelName);
	model.push_back(newModel);
}