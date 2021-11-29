#pragma once
#ifndef AIMBOT_H
#define AIMBOT_H
#include "Hack.h"
#include "SDK.h"
class Aimbot : public Hack
{
private:

	class AimbotTarget {
	public:
		PlayerEntity* entity = nullptr;
		vec angles = vec(0,0,0);
		AimbotTarget()
		{
		}
	};
	AimbotTarget targetPlayer;

public:
	Aimbot(std::string nm) : Hack(nm) {}

	void onUpdate() override
	{
		this->pEntites = (PlayerEntityList*)*(int*)Offsets::EntityArray;
		this->localPlayer = *(PlayerEntity**)Offsets::LocalPlayer;

		if (this->isToggled && localPlayer != NULL && localPlayer->state == CS_ALIVE)
		{
			/* Target Picking */
			targetPlayer = AimbotTarget();
			float bestTarget = 999999;
			for(int i = 0; i < (*((int*)Offsets::PlayerCount)); i++)
			{
				PlayerEntity* entity = pEntites->_ents[i];
			
				if (entity != NULL && entity != localPlayer && entity->state == CS_ALIVE && IsVisible(localPlayer, localPlayer->vLocationHead, entity->vLocationHead))
				{
					float PI = 3.14159265358979F;
					float yaw = -(float)atan2(entity->vLocation.x - localPlayer->vLocation.x,
						entity->vLocation.y - localPlayer->vLocation.y) / PI * 180 + 180;
					float pitch = acos((entity->vLocationHead.z - localPlayer->vLocationHead.z) /
						entity->vLocationHead.dist(localPlayer->vLocationHead)) * -180 / PI + 90;
					vec aimAngles = (vec( yaw,  pitch, 0));
					
					if (aimAngles.dist(localPlayer->vViewAngle) < bestTarget)
					{
						targetPlayer.entity = entity;
						targetPlayer.angles = aimAngles;
						bestTarget = aimAngles.dist(localPlayer->vViewAngle);
					}
				}
			}
			/* If a valid target was found, set view angles to their location.*/

			if (targetPlayer.entity != nullptr)
				if (targetPlayer.angles.x != localPlayer->vViewAngle.x || targetPlayer.angles.y != localPlayer->vViewAngle.y) {
					//Eye level
					localPlayer->vViewAngle = targetPlayer.angles;
				}
			
		}
	}

	void onToggle() override
	{
		this->isToggled = !this->isToggled;
		((void(__thiscall*)(const char* string))0x408E80)(("Aimbot Toggled [" + std::to_string(this->isToggled) + "]").c_str());
	}

	void onRender() override {

	}
};
#endif