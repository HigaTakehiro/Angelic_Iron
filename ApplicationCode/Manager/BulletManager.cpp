#include "BulletManager.h"

void BulletManager::Update()
{
	enemyBullets_.remove_if([](std::unique_ptr<EnemyBullet>& enemyBullet) { return enemyBullet->IsDead(); });
	playerBullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	bulletCases_.remove_if([](std::unique_ptr<BulletCase>& bulletCase) {return bulletCase->IsDead(); });
	bombs_.remove_if([](std::unique_ptr<Bomb>& bomb) {return bomb->GetIsDead(); });

	for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets_) {
		playerBullet->Update();
	}
	for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets_) {
		enemyBullet->Update();
	}
	for (std::unique_ptr<Bomb>& bomb : bombs_) {
		bomb->Update();
	}
	for (std::unique_ptr<BulletCase>& bulletCase : bulletCases_) {
		bulletCase->Update();
	}
}

void BulletManager::Draw()
{
	for (std::unique_ptr<PlayerBullet>& playerBullet : playerBullets_) {
		playerBullet->Draw();
	}
	for (std::unique_ptr<EnemyBullet>& enemyBullet : enemyBullets_) {
		enemyBullet->Draw();
	}
	for (std::unique_ptr<Bomb>& bomb : bombs_) {
		bomb->Draw();
	}
	for (std::unique_ptr<BulletCase>& bulletCase : bulletCases_) {
		bulletCase->Draw();
	}
}

void BulletManager::AddPlayerBullet(std::unique_ptr<PlayerBullet> playerBullet)
{
	playerBullets_.push_back(std::move(playerBullet));
}

void BulletManager::AddBulletCase(std::unique_ptr<BulletCase> bulletCase)
{
	bulletCases_.push_back(std::move(bulletCase));
}

void BulletManager::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet)
{
	enemyBullets_.push_back(std::move(enemyBullet));
}

void BulletManager::AddBomb(std::unique_ptr<Bomb> bomb)
{
	bombs_.push_back(std::move(bomb));
}
