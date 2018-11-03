#pragma once

class Player {
public:
	Player(int position, int lives);

	void move(int direction);
	char getImage();

	int m_position;
	int m_lives;
	int m_bullets;
	int m_points;
};