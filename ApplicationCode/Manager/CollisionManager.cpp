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
	const int32_t noObjType = -1;
	auto itr = std::remove_if(objList_.begin(), objList_.end(), [&](Object3d* obj)->bool {return obj->GetObjType() <= noObjType; });
	objList_.erase(itr, objList_.end());

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
	int32_t type;
	int32_t type1 = obj1->GetObjType();
	int32_t type2 = obj2->GetObjType();

	const int32_t playerAndScoreItemHit = 0x0f;
	const int32_t bombAndEnemyHit = 0x0a;
	const int32_t enemyAndEnemyBulletHit = 0x06;
	const int32_t enemyAndEnemyHit = 0x02;
	const int32_t playerAndPlayerBulletHit = 0x05;
	const int32_t playerAndBombHit = 0x09;
	const int32_t bombAndBombHit = 0x08;
	const int32_t playerBulletAndEnemyBullet = 0x07;

	type = type1 | type2;

	if (obj1 == obj2) {
		return;
	}

	if (type == playerAndScoreItemHit) {
		HitTest(obj1, obj2);
		if (type1 == (int32_t)Object3d::OBJType::Player) obj1->SetIsHit(false);
		if (type2 == (int32_t)Object3d::OBJType::Player) obj2->SetIsHit(false);
		return;
	}
	if (type == bombAndEnemyHit) {
		HitTest(obj1, obj2, true);
		return;
	}

	if (type == enemyAndEnemyHit) return;
	if (type == enemyAndEnemyBulletHit) return;
	if (type == playerAndPlayerBulletHit) return;
	if (type == playerAndBombHit) return;
	if (type == bombAndBombHit) return;
	if (type == playerBulletAndEnemyBullet) return;

	HitTest(obj1, obj2);
}

void CollisionManager::HitTest(Object3d* obj1, Object3d* obj2, bool isBomb)
{
	if (obj1->GetColType() == Object3d::CollisionType::Sphere && obj2->GetColType() == Object3d::CollisionType::Sphere) {
		if (collision_[(long long)Object3d::CollisionType::Sphere][(long long)Object3d::CollisionType::Sphere]->HitTest(obj1, obj2) && isBomb) {
			obj1->BombOnCollision();
			obj2->BombOnCollision();
		}
		else if (collision_[(long long)Object3d::CollisionType::Sphere][(long long)Object3d::CollisionType::Sphere]->HitTest(obj1, obj2)) {
			obj1->OnCollision();
			obj2->OnCollision();
		}	
	}
}

void CollisionManager::Finalize()
{
	objList_.clear();
}
