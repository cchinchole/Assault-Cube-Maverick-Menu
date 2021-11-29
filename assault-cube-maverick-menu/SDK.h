#ifndef SDK_H
#define SDK_H

#include "pch.h"
#include "Math.h"
#include "glut.h"
#include "openglDraw.h"
#include <bitset>


enum Offsets {

	LocalPlayer = 0x50F4F4,
	EntityArray = 0x50F4F8,
	CrosshairName = 0x501C38,
	SCRWidth = 0x510C94,
	SCHeight = 0x510C98,
	GLMatrix = 0x501AE8,
	AmmoModifier = 0x4637E9,
	AutoWeaponModifier = 0x463716,
	RapidFireModifier = 0x4637E4,
	RapidFireModifier2 = 0x463387,
	GrenadeModifier = 0x463378,
	GameMode = 0x50F49C,
	TraceLine = 0x048a310,
	PlayerCount = 0x50F500,

};

enum State {
	CS_ALIVE = 0,
	CS_DEAD,
	CS_SPECTATOR,
};

class weapon {
public:
	char _0x0000[4];
	BYTE ID;
	char _0x0005[59];
};

class PlayerEntity {
public:
	DWORD vTable;
	vec vLocationHead; //0x0004
	char _0x0010[36];
	vec vLocation; //0x0034
	vec vViewAngle; //0x0040
	char _0x004C[37];
	BYTE bScoping; //0x0071
	char _0x0072[134];
	__int32 health; //0x00F8
	__int32 armor; //0x00FC
	char _0x0100[292];
	BYTE bAttacking; //0x0224
	char name[16]; //0x0225
	char _0x0235[247];
	BYTE team; //0x032C
	char _0x032D[11];
	BYTE state; //0x0338
	char _0x0339[59];
	weapon* currentWeapon; //0x0374
	char _0x0378[520];
};

struct PlayerEntityList {
	PlayerEntity* _ents[31];
};

struct traceresult_s
{
	vec end;
	bool collided;
};
bool IsVisible(PlayerEntity* localPlayer, vec from, vec to);
#endif