#include "Base.h"
#include "Enemy.h"

Enemy::Enemy(int position, int direction) {
	m_position  = position;
	m_direction = direction;
}

bool Enemy::move() {
	m_position += m_direction;
	return (m_position >= 0 && m_position < WIDTH);
}

char Enemy::getImage() {
	return '@';
}
