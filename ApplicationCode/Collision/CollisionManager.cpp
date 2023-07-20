#include "CollisionManager.h"
#include "SphereAndSphere.h"
#include "SafeDelete.h"

CollisionManager::CollisionManager()
{
	collision_[(long long)Object3d::CollisionType::Sphere][(long long)Object3d::CollisionType::Sphere] = new SphereAndSphere();
}

CollisionManager::~CollisionManager()
{
	for (int32_t i = 0; i < (int32_t)Object3d::CollisionType::None; i++) {
		for (int32_t j = 0; j < (int32_t)Object3d::CollisionType::None; j++) {
			safe_delete(collision_[i][j]);
		}
	}
}

void CollisionManager::Update()
{
	for (auto obj1 : objList_) {
		for (auto obj2 : objList_) {
			CollisionCheck(obj1, obj2);
		}
	}
}

void CollisionManager::AddObj(Object3d& obj)
{
	objList_.push_back(&obj);
}

void CollisionManager::CollisionCheck(Object3d* obj1, Object3d* obj2)
{
	if (obj1 == obj2) {
		return;
	}
	else if (obj1->GetObjType() == Object3d::OBJType::None || obj2->GetObjType() == Object3d::OBJType::None) {
		return;
	}
	else if (obj1->GetObjType() == Object3d::OBJType::Player && obj2->GetObjType() == Object3d::OBJType::PlayerBullet) {
		return;
	}
	else if (obj1->GetObjType() == Object3d::OBJType::PlayerBullet && obj2->GetObjType() == Object3d::OBJType::Player) {
		return;
	}
	else if (obj1->GetObjType() == Object3d::OBJType::Enemy && obj2->GetObjType() == Object3d::OBJType::EnemyBullet) {
		return;
	}
	else if (obj1->GetObjType() == Object3d::OBJType::EnemyBullet && obj2->GetObjType() == Object3d::OBJType::Enemy) {
		return;
	}
	else if (obj1->GetObjType() == Object3d::OBJType::Player && obj2->GetObjType() == Object3d::OBJType::Enemy) {
		return;
	}
	else if (obj1->GetObjType() == Object3d::OBJType::Enemy && obj2->GetObjType() == Object3d::OBJType::Player) {
		return;
	}

	if (obj1->GetColType() == Object3d::CollisionType::Sphere && obj2->GetColType() == Object3d::CollisionType::Sphere) {
		if (collision_[(long long)Object3d::CollisionType::Sphere][(long long)Object3d::CollisionType::Sphere]->HitTest(obj1, obj2)) {
			obj1->OnCollision();
			obj2->OnCollision();
		}
	}
}
