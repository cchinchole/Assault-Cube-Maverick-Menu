#pragma once
#ifndef MENU_H
#define MENU_H
#include "Hack.h"
#include "Console.h"
#include <iostream>
#include <vector>

class MenuOption {
public:
	Hack* hack;
	MenuOption(Hack* hack)
	{
		this->hack = hack;
	}
};

class MenuTab {
public:
	std::string locName, tabName;
	std::vector<MenuOption> optionArray;

	MenuTab(std::string locName, std::string tabName)
	{
		this->locName = locName;
		this->tabName = tabName;
	}
};

class Menu {
public:
	int xPos = 0, yPos = 0;
	int selectedTab = 0, selectedOption = 0;
	std::string menuName;
	std::vector<MenuTab> tabArray;

	void addTab(std::string locName, std::string name)
	{
		tabArray.push_back(MenuTab(locName, name));
		_Console->Log("Added tab to menu");
	}

	void addOption(std::string locName, Hack* hack)
	{
		for (int i = 0; i < tabArray.size(); i++)
		{
			if (tabArray.at(i).locName == locName)
			{
				tabArray.at(i).optionArray.push_back(MenuOption(hack));
				_Console->LogInt("added option to menu, size of menu now", tabArray.at(i).optionArray.size());
			}
		}
	}

	MenuTab* getTab(std::string locName)
	{
		for (int i = 0; i < tabArray.size(); i++)
		{
			if (tabArray.at(i).locName == locName)
			{
				return &tabArray.at(i);
			}
		}
		return nullptr;
	}
	
	MenuTab* getTab(int tabIndex)
	{
		return &tabArray.at(tabIndex);
	}

	void moveLeft()
	{
		if ( (selectedTab - 1) < 0)
			selectedTab = tabArray.size()-1;
		else selectedTab--;
	}

	void moveRight()
	{
		if ( (selectedTab + 1) >= tabArray.size())
			selectedTab = 0;
		else selectedTab++;
	}

	void moveUp()
	{
		if ((selectedOption - 1) < 0)
			selectedOption = getTab(selectedTab)->optionArray.size() - 1;
		else selectedOption--;
	}

	void moveDown()
	{
		if ((selectedOption + 1) >= getTab(selectedTab)->optionArray.size())
			selectedOption = 0;
		else selectedOption++;
	}

	void selectOption()
	{
		tabArray.at(selectedTab).optionArray.at(selectedOption).hack->onToggle();
	}
};

void DrawMenu(Menu menu);

#endif