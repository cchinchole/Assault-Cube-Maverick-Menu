#include "pch.h"
#include "SDK.h"


bool IsVisible(PlayerEntity* localPlayer, vec from, vec to)
{
	DWORD traceLine = Offsets::TraceLine;
	traceresult_s traceresult;
	traceresult.collided = false;
	from.z -= 0.2f; //weaponBelowEye
	__asm
	{
		push 0; bSkipTags   //try with 1
		push 0; bCheckPlayers
		push localPlayer
		push to.z
		push to.y
		push to.x
		push from.z
		push from.y
		push from.x
		lea eax, [traceresult]
		call traceLine;
		add esp, 36
	}
	return !traceresult.collided;
};