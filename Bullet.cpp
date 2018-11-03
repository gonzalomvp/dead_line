#include "Base.h"
#include "Bullet.h"

Bullet::Bullet(int position, int direction) {
	m_position  = position;
	m_direction = direction;
}

bool Bullet::move() {
	m_position += m_direction;
	return (m_position >= 0 && m_position < WIDTH);
}

char Bullet::getImage() {
	return (m_direction == D_LEFT) ? '<' : '>';
}
