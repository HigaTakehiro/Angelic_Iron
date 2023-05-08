#include "MapChip.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void MapChip::MapChipInitialize() {
	blockModel_ = Model::CreateModel("Block");
}

int32_t** MapChip::MapLoad(const std::string& mapname, int32_t map_width, int32_t map_height) {

	map_ = (int32_t**)malloc(sizeof(int32_t*) * map_height); //��
	map_[0] = (int32_t*)malloc(map_width * map_height * sizeof(int32_t)); //�c
	for (int32_t i = 0; i < map_height; i++) {
		map_[i] = map_[0] + i * map_width;
	}

	const string& filename = "Engine/Resources/Mapchip/" + mapname + ".csv";
	const char* mapfile = filename.c_str();

	//��s���ǂݍ���
	FILE* fp;
	fopen_s(&fp, mapfile, "r");
	for (int32_t i = 0; i < map_height; i++) {
		for (int32_t j = 0; j < map_width; j++) {
			fscanf_s(fp, "%d,", &map_[i][j]);
		}
	}

	fclose(fp);

	return map_;
}

std::vector<Object3d*> MapChip::MapSet(int32_t** map_, int32_t map_width, int32_t map_height, int32_t height) {
	const float LAND_SCALE = 30.0f;

	std::vector<Object3d*> objects;

	Model* modeltable[] = {
		nullptr,
		blockModel_,
	};

	for (int32_t i = 0; i < map_height; i++) {
		for (int32_t j = 0; j < map_width; j++) {

			int32_t modelIndex = map_[i][j];

			if (modeltable[modelIndex] != nullptr) {
				Object3d* object = Object3d::Create(modeltable[modelIndex]);
				object->SetScale({ LAND_SCALE, LAND_SCALE, LAND_SCALE });
				object->SetPosition({ j * LAND_SCALE - 50, height * LAND_SCALE + 50, i * LAND_SCALE + 50 });
				objects.push_back(object);
			}
		}
	}

	return objects;
}


void MapChip::MapChipFinalize() {
	safe_delete(blockModel_);
}