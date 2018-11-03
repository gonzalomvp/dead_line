#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "MeteorologyManager.h"

class World {
public:
	World(Player& player);
	
	void run();
	void draw();
	void fireBullet(int direction);

private:
	void moveEnemies();
	void moveBullets();
	void generateObjects();
	void checkCollisions();

	Player&             m_player;
	std::list<Bullet>   m_bullets;
	std::list<Enemy>    m_enemies;
	int                 m_mushroom;
	MeteorologyManager  m_meteorology;

	//timers
	int m_enemyTimer;
	int m_mushroomTimer;
};