#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <list>

#define ESC         27
#define MOVE_LEFT   'j'
#define MOVE_RIGHT  'k'
#define FIRE_LEFT   'h'
#define FIRE_RIGHT  'l'
#define WIDTH       90
#define T_ENEMY     30
#define T_MUSHROOM 100

void checkCollisions();

struct bullet {
	int pos;
	int dir;
};

struct enemy {
	int pos;
	int dir;
};

int g_player    = (WIDTH / 2);
int g_mushroom  = -1;
int g_points    =  0;
int g_lives     =  3;

//timers
int g_enemyTimer    = T_ENEMY;
int g_mushroomTimer = T_MUSHROOM;

std::list<bullet> bullets;
std::list<enemy>  enemies;

int main() {
	//init console
	SetConsoleTitle(TEXT("Dead Line - The Videogame"));
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	printf("\n\n\n\n\n\n\n\n\n\n\n\n");

	int key = NULL;
	while (key != ESC && g_lives >= 0) {
		//check input
		key = NULL;
		if (_kbhit()) {
			key = _getch();
		}
		//process input
		switch (key) {
			case MOVE_LEFT :g_player--;                              break;
			case MOVE_RIGHT:g_player++;                              break;
			case FIRE_LEFT :bullets.push_back(bullet{g_player, -1}); break;
			case FIRE_RIGHT:bullets.push_back(bullet{g_player,  1}); break;
		}
		//check player in limits
		if (g_player < 0) {
			g_player = 0;
		}
		else if (g_player >= WIDTH) {
			g_player = WIDTH - 1;
		}
		checkCollisions();

		//move enemies
		auto itEnemy = enemies.begin();
		while (itEnemy != enemies.end()) {
			itEnemy->pos += itEnemy->dir;
			if (itEnemy->pos < 0 || itEnemy->pos >= WIDTH) {
				itEnemy = enemies.erase(itEnemy);
			}
			else {
				itEnemy++;
			}
		}

		//generate enemy
		if (g_enemyTimer == 0) {
			if (rand() % 2) {
				enemies.push_back(enemy{0, 1});
			}
			else {
				enemies.push_back(enemy{WIDTH - 1, -1});
			}
			g_enemyTimer = T_ENEMY;
		}
		else {
			g_enemyTimer--;
		}

		//generate mushroom
		if (g_mushroomTimer == 0 && g_mushroom == -1) {
			g_mushroom = rand() % WIDTH;
			g_mushroomTimer = T_MUSHROOM;
		}
		else {
			g_mushroomTimer--;
		}
		checkCollisions();

		//move bullets
		auto itBullet = bullets.begin();
		while (itBullet != bullets.end()) {
			itBullet->pos += itBullet->dir;
			if (itBullet->pos < 0 || itBullet->pos >= WIDTH) {
				itBullet = bullets.erase(itBullet);
			}
			else {
				itBullet++;
			}
		}
		checkCollisions();

		//draw
		printf("   ");
		for (unsigned int i = 0; i < WIDTH; i++) {
			char toDraw = '_';
			
			//draw bullets
			for (auto it = bullets.begin(); it != bullets.end(); ++it) {
				if (i == it->pos) {
					if (it->dir == -1) {
						toDraw = '<';
					}
					else {
						toDraw = '>';
					}
					break;
				}
			}

			//draw enemies
			for (auto it = enemies.begin(); it != enemies.end(); ++it) {
				if (i == it->pos) {
					toDraw = '@';
					break;
				}
			}
			
			//draw mushroom
			if (i == g_mushroom) {
				toDraw = 'o';
			}

			//draw player
			if (i == g_player) {
				toDraw = 'X';
			}
			printf("%c", toDraw);
		}

		//draw stats
		printf(" Lives: %d | Points: %d", g_lives, g_points);
		printf("\r");

		Sleep(50);
	}

	//game over message
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n                                                ");
	printf("GAME OVER   Score: %d\n", g_points);
	getchar();

    return 0;
}

void checkCollisions() {
	//check if player picks mushroom
	if (g_player == g_mushroom) {
		g_mushroom = -1;
		g_mushroomTimer = T_MUSHROOM;
		g_points += 10;
	}

	//check if enemy hits something
	auto itEnemies = enemies.begin();
	while (itEnemies != enemies.end()) {
		int enemyPos = itEnemies->pos;

		//check if enemy hits player
		if (enemyPos == g_player) {
			g_lives--;
			g_player = (WIDTH / 2);
			enemies.clear();
			bullets.clear();
			g_mushroom = -1;
			g_mushroomTimer = T_MUSHROOM;
			g_enemyTimer = T_ENEMY;
			break;
		}

		//check if enemy hits mushroom
		if (enemyPos == g_mushroom) {
			g_mushroom = -1;
			g_mushroomTimer = T_MUSHROOM;
		}

		//check if enemy hits bullet
		bool destroyEnemy = false;
		auto itBullets = bullets.begin();
		while (!destroyEnemy && itBullets != bullets.end()) {
			if (enemyPos == itBullets->pos) {
				destroyEnemy = true;
				bullets.erase(itBullets);
			}
			else {
				itBullets++;
			}
		}

		if (destroyEnemy) {
			itEnemies = enemies.erase(itEnemies);
			destroyEnemy = false;
		}
		else {
			itEnemies++;
		}
	}
}
