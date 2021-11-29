#pragma once
#ifndef ESP_H
#define ESP_H
#include "Hack.h"
#include "SDK.h"
class Esp : public Hack
{
public:
	Esp(std::string nm) : Hack(nm) {}

	void onUpdate() override
	{
	}

	void onToggle() override
	{
		this->isToggled = !this->isToggled;
		//((void(__thiscall*)(const char* string))0x408E80)(("Aimboted Toggled [" + std::to_string(this->isToggled) + "]").c_str());
	}


	glmatrixf* GetViewMatrix() {
		return (glmatrixf*)0x00501AE8;
	};



	vec W2S(glmatrixf* mvpmatrix, vec vPlayerLoc)
	{
		//GuidedHacking.com : AnomanderRake

		//Matrix-Vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
		vec4 clipCoords;
		clipCoords.x = vPlayerLoc.x * mvpmatrix->v[0] + vPlayerLoc.y * mvpmatrix->v[4] + vPlayerLoc.z * mvpmatrix->v[8] + mvpmatrix->v[12];
		clipCoords.y = vPlayerLoc.x * mvpmatrix->v[1] + vPlayerLoc.y * mvpmatrix->v[5] + vPlayerLoc.z * mvpmatrix->v[9] + mvpmatrix->v[13];
		clipCoords.z = vPlayerLoc.x * mvpmatrix->v[2] + vPlayerLoc.y * mvpmatrix->v[6] + vPlayerLoc.z * mvpmatrix->v[10] + mvpmatrix->v[14];
		clipCoords.w = vPlayerLoc.x * mvpmatrix->v[3] + vPlayerLoc.y * mvpmatrix->v[7] + vPlayerLoc.z * mvpmatrix->v[11] + mvpmatrix->v[15];

		if (clipCoords.w < 0) return vec(-1, -1, -1);

		//perspective division, dividing by clip.W = NDC
		vec normalizedDeviceCoordinates;
		normalizedDeviceCoordinates.x = clipCoords.x / clipCoords.w;
		normalizedDeviceCoordinates.y = clipCoords.y / clipCoords.w;
		normalizedDeviceCoordinates.z = clipCoords.z / clipCoords.w;

		//viewport tranform to screenCooords
		int  viewport[4] = { 0, 0 , *(int*)0x510c94, *(int*)0x510c98 };

		vec playerScreenCoords;
		playerScreenCoords.x = (viewport[2] / 2 * normalizedDeviceCoordinates.x) + (normalizedDeviceCoordinates.x + viewport[2] / 2);
		playerScreenCoords.y = -(viewport[3] / 2 * normalizedDeviceCoordinates.y) + (normalizedDeviceCoordinates.y + viewport[3] / 2);
		playerScreenCoords.z = 0;

		return playerScreenCoords;
	};


	void RenderESP(PlayerEntity* ent,  int r, int g, int b)
	{
		int width = *(DWORD*)Offsets::SCRWidth;
		int height = *(DWORD*)Offsets::SCHeight;
		int heal = ent->health;
		float dist = localPlayer->vLocation.dist(ent->vLocation);
		glmatrixf* glmvpmatrix = (glmatrixf*)(Offsets::GLMatrix);
		vec footPos = W2S(glmvpmatrix, ent->vLocation);
		vec headPosistion = W2S(glmvpmatrix, ent->vLocationHead);
		int heightesp = footPos.y - (headPosistion.y);
		int widthesp = heightesp / 2;
		heightesp *= 1.17;
		widthesp *= 1.17;
		int x = headPosistion.x - widthesp / 2;
		int y = headPosistion.y;
		if (heal > 100)
			heal = 100;
		if (heal < 1)
			heal = 1;
		drawString(x, y - 15, 255, 255, 255, GLUT_BITMAP_9_BY_15, "%s", ent->name);
		int strHeal = (int)heightesp - heal * (int)heightesp / 100;
		boxLine(2.0f, x - 12, y - 16, 6, heightesp + 4, 0, 0, 0);
		box(x - 10, y + strHeal - 15, 4, heightesp - strHeal + 2, 153, 255, 0);
		boxLine(1.0f, x, y - 15, widthesp, heightesp, r, g, b);
		glPopMatrix();
	}


	void onRender() override {
		this->pEntites = (PlayerEntityList*)*(int*)Offsets::EntityArray;
		this->localPlayer = *(PlayerEntity**)Offsets::LocalPlayer;
		if (this->isToggled)
		{
			for (int i = 0; i < (*((int*)Offsets::PlayerCount)); i++)
			{
				PlayerEntity* entity = pEntites->_ents[i];
				if (!entity) continue;
				glmatrixf* glmvpmatrix = (glmatrixf*)(Offsets::GLMatrix);
				if (!entity || !localPlayer) continue;
				vec DrawPos;
				if (entity->state != CS_DEAD)
				{
					vec footPos = W2S(glmvpmatrix, entity->vLocation);
					vec headPosistion = W2S(glmvpmatrix, entity->vLocationHead);
					if (footPos.x > 0 && headPosistion.x > 0)
					{
						float dist = getDistance(entity->vLocationHead, localPlayer->vLocationHead);

						float r = 0, g = 0, b = 0;

						if (IsVisible(localPlayer, localPlayer->vLocation, entity->vLocation))
						{
							r = 0; g = 255; b = 0;
						}
						else {
							r = 255; g = 0; b = 0;
						}

						if (localPlayer->team != entity->team) {
							r = 0; g = 0; b = 255;
						}
						RenderESP(entity, r, g, b);
					}
				}
			}
		}
	}
};
#endif