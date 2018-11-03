#include "Base.h"
#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

int main() {
	//init console
	SetConsoleTitle(TEXT("Dead Line - The Videogame"));
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	//init player and world
	Player player ((WIDTH / 2), 3);
	World  world  (player);

	printf("\n\n\n\n\n\n\n\n\n\n\n\n");

	int key = NULL;
	while (key != ESC && player.m_lives >= 0) {
		//check input
		key = NULL;
		if (_kbhit()) {
			key = _getch();
		}
		//process input
		switch (key) {
			case MOVE_LEFT : player.move     (D_LEFT);  break;
			case MOVE_RIGHT: player.move     (D_RIGHT); break;
			case FIRE_LEFT : world.fireBullet(D_LEFT);  break;
			case FIRE_RIGHT: world.fireBullet(D_RIGHT); break;
		}
		
		//game logic
		world.run();

		//draw
		world.draw();
		
		Sleep(50);
	}

	//game over message
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n                                                ");
	printf("GAME OVER   Score: %d\n", player.m_points);
	getchar();

    return 0;
}