#include "Base.h"
#include "Player.h"

Player::Player(int position, int lives) {
	m_position = position;
	m_lives    = lives;
	m_bullets  = 30;
	m_points   = 0;
}

void Player::move(int direction) {
	m_position += direction;

	//check limits
	if (m_position >= WIDTH) {
		m_position = WIDTH - 1;
	}
	else if (m_position < 0) {
		m_position = 0;
	}
}

char Player::getImage() {
	return 'X';
}