#include "Base.h"
#include "World.h"


World::World(Player& player) : m_player(player), m_meteorology() {
	m_enemyTimer    = T_ENEMY;
	m_mushroomTimer = T_MUSHROOM;
	m_mushroom      = -1;
}

void World::run() {
	checkCollisions();
	moveEnemies();
	generateObjects();
	checkCollisions();
	moveBullets();
	checkCollisions();
	m_meteorology.run();
}

void World::draw() {
	//init board with meteorology
	char board[WIDTH + 1];
	for (int i = 0; i < WIDTH; i++) {
		board[i] = m_meteorology.getImage(i);
	}
	board[WIDTH] = '\0';

	//set the bullets in the board
	for (auto itBullet = m_bullets.begin(); itBullet != m_bullets.end(); ++itBullet) {
		board[itBullet->m_position] = itBullet->getImage();
	}

	//set the enemies in the board
	for (auto itEnemies = m_enemies.begin(); itEnemies != m_enemies.end(); ++itEnemies) {
		board[itEnemies->m_position] = itEnemies->getImage();
	}

	//set the mushroom in the board
	if (m_mushroom != -1) {
		board[m_mushroom] = 'o';
	}

	//set the player in the board
	board[m_player.m_position] = m_player.getImage();

	//draw board
	printf("   ");
	for (int i = 0; i < WIDTH; i++) {
		WORD color = COLOR_WHITE;
		switch (board[i]) {
			case '@':                                color = COLOR_RED;   break;
			case 'X': if (m_player.m_bullets <= 10)  color = COLOR_YELLOW;
					  else							 color = COLOR_GREEN; break;
			case 'o':                                color = COLOR_GREEN; break;
			case '/':                                color = COLOR_BLUE;  break;
			case ';':                                color = COLOR_BLUE;  break;
			case ',':                                color = COLOR_BLUE;  break;
			case '.':                                color = COLOR_BLUE;  break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		printf("%c", board[i]);
	}

	//draw stats
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
	printf(" Lives: %d | Points: %d", m_player.m_lives, m_player.m_points);
	printf("\r");
}

void World::fireBullet(int direction) {
	if (m_player.m_bullets > 0) {
		m_bullets.push_back(Bullet(m_player.m_position, direction));
		m_player.m_bullets--;
	}
}

void World::moveBullets() {
	auto itBullet = m_bullets.begin();
	while (itBullet != m_bullets.end()) {
		if (!itBullet->move()) {
			itBullet = m_bullets.erase(itBullet);
		}
		else {
			itBullet++;
		}
	}
}

void World::moveEnemies() {
	auto itEnemy = m_enemies.begin();
	while (itEnemy != m_enemies.end()) {
		if (!itEnemy->move()) {
			itEnemy = m_enemies.erase(itEnemy);
		}
		else {
			itEnemy++;
		}
	}
}

void World::generateObjects() {
	//generate enemy
	if (m_enemyTimer == 0) {
		if (rand() % 2) {
			m_enemies.push_back(Enemy(0, D_RIGHT));
		}
		else {
			m_enemies.push_back(Enemy(WIDTH - 1, D_LEFT));
		}
		//increase enemy frecuency every 50 points
		m_enemyTimer = T_ENEMY - (m_player.m_points / 50) * 5;
	}
	else {
		m_enemyTimer--;
	}
	//generate mushroom
	if (m_mushroomTimer == 0 && m_mushroom == -1) {
		m_mushroom = rand() % WIDTH;
		m_mushroomTimer = T_MUSHROOM;
	}
	else {
		m_mushroomTimer--;
	}
}

void World::checkCollisions() {
	//check if player picks mushroom
	if (m_player.m_position == m_mushroom) {
		m_player.m_bullets = 30;
		m_mushroom = -1;
		m_mushroomTimer = T_MUSHROOM;
		m_player.m_points += 10;
	}

	//check if enemy hits something
	auto itEnemies = m_enemies.begin();
	while (itEnemies != m_enemies.end()) {
		int enemyPos = itEnemies->m_position;
		
		//check if enemy hits player
		if (enemyPos == m_player.m_position) {
			m_player.m_lives--;
			m_player.m_bullets = 30;
			m_player.m_position = (WIDTH / 2);
			m_enemies.clear();
			m_bullets.clear();
			m_mushroom = -1;
			m_mushroomTimer = T_MUSHROOM;
			m_enemyTimer = T_ENEMY - (m_player.m_points / 50) * 5;
			break;
		}

		//check if enemy hits mushroom
		if (enemyPos == m_mushroom) {
			m_mushroom = -1;
			m_mushroomTimer = T_MUSHROOM;
		}

		//check if enemy hits bullet
		bool destroyEnemy = false;
		auto itBullets = m_bullets.begin();
		while (!destroyEnemy && itBullets != m_bullets.end()) {
			if (enemyPos == itBullets->m_position) {
				destroyEnemy = true;
				m_bullets.erase(itBullets);
			}
			else {
				itBullets++;
			}
		}

		if (destroyEnemy) {
			itEnemies = m_enemies.erase(itEnemies);
			destroyEnemy = false;
		}
		else {
			itEnemies++;
		}
	}
}
