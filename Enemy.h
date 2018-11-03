#pragma once

class Enemy {
public:
	Enemy(int position, int direction);
	
	bool move();
	char getImage();

	int m_position;
	int m_direction;
};