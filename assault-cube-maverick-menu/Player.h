#ifndef PLAYER_H
#define PLAYER_H
#include "SDK.h"

class Player {
public:
	Player(PlayerEntity* entity);
	vec* pos, *head, *angle, *velocity;
	int* health;
	State state;
	int team;
	char name[16];
};
#endif