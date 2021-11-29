#pragma once
#ifndef HACK_H
#define HACK_H
#include <iostream>
#include "SDK.h"

class Hack {
protected:
	bool isToggled = false;
	PlayerEntityList* pEntites;
	PlayerEntity* localPlayer;
public:
	std::string name;
	virtual void onRender() = 0;
	virtual void onUpdate() = 0;
	virtual void onToggle() = 0;
	bool getToggled() {
		return isToggled;
	}
	Hack(std::string nm)
	{
		name = nm;
	}

};


#endif