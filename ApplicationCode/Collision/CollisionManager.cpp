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
	int32_t type1 = obj1->GetObjType();
	int32_t type2 = obj2->GetObjType();

	if (obj1 == obj2) {
		return;
	}

	if ((type1 | type2) == 0x16) {
		HitTest(obj1, obj2);
		return;
	}

	if ((type1 | type2) == 0x03) return;
	if ((type1 | type2) == 0x08) return;
	if ((type1 | type2) == 0x06 && ((obj1->GetObjType() == 0x01) || (obj2->GetObjType() == 0x01))) return;


	if (obj1->GetColType() == Object3d::CollisionType::Sphere && obj2->GetColType() == Object3d::CollisionType::Sphere) {
		HitTest(obj1, obj2);
	}
}

void CollisionManager::HitTest(Object3d* obj1, Object3d* obj2)
{
	if (obj1->GetColType() == Object3d::CollisionType::Sphere && obj2->GetColType() == Object3d::CollisionType::Sphere) {
		if (collision_[(long long)Object3d::CollisionType::Sphere][(long long)Object3d::CollisionType::Sphere]->HitTest(obj1, obj2)) {
			obj1->OnCollision();
			obj2->OnCollision();
		}
	}
}
