#pragma once

class Bullet {
public:
	Bullet(int position, int direction);

	bool move();
	char getImage();

	int m_position;
	int m_direction;
};