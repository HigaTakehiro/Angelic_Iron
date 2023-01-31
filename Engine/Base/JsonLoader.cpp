#include "JsonLoader.h"

const std::string JsonLoader::baseDirectory = "Engine\\Resources\\GameData";
const std::string JsonLoader::extension = ".json";

void JsonLoader::JsonFileLoad(const std::string fileName) {
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

	LevelData* levelData = new LevelData();

	for (nlohmann::json& object : deserialised["objects"]) {
		assert(object.contains("type"));

		std::string type = object["type"].get<std::string>();

		if (type.compare("MESH") == 0) {
			levelData->objects.emplace_back(LevelData::ObjectData{});
			LevelData::ObjectData& objectData = levelData->objects.back();

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

		if (object.contains("children")) {

		}
	}
}