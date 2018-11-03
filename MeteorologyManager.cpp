#include "Base.h"
#include "MeteorologyManager.h"

MeteorologyManager::MeteorologyManager() {
	for (unsigned int i = 0; i < WIDTH; i++) {
		m_rainDrops[i] = DROP_STATES - 1;
	}
	m_rainTimer = T_RAIN;
}

void MeteorologyManager::run() {
	if (m_rainTimer == 0) {
		//change current drops
		for (unsigned int i = 0; i < WIDTH; i++) {
			if (m_rainDrops[i] < DROP_STATES - 1) {
				m_rainDrops[i]++;
			}
		}
		//generate new drops
		int numDrops = rand() % RAIN_AMOUNT;
		for (int i = 0; i < numDrops; i++) {
			int dropPos = rand() % WIDTH;
			m_rainDrops[dropPos] = 0;
		}
		//reset timer
		m_rainTimer = T_RAIN;
	}
	else {
		m_rainTimer--;
	}
}

char MeteorologyManager::getImage(int pos) {
	return m_dropStates[m_rainDrops[pos]];
}
