#include "JsonLoader.h"

const std::string JsonLoader::baseDirectory = "Engine/Resources/GameData/";
const std::string JsonLoader::extension = ".json";

void JsonLoader::StageDataLoadandSet(const std::string fileName) {
	const std::string fullpath = baseDirectory + fileName + extension;

	std::ifstream file;

	file.open(fullpath);
	if (file.fail()) {
		assert(0);
	}

	nlohmann::json deserialised;

	file >> deserialised;

	assert(deserialised.is_object());
	assert(deserialised.contains("name"));
	assert(deserialised["name"].is_string());

	std::string name = deserialised["name"].get<std::string>();

	assert(name.compare("scene") == 0);

	StageData* stageData = new StageData();

	for (nlohmann::json& object : deserialised["objects"]) {
		assert(object.contains("type"));

		std::string type = object["type"].get<std::string>();

		if (type.compare("MESH") == 0) {
			stageData->objects.emplace_back(StageData::ObjectData{});
			StageData::ObjectData& objectData = stageData->objects.back();

			if (object.contains("file_name")) {
				objectData.fileName = object["file_name"];
			}

			nlohmann::json& transform = object["transform"];
			//平行移動
			objectData.transform.x = (float)transform["translation"][1];
			objectData.transform.y = (float)transform["translation"][2];
			objectData.transform.z = -(float)transform["translation"][0];
			//回転角
			objectData.rotation.x = -(float)transform["rotation"][1];
			objectData.rotation.y = -(float)transform["rotation"][2];
			objectData.rotation.z = (float)transform["rotation"][0];
			//スケーリング
			objectData.scaling.x = (float)transform["scaling"][1];
			objectData.scaling.y = (float)transform["scaling"][2];
			objectData.scaling.z = (float)transform["scaling"][0];
		}
	}

	for (auto& objectData : stageData->objects) {
		//仮モデルで生成(後々モデルも読み込むようにする)
		Object3d* newObject = Object3d::Create(ModelManager::GetIns()->GetModel("building"));
		Vector3 pos;
		pos = objectData.transform;
		newObject->SetPosition(pos);
		Vector3 rot;
		rot = objectData.rotation;
		newObject->SetRotation(rot);
		Vector3 scale;
		scale = objectData.scaling;
		newObject->SetScale(scale);
		allObjects.emplace_back(newObject);
	}

	delete(stageData);
	stageData = nullptr;
}

void JsonLoader::Update()
{
	for (std::unique_ptr<Object3d>& object : allObjects) {
		object->Update();
	}
}

void JsonLoader::Draw()
{
	for (std::unique_ptr<Object3d>& object : allObjects) {
		object->Draw();
	}
}
