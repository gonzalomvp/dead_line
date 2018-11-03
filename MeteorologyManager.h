#pragma once

#define DROP_STATES 5
#define RAIN_AMOUNT 5

static const char m_dropStates[DROP_STATES] = { '/', ';', ',', '.', '_' };

class MeteorologyManager {
public:
	MeteorologyManager();

	void run();
	char getImage(int pos);

private:
	int m_rainDrops[WIDTH];
	int m_rainTimer;
};
