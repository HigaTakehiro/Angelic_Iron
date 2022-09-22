#include "ModelManager.h"

void ModelManager::Initialize() {
	LoadModel(Player, "Player");
	LoadModel(Enemy, "Enemy");
	LoadModel(Shot, "Block");
}

void ModelManager::Finalize() {
	model.clear();
	model.shrink_to_fit();
}

void ModelManager::LoadModel(const ModelName modelType, const std::string modelName) {
	Model* newModel = nullptr;
	newModel = Model::CreateModel(modelName);
	model[modelType] = newModel;
}